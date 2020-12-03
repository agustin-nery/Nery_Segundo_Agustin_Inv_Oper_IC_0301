/**
* @file simplex.c
* @brief Fichero principal
* @par  Objetivo
* -el simplex.c tiene el objetivo de contener las funciones utilizadas en el programa
* -aqui se resguardan las funciones simplex,Pivot,Optimize,Results.
* @autor Nery Segundo Agustin
* @date 2020-12-01
* @title funciones independientes del programa.
*/
#include "simplex.h"
/**
* @brief Funciones  principales del programa simplex
* @par
*
* @param void
* @return 0
* @todo
*/
void Simplex() {
e10: Pivot();
Formula();
Optimize();

if (NOPTIMAL == 1) goto e10;
}

/**
* @brief Funcion pivote
* @param void
* @return el pivote obtenido de las restricciones del programa.
* @todo se hace uso de las variables obtenidas de las restricciones.
*/
void Pivot() {
double RAP,V,XMAX;
int I,J;
XMAX = 0.0;


for(J=2; J<=NV+1; J++) {
if (TS[1][J] > 0.0 && TS[1][J] > XMAX) {
XMAX = TS[1][J];
P2 = J;
}
}
RAP = 999999.0;


for (I=2; I<=NC+1; I++) {
if (TS[I][P2] >= 0.0) goto e10;
V = fabs(TS[I][1] / TS[I][P2]);
if (V < RAP) {
RAP = V;
P1 = I;
}
e10:;}
V = TS[0][P2]; TS[0][P2] = TS[P1][0]; TS[P1][0] = V;
}

/**
* @brief Funcion formula
* @param void
* @return resultado de la tabla aplicando la formula.
* @todo nos sirve para ingresar los datos y de esa manera sustituirlos en la formula para calcular el metodo simplex.
*/
void Formula() {;
int I,J;
for (I=1; I<=NC+1; I++) {
if (I == P1) goto e70;
for (J=1; J<=NV+1; J++) {
if (J == P2) goto e60;
TS[I][J] -= TS[P1][J] * TS[I][P2] / TS[P1][P2];
e60:;}
e70:;}
TS[P1][P2] = 1.0 / TS[P1][P2];


for (J=1; J<=NV+1; J++) {
if (J == P2) goto e100;
TS[P1][J] *= fabs(TS[P1][P2]);
e100:;}


for (I=1; I<=NC+1; I++) {
if (I == P1) goto e110;
TS[I][P2] *= TS[P1][P2];
e110:;}
}


/**
* @brief Funcion de optimizaciones
* @param void
* @todo nos sirve para obtener la optimizacion de los datos de la tabla de las restricciones.
*/
void Optimize() {
int I,J;
for (I=2; I<=NC+1; I++)
if (TS[I][1] < 0.0) XERR = 1;
NOPTIMAL = 0;
if (XERR == 1) return;
for (J=2; J<=NV+1; J++)
if (TS[1][J] > 0.0) NOPTIMAL = 1;
}

/**
* @brief Funcion para los resultados.
* @param void
* @return resultado de la tabla Simplex
* @todo esta funcion nos ayuda a saber el resultado de la optimizacion de el proseso de el metodo simplex.
*/
void Results() {
int I,J;
if (XERR == 0) goto e30;
printf(" solucion \n"); goto e100;
e30:for (I=1; I<=NV; I++)
for (J=2; J<=NC+1; J++) {
if (TS[J][0] != 1.0*I) goto e70;
printf(" la solucion es la #%d variable: %f\n", I, TS[J][1]);
e70: ;}
printf("\n Resultado de la funcion : %f\n", TS[1][1]);
e100:printf("\n");
}


void main() {
Data();
Simplex();
Results();
}
