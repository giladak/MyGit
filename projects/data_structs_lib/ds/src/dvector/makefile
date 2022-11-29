


CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra
GD = gcc -ansi -pedantic-errors -Wall -Wextra -g
GC = gcc -ansi -pedantic-errors -Wall -DNDEBUG -O3 
GDOBJ = gcc -ansi -pedantic-errors -Wall -Wextra -g -c 
GCOBJ =gcc -ansi -pedantic-errors -Wall -Wextra -g -c
OBJs =  dvector_test.o dvector.o


dvector.out: $(OBJs)
	$(CC) $(CFLAGS) $(OBJs)  -o dvector.out 
		
dvector_test.o: ../../test/dvector_test.c 
	$(GCOBJ) ../../test/dvector_test.c 
	
dvector.o: dvector.c 
	$(GCOBJ) dvector.c

debug: dvector.c ../../test/dvector_test.c 
	$(GD) dvector.c ../../test/dvector_test.c 

relese: dvector.c ../../test/dvector_test.c 
	$(GC) dvector.c ../../test/dvector_test.c 

clean:
	rm *.out
	


