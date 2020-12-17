/**
*@file main.c
*@version 1.0
*@date 02/11/2020
*@author NerySegundoAgustin
*@title aplicacion fuente de el programa
*/

#include "RUTANERY.h"

int main(){   
    int opcion,N,i;
    printf("\n ENCONTRAR LA RUTA MAS CORTA__NERY \n");
	printf("Cual es el numero de NODOS(vertices)--->\n");
    scanf("%i",&N);
    for(i=0;i<N;i++){
    	insertarNodo();
	}
	system("cls");
    do{
    	printf("\t +++QUE DESEAS HACER+++\n");
    	printf("--------------------------------------\n");
        printf(" 1. Agregar un  Vertice              \n");
        printf(" 2. Agregar una Arista               \n");
        printf(" 3. visualizar la matriz             \n");
        printf(" 4. Encontrar la ruta mas corta      \n");
        printf(" 5. Salir                            \n");
        printf("-------------------------------------\n");
        printf("Escoge una opcion--->");
        scanf("%i",&opcion);
        switch(opcion){
            case 1:
                    insertarNodo();
                    break;
            case 2: insertarArista();
                    break;
            case 3: visualizarGrafo();
                    break;
            case 4: dijkstra();
                    break;
			case 5: break;
            default: printf("Opcion no valida...!!!\n");
                     break;
        }
        system("pause");
        system("cls");
    }while(opcion!=5);
    return 1;
}
