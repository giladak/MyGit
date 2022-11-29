

INCLUDE = -I/home/koko/Desktop/git/gilad-kahn/ds/include
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
GD = gcc -ansi -pedantic-errors -Wall -Wextra -g
GC = gcc -ansi -pedantic-errors -Wall -DNDEBUG -O3 
GDOBJ = gcc -ansi -pedantic-errors -Wall -Wextra -g -c  
GCOBJ =gcc -ansi -pedantic-errors -Wall -Wextra -g -c
OBJs =  uid_test.o uid.o 


uid.out: $(OBJs)
	$(CC) $(CFLAGS) $(OBJs)  -o uid.out 
		
uid_test.o: ../../test/uid_test.c 
	$(GCOBJ) $(INCLUDE)  ../../test/uid_test.c 
	
uid.o: uid.c
	$(GCOBJ) $(INCLUDE) uid.c
	
debug: uid.c ../../test/uid_test.c 
	$(GD) $(INCLUDE) uid.c ../../test/uid_test.c 

relese: uid.c ../../test/uid_test.c 
	$(GC) $(INCLUDE) uid.c ../../test/uid_test.c 

clean:
	rm *.out
	


