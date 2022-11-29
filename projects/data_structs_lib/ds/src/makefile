FULL_PATH = /home/koko/Desktop/git/gilad-kahn/ds/src/
TESTS_DEBUG = $(wildcard /home/koko/Desktop/git/gilad-kahn/ds/test/*.c)
TESTS_REALESE = $(wildcard /home/koko/Desktop/git/gilad-kahn/ds/test/*.c)
TESTS_OUT =$(subst c, out,/home/koko/Desktop/git/gilad-kahn/ds/test/*.c)
TEST_PATH = /home/koko/Desktop/git/gilad-kahn/ds/test/
HEADER = -I/home/koko/Desktop/git/gilad-kahn/ds/include
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall
DYNAMIC_LIBRARY = -c -fPIC
DEBUG = -Wextra -g
LINK= -L$(FULL_PATH) -Wl,-rpath=$(FULL_PATH)
REALESE = -DNDEBUG -O3
OBJ_CREATE = -c
FOLDER=$(shell basename $(CURDIR))
SRCs=$(wildcard /home/koko/Desktop/git/gilad-kahn/ds/src/**/*.c)
OBJs=$(wildcard /home/koko/Desktop/git/gilad-kahn/ds/src/*.o)


all: libdata_structs.so $(TESTS_REALESE) $(TESTS_DEBUG)
	make $(TESTS_REALESE) && make $(TESTS_DEBUG)


$(TESTS_REALESE): $(TESTS_REALESE) libdata_structs.so
	cp $(TESTS_REALESE) $(FULL_PATH)
	$(CC) $(CFLAGS) $(REALESE) $(HEADER) -L$(FULL_PATH) -Wl,-rpath=$(FULL_PATH) -o $@.out $@ -ldata_structs
	rm $(FULL_PATH)*.c
	mv $@.out $(FULL_PATH)


$(TESTS_DEBUG): $(TESTS_DEBUG) libdata_structs.so
	cp $(TESTS_DEBUG) $(FULL_PATH)
	$(CC) $(CFLAGS) $(DEBUG) $(HEADER) -L$(FULL_PATH) -Wl,-rpath=$(FULL_PATH) -o $@.out $@ -ldata_structs
	rm $(FULL_PATH)*.c
	mv $@.out $(FULL_PATH)

libdata_structs.so: $(OBJs)
	$(CC) $(CFLAGS) $(HEADER) $(OBJs) -shared -o $@  

create_o_files: $(SRCs)
	$(CC) $(CFLAGS) $(HEADER) $(DEBUG) -c -fPIC $(SRCs) -lm
	
clean:
	rm *.out *.o









#$(TESTS_OUT): $ libdata_structs.so
#	$(CC) $(CFLAGS) $(HEADER) $(TESTS) -o $@ -L$(FULL_PATH) -Wl,-rpath=$(FULL_PATH) -ldata_structs






