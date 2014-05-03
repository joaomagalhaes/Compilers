clear
lex ijparser.l 
yacc -d ijparser.y
gcc -o exe *.c
./exe -t -s < $1
rm y.tab.h
rm y.tab.c
rm lex.yy.c
rm exe
