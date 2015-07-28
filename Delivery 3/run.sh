clear
rm exe
rm out
lex ijcompiler.l 
yacc -d ijcompiler.y
gcc -o exe *.c
./exe -t < $1
./exe < $1 > out.ll
llc out.ll
clang -o out out.s
./out $2
rm y.tab.h
rm y.tab.c
rm lex.yy.c
