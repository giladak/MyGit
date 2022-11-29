

#include <stdio.h> /*for*/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/

#include "utilities.h"


#include "knights_tour.h"


struct cell
{
    int row;
    int col;
}; 

static int IsInvalid(int row, int col);
static void PrintMovesLut(void);
static void InitilizeLut(void);
static size_t ConvertCellToTotalIndex(cell_t *cell);
static size_t ConvertTwoIndexTototalIndex(size_t row, size_t col);
static int CalculateNextBackTarce(size_t *array_answer, size_t moves, size_t current_row, size_t current_col);
static int CalculateNextWarndorffs(size_t *array_answer, size_t moves, size_t current_row, size_t current_col);
static void PrintBoard ();
static size_t CountOptions (cell_t *cell);
/**********************matrizas**********************/
static cell_t moves_lut[NUM_OF_CELLS][KNIGHT_MOVES];
static int chess_board[ROW][COL] = {0};


/****************backtrace*************/

int GetPathWithBackTrace(size_t *array_answer, size_t start_point_row, size_t start_point_col)
{   
    size_t moves = 0;
    int success = 0;

    InitilizeLut();
  
    assert(array_answer);

    success = CalculateNextBackTarce(array_answer, moves, start_point_row, start_point_col);

    PrintBoard();

    return(success);  
}

/****************wardorffs*************/

int GetPathWithWarndorffs(size_t *array_answer, size_t start_point_row, size_t start_point_col)
{   
    size_t moves = 0;
    int success = 0;

    assert(array_answer);

    InitilizeLut();

    PrintMovesLut();

    success = CalculateNextWarndorffs(array_answer, moves, start_point_row, start_point_col);

    PrintBoard();

    return(success);  
}



/**************************help functions*****************/

int CalculateNextWarndorffs(size_t *array_answer, size_t moves, size_t current_row, size_t current_col)
{
    int success = 0;
    size_t total_index = 0;
    size_t try_num = 0;
    size_t i = 0;
    size_t array[KNIGHT_MOVES] = {1 , 2, 3, 4, 5, 6, 7, 0};

    if (NUM_OF_CELLS == moves)
    {
        return(0);
    } 

    if (EMPTY != chess_board[current_row][current_col])
    {
        return(FAIL);
    }

    total_index = ConvertTwoIndexTototalIndex(current_row, current_col);
    array_answer[moves] = total_index;
    chess_board[current_row][current_col] = FULL;
    ++moves;

    success = FAIL; /*for loop*/

    for (i = 0; i < KNIGHT_MOVES && FAIL == success; ++i)
    {
        for (try_num = 0; KNIGHT_MOVES > try_num && moves_lut[total_index][try_num].row != -1 && FAIL == success; ++try_num)
        {   
            if (array[i] == CountOptions(&moves_lut[total_index][try_num]))
            {
                success = CalculateNextWarndorffs(array_answer, moves, moves_lut[total_index][try_num].row, moves_lut[total_index][try_num].col);
            }
        }
    }

    if (FAIL == success)
    {
        chess_board[current_row][current_col] = EMPTY;
        --moves;
        array_answer[moves] = NUM_OF_CELLS;
        return(FAIL);
    }

    return(success);
}


int CalculateNextBackTarce(size_t *array_answer, size_t moves, size_t current_row, size_t current_col)
{
    int success = 0;
    size_t total_index = 0;
    size_t try_num = 0;

    if (NUM_OF_CELLS == moves)
    {
        return(success);
    }

    if (EMPTY != chess_board[current_row][current_col])
    {
        return(FAIL);
    }

    total_index = ConvertTwoIndexTototalIndex(current_row, current_col);
    array_answer[moves] = total_index;
    chess_board[current_row][current_col] = FULL;
    ++moves;

    success = FAIL; /*for loop*/

    while (KNIGHT_MOVES > try_num && moves_lut[total_index][try_num].row != -1 && FAIL == success)
    {   
        success = CalculateNextBackTarce(array_answer, moves, moves_lut[total_index][try_num].row, moves_lut[total_index][try_num].col);
        ++try_num;
    }


    if (FAIL == success)
    {
        chess_board[current_row][current_col] = EMPTY;
        --moves;
        array_answer[moves] = NUM_OF_CELLS;
        return(FAIL);
    }

    return(success);
}

void InitilizeLut(void)
{

    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    size_t lut_index = 0;

    for (i = 0; i < NUM_OF_CELLS; ++i)
    {
        for (j = 0; j < KNIGHT_MOVES; ++j)
        {
            moves_lut[i][j].row = -1;
            moves_lut[i][j].col = -1;
        }
    }

    for (i = 0; i < ROW; ++i)
    {
        for (j = 0; j < COL; ++j)
        {
            
            k = 0;
            lut_index = ConvertTwoIndexTototalIndex(i, j);

            if (TRUE == IsInvalid(i - 2, j-1))
            {   
                moves_lut[lut_index][k].row = i - 2;
                moves_lut[lut_index][k].col = j - 1;
                ++k;
            }


            if (TRUE == IsInvalid(i - 2, j+1))
            {
                moves_lut[lut_index][k].row = i - 2;
                moves_lut[lut_index][k].col = j+1;
                ++k;
            }


            if (TRUE == IsInvalid(i - 1, j + 2))
            {
                moves_lut[lut_index][k].row = i - 1;
                moves_lut[lut_index][k].col = j + 2;
                ++k;
            }

            if (TRUE == IsInvalid(i + 1, j + 2))
            {
                moves_lut[lut_index][k].row = i + 1;
                moves_lut[lut_index][k].col = j + 2;
                ++k;
            }

            if (TRUE == IsInvalid(i + 2, j + 1))
            {
                moves_lut[lut_index][k].row = i + 2;
                moves_lut[lut_index][k].col = j + 1;
                ++k;
            }

            if (TRUE == IsInvalid(i + 2, j - 1))
            {
                moves_lut[lut_index][k].row = i + 2;
                moves_lut[lut_index][k].col = j - 1;
                ++k;
            }


            if (TRUE == IsInvalid(i + 1, j - 2))
            {
                moves_lut[lut_index][k].row = i + 1;
                moves_lut[lut_index][k].col = j - 2;
                ++k;
            }



            if (TRUE == IsInvalid(i - 1, j - 2))
            {
                moves_lut[lut_index][k].row = i - 1;
                moves_lut[lut_index][k].col = j - 2;
                ++k;
            }
        }    
    }
}


int IsInvalid(int row, int col)
{
    return(row < ROW && 0 <= row && 0 <= col && col < COL);
}

void PrintMovesLut(void)
{
    size_t i = 0;
    size_t j = 0;

    for (i = 0; i < NUM_OF_CELLS; ++i)
    {   
        j = 0;

        printf ("moves for cell %ld: \n", i);

        while (-1 != moves_lut[i][j].row && j < KNIGHT_MOVES)
        {
            printf("r%d c%d    ",moves_lut[i][j].row, moves_lut[i][j].col);
            ++j;
        }

        printf ("total moves : %ld \n", j);

    }

}


static size_t ConvertCellToTotalIndex(cell_t *cell)
{
    size_t index = cell->row*ROW + cell->col;

    return (index);
}

static size_t ConvertTwoIndexTototalIndex(size_t row, size_t col)
{
    size_t index = row*ROW + col;

    return(index);
}

void PrintBoard ()
{
    size_t i = 0;
    size_t j = 0;

    for (i = 0; i< ROW; ++i)
    {
        for (j = 0; j < COL; ++j)
        {
            printf("%d  ", chess_board[i][j]);
        }
         printf("\n");
    }
}


static size_t CountOptions (cell_t *cell)
{
    size_t total_index = 0;
    int options_num = 0;    
    size_t i = 0;

    total_index = ConvertCellToTotalIndex(cell);

    while (-1 != moves_lut[total_index][i].row && KNIGHT_MOVES > i)
    {
        if (EMPTY == chess_board[moves_lut[total_index][i].row][moves_lut[total_index][i].col])
        {
            ++options_num;
        }

        ++i;
    }

    return(options_num);
}

