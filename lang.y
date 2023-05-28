

%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "symbol_table.h"
int yylex();
int yywrap();
struct regpool * Reg;
FILE *outputfile;
int printval;
int loopflag[3];
int yyerror(char const *s);

%}


%union{
struct tnode * tn;
struct Gsymbol * gn;
struct Lsymbol * ln;
struct Paramstruct * pn;
int i;
}

%type <ln> LID LdeclBlock LDecList LDecl IdList
%type <i> NUP Type
%type <pn> ParamList Param PM
%type <gn> GDeclBlock GDeclList GDecl GidList GID ID
%type <tn> expr Body NUM STRING END AsgStmt OutputStmt InputStmt VAR Stmt Slist E IfStmt WhileStmt BreakStmt ContinueStmt
ArgList ReturnStmt
%token NUM PLUS END MINUS DIV MUL ID BEGN READ WRITE EQUAL SEMCL LP RP IF THEN ENDIF BREAK CONTINUE COMMA DECL ENDDECL INT STR
ELSE WHILE DO ENDWHILE LT GT NOT VAR NUP LID LSB RSB STRING MAIN LCB RCB PM RETURN
%right EQUAL
%left PLUS MINUS
%left MUL DIV


%%

Program : GDeclBlock FdefBlock MainBlock 
      | GDeclBlock MainBlock  
      | MainBlock 
      ;
GDeclBlock : DECL GDeclList ENDDECL {printsymbols($2);$$=$2;}
      | DECL ENDDECL  {printf(" y5 ");}
      ;
GDeclList : GDeclList GDecl {printf(" Declaration ");$$=$2;}
      | GDecl {printf(" Declaration ");$$=$1;}
      ;
GDecl : Type GidList SEMCL {printf(" Type ");updatetype($2,$1);$$=$2;}
      ;
GidList : GidList COMMA GID {printf(" multiple variable definition \n ");$$=$3;}
      | GID {printf(" One variable definition \n ");$$=$1;}
      ;
GID :
 ID LP ParamList RP {printf(" Function ");$1->paramlist=$3;$$=$1;}
      |ID LSB NUP RSB {printf(" Array %s of %d elements ", $1 , $3);sizeupdate($1,$3);$$=$1;}
      | ID {printf(" Variable %s ",$1);$$=$1;}
      ;
FdefBlock : FdefBlock Fdef// {printf(" Multiple functions definions \n  ");}
      | Fdef //{printf(" Function Definition ");}
      ;
MainBlock : Type MAIN LP RP LCB LdeclBlock Body RCB {printf(" Main Function \n ");int l=0;
                                  fprintf(outputfile,"L%d:\n",l);
                                  ml=1;
                                  strcpy(currentfname,"main");
                                  generate($7);
                                  fprintf(outputfile,"L%d:\n",ml);
                                  lpop();
                                  fprintf(outputfile,"RET\n");
                                  l=getlabel();
                                  fprintf(outputfile,"L%d:\n",l);}
      ;
Fdef : Type ID LP ParamList RP LCB LdeclBlock Body RCB {printf(" Function Definition %s \n ", $2);int l=getlabel();
                                  fprintf(outputfile,"L%d:\n",l);
                                  $2->binding=l;
                                  l=getlabel();
                                  strcpy(currentfname,$2->name);
                                  generate($8);
                                  fprintf(outputfile,"L%d:\n",l);
                                  lpop();
                                  fprintf(outputfile,"RET\n");
                                  l=getlabel();
                                  fprintf(outputfile,"L%d:\n",l);
                                  resetreg();}
      ;
ParamList : ParamList COMMA Param {//printf(" y18 ");
$$=$3;}
      | Param {printf(" Function parameters \n ");$$=$1;}
      ;
Param : Type PM {printf(" Parametre de type %d \n", $1 );$$=$2;}
      ;
Type : INT {$$=1;}
      | STR {$$=2;}
      ;
LdeclBlock : DECL LDecList ENDDECL {//printf(" Local declaration : \n ");
printlsymbols(lhead);$$=$2;}
      | DECL ENDDECL {//printf(" Local declaration : \n ");
      $$=NULL;}
      ;
LDecList : LDecList LDecl {//printf(" y25 ");
$$=$2;}
      | LDecl {printf(" Local declaration : \n ");$$=$1;}
      ;
LDecl : Type IdList SEMCL {
      printf(" Variable %s de type %s \n ",$2 , $1);
      updateltype($2,$1);$$=$2;}
      ;
IdList : IdList COMMA LID  {//printf(" y28 ");
      $$=$3;}
      | LID {//printf(" y29 ");
      $$=$1;}
      ;
ArgList : ArgList COMMA expr {//printf(" y30 ");
$1->Arglist=$3;$$=$1;}
      | expr {printf(" Expression : ");$$=$1;}
      ;
Body : BEGN Slist END {printf(" Body \n");generate_flag=0;$$=$2;}
      | BEGN END  {printf(" EMPTY \n");$$=NULL;}
      ;
Slist : Slist Stmt {
//printf(" y34 ");
$$=connector($1,$2);}
      | Stmt {//printf(" y35 ");
      $$=$1;}
      ;
Stmt : InputStmt {$$=$1;}
      | OutputStmt {$$=$1;}
      | AsgStmt {$$=$1;}
      | IfStmt {;$$=$1;}
      | WhileStmt {$$=$1;}
      | BreakStmt {$$=$1;}
      | ContinueStmt {$$=$1;}
      | ReturnStmt {$$=$1;}
      ;
InputStmt : READ LP expr RP SEMCL {printf(" Input statement : \n ");$$=Inode($3);}
      ;
OutputStmt : WRITE LP expr RP SEMCL {printf(" Output statement : \n ");$$=Onode($3);}
      ;
AsgStmt : expr EQUAL expr SEMCL {printf(" Assignement : \n");$$=opnode('=',$1,$3);}
      ;
IfStmt : IF LP E RP THEN Slist ELSE Slist ENDIF SEMCL {struct tnode *t;
        t=connector($6,$8);$$=ifelsenode($3,t);}
      | IF LP E RP THEN Slist ENDIF SEMCL {printf(" IF statement : \n");$$=ifnode($3,$6);}
      ;
WhileStmt : WHILE LP E RP DO Slist ENDWHILE SEMCL {printf(" While statement : \n");$$=whilenode($3,$6);}
      ;
BreakStmt : BREAK SEMCL {printf(" Break Point  \n");$$=breaknode();}
      ;
ContinueStmt : CONTINUE SEMCL {printf(" Continue \n");$$=continuenode();}
      ;
ReturnStmt : RETURN expr SEMCL {printf(" Return  \n");$$=retnode($2);}
      | RETURN SEMCL {$$=retnode(NULL);}
      ;
E : expr LT expr {printf(" Less than expression \n");$$=relnode("<",$1,$3);}
      | expr GT expr {printf(" Greater than expression \n");$$=relnode(">",$1,$3);}
      | expr LT EQUAL expr {printf(" Less than Or equal expression \n");$$=relnode("<=",$1,$4);}
      | expr GT EQUAL expr {printf(" Greater than Or equal expression \n ");$$=relnode(">=",$1,$4);}
      | expr NOT EQUAL expr {printf(" Not equal expression \n ");$$=relnode("!=",$1,$4);}
      | expr EQUAL EQUAL expr {printf(" Equal expression \n");$$=relnode("==",$1,$4);}
      ;
expr : expr PLUS expr   {printf(" Addition \n");$$=opnode('+',$1,$3);}
      | expr MUL expr   {printf(" Multiplication \n");$$=opnode('*',$1,$3);}
      | expr MINUS expr {printf(" Substraction \n");$$=opnode('-',$1,$3);}
      | expr DIV expr   {printf(" DIVIDE \n");$$=opnode('/',$1,$3);}
      | LP expr RP   {$$=$2;}
      | NUM            {printf(" Number %d \n",$1);$$=$1;}
      | STRING        {printf(" String %s \n",$1);$$=$1;}
      | VAR           {printf(" Var \n");$$=$1;}
      | VAR LP RP {printf(" Var ()\n ");$$=$1;}
      | VAR LP ArgList RP {printf(" Var \n ");$1->Arglist=$3;$$=$1;}
      ;

%%

int yyerror(char const *s)
{
  printf("yyerror %s",s);
}
int main()
{
  loopflag[0]=0;
  outputfile=fopen("input.xsm","w");
  Reg=(struct regpool *)malloc(sizeof(struct regpool));
  Reg->reg=-1;
  Reg->label=1;
  fprintf(outputfile,"%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\nMOV SP,4095\nMOV BP,4096\nPUSH R0\nCALL L0\nINT 10\n",0,2056,0,0,0,0,0,0);
  inp();
  yyparse();
  return 0;
}