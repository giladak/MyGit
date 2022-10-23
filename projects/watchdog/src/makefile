INCLUDE = -I /home/koko/Desktop/git/gilad-kahn/ds/include
INCLUDE_PROJECT = -I/home/shikamaru/Desktop/git/gilad-kahn/projects/watchdog/include
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra
GD = gcc -ansi -pedantic-errors -Wall -Wextra -g
GC = gcc -ansi -pedantic-errors -Wall -DNDEBUG -O3 
GDOBJ = gcc -ansi -pedantic-errors -Wall -Wextra -g -c  
GCOBJ =gcc -ansi -pedantic-errors -Wall -Wextra -g -c
FULL_PATH = /home/shikamaru/Desktop/git/gilad-kahn/projects/watchdog/src/
FULL_PATH_TEST = /home/shikamaru/Desktop/git/gilad-kahn/projects/watchdog/test/
FULL_PATH_DS = /home/koko/Desktop/git/gilad-kahn/ds/src/
OBJs = watchdog_test.o watchdog.o watchdog_funcs.o
RELESE_OBJs = watchdog_test_relese.o watchdog_relese.o watchdog_funcs_relese.o
DATA_LIBRARY = -L$(FULL_PATH_DS) -Wl,-rpath=$(FULL_PATH_DS) -o $@ -ldata_structs

	
	
	
	
	
	

		
debug: $(FULL_PATH_TEST)watchdog_test.c libwatchdog.so watchdog.out
	$(GD) $(INCLUDE_PROJECT)  $(FULL_PATH_TEST)watchdog_test.c -pthread -o watchdog_test.out -L$(FULL_PATH) -Wl,-rpath=$(FULL_PATH) -lwatchdog $(DATA_LIBRARY)
	
watchdog.out: watchdog.c libwatchdog.so
	$(GD) $(INCLUDE_PROJECT) watchdog.c -pthread -L$(FULL_PATH) -Wl,-rpath=$(FULL_PATH) -o $@   -lwatchdog $(DATA_LIBRARY)
	chmod 755 watchdog.out

libwatchdog.so: watchdog_funcs.o 
	$(GD) watchdog_funcs.o -pthread -shared -o $@  

watchdog_funcs.o: watchdog_funcs.c
	$(GD) $(INCLUDE_PROJECT) -pthread watchdog_funcs.c -o $@ -c -fPIC $(DATA_LIBRARY)



relese: $(FULL_PATH_TEST)watchdog_test.c libwatchdog_relese.so watchdog_relese.out
	$(GC) $(INCLUDE_PROJECT)  $(FULL_PATH_TEST)watchdog_test.c -pthread -o $@ -L$(FULL_PATH) -Wl,-rpath=$(FULL_PATH) -lwatchdog $(DATA_LIBRARY)
	
watchdog_relese.out: watchdog.c libwatchdog_relese.so
	$(GC) $(INCLUDE_PROJECT) watchdog.c -pthread -L$(FULL_PATH) -Wl,-rpath=$(FULL_PATH) -o watchdog_test_relese.out  -lwatchdog $(DATA_LIBRARY)
	chmod 755 watchdog.out

libwatchdog_relese.so: watchdog_funcs_relese.o 
	$(GC) watchdog_funcs.o -pthread -shared -o $@  

watchdog_funcs_relese.o: watchdog_funcs.c
	$(GC) $(INCLUDE_PROJECT) -pthread watchdog_funcs.c -o $@ -c -fPIC $(DATA_LIBRARY)







#task.o: $(FULL_PATH_DS)scheduler/task.c
#scheduler.o: $(FULL_PATH_DS)scheduler/task.c

#debug: watchdog.c ../../test/watchdog_test.c 
#	$(GD) $(INCLUDE) watchdog.c ../../test/watchdog_test.c 

#relese: watchdog.c ../../test/watchdog_test.c 
#	$(GC) $(INCLUDE) watchdog.c ../../test/watchdog_test.c 

clean:
	rm *.out
	


