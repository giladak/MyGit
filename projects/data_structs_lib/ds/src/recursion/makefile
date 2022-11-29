INCLUDE = -I/home/koko/Desktop/git/gilad-kahn/ds/include
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
GD = gcc -ansi -pedantic-errors -Wall -Wextra -g
GC = gcc -ansi -pedantic-errors -Wall -DNDEBUG -O3 
GDOBJ = gcc -ansi -pedantic-errors -Wall -Wextra -g -c  
GCOBJ =gcc -ansi -pedantic-errors -Wall -Wextra -g -c
OBJs =  recursion_test.o recursion.o stack.o


recursion.out: $(OBJs)
	$(CC) $(CFLAGS) $(OBJs)  -o $@ -lm
		
recursion_test.o: ../../test/recursion_test.c 
	$(GCOBJ) $(INCLUDE)  ../../test/recursion_test.c 
	
recursion.o: recursion.c
	$(GCOBJ) $(INCLUDE) recursion.c  -lm

stack.o: ../stack/stack.c
	$(GCOBJ) $(INCLUDE) ../stack/stack.c	
	
debug: recursion.c ../../test/recursion_test.c 
	$(GD) $(INCLUDE) recursion.c ../../test/recursion_test.c 

relese: recursion.c ../../test/recursion_test.c 
	$(GC) $(INCLUDE) recursion.c ../../test/recursion_test.c 

clean:
	rm *.out
	


