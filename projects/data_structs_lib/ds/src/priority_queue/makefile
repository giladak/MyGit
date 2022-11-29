

INCLUDE = -I/home/koko/Desktop/git/gilad-kahn/ds/include
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
GD = gcc -ansi -pedantic-errors -Wall -Wextra -g
GC = gcc -ansi -pedantic-errors -Wall -DNDEBUG -O3 
GDOBJ = gcc -ansi -pedantic-errors -Wall -Wextra -g -c  
GCOBJ =gcc -ansi -pedantic-errors -Wall -Wextra -g -c
OBJs =  p_queue_test.o p_queue.o doubly_linked_list.o sorted_list.o


p_queue.out: $(OBJs)
	$(CC) $(CFLAGS) $(OBJs)  -o p_queue.out 
		
p_queue_test.o: ../../test/p_queue_test.c 
	$(GCOBJ) $(INCLUDE)  ../../test/p_queue_test.c 
	
p_queue.o: p_queue.c 
	$(GCOBJ) $(INCLUDE) p_queue.c
	
sorted_list.o: ../sorted_list/sorted_list.c 
	$(GCOBJ) $(INCLUDE) ../sorted_list/sorted_list.c	
	
doubly_linked_list.o: ../doubly_linked_list/doubly_linked_list.c 
	$(GCOBJ) $(INCLUDE) ../doubly_linked_list/doubly_linked_list.c	

debug: p_queue.c ../../test/p_queue_test.c 
	$(GD) $(INCLUDE) p_queue.c ../../test/p_queue_test.c 

relese: p_queue.c ../../test/p_queue_test.c 
	$(GC) $(INCLUDE) p_queue.c ../../test/p_queue_test.c 

clean:
	rm *.out
	


