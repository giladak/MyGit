
typedef struct calculator calc_t;

typedef enum 
{
    SUCCESS,
    MATH_ERROR,
    SYNTAX_ERROR,
    PENDING
} status_t;

calc_t *CalcInit(size_t max_length);
void CalcDestroy(calc_t *calc);
double CalcCalculate(const char *str, status_t *status, calc_t *calc);