
#ifndef KNGHITS_TOUR_H
#define KNGHITS_TOUR_H


#include <stdio.h> /*ssize_t*/
#include <stddef.h>
#include <unistd.h> /*ssize_t*/

#define ROW 8
#define COL 8
#define NUM_OF_CELLS ROW*COL
#define KNIGHT_MOVES 8

typedef struct cell cell_t;


int GetPathWithBackTrace(size_t *array_answer, size_t start_point_row, size_t start_point_col);

int GetPathWithWarndorffs(size_t *array_answer, size_t start_point_row, size_t start_point_col);

size_t CalculateTotalIndex(size_t row, size_t col);






#endif /*KNGHITS_TOUR_H*/