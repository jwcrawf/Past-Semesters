cxref.exe: lex.yy.c
	gcc -g -o $@ lex.yy.c -lfl
lex.yy.c: cxref.l
	flex cxref.l
clean: 
	rm -f cxref.exe lex.yy.* *.o *~
