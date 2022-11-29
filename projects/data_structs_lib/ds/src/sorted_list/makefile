

INCLUDE = -I/home/koko/Desktop/git/gilad-kahn/ds/include
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
GD = gcc -ansi -pedantic-errors -Wall -Wextra -g
GC = gcc -ansi -pedantic-errors -Wall -DNDEBUG -O3 
GDOBJ = gcc -ansi -pedantic-errors -Wall -Wextra -g -c  
GCOBJ =gcc -ansi -pedantic-errors -Wall -Wextra -g -c
OBJs =  sorted_list_test.o sorted_list.o doubly_linked_list.o


sorted_list.out: $(OBJs)
	$(CC) $(CFLAGS) $(OBJs)  -o sorted_list.out 
		
sorted_list_test.o: ../../test/sorted_list_test.c 
	$(GCOBJ) $(INCLUDE)  ../../test/sorted_list_test.c 
	
sorted_list.o: sorted_list.c 
	$(GCOBJ) $(INCLUDE) sorted_list.c
	
doubly_linked_list.o: ../doubly_linked_list/doubly_linked_list.c 
	$(GCOBJ) $(INCLUDE) ../doubly_linked_list/doubly_linked_list.c	

debug: sorted_list.c ../../test/sorted_list_test.c 
	$(GD) $(INCLUDE) sorted_list.c ../../test/sorted_list_test.c 

relese: sorted_list.c ../../test/sorted_list_test.c 
	$(GC) $(INCLUDE) sorted_list.c ../../test/sorted_list_test.c 

clean:
	rm *.out
	


