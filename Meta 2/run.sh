clear
lex ijscanner.l 
yacc -d ijparser.y
cc -o exe y.tab.c lex.yy.c -ll -ly
./exe