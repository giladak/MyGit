INCLUDE = -I/home/koko/Desktop/git/gilad-kahn/ds/include
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
GD = gcc -ansi -pedantic-errors -Wall -Wextra -g
GC = gcc -ansi -pedantic-errors -Wall -DNDEBUG -O3 
GDOBJ = gcc -ansi -pedantic-errors -Wall -Wextra -g -c  
GCOBJ =gcc -ansi -pedantic-errors -Wall -Wextra -g -c
OBJs =  calculator_test.o calculator.o stack.o


calculator.out: $(OBJs)
	$(CC) $(CFLAGS) $(OBJs)  -o $@ -lm
		
calculator_test.o: ../../test/calculator_test.c 
	$(GCOBJ) $(INCLUDE)  ../../test/calculator_test.c 
	
calculator.o: calculator.c
	$(GCOBJ) $(INCLUDE) calculator.c  -lm

stack.o: ../stack/stack.c
	$(GCOBJ) $(INCLUDE) ../stack/stack.c	
	
debug: calculator.c ../../test/calculator_test.c 
	$(GD) $(INCLUDE) calculator.c ../../test/calculator_test.c 

relese: calculator.c ../../test/calculator_test.c 
	$(GC) $(INCLUDE) calculator.c ../../test/calculator_test.c 

clean:
	rm *.out
	


