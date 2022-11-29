INCLUDE = -I /home/koko/Desktop/git/gilad-kahn/ds/include
INCLUDE_SYSTEM = -I /home/shikamaru/Desktop/git/gilad-kahn/ds/include
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra
GD = gcc -ansi -pedantic-errors -Wall -Wextra -g
GC = gcc -ansi -pedantic-errors -Wall -DNDEBUG -O3 
GDOBJ = gcc -ansi -pedantic-errors -Wall -Wextra -g -c  
GCOBJ =gcc -ansi -pedantic-errors -Wall -Wextra -g -c
FULL_PATH = /home/koko/Desktop/git/gilad-kahn/system_programing/src/watchdog/
FULL_PATH_DS = /home/koko/Desktop/git/gilad-kahn/ds/src/

OBJs =  watchdog_test.o watchdog.o watchdog_funcs.o

		
watchdog_test.out: watchdog_test.c 
	$(GD) $(INCLUDE_SYSTEM)  watchdog_test.c -o $@ -L$(FULL_PATH) -Wl,-rpath=$(FULL_PATH) -o $@.out $@ -lwatchdog 
	
watchdog.out: watchdog.c
	$(GCOBJ) $(INCLUDE_SYSTEM) watchdog.c -L$(FULL_PATH) -Wl,-rpath=$(FULL_PATH) -o $@.out $@ -lwatchdog


libwatchdog.so: watchdog_funcs.o watchdog.h
	$(GD) watchdog_funcs.o -shared -o $@  

watchdog_funcs.o: watchdog_funcs.c
	$(GD) $(INCLUDE_SYSTEM)  watchdog_funcs.c -o $@	-c -fPIC -L$(FULL_PATH_DS) -Wl,-rpath=$(FULL_PATH_DS) $@ -ldata_structs



#debug: watchdog.c ../../test/watchdog_test.c 
#	$(GD) $(INCLUDE) watchdog.c ../../test/watchdog_test.c 

#relese: watchdog.c ../../test/watchdog_test.c 
#	$(GC) $(INCLUDE) watchdog.c ../../test/watchdog_test.c 

clean:
	rm *.out
	


