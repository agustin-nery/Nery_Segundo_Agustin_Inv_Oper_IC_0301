/**
* @file matriz.h
* @brief Fichero principal
* @par  Objetivo
* -matriz.h tiene como objetivo almacenar las funciones utilizadas en el programa de ecuaciones lineales
* -aqui se resguardan las funciones utilizadas en el programa.
* @autor Nery Segundo Agustin
* @date 2020-12-01
* @title funciones independientes del programa.
*/
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/* Macros */
#define _Bool int
#define true 1
#define false 0

/**
* @brief Funciones para la pila
* @par Funciones para la pila utilizadas para deshacer intercambios de columnas
* para encontrar espacio nulo
* @param void
* @return 0
* @todo
*/

#define push(sp, n) (*((sp)++) = (n))
#define pop(sp) (*--(sp))
#define STACKSIZE 1000

/* Encapsulando la matriz en una estructura */
typedef struct
{
    int rows, cols;
    double **data;
} matrix;

/* Declaraciones de funciones */
int min(int a, int b);
matrix *newMatrix(int rows, int cols);
void readMatrix(matrix *m, FILE *fp);
void printMatrix(matrix *m);
void copyMatrix(matrix *d, matrix *s);
matrix *addMatrix(matrix *m1, matrix *m2, _Bool opcode);
void switchRows(matrix *m, int row1, int row2);
void switchColumns(matrix *m, int col1, int col2);
void rref(matrix *A, matrix *b);
_Bool solutionExists(matrix *R, matrix *b);
matrix *particularSolution(matrix *R, matrix *b);
matrix *nullspaceSolution(matrix *R);
_Bool isZero(double a, double threshold);

int min(int a, int b)
{
    return (a < b) ? a : b;
}

/**
* @brief Funciones para agregar una nueva matriz
* @par estructura de matriz
* para encontrar espacio nulo
* @param void
* @return  Devuelve un puntero a una estructura de matriz después de asignar el espacio apropiado para los datos
* @todo
*/
matrix *newMatrix(int rows, int cols)
{
    int i;
    matrix *m = (matrix *)malloc(sizeof(matrix));
    m->rows = rows;
    m->cols = cols;
    m->data = (double **)calloc(rows, sizeof(double *));
    for (i = 0; i < rows; i++)
    {
        m->data[i] = (double *)calloc(cols, sizeof(double));
    }
    return m;
}


/**
* @brief Funcion leer matriz
* @par estructura de matriz
*  Leer datos en una matriz desde un puntero de archivo (stdin para consola)
* @param void
*/

void readMatrix(matrix *m, FILE *fp)
{
    int row, col;
    for (row = 0; row < m->rows; row++)
    {
        for (col = 0; col < m->cols; col++)
        {
            fscanf(fp, "%lf", &(m->data[row][col]));
        }
    }
}

/**
* @brief Funcion para imprimir matriz
* @par estructura de matriz
* Imprimir una matriz
* @param void
* @return  Imprimir contenido de una matriz
* @todo
*/
void printMatrix(matrix *m)
{
    int row, col;
    for (row = 0; row < m->rows; row++)
    {
        for (col = 0; col < m->cols; col++)
        {
            printf("%f ", m->data[row][col]);
        }
        /*        printf("%lf", m->data[row][m->cols - 1]); */
        printf("\n");
    }
}

/**
* @brief Funcion para cambiar dos filas de la matriz
* @par estructura de matriz
* Cambiar dos filas: fila1 y fila 2
* @param void
* @return  Cambiar dos filas: fila1 y fila 2
* @todo
*/
void switchRows(matrix *m, int row1, int row2)
{
    double *arr = calloc(m->cols, sizeof(double));
    int i;
    if (row1 >= m->rows || row2 >= m->rows)
    {
        printf("¡Cambio de fila no válido!\n");
        return;
    }
    for (i = 0; i < m->cols; i++)
    {
        arr[i] = m->data[row1][i];
    }
    for (i = 0; i < m->cols; i++)
    {
        m->data[row1][i] = m->data[row2][i];
    }
    for (i = 0; i < m->cols; i++)
    {
        m->data[row2][i] = arr[i];
    }
    free(arr);
}


/**
* @brief Funcion para cambiar dos columnas de la matriz
* @par estructura de matriz
* Cambiar dos columnas: col1 y col2
* @param void
* @return  Cambiar dos columnas: col1 y col2
* @todo
*/
void switchColumns(matrix *m, int col1, int col2)
{
    double *arr = calloc(m->rows, sizeof(double));
    int i;
    if (col1 == col2)
    {
        return;
    }
    if (col1 >= m->cols || col2 >= m->cols)
    {
        printf("Cambio de columna no válido\n");
        return;
    }
    for (i = 0; i < m->rows; i++)
    {
        arr[i] = m->data[i][col1];
    }
    for (i = 0; i < m->rows; i++)
    {
        m->data[i][col1] = m->data[i][col2];
    }
    for (i = 0; i < m->rows; i++)
    {
        m->data[i][col2] = arr[i];
    }
    free(arr);
}


/**
* @brief Funcion para Convertir una matriz a forma real
* @par estructura de matriz
* @param void
* @return  Convertir una matriz a forma real
* @todo
*/
void rref(matrix *A, matrix *b)
{
    int pivotRow = 0;
    int pivotCol = 0;
    int j;
    int switchRow;
    double r;
    int k;
    double quotient;
    /* Convertir a triangular superior */
    while (pivotRow < A->rows && pivotCol < A->cols)
    {
        switchRow = -1;
        if (isZero(A->data[pivotRow][pivotCol], 1e-3))
        {
#ifdef DEBUG_RREF
            printf("Cero en: %d %d\n", pivotRow, pivotCol);
#endif
            for (j = pivotRow + 1; j < A->rows; j++)
            {
                if (!isZero(A->data[j][pivotCol], 1e-3))
                {
                    switchRow = j;
#ifdef DEBUG_RREF
                    printf("Cambiar %d %d\n", pivotRow, j);
#endif
                    switchRows(A, pivotRow, switchRow);
                    switchRows(b, pivotRow, switchRow);
                    break;
                }
            }
            if (switchRow == -1)
            {
#ifdef DEBUG_RREF
                printf("Sin cambio de fila: %d\n", pivotRow);
#endif
                pivotCol++;
                continue;
            }
        }
        for (j = pivotRow + 1; j < A->rows; j++)
        {
            if (!isZero(A->data[j][pivotCol], 1e-3))
            {
                r = A->data[j][pivotCol] / A->data[pivotRow][pivotCol];
#ifdef DEBUG_RREF
                printf("%d %d %d %lf %lf r : %lf\n\n", pivotRow, pivotCol, j, A->data[j][pivotCol], A->data[pivotRow][pivotCol], r);
#endif
                for (k = pivotCol; k < A->cols; k++)
                {
                    A->data[j][k] -= r * A->data[pivotRow][k];
                }
                b->data[j][0] -= r * b->data[pivotRow][0];
            }
#ifdef DEBUG_RREF
            printMatrix(A);
            printf("\n");
#endif
        }
        pivotRow++;
        pivotCol++;
    }
#ifdef DEBUG_RREF
    printf("A convertido a triangular superior: ");
    printMatrix(A);
    printMatrix(b);
#endif

    /*  Convertir a rref desde triangular superior
         Seleccione un pivote */
    pivotRow = 0;
    pivotCol = 0;
    while (pivotRow < A->rows && pivotCol < A->cols)
    {
        if (isZero(A->data[pivotRow][pivotCol], 1e-3))
        {
            pivotCol++;
            continue;
        }
        else
        {
            for (j = pivotRow - 1; j >= 0; j--)
            {
                r = A->data[j][pivotCol] / A->data[pivotRow][pivotCol];
#ifdef DEBUG_RREF
                printMatrix(A);
                printf("\n");
                printf("%d %d %d %lf %lf r : %lf\n\n", pivotRow, pivotCol, j, A->data[j][pivotCol], A->data[pivotRow][pivotCol], r);
                // printf("%d %d %lf %lf r : %lf\n", , j, A->data[j][i], A->data[i][i], r);
#endif
                /* Operaciones de fila */
                for (k = pivotCol; k < A->cols; k++)
                {
                    A->data[j][k] -= r * A->data[pivotRow][k];
                }
                b->data[j][0] -= r * b->data[pivotRow][0];
            }
        }
        pivotRow++;
        pivotCol++;
    }
    /* Hacer todos los elementos de pivote '1' */
    pivotRow = 0;
    pivotCol = 0;
    while (pivotRow < A->rows && pivotCol < A->cols)
    {
        if (isZero(A->data[pivotRow][pivotCol], 1e-3))
        {
            pivotCol++;
            continue;
        }
        quotient = A->data[pivotRow][pivotCol];
        for (j = pivotCol; j < A->cols; j++)
        {
            if (A->data[pivotRow][j])
                A->data[pivotRow][j] /= quotient;
        }
        if (b->data[pivotRow][0])
            b->data[pivotRow][0] /= quotient;
        pivotRow++;
        pivotCol++;
    }
}

/**
* @brief Funcion para comprobar si hay inconsistencias
* @par estructura de matriz
* @param void
* @return inconsistencias en Rx = b
* @todo
*/
_Bool solutionExists(matrix *R, matrix *b)
{
    int i, j;
    _Bool zeroFlag;
    for (i = 0; i < R->rows; i++)
    {
        zeroFlag = true;
        for (j = 0; j < R->cols; j++)
        {
            if (!isZero(R->data[i][j], 1e-3))
            {
                zeroFlag = false;
                break;
            }
        }
        if (zeroFlag)
        {
            if (!isZero(b->data[i][0], 1e-3))
            {
                return false;
            }
        }
    }
    return true;
}


/**
* @brief Funcion para Deducir una solución particular
* @par Deducir una solución particular de la matriz escalonada de filas reducida con elementos de pivote 1*
* @param void
* @return la matriz escalonada de filas reducida con elementos de pivote 1
* @todo
*/
matrix *particularSolution(matrix *R, matrix *b)
{
    matrix *xp = newMatrix(R->cols, 1);
    int pivotRow = 0, pivotCol = 0;
    while (pivotRow < R->rows && pivotCol < R->cols)
    {
        if (!R->data[pivotRow][pivotCol])
        {
            pivotCol++;
            continue;
        }
        xp->data[pivotCol][0] = b->data[pivotRow][0] / R->data[pivotRow][pivotCol];
#ifdef DEBUG_PS
        printf("%d %d\n", pivotRow, pivotCol);
#endif
        pivotRow++;
        pivotCol++;
    }
#ifdef DEBUG_PS
    printf("Solución particular calculada\n");
#endif
    return xp;
}


/**
* @brief Compruebe si un número es aproximadamente cero, hasta un umbral. Se usa para lidiar con problemas de precisión
*/
_Bool isZero(double a, double threshold)
{
    if (a >= -threshold && a <= threshold)
    {
        return true;
    }
    return false;
}

/**
* @brief Funcion para Deducir la solución de espacio nulo
* @par Deducir la solución de espacio nulo de una matriz rref *
* @param void
* @return una matriz rref
* @todo
*/
matrix *nullspaceSolution(matrix *R)
{
#ifdef DEBUG_NS
    printf("Calcular la solución de espacio nulo\n");
#endif
    int maxPivots = min(R->rows, R->cols);
    int stackA[STACKSIZE], stackB[STACKSIZE];
    int *sA, *sB;
    int length = 0;
    int pivots = 0;
    int i, j, i1, j1;
    matrix *xn;
    int Frows, Fcols;
    sA = stackA;
    sB = stackB;
    /* Traiga los pivotes a la diagonal, si no están */
    for (i = 0; i < maxPivots; i++)
    {
#ifdef DEBUG_NS
        printf("%lf\n", R->data[i][i]);
#endif
        if (isZero(R->data[i][i], 1e-3))
        {

            for (j = i + 1; j < R->cols; j++)
            {
                if (!isZero(R->data[i][j], 1e-3))
                {
                    /* Si se requiere el intercambio de columnas, empuje los índices en pilas,
                         para que se puedan deshacer */
                    push(sA, i);
                    push(sB, j);
                    length++;
#ifdef DEBUG_NS
                    printf("%d %d\n", i, j);
#endif
                    /* Cambiar las columnas apropiadas */
                    switchColumns(R, i, j);
                    pivots++;
                    break;
                }
            }
        }
        else
        {
            pivots++;
        }
    }
#ifdef DEBUG_NS
    printf("%d", pivots);
    printf("R conmutado: \n");
    printMatrix(R);
    printf("Max y pivotes: %d %d\n", maxPivots, pivots);
#endif
    if (R->cols == pivots)
    {
#ifdef DEBUG_NS
        printf("Devolviendo NULL");
#endif
        return NULL;
    }

    /* Las dimensiones de la matriz base del espacio nulo se pueden determinar ahora */
    xn = newMatrix(R->cols, R->cols - pivots);
    Frows = pivots, Fcols = R->cols - pivots;

    /* Copie '-F' a la nueva matriz */
    for (i = 0; i < Frows; i++)
    {
        for (j = 0; j < Fcols; j++)
        {
            xn->data[i][j] = -(R->data[i][pivots + j]);
        }
    }

    /* Llene el espacio restante con 'I' */
    i1 = 0;
    for (i = Frows; i < xn->rows; i++, i1++)
    {
        j1 = 0;
        for (j = 0; j < xn->cols; j++, j1++)
        {
            if (i1 == j1)
                xn->data[i][j] = 1;
            else
                xn->data[i][j] = 0;
        }
    }

    /* Cambie las filas en xn en el orden inverso de los cambios de columna realizados en A.
         La pila es el último en entrar, primero en salir */
    while (length--)
    {
        switchRows(xn, pop(sA), pop(sB));
    }
    return xn;
}
