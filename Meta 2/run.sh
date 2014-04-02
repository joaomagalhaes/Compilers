clear
lex ijscanner.l 
yacc -d ijparser.y
gcc -o exe lex.yy.c y.tab.c functions.c
./exe < gcd.ijava
