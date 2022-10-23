FULL_PATH = /home/shikamaru/Desktop/git/gilad-kahn/projects/final_project/framework/src/
TESTS_DEBUG = $(wildcard /home/shikamaru/Desktop/git/gilad-kahn/projects/final_project/framework/test/*.cpp)
TESTS_REALESE = $(wildcard /home/shikamaru/Desktop/git/gilad-kahn/projects/final_project/framework/test/*.cpp)
TESTS_OUT =$(subst cpp, out,/home/shikamaru/Desktop/git/gilad-kahn/projects/final_project/framework/test/*.cpp)
TEST_PATH = /home/shikamaru/Desktop/git/gilad-kahn/projects/final_project/framework/test/
HEADER = -I/home/shikamaru/Desktop/git/gilad-kahn/projects/final_project/framework/include
CC = g++
CFLAGS = -std=c++11 -pedantic-errors -Wall -pthread
DYNAMIC_LIBRARY = -c -fPIC
DEBUG = -Wextra -g
LINK= -L$(FULL_PATH) -Wl,-rpath=$(FULL_PATH)
REALESE = -DNDEBUG -O3
OBJ_CREATE = -c
FOLDER=$(shell basename $(CURDIR))
SRCs=$(wildcard /home/shikamaru/Desktop/git/gilad-kahn/projects/final_project/framework/src/**/*.cpp)
OBJs=$(wildcard /home/shikamaru/Desktop/git/gilad-kahn/projects/final_project/framework/src/*.o)


all: libfinal_project.so $(TESTS_REALESE) $(TESTS_DEBUG)
	make $(TESTS_REALESE) && make $(TESTS_DEBUG)


$(TESTS_REALESE): $(TESTS_REALESE) libfinal_project.so
	cp $(TESTS_REALESE) $(FULL_PATH)
	$(CC) $(CFLAGS) $(REALESE) $(HEADER) -L$(FULL_PATH) -Wl,-rpath=$(FULL_PATH) -o $@.out $@ -lfinal_project
	rm $(FULL_PATH)*.cpp
	mv $@.out $(FULL_PATH)


$(TESTS_DEBUG): $(TESTS_DEBUG) libfinal_project.so
	cp $(TESTS_DEBUG) $(FULL_PATH)
	$(CC) $(CFLAGS) $(DEBUG) $(HEADER) -L$(FULL_PATH) -Wl,-rpath=$(FULL_PATH) -o $@.out $@ -lfinal_project
	rm $(FULL_PATH)*.cpp
	mv $@.out $(FULL_PATH)

libfinal_project.so: $(OBJs)
	$(CC) $(CFLAGS) $(HEADER) $(OBJs) -shared -o $@ -DSHARED


create_o_files: $(SRCs)
	$(CC) $(HEADER) $(CFLAGS)  $(DEBUG) -c -fPIC $(SRCs)
	
clean:
	rm *.out *.o









#$(TESTS_OUT): $ libdata_structs.so
#	$(CC) $(CFLAGS) $(HEADER) $(TESTS) -o $@ -L$(FULL_PATH) -Wl,-rpath=$(FULL_PATH) -ldata_structs






