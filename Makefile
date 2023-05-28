flex :	
	flex lang.l
bison :	
	bison -d lang.y

compile : 
	gcc -o prog lang.tab.c lex.yy.c symbol_table.c

exec : 
	./prog
