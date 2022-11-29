#dev : Gilad Kahn
#rev : Eliezer Lancry
#status : approved
#date : 5.1.22



CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra
GD = gcc -ansi -pedantic-errors -Wall -Wextra -g 
GC = gcc -ansi -pedantic-errors -Wall -DNDEBUG -O3 
GDOBJ = gcc -ansi -pedantic-errors -Wall -Wextra -g -c 
GCOBJ =gcc -ansi -pedantic-errors -Wall -Wextra -g -c
OBJs =  ../../test/stack_test.o stack.o
INCLUDE = -I/home/koko/Desktop/git/gilad-kahn/ds/include



stack.out: $(OBJs)
	$(CC) $(INCLUDE) $(CFLAGS) $(OBJs)  -o stack.out 
		
stack_test.o: ../../test/stack_test.c 
	$(GCOBJ) $(INCLUDE) ../../test/stack_test.c 
	
stack.o: stack.c 
	$(GCOBJ) $(INCLUDE) stack.c

debug: stack.c ../../test/stack_test.c 
	$(GD) stack.c ../../test/stack_test.c 

relese: stack.c ../../test/stack_test.c 
	$(GC) stack.c ../../test/stack_test.c 

clean:
	rm *.out
	


