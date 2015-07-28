clear
rm exe
rm ~/Desktop/ijparser.zip
lex ijparser.l 
yacc -d ijparser.y
gcc -o exe *.c
zip ~/Desktop/ijparser.zip functions.c functions.h ijparser.l ijparser.y semantics.c semantics.h shows.c shows.h structures.h symbol_table.c symbol_table.h
./exe -t -s < $1
rm y.tab.h
rm y.tab.c
rm lex.yy.c

