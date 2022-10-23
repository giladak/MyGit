INCLUDE = -I/home/koko/Desktop/git/gilad-kahn/ds/include
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
GD = gcc -ansi -pedantic-errors -Wall -Wextra -g
GC = gcc -ansi -pedantic-errors -Wall -DNDEBUG -O3 
GDOBJ = gcc -ansi -pedantic-errors -Wall -Wextra -g -c  
GCOBJ =gcc -ansi -pedantic-errors -Wall -Wextra -g -c
OBJs =  sorts_test.o sorts.o 


sorts.out: $(OBJs)
	$(CC) $(CFLAGS) $(OBJs)  -o sorts.out 
		
sorts_test.o: ../../test/sorts_test.c 
	$(GCOBJ) $(INCLUDE)  ../../test/sorts_test.c 
	
sorts.o: sorts.c
	$(GCOBJ) $(INCLUDE) sorts.c
	
debug: sorts.c ../../test/sorts_test.c 
	$(GD) $(INCLUDE) sorts.c ../../test/sorts_test.c 

relese: sorts.c ../../test/sorts_test.c 
	$(GC) $(INCLUDE) sorts.c ../../test/sorts_test.c 

clean:
	rm *.out
	


