

INCLUDE = -I/home/koko/Desktop/git/gilad-kahn/ds/include
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
GD = gcc -ansi -pedantic-errors -Wall -Wextra -g
GC = gcc -ansi -pedantic-errors -Wall -DNDEBUG -O3 
GDOBJ = gcc -ansi -pedantic-errors -Wall -Wextra -g -c  
GCOBJ =gcc -ansi -pedantic-errors -Wall -Wextra -g -c
OBJs =  queue_test.o queue.o ../singly_linked_list/singly_linked_list.o
LINKED = ../singly_linked_list/singly_linked_list.c


queue.out: $(OBJs)
	$(CC) $(INCLUDE) $(CFLAGS) $(OBJs)  -o queue.out 
		
queue_test.o: ../../test/queue_test.c 
	$(GCOBJ) $(INCLUDE)  ../../test/queue_test.c 
	
queue.o: queue.c $(LINKED)
	$(GCOBJ) $(INCLUDE) queue.c $(LINKED)

singly_linked_list.o: $(LINKED)
	$(GCOBJ) $(INCLUDE) $(LINKED)

debug: queue.c ../../test/queue_test.c $(LINKED)
	$(GD) $(INCLUDE) queue.c ../../test/queue_test.c $(LINKED)

relese: queue.c ../../test/queue_test.c $(LINKED)
	$(GC) $(INCLUDE) queue.c ../../test/queue_test.c $(LINKED)

clean:
	rm *.out
	


