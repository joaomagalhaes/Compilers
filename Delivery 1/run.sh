clear
lex -l ijscanner.l 
cc -o ijscan lex.yy.c -ll
./ijscan < echo.ijava
