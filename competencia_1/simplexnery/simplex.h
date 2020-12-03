/**
* @file simplex.h
*@version 1.0
*@title aplicacion fuente de el programa
* @brief Fichero principal
* @par  salida del programa
* - primero nos pide que ingresemos a que numero queremos maximizar
* - despues nos pide el numero de variables de la funcion y el numero de restricciones
* - e ingresamos los datos para la tabla y estos serian todos los datos de entrada.
* @par Flujo
* @autor Nery Segundo Agustin
* @date 2020-12-01
*/
#ifndef __SIMPLEX_H
#define __SIMPLEX_H

#include <stdio.h>
#include <math.h>

#define CMAX 10
#define VMAX 10

int NC, NV, NOPTIMAL,P1,P2,XERR;
double TS[CMAX][VMAX];
void Data() {
double R1,R2;
char R;
int I,J;

printf("\n PROGRAMA PARA HACER EL\n");
printf("\n *** Metodo Simplex ***\n\n");
printf(" A quien deseas maximizar ---> "); scanf("%c", &R);
printf("\n Cual es el numero de variables de la funcion ---> ");
scanf("%d", &NV);
printf("\n Cual es el numero de restricciones---> "); scanf("%d", &NC);

if (R == 'Z' || R=='z')
R1 = 1.0;
else
R1 = -1.0;
printf("\n+ Ingresa los coeficientes de la funcion +\n");

for (J = 1; J<=NV; J++) {
printf(" #%d ? ", J); scanf("%lf", &R2);
TS[1][J+1] = R2 * R1;
}
printf(" Cual es R ---> "); scanf("%lf", &R2);
TS[1][1] = R2 * R1;


for (I = 1; I<=NC; I++) {
printf("\n Ingresa los datos de la restriccion #%d  --->\n", I);

for (J = 1; J<=NV; J++) {
printf("Escribe el valor  %d ---> ", J); scanf("%lf", &R2);
TS[I + 1][J + 1] = -R2;
}

printf(" Cual es R --->  "); scanf("%lf", &TS[I+1][1]);
}

printf("\n\n **Los resultados obtenidos fueron**\n\n");
for(J=1; J<=NV; J++) TS[0][J+1] = J;
for(I=NV+1; I<=NV+NC; I++) TS[I-NV+1][0] = I;
}



#endif
