/**
* @file aplicacion.c
* @brief Fichero principal
* @par  Objetivo
* -aplicacion.c  tiene como objetivo almacenar las declaraciones de las matrices en el programa
* -aqui se resguardan las funciones utilizadas en el programa.
* @autor Nery Segundo Agustin
* @date 2020-12-01
* @title aplicacion.c
*/}
#include <stdio.h>
#include "matriz.h"

int main()
{
    int t, m, n, z;
    matrix *A, *xp, *xn, *b;
#ifdef FILE_IN
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
#ifndef FILE_IN
    printf("Ingrese el número de casos de prueba: ");
#endif
    scanf("%d", &t);
    for (z = 0; z < t; z++)
    {
#ifndef FILE_IN
        printf("Introduzca m y n : ");
#endif
        scanf("%d %d", &m, &n);
        printf("Test %d\n", z + 1);
        A = newMatrix(m, n);
#ifndef FILE_IN
        printf("Ingresa A: \n");
#endif
        readMatrix(A, stdin);
        b = newMatrix(m, 1);
#ifndef FILE_IN
        printf("ingresa b: \n");
#endif
        readMatrix(b, stdin);
        rref(A, b);
#ifdef DEBUG_MAIN
        printMatrix(A);
        printMatrix(b);
#endif
        if (!solutionExists(A, b))
        {
            printf("no hay solucion\n");
            continue;
        }
#ifdef DEBUG_MAIN
        printMatrix(A);
        printMatrix(b);
#endif
        xp = particularSolution(A, b);
        xn = nullspaceSolution(A);
        if (xn != NULL)
        {
            printf("Soluciones infinitas\n");
            printf("Solución particular:\n");
            printMatrix(xp);
            printf("Espacio nulo:\n");
            printf("%d %d\n", xn->rows, xn->cols);
            printMatrix(xn);
            continue;
        }
        printf("Solución única\n");
        printf("Solución particular:\n");
        printMatrix(xp);
        printf("\n");
        free(A);
        free(b);
        free(xp);
        free(xn);
    }
    return 0;
}
