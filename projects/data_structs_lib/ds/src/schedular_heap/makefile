FULL_PATH = /home/koko/Desktop/git/gilad-kahn/ds/src/doubly_linked_list
TEST_PATH = /home/koko/Desktop/git/gilad-kahn/ds/test
HEADER = -I/home/koko/Desktop/git/gilad-kahn/ds/include
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall
DYNAMIC_LIBRARY = -c -fPIC
DEBUG = -Wextra -g
REALESE = -DNDEBUG -O3
OBJ_CREATE = -c
OBJs =  scheduler.o task.o sorted_list.o doubly_linked_list.o uid.o p_queue.o


scheduler_test.out: libscheduler.so $(OBJs)
	$(CC) $(CFLAGS) $(HEADER) $(DEBUG) -L. -Wl,-rpath=. $(TEST_PATH)/scheduler_test.c -o $@ -lscheduler
	 

libscheduler.so: $(OBJs)
	$(CC) $(CFLAGS) $(OBJs) -shared -o $@

	
scheduler.o: scheduler.c
	$(CC) $(CFLAGS) $(HEADER) $(DYNAMIC_LIBRARY) -o $@ scheduler.c


task.o: task.c uid.o
	$(CC) $(CFLAGS) $(HEADER) $(DYNAMIC_LIBRARY) -o $@ task.c


uid.o: ../uid/uid.c
	$(CC) $(CFLAGS) $(HEADER) $(DYNAMIC_LIBRARY) -o $@ ../uid/uid.c


p_queue.o: ../priority_queue/p_queue.c 
	$(CC) $(CFLAGS) $(HEADER) $(DYNAMIC_LIBRARY) -o $@ ../priority_queue/p_queue.c


sorted_list.o: ../sorted_list/sorted_list.c
	$(CC) $(CFLAGS) $(HEADER) $(DYNAMIC_LIBRARY) -o $@ ../sorted_list/sorted_list.c	

	
doubly_linked_list.o: ../doubly_linked_list/doubly_linked_list.c 
	$(CC) $(CFLAGS) $(HEADER) $(DYNAMIC_LIBRARY) -o $@ ../doubly_linked_list/doubly_linked_list.c	


clean:
	rm *.out *.o *.so
	
 

