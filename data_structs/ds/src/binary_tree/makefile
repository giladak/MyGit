INCLUDE = -I/home/koko/Desktop/git/gilad-kahn/ds/include
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
GD = gcc -ansi -pedantic-errors -Wall -Wextra -g
GC = gcc -ansi -pedantic-errors -Wall -DNDEBUG -O3 
GDOBJ = gcc -ansi -pedantic-errors -Wall -Wextra -g -c  
GCOBJ =gcc -ansi -pedantic-errors -Wall -Wextra -g -c
OBJs =  binary_tree_test.o binary_tree.o 


binary_tree.out: $(OBJs)
	$(CC) $(CFLAGS) $(OBJs)  -o binary_tree.out 
		
binary_tree_test.o: ../../test/binary_tree_test.c 
	$(GCOBJ) $(INCLUDE)  ../../test/binary_tree_test.c 
	
binary_tree.o: binary_tree.c
	$(GCOBJ) $(INCLUDE) binary_tree.c
	
debug: binary_tree.c ../../test/binary_tree_test.c 
	$(GD) $(INCLUDE) binary_tree.c ../../test/binary_tree_test.c 

relese: binary_tree.c ../../test/binary_tree_test.c 
	$(GC) $(INCLUDE) binary_tree.c ../../test/binary_tree_test.c 

clean:
	rm *.out
	


