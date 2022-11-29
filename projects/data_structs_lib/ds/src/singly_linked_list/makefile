

INCLUDE = -I/home/koko/Desktop/git/gilad-kahn/ds/include
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
GD = gcc -ansi -pedantic-errors -Wall -Wextra -g
GC = gcc -ansi -pedantic-errors -Wall -DNDEBUG -O3 
GDOBJ = gcc -ansi -pedantic-errors -Wall -Wextra -g -c  
GCOBJ =gcc -ansi -pedantic-errors -Wall -Wextra -g -c
OBJs =  singly_linked_list_test.o singly_linked_list.o


singly_linked_list.out: $(OBJs)
	$(CC) $(CFLAGS) $(OBJs)  -o singly_linked_list.out 
		
singly_linked_list_test.o: ../../test/singly_linked_list_test.c 
	$(GCOBJ) $(INCLUDE)  ../../test/singly_linked_list_test.c 
	
singly_linked_list.o: singly_linked_list.c 
	$(GCOBJ) $(INCLUDE) singly_linked_list.c

debug: singly_linked_list.c ../../test/singly_linked_list_test.c 
	$(GD) $(INCLUDE) singly_linked_list.c ../../test/singly_linked_list_test.c 

relese: singly_linked_list.c ../../test/singly_linked_list_test.c 
	$(GC) $(INCLUDE) singly_linked_list.c ../../test/singly_linked_list_test.c 

clean:
	rm *.out
	


