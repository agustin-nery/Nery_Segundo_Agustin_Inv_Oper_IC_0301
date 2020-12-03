/**
*@file prueba.c
*@version 1.0
*@date 01/12/2020
*@author NerySegundoAgustin
*@title prueba del programa
*/
#include <stdio.h>
#include "matriz.h"

_Bool checkParticularSolution(matrix *A, matrix *xp, matrix *b);
_Bool checkNullspaceSolution(matrix *A, matrix *xn);

int main()
{
/* El probador solo funciona si INTERACTIVO no está definido y FILE_IN sí.
     Esto se debe a que las declaraciones de impresión INTERACTIVAS también se imprimen en la salida */
#ifdef FILE_IN
    FILE *fin, *fout, *fp;
    int t, m, n, mn, nn;
    char solution[100], dummy[100];
    int i, dummyI;
    matrix *A, *xn, *xp, *b;
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "r");
    fp = fopen("resultados.txt", "w");
    fscanf(fin, "%d", &t);
    for (i = 0; i < t; i++)
    {
        fprintf(fp, "Test %d: \n", i + 1);
        fscanf(fin, "%d %d", &m, &n);
        fscanf(fout, "%s %d", dummy, &dummyI);
        A = newMatrix(m, n);
        readMatrix(A, fin);
        b = newMatrix(m, 1);
        readMatrix(b, fin);
        fscanf(fout, "%s", solution);
        if (strcmp(solution, "Sin solución") == 0)
        {
            fprintf(fp, "bien: no hay solución\n");
            continue;
        }
        fscanf(fout, "%s", dummy);
        xp = newMatrix(n, 1);
        readMatrix(xp, fout);
        if (checkParticularSolution(A, xp, b))
        {
            fprintf(fp, "bien: xp\n");
        }
        else
        {
            fprintf(fp, "ERROR: no coincide\n");
        }
        if (!strcmp(solution, "Solución única"))
        {
            continue;
        }
        fscanf(fout, "%s", dummy);
        fscanf(fout, "%d %d", &mn, &nn);
        xn = newMatrix(mn, nn);
        readMatrix(xn, fout);
        if (checkNullspaceSolution(A, xn))
        {
            fprintf(fp, "bien: xn\n");
        }
        else
        {
            fprintf(fp, "ERROR: no coincide\n");
        }
    }
    fclose(fin);
    fclose(fout);
    fclose(fp);
#endif
    return 0;
}

_Bool checkParticularSolution(matrix *A, matrix *xp, matrix *b)
{
    int i, j;
    double ans;
    _Bool flag = true;
    for (i = 0; i < A->rows; i++)
    {
        ans = 0;
        for (j = 0; j < A->cols; j++)
        {
            ans += ((A->data[i][j]) * (xp->data[j][0]));
        }
        flag = flag && isZero(ans - b->data[i][0], 1e-3);
    }
    return flag;
}

_Bool checkNullspaceSolution(matrix *A, matrix *xn)
{
    int i, j, k;
    double ans;
    _Bool flag = true;
    for (k = 0; k < xn->cols; k++)
    {
        for (i = 0; i < A->rows; i++)
        {
            ans = 0;
            for (j = 0; j < A->cols; j++)
            {
                ans += ((A->data[i][j]) * (xn->data[j][k]));
            }
            flag = flag && isZero(ans, 1e-3);
        }
    }
    return flag;
}
