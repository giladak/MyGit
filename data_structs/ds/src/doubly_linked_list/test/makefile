FULL_PATH = /home/koko/Desktop/git/gilad-kahn/ds/src/doubly_linked_list/test
TEST_PATH = /home/koko/Desktop/git/gilad-kahn/ds/src/doubly_linked_list/test
HEADER = -I/home/koko/Desktop/git/gilad-kahn/ds/include
CC = gcc
CFLAGS = -ansi -pedantic -errors -Wall
DYNAMIC_LIBRARY = -c -fPIC
DEBUG = -Wextra -g
REALESE = -DNDEBUG -O3
OBJ_CREATE = -c
OBJs =  hello_test.o hello.o


hello_test.out: libhello.so hello_test.o
	$(CC) $(CFLAGS) $(HEADER) $(DEBUG) -L. -Wl,-rpath=. -lhello hello_test.c -o $@

libhello.so: hello.o
	$(CC) $(CFLAGS) $(DEBUG) $(HEADER) hello.o -shared -o $@

hello.o:
	$(CC) $(CFLAGS) $(DEBUG) $(HEADER) hello.c -c -fpic -o hello.o
	
hello_test.o:
	$(CC) $(CFLAGS) $(DEBUG) $(HEADER) -c $(TEST_PATH)/hello_test.c -o hello_test.o
	

clean:
	rm *.out *.o *.so
	


