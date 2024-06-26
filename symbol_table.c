#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "symbol_table.h"
//creates node for integers
struct tnode * intnode(int val)
{
  struct tnode *temp;
  temp=(struct tnode*)malloc(sizeof(struct tnode));
  temp->val=val;
  temp->type=0;
  temp->nodetype=malloc(sizeof(char));
  *(temp->nodetype)='N';
  temp->varname=NULL;
  temp->Arglist=NULL;
  temp->Gentry=NULL;
  temp->Lentry=NULL;
  temp->left=NULL;
  temp->right=NULL;
  return temp;
}

//creates string node
struct tnode * stringnode(char *word)
{
  struct tnode *temp;
  temp=(struct tnode*)malloc(sizeof(struct tnode));
  //temp->val=val;
  //temp->type=0;
  temp->nodetype=malloc(sizeof(char));
  *(temp->nodetype)='L';
  temp->varname=malloc(8*sizeof(char));
  strcpy(temp->varname,word);
  temp->Arglist=NULL;
  temp->Gentry=NULL;
  temp->Lentry=NULL;
  temp->left=NULL;
  temp->right=NULL;
  return temp;
}

//creates nodes for variable
struct tnode * varnode(char *vname,struct Lsymbol *lentry,struct Gsymbol *gentry)
{
  struct tnode *temp;
  temp=(struct tnode*)malloc(sizeof(struct tnode));
  //temp->val=val;
  //temp->type=0;
  temp->nodetype=malloc(sizeof(char));
  *(temp->nodetype)='V';
  temp->varname=malloc(10*sizeof(char));
  strcpy(temp->varname,vname);
  temp->Arglist=NULL;
  temp->Gentry=gentry;
  temp->Lentry=lentry;
  temp->left=NULL;
  temp->right=NULL;
  return temp;
}

//operator node
struct tnode * opnode(char op,struct tnode *l,struct tnode *r)
{
  struct tnode *temp;
  temp=(struct tnode*)malloc(sizeof(struct tnode));
  //temp->val=val;
  //temp->type=0;
  temp->nodetype=malloc(sizeof(char));
  *(temp->nodetype)='S';
  temp->varname=malloc(sizeof(char));
  *(temp->varname)=op;
  temp->Arglist=NULL;
  temp->Gentry=NULL;
  temp->Lentry=NULL;
  temp->left=l;
  temp->right=r;
  return temp;
}

//input node
struct tnode * Inode(struct tnode *l)
{
  struct tnode *temp;
  temp=(struct tnode*)malloc(sizeof(struct tnode));
  //temp->val=val;
  //temp->type=0;
  temp->nodetype=malloc(sizeof(char));
  *(temp->nodetype)='I';
  temp->varname=NULL;
  temp->Arglist=NULL;
  temp->Gentry=NULL;
  temp->Lentry=NULL;
  temp->left=l;
  temp->right=NULL;
  return temp;
}

//output node
struct tnode * Onode(struct tnode *l)
{
  struct tnode *temp;
  temp=(struct tnode*)malloc(sizeof(struct tnode));
  //temp->val=val;
  //temp->type=0;
  temp->nodetype=malloc(sizeof(char));
  *(temp->nodetype)='O';
  temp->varname=NULL;
  temp->Arglist=NULL;
  temp->Gentry=NULL;
  temp->Lentry=NULL;
  temp->left=l;
  temp->right=NULL;
  return temp;
}

//connector node
struct tnode * connector(struct tnode *l,struct tnode *r)
{
  struct tnode *temp;
  temp=(struct tnode*)malloc(sizeof(struct tnode));
  //temp->val=val;
  //temp->type=0;
  temp->nodetype=malloc(sizeof(char));
  *(temp->nodetype)='C';
  temp->varname=NULL;
  temp->Arglist=NULL;
  temp->Gentry=NULL;
  temp->Lentry=NULL;
  temp->left=l;
  temp->right=r;
  return temp;
}

//relational node
struct tnode * relnode(char *op,struct tnode *l,struct tnode *r)
{
  struct tnode *temp;
  temp=(struct tnode*)malloc(sizeof(struct tnode));
  //temp->val=val;
  //temp->type=0;
  temp->nodetype=malloc(sizeof(char));
  *(temp->nodetype)='R';
  temp->varname=malloc(2*sizeof(char));
  temp->varname=op;
  temp->Arglist=NULL;
  temp->Gentry=NULL;
  temp->Lentry=NULL;
  temp->left=l;
  temp->right=r;
  return temp;
}

//ifnode
struct tnode * ifnode(struct tnode *l,struct tnode *r)
{
  struct tnode *temp;
  temp=(struct tnode*)malloc(sizeof(struct tnode));
  //temp->val=val;
  //temp->type=0;
  temp->nodetype=malloc(sizeof(char));
  *(temp->nodetype)='f';
  temp->varname=NULL;
  temp->Arglist=NULL;
  temp->Gentry=NULL;
  temp->Lentry=NULL;
  temp->left=l;
  temp->right=r;
  return temp;
}

//ifelse node
struct tnode * ifelsenode(struct tnode *l,struct tnode *r)
{
  struct tnode *temp;
  temp=(struct tnode*)malloc(sizeof(struct tnode));
  //temp->val=val;
  //temp->type=0;
  temp->nodetype=malloc(sizeof(char));
  *(temp->nodetype)='F';
  temp->varname=NULL;
  temp->Arglist=NULL;
  temp->Gentry=NULL;
  temp->Lentry=NULL;
  temp->left=l;
  temp->right=r;
  return temp;
}

//while node
struct tnode * whilenode(struct tnode *l,struct tnode *r)
{
  struct tnode *temp;
  temp=(struct tnode*)malloc(sizeof(struct tnode));
  //temp->val=val;
  //temp->type=0;
  temp->nodetype=malloc(sizeof(char));
  *(temp->nodetype)='W';
  temp->varname=NULL;
  temp->Arglist=NULL;
  temp->Gentry=NULL;
  temp->Lentry=NULL;
  temp->left=l;
  temp->right=r;
  return temp;
}

//break node
struct tnode * breaknode()
{
  struct tnode *temp;
  temp=(struct tnode*)malloc(sizeof(struct tnode));
  //temp->val=val;
  //temp->type=0;
  temp->nodetype=malloc(sizeof(char));
  *(temp->nodetype)='B';
  temp->varname=NULL;
  temp->Arglist=NULL;
  temp->Gentry=NULL;
  temp->Lentry=NULL;
  temp->left=NULL;
  temp->right=NULL;
  return temp;
}

//continue node
struct tnode * continuenode()
{
  struct tnode *temp;
  temp=(struct tnode*)malloc(sizeof(struct tnode));
  //temp->val=val;
  //temp->type=0;
  temp->nodetype=malloc(sizeof(char));
  *(temp->nodetype)='c';
  temp->varname=NULL;
  temp->Arglist=NULL;
  temp->Gentry=NULL;
  temp->Lentry=NULL;
  temp->left=NULL;
  temp->right=NULL;
  return temp;
}

//return node
struct tnode * retnode(struct tnode *l)
{
    struct tnode *temp;
    temp=(struct tnode*)malloc(sizeof(struct tnode));
    //temp->val=val;
    //temp->type=0;
    temp->nodetype=malloc(sizeof(char));
    *(temp->nodetype)='r';
    temp->varname=NULL;
    temp->Arglist=NULL;
    temp->Gentry=NULL;
    temp->Lentry=NULL;
    temp->left=l;
    temp->right=NULL;
    return temp;
}

//funtion to look for the variable in symbol table
struct Gsymbol *lookup(char * name)
{
  struct Gsymbol *temp;
  temp=Symbolhead;
  while(temp!=NULL)
  {
    if(strcmp(temp->name,name)==0)
    {
      return temp;
    }
    temp=temp->next;
  }
  return NULL;
}

//function to look for the local Variable
struct Lsymbol *llookup(char * name)
{
  struct Lsymbol *temp;
  temp=lhead;
  while(temp!=NULL)
  {
    if(strcmp(temp->name,name)==0)
    {
      return temp;
    }
    temp=temp->next;
  }
  return NULL;
}

//function to make entry to symbol table
void install(char *name,int type,int size)
{
  if(Symbolhead==NULL)
    Symbolhead=makesymbolnode(name,type,size);
  else
  {
    struct Gsymbol *tmp;
    tmp=Symbolhead;
    tmp->next=Symbolhead->next;
    Symbolhead=makesymbolnode(name,type,size);
    Symbolhead->next=tmp;
  }
}

//function to make entry to local symbol table
void linstall(char *yytext,int type,int bind)
{
  if(lhead==NULL)
    lhead=makelnode(yytext,type,bind);
  else
  {
    struct Lsymbol *tmp;
    tmp=lhead;
    tmp->next=lhead->next;
    lhead=makelnode(yytext,type,bind);
    lhead->next=tmp;
  }
}

//function to make parameter table entrry
void finstall(char *name,int vtype)
{
  if(paramhead==NULL)
    paramhead=makepnode(name,vtype);
  else
  {
    struct Paramstruct *temp;
    temp=paramhead;
    temp->next=paramhead->next;
    paramhead=makepnode(name,vtype);
    paramhead->next=temp;
  }
}

//function to create global symbol node
struct Gsymbol *makesymbolnode(char *name,int type,int size)
{
  struct Gsymbol * temp;
  temp=(struct Gsymbol *)malloc(sizeof(struct Gsymbol));
  temp->name=malloc(10*sizeof(char));
  strcpy(temp->name,name);
  temp->type=type;
  temp->size=size;
  temp->binding=bindval;
  temp->paramlist=NULL;
  temp->next=NULL;
  bindval+=1;
  return temp;
}

//function to create local symbol node
struct Lsymbol *makelnode(char *name,int type,int bind)
{
  struct Lsymbol * temp;
  temp=(struct Lsymbol *)malloc(sizeof(struct Lsymbol));
  temp->name=malloc(10*sizeof(char));
  strcpy(temp->name,name);
  temp->type=type;
  temp->binding=bind;
  temp->next=NULL;
  return temp;
}
//function to create parameter nodes
struct Paramstruct * makepnode(char *name,int type)
{
    struct Paramstruct *temp;
    temp=(struct Paramstruct *)malloc(sizeof(struct Paramstruct));
    temp->name=malloc(10*sizeof(char));
    strcpy(temp->name,name);
    temp->type=type;
    temp->binding=lbindval;
    lbindval+=1;
    temp->next=NULL;
    return temp;
}

//function to update size of arrays
void sizeupdate(struct Gsymbol *temp,int size)
{
  temp->size=size;
  bindval+=(size-1);
  return;
}

//function to update type
void updatetype(struct Gsymbol *temp,int type)
{
  temp->type=type;
  return;
}

//function to update local variable type
void updateltype(struct Lsymbol *temp,int type)
{
  temp->type=type;
  return;
}

//function to print symbol table
void printsymbols(struct Gsymbol *temp)
{
  while(temp!=NULL)
  {
    printf("\nNAME-%s Type-%d Size-%d Binding-%d",temp->name,temp->type,temp->size,temp->binding);
    if(temp->paramlist!=NULL)
      printparam(temp->paramlist);
    temp=temp->next;
  }
  return;
}

//function for printing local symboltable
void printlsymbols(struct Lsymbol *head)
{
  while(head!=NULL)
    {
    printf("\nNAME-%s Type-%d Binding-%d",head->name,head->type,head->binding);
    head=head->next;
  }
  return;
}

//function to print parameters
void printparam(struct Paramstruct *temp)
{
  while(temp!=NULL)
  {
    printf("\n\tNAME-%s Type-%d",temp->name,temp->type);
    temp=temp->next;
  }
}

//function to check parameter name and type correctness
struct Paramstruct * checkfor(struct Paramstruct * temp,char * yytext,int ptype)
{
    int flg=0;
    while(temp!=NULL)
    {
      if(strcmp(temp->name,yytext)==0)
      {
        if(temp->type==ptype)
          return temp;
      }
      temp=temp->next;
    }
    return temp;
}

//function to chceck wether the name exists in global table
int checkname(char * yytext)
{
  if(lookup(yytext)!=NULL)
    return 1;
  if(llookup(yytext)!=NULL)
    return 1;
  return 0;
}

//function to check validity in parameters
int plook(char *name,struct Paramstruct * p)
{
  while(p!=NULL)
  {
    if(strcmp(p->name,name)==0)
    {
      return 1;
    }
    p=p->next;
  }
  return 0;
}

//funtion to generate code
int generate(struct tnode *t)
{
  if(generate_flag==0)
  {
    fprintf(outputfile,"PUSH BP\n");
    fprintf(outputfile,"MOV BP,SP\n");
    struct Lsymbol *lv;
    lv=lhead;
    while(lv!=NULL)
    {
      if(lv->binding>0)
        fprintf(outputfile,"PUSH R0\n");
      lv=lv->next;
    }
    generate_flag=1;
  }
  struct Gsymbol *gn;
  struct Lsymbol *ln;
  struct Paramstruct *pn;
  struct tnode *tn;
  if(t==NULL)
    return 0;
  int p,q,loc,lval,rval,rval2,l1=0,l2=0,l3=0,t1,t2,no,count;
  switch(*(t->nodetype))
  {
    case 'N': p=getfreereg();
              fprintf(outputfile,"MOV R%d, %d\n",p,t->val);
              return p;
              break;
    case 'L': p=getfreereg();
              fprintf(outputfile,"MOV R%d, %s\n",p,t->varname);
              return p;
              break;
    case 'V': if(functionargflag==0&&t->Arglist==NULL)
              {
                p=getfreereg();
                if(t->Lentry!=NULL)
                  loc=t->Lentry->binding;
                else
                  loc=t->Gentry->binding;
                fprintf(outputfile,"MOV R%d, BP\n",p);
                if(loc>0)
                  fprintf(outputfile,"ADD R%d, %d\n",p,loc);
                else
                  fprintf(outputfile,"SUB R%d, %d\n",p,(2-loc));
                fprintf(outputfile,"MOV R%d, [R%d]\n",p,p);
                return p;
                break;
              }
              else
              {
                if(t->varname==NULL)
                {
                  printf("testing error");
                }
                printf(" *%s* ",t->varname);
                gn=lookup(t->varname);
                if(gn==NULL&&functionargflag==1)
                {
                  printf(" 1 \n");
                  p=getfreereg();
                  if(t->Lentry!=NULL)
                    loc=t->Lentry->binding;
                  else
                    loc=t->Gentry->binding;
                  fprintf(outputfile,"MOV R%d, BP\n",p);
                  if(loc>0)
                    fprintf(outputfile,"ADD R%d, %d\n",p,loc);
                  else
                    fprintf(outputfile,"SUB R%d, %d\n",p,(2-loc));
                  fprintf(outputfile,"MOV R%d, [R%d]\n",p,p);
                  return p;
                }
                else
                {
                  functionargflag=1;
                  printf("function");
                  no=-1;
                  for(int i=0;i<Reg->reg;i++)
                  {
                    fprintf(outputfile,"PUSH R%d\n",i);
                    no+=1;
                  }
                  p=getfreereg();
                  tn=t->Arglist;
                  count=0;
                  while(tn!=NULL)
                  {
                    p=generate(tn);
                    fprintf(outputfile,"PUSH R%d\n",p);
                    releasereg();
                    tn=tn->Arglist;
                    count+=1;
                  }
                  printf("count--%dno--%d",count,no);
                  fprintf(outputfile,"PUSH R0\n");
                  fprintf(outputfile,"CALL L%d\n",gn->binding);
                  fprintf(outputfile,"POP R%d\n",p);
                  for(int i=0;i<count;i++)
                    fprintf(outputfile,"POP R0\n");
                  for(int i=no;i>=0;i--)
                    fprintf(outputfile,"POP R%d\n",i);
                  functionargflag=0;
                }
                return p;
              }
    case 'S':
              switch(*(t->varname))
              {
                case '+': lval=generate(t->left);
                          rval=generate(t->right);
                          fprintf(outputfile,"ADD R%d, R%d\n",lval,rval);
                          break;
                case '-': lval=generate(t->left);
                          rval=generate(t->right);
                          fprintf(outputfile,"SUB R%d, R%d\n",lval,rval);
                          break;
                case '*': lval=generate(t->left);
                          rval=generate(t->right);
                          fprintf(outputfile,"MUL R%d, R%d\n",lval,rval);
                          break;
                case '/': lval=generate(t->left);
                          rval=generate(t->right);
                          fprintf(outputfile,"DIV R%d, R%d\n",lval,rval);
                          break;
                case '=': p=getfreereg();
                          rval=generate(t->right);
                          if(t->left->Lentry!=NULL)
                            loc=t->left->Lentry->binding;
                          else
                            loc=t->left->Gentry->binding;
                          fprintf(outputfile,"MOV R%d, BP\n",p);
                          if(loc>0)
                            fprintf(outputfile,"ADD R%d, %d\n",p,loc);
                          else
                            fprintf(outputfile,"SUB R%d, %d\n",p,(2-loc));
                          fprintf(outputfile,"MOV [R%d], R%d\n",p,rval);
                          releasereg();
                          break;
                default: printf("\nerror in operator node \n");
              }
              releasereg();
              return lval;
    case 'I': gn=t->left->Gentry;
              if(gn!=NULL)
              {
                r_val((gn->binding));
              }
              ln=t->left->Lentry;
              if(ln!=NULL)
              {
                r_val(ln->binding);
              }
              break;
    case 'O': q=generate(t->left);
              p_val(q);
              releasereg();
              break;
    case 'C': generate(t->left);
              generate(t->right);
              break;
    case 'R': lval=generate(t->left);
              rval=generate(t->right);
              if(strcmp((t->varname),"<")==0)
              {
                printf("%s",t->varname);
                fprintf(outputfile,"LT R%d, R%d\n",lval,rval);
              }
              else if(strcmp((t->varname),">")==0)
              {
                printf("%s",t->varname);
                fprintf(outputfile,"GT R%d, R%d\n",lval,rval);
              }
              else if(strcmp((t->varname),"<=")==0)
              {
                printf("%s",t->varname);
                fprintf(outputfile,"LE R%d, R%d\n",lval,rval);
              }
              else if(strcmp((t->varname),">=")==0)
              {
                printf("%s",t->varname);
                fprintf(outputfile,"GE R%d, R%d\n",lval,rval);
              }
              else if(strcmp((t->varname),"!=")==0)
              {
                printf("%s",t->varname);
                fprintf(outputfile,"NE R%d, R%d\n",lval,rval);
              }
              else if(strcmp((t->varname),"==")==0)
              {
                printf("%s",t->varname);
                fprintf(outputfile,"EQ R%d, R%d\n",lval,rval);
              }
              else
              {
                printf("\nrelational operator error \n");
              }
              releasereg();
              return lval;
              break;
    case 'f': l1=getlabel();
              l2=getlabel();
              fprintf(outputfile,"L%d:\n",l1);
              lval=generate(t->left);
              fprintf(outputfile,"JZ R%d, L%d\n",lval,l2);
              releasereg();
              rval=generate(t->right);
              fprintf(outputfile,"L%d:\n",l2);
              break;
    case 'F': l1=getlabel();
              l2=getlabel();
              l3=getlabel();
              fprintf(outputfile,"L%d:\n",l1);
              lval=generate(t->left);
              fprintf(outputfile,"JZ R%d, L%d\n",lval,l2);
              releasereg();
              rval=generate(t->right->left);
              fprintf(outputfile,"JMP L%d\n",l3);
              fprintf(outputfile,"L%d:\n",l2);
              rval2=generate(t->right->right);
              fprintf(outputfile,"L%d:\n",l3);
              break;
    case 'W': l1=getlabel();
              l2=getlabel();
              t1=loopflag[1];
              t2=loopflag[2];
              loopflag[0]+=1;
              loopflag[1]=l1;
              loopflag[2]=l2;
              fprintf(outputfile,"L%d:\n",l1);
              lval=generate(t->left);
              fprintf(outputfile,"JZ R%d, L%d\n",lval,l2);
              releasereg();
              rval=generate(t->right);
              fprintf(outputfile,"JMP L%d\n",l1);
              fprintf(outputfile,"L%d:\n",l2);
              loopflag[0]-=1;
              loopflag[1]=t1;
              loopflag[2]=t2;
              break;
    case 'B': fprintf(outputfile,"JMP L%d\n",loopflag[2]);
              break;
    case 'c':fprintf(outputfile,"JMP L%d\n",loopflag[1]);
              break;
    case 'r': gn=lookup(currentfname);
              printf("   $$ %s  $$  ",currentfname);
              if(strcmp(currentfname,"main")==0)
              {
                fprintf(outputfile,"JMP L%d\n",ml);
                break;
              }
              else
              {
                l2=gn->binding+1;
                if(t->left!=NULL)
                {
                  lval=generate(t->left);
                  l1=getfreereg();
                  fprintf(outputfile,"MOV R%d, BP\n",l1);
                  fprintf(outputfile,"SUB R%d, 2\n",l1);
                  fprintf(outputfile,"MOV [R%d], R%d\n",l1,lval);
                }
                fprintf(outputfile,"JMP L%d\n",(l2));
              }
              break;
    default:printf("\nERROR IN PARSING TREE\n");
  }
}

//function to pop local elements code
void lpop()
{
  struct Lsymbol *temp;
  printf("\netrd");
  temp=lhead;
  while(temp!=NULL)
  {
    if(temp->binding>0)
      fprintf(outputfile,"POP R0\n");
    temp=temp->next;
  }
  fprintf(outputfile,"MOV BP, [SP]\n");
  fprintf(outputfile,"POP R0\n");
}

//function to get free register from register pool
int getfreereg()
{
  (Reg->reg)+=1;
  if(Reg->reg==20)
  {
    printf("error max no of registeres exceeded");
    exit (1);
  }
  if(Reg->reg<0)
  {
    printf("\nerror in releasing register");
    exit (1);
  }
  return (Reg->reg);
}

//function to return free label number
int getlabel()
{
  Reg->label+=1;
  return (Reg->label);
}

//function to release register to register pool
void releasereg()
{
  Reg->reg-=1;
}

//function to reset registers to 0
void resetreg()
{
  Reg->reg=-1;
}
//funtion to generate readvalue code
int r_val(int loc)
{
  int r=getfreereg();
  int r_1=getfreereg();
  int r_2=getfreereg();
  fprintf(outputfile,"MOV R%d,BP\n",r_2);
  fprintf(outputfile,"ADD R%d,%d\n",r_2,loc);
  fprintf(outputfile,"MOV R%d, R%d\n",r,r_2);
  fprintf(outputfile,"MOV R%d, \"Read\"\n",r_2);
  fprintf(outputfile,"PUSH R%d\n",r_2);
  releasereg();
  fprintf(outputfile,"MOV R%d, -1\n",r_2);
  fprintf(outputfile,"PUSH R%d\n",r_2);
  fprintf(outputfile,"PUSH R%d\n",r);
  fprintf(outputfile,"PUSH R%d\n",r_1);
  fprintf(outputfile,"PUSH R%d\n",r_1);
  fprintf(outputfile,"CALL 0\n");
  fprintf(outputfile,"POP R%d\n",r);
  fprintf(outputfile,"POP R%d\n",r_1);
  fprintf(outputfile,"POP R%d\n",r_1);
  fprintf(outputfile,"POP R%d\n",r_1);
  fprintf(outputfile,"POP R%d\n",r_1);
  releasereg();
  releasereg();
}

//function to generate printvalue code
int p_val(int reg)
{
  int r=getfreereg();
  int r_1=getfreereg();
  int r_2=getfreereg();
  fprintf(outputfile,"MOV R%d, R%d\n",r,reg);
  fprintf(outputfile,"MOV R%d, \"Write\"\n",r_2);
  fprintf(outputfile,"PUSH R%d\n",r_2);
  releasereg();
  fprintf(outputfile,"MOV R%d, -2\n",r_2);
  fprintf(outputfile,"PUSH R%d\n",r_2);
  fprintf(outputfile,"PUSH R%d\n",r);
  fprintf(outputfile,"PUSH R%d\n",r_1);
  fprintf(outputfile,"PUSH R%d\n",r_1);
  fprintf(outputfile,"CALL 0\n");
  fprintf(outputfile,"POP R%d\n",r);
  fprintf(outputfile,"POP R%d\n",r_1);
  fprintf(outputfile,"POP R%d\n",r_1);
  fprintf(outputfile,"POP R%d\n",r_1);
  fprintf(outputfile,"POP R%d\n",r_1);
  releasereg();
  releasereg();
}

//function that returns location in stack for a variable
int loc_for_name(char var)
{
  for(int i=0;i<26;i++)
  {
    if(var-'a'==i)
      return i+4096;
  }
}
