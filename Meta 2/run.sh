clear
lex ijscanner.l 
yacc -d ijparser.y
gcc -o exe lex.yy.c y.tab.c functions.c shows.c semantics.c
./exe -t -s < $1
rm lex.yy.c
rm exe
rm y.tab.c
rm y.tab.h
