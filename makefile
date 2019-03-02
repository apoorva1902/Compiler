output: driver.o lexer.o
	gcc driver.o lexer.o -o a
gram: grammartoff.o
	gcc grammartoff.o -o gram
driver.o: driver.c
	gcc -c driver.c
lexer.o: lexer.c lexer.h
	gcc -c lexer.c
grammartoff.o: grammartoff.c
	gcc -c -g grammartoff.c
clean:
	rm *.o a
