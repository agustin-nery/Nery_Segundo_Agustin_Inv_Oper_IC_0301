/**
*@file main.c
*@version 1.0
*@date 22/12/2020
*@author NerySegundoAgustin
*@title Clase principal main de una Linea de espera de un supermercado.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linea_de_espera.h"


/* -------------METODO MAIN------------------------------------------------ */
int main (int argc, char **argv){

  Node *root = NULL; // primer nodo
  Node *end = NULL;  // ultimo nodo
  char *input;
  int ch, debug = FALSE;

	if(argc >= 2){
		if( strcmp(argv[1], "-d") == 0 ){
			debug = TRUE;
			printf("\nInformaci�n de depuraci�n\n\n");
		}
	}

 	printf ("Inicio del programa de lista de espera del supermercado\n\n");
 	printf ("Ingrese el comando (<?> Para los comandos disponibles): ");

 	while ((ch = getNextNWSChar ()) != EOF){
    	/* comprobar para salir */
    	if ('q' == ch){
       		printf ("Programa de salida\n");
       		return (0);
      	}
    	else if ('?' == ch){ // Informacion
       		ImprimirComandos();
      	}
    	else if('a' == ch){ // Agregar nuevo grupo como disponible en el SUPERMERCADO
       		Agregar(&root, &end);
      	}
    	else if('c' == ch){ // Agregar nuevo grupo como reserva de llamada anticipada
       		llamar_cabecera(&root, &end);
      	}
    	else if('w' == ch){ // Cambiar el estado del grupo a disponible en el SUPERMERCADO
       		Cambios_en_linea(&root);
      	}
    	else if('r' == ch){ // Recupere el primer grupo que pueda caber en la caja disponible
       		Recuperar(&root, &end);
      	}
    	else if('l' == ch){ // Enumere todos los grupos antes de un nombre de grupo determinado
       		Crear_lista(root);
      	}
    	else if('d' == ch){ // Mostrar lista de espera completa
       		Mostrar(root);
      	}
    	else{
       		printf ("%c - No es un comando v�lido\n", ch);
       		printf ("Para obtener una lista de comandos v�lidos, escriba ?\n");
       		clearToEoln();
      	}
		if(debug == TRUE)
			Muestra_Informacion(root);
    	printf ("\nIngrese el comando (<?> Para los comandos disponibles): ");
   	}

	printf ("Saliendo del programa - EOF alcanzado\n");
  return 1;
}
