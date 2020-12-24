/**
*@file linea_de_espera.h
*@version 1.0
*@date 22/12/2020
*@author NerySegundoAgustin
*@title Funciones que se implementan en la clase main.
*/

#ifndef __LINEA_DE_ESPERA_H
#define __LINEA_DE_ESPERA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum {FALSE = 0, TRUE, NO = 0, YES} boolean;


typedef struct node{
	char Name[30];
	int Size;
	boolean Status;
	struct node *next;
} Node;

/**
*@brief  definicion avanzada de funciones
@return void
*/
void clearToEoln();
/* ------------------------------------------------ ------------- */
int getNextNWSChar (){
  int ch;

 	ch = getc(stdin);
 	if (ch == EOF)
   		return ch;
 	while (isspace (ch)){
	    ch = getc(stdin);
    	if (ch == EOF)
      	return ch;
   	}
 	return ch;
}


/* ------------------------------------------------ ------------- * /
/**
* @brief leer en el siguiente entero positivo o error
* @todo Esto se basa en la definicion matematica de un entero positivo
* @return un cero no se cuenta como un numero positivo
*/
int getPosInt (){
  int value = 0;

 	/* caracteres de espacio en blanco claro */
 	int ch;
	ch = getc(stdin);
 	while (!isdigit(ch)){
    	if ('\n' == ch)  /* error \ n ==> ning�n entero dado */
       		return 0;
    	if (!isspace(ch)) /* error sin espacio en blanco ==> n�mero entero no dado a continuaci�n */{
       		clearToEoln();
       		return 0;
      	}
    	ch = getc(stdin);
   	}

 	value = ch - '0';
 	ch = getc(stdin);
 	while (isdigit(ch)){
    	value = value * 10 + ch - '0';
    	ch = getc(stdin);
   	}

 	ungetc (ch, stdin);  /* volver a poner el �ltimo car�cter le�do en el flujo de entrada */

 	/* El valor entero de 0 es un error en este programa */
 	if (0 == value)
    	clearToEoln();

 	return value;
}


/* ------------------------------------------------------------- */
/**
* @brief leer el nombre hasta el final de la entrada
* @return lectura de datos
*/
char *getName(){
  /* omitir los caracteres de espacio en blanco */
  int ch;
	ch = getc(stdin);
 	while (isspace(ch)){
	    if ('\n' == ch)  /* error \ n ==> ning�n entero dado*/
       	return NULL;
    	ch = getc(stdin);
   	}

  char *word;
  int size;
 	size = 10;
 	word = (char *) malloc (sizeof(char) * size);

 	// leer car�cter por car�cter hasta que se encuentre la nueva l�nea
 	int count = 0;

 	while (ch != '\n'){
    	if (count+1 >= size){
       		// para hacer crecer una matriz para que tenga un "tama�o din�mico" usando malloc
       		char* temp;
       		int i;
       		size = size * 2;
       		temp = (char *) malloc (sizeof(char) * size);

       		// printf ("Matriz creciente desde el tama�o% d hasta el tama�o% d \ n", count, size);
       		// copiar los caracteres a la nueva matriz
       		for (i = 0 ; i < count ; i++)
           		temp[i] = word[i];

       		free (word);
       		word = temp;
      	}

    	word[count] = ch;
    	count++;
    	word[count] = '\0';

    	//leer el siguiente car�cter
    	ch = getc(stdin);
   	}

 	if (count > 30){
    	count = 30;
    	word[count] = '\0';
   	}

 	/* caracteres de espacios en blanco finales claros */
 	while (isspace (word[count-1])){
    	count--;
    	word[count] = '\0';
   	}

 	return word;
}


/* ------------------------------------------------------------- */
/* Borrar entrada hasta el pr�ximo car�cter de fin de l�nea - \ n */
/**
* @brief Funcion para borrar entrada de datos hasta el proximo caracter de fin de linea
*/
void clearToEoln(){
  int ch;

	do {
     	ch = getc(stdin);
    }
 	while ((ch != '\n') && (ch != EOF));

}
/* ------------------------------------------------------------- */
/**
* @brief Funcion que imprime la lista de comandos de este programa
* @todo al final borra la entrada de la linea.
*/
void ImprimirComandos(){
 	printf ("Los comandos para este programa son: \n \n");
  printf ("q - para salir del programa \n");
  printf ("? - para listar los comandos aceptados \n\n");
  printf ("a <tamano> <nombre> - para agregar un grupo a la lista de espera \n");
  printf ("c <tamano> <nombre> - para agregar un grupo de llamada anticipada a la lista de espera \n");
  printf ("w <nombre> - para especificar que un grupo de llamada anticipada ahora est� esperando en la caja \n");
  printf ("r <tamano-tabla> - para recuperar el primer grupo en espera que pueda caber en el tama�o la caja disponible \n");
  printf ("l <nombre> - enumera cu�ntos grupos est�n por delante del grupo nombrado \n");
  printf ("d - muestra la informaci�n de la lista de espera \n");
 	/* borrar entrada al final de la l�nea */
 	clearToEoln();
}


/* ------------------------------------------------------------- */
/**
* @brief Comprueba si el nombre esta en la lista
* @return valor falso
*/
boolean NombreExistente(Node *root, char name[]){
	while(root != NULL){
		if( strcmp(root->Name, name) == 0 )
			return TRUE; // Verdadero si el nombre ya existe en la lista
		root = root->next;
	}
	return FALSE;
}


/* ------------------------------------------------------------- */
/**
* @brief Agrega una caja a la lista
*@ todo si la lista esta vacia, crea un nuevo nodo
*@ todo De lo contrario, agrega a la lista vinculada
*@ todo Copia el nuevo nombre en el elemento de nodo 'Nombre'
* @return un valor en la lista de espera.
*/
void Agregar_A_Lista(Node **root, Node **end, char name[], int size, int status){
  int i;

	// Si la lista est� vac�a, cree un nuevo nodo
	if(*root == NULL){
		*root = (Node*)malloc(sizeof(Node));
		*end = *root;
	}
	// De lo contrario, agregar a la lista vinculada
	else{
		(*end)->next = (Node*)malloc(sizeof(Node));
		*end = (*end)->next;
	}

	i = 0;
	// Copie el nuevo nombre en el elemento de nodo 'Nombre'
	while(name[i] != '\0'){
		(*end)->Name[i] = name[i];
		i++;
	}
	(*end)->Size = size;
	(*end)->Status = status;
	(*end)->next = NULL; // Tail-> next siempre apunta a NULL
}


/* ------------------------------------------------------------- */
/**
* @brief obtener el tamano del grupo de la entrada
* @return el valor del tamaño del grupo
*/
void Agregar (Node **root, Node **end){
  /*  */
  int size = getPosInt();
 	if (size < 1){
    	printf ("Error: el comando Agregar requiere un valor entero de al menos 1 \n");
     printf ("El comando Agregar tiene la forma: a <tama�o> <nombre> \n");
     printf ("donde: <tama�o> es el tama�o del grupo que hace la reserva \n");
     printf ("<nombre> es el nombre del grupo que hace la reserva \n");
    	return;
   	}

  	/*obtener el nombre del grupo de la entrada*/
  	char *name = getName();
 	if (NULL == name){
    	printf ("Error: el comando Agregar requiere un nombre \n");
     printf ("El comando Agregar tiene la forma: a <tama�o> <nombre> \n");
     printf ("donde: <tama�o> es el tama�o del grupo que hace la reserva \n");
     printf ("<nombre> es el nombre del grupo que hace la reserva \n");
    	return;
   	}

 	printf ("Anadiendo grupo\"%s\" de tama�o %d\n", name, size);

 	// agregue c�digo para realizar esta operaci�n aqu�
	if( NombreExistente(*root, name) ){ // Agrega un grupo si el grupo a�n no est� en la lista
		printf("Error: el nombre del grupo ya existe\n");
	}
	else{
		int status = TRUE; // Medios en restaurante
		Agregar_A_Lista(root, end, name, size, status);
	}
}


/* ------------------------------------------------------------- */
/**
* @brief Funcion para relaizar una llamada a la cabecera de la linea de espera
* @return tamaño de la caja en la que se encuentre
*/
void llamar_cabecera (Node **root, Node **end){
  	/* obtener el tama�o del grupo de la entrada */
  	int size = getPosInt();
 	if (size < 1){
    	printf ("Error: el comando de llamada anticipada requiere un valor entero de al menos 1 \n");
     printf ("El comando de llamada anticipada tiene la forma: c <tama�o> <nombre> \n");
     printf ("donde: <tama�o> es el tama�o del grupo que hace la reserva \n");
     printf ("<nombre> es el nombre del grupo que hace la reserva \n");
    	return;
   	}

 	/* obtener el nombre del grupo de la entrada*/
 	char *name = getName();
 	if (NULL == name){
    	printf ("Error: el comando de llamada anticipada requiere un nombre \n");
     printf ("El comando de llamada anticipada tiene la forma: c <tama�o> <nombre> \n");
     printf ("donde: <tama�o> es el tama�o del grupo que hace la reserva \n");
     printf ("<nombre> es el nombre del grupo que hace la reserva \n");
    	return;
   	}

 	printf ("Grupo de llamada anticipada \"%s\" de tamano %d\n", name, size);

 	// agregue c�digo para realizar esta operaci�n aqu�
	if( NombreExistente(*root, name) ){ // Agrega un grupo si el grupo a�n no est� en la lista
		printf("Error: el nombre del grupo ya existe\n");
	}
	else{
		int status = FALSE; // Significa que no est� en el supermercado
		Agregar_A_Lista(root, end, name, size, status);
	}
}


/* ------------------------------------------------------------- */
/**
* @brief Funcion para cambiar el estado a espera en el supermercado
* @return Verdadero
*/
boolean cambiar_estado(Node **root, char name[]){
  Node *p = *root;
	while(p != NULL){
		// Si hay una coincidencia, strcmp devolver� 0
		if(strcmp(p->Name, name) == 0){
			if(p->Status == TRUE){
				printf("Error: el grupo '% s' ya est� esperando en el restaurante\n", name);
				return FALSE;
			}
			p->Status = TRUE;
			return TRUE;
		}
		p = p->next;
	}
}


/* ------------------------------------------------------------- */
/**
* @brief Funcion para cambiar el estado a espera en el supermercado
* @return Verdadero
*/
void Cambios_en_linea(Node **root){
  	/*obtener el nombre del grupo de la entrada */
  	char *name = getName();
 	if (NULL == name){
    	printf ("Error: el comando en espera requiere que se le d� un nombre \n");
     printf ("El comando en espera tiene la forma: w <nombre> \n");
     printf ("donde: <nombre> es el nombre del grupo que ahora est� esperando \n");
    	return;
   	}

 	printf ("El grupo de espera \"%s\" ahora est� en el restaurante\n", name);

	if( NombreExistente(*root, name) )
		cambiar_estado(root, name);

}


/* ------------------------------------------------------------- */
/**
* @brief elimina un  grupo con un tamano menor o igual al tama�o de la tabla disponible
* @return modificacion en la tabla
*/
char* Recupera_y_quita_datos(Node **root, Node **end, char table_size){
  Node *p = *root;
  static char removedName[30];

	while(p != NULL){
		//Si solo hay un grupo en la lista
		if( (*root == *end) && ((*root)->Status == 1) && ((*root)->Size <= table_size) ){
			strcpy( removedName, (*root)->Name );
			*root = NULL;
			*end = NULL;
			free(p);
			return removedName;
		}
		// Si el grupo est� en el primer nodo
		else if( ((*root)->Status == TRUE) && ( ((*root)->Size) <= table_size) ){
			strcpy( removedName, (*root)->Name );
			*root = (*root)->next;
			free(p);
			return removedName;
		}
		else if( (p->next->Status == TRUE) && (p->next->Size <= table_size) ){
			// Si el grupo est� en el �ltimo nodo
			if(p->next == *end){
				strcpy( removedName, (*end)->Name );
				*end = p;
				free(p->next);
				(*end)->next = NULL;
				return removedName;
			}
			// Si el grupo est� en el medio
			else{
				strcpy( removedName, p->next->Name );
				Node *tmp = p->next;
				p->next = tmp->next;
				free(tmp);
				return removedName;
			}
		}
		p = p->next;
		if(p->next == NULL){
			break;
		}
	}
	printf("Error: ning�n grupo disponible puede caber en esa tabla\n");
	return NULL;
}


/* ------------------------------------------------------------- */
/**
* @brief Funcion para recuperar datos de la linea de espera
* @todo principalmente esta funcion se enfoca en recuperar y quitar datos.
*/
void Recuperar (Node **root, Node **end){
  	/* obtener el tama�o de la tabla de la entrada */
  	int size = getPosInt();
 	if (size < 1){
    	printf ("Error: el comando de recuperaci�n requiere un valor entero de al menos 1 \n");
     printf ("El comando de recuperaci�n tiene la forma: r <tama�o> \n");
     printf ("donde: <tamano> es el tamano del grupo que hace la reserva \n");
    	return;
   	}
 	clearToEoln();
 	printf ("Recupere (y elimine) el primer grupo que pueda caber en una caja para cobrar de tamano %d\n", size);

	char* removedName = Recupera_y_quita_datos(root, end, size);
 	//agregue c�digo para realizar esta operaci�n aqu�
	if(removedName != NULL)
		printf("Grupo eliminado '%s'\n", removedName);
}


/* ------------------------------------------------------------- */
/**
	*@brief Cuenta los grupos que esperan delante de un grupo determinado en la caja
	*@todo Devuelve i-1 porque estar  un valor por delante
	*/
int Contados_gruposEnLinea(Node *root, char name[]){
  int i = 1;
	while(root != NULL){
		if(strcmp(root->Name, name) == 0)
			return i-1; // Devuelve i-1 porque estar� un valor por delante
		root = root->next;
		i++;
	}
}


/* ------------------------------------------------------------- */
/**
	*@brief Imprime tamaños de grupos que esperan delante de un grupo determinado
	*@return el grupo su nombre y el tamaño
	*/
void Mostrar_TamanoLinea (Node *root, int count){
  int i;
	for(i=1; i<=count; i++){
		printf(" Grupo %d: \n \t Nombre: %s \n tama�o:%d \n", i, root->Name, root->Size);
		root = root->next;
	}
}


/* ------------------------------------------------------------- */
/**
	*@brief obtener el nombre del grupo de la entrada
	*@return la actualizacion en la lista de la linea de espera.
	*/
void Crear_lista (Node *root){
  	/* obtener el nombre del grupo de la entrada */
  	char *name = getName();
 	if (NULL == name){
    	printf ("Error: El comando de lista requiere que se le d� un nombre \n");
     printf ("El comando de lista tiene la forma: l <nombre> \n");
     printf ("donde: <nombre> es el nombre del grupo sobre el que preguntar \n");
   	}

 	printf ("El grupo \"%s\" est� detr�s de los siguientes grupos\n", name);

 	// c�digo para realizar esta operaci�n aqu�
	int count = 0, size;
	if( NombreExistente(root, name) ){
		count = Contados_gruposEnLinea(root, name);
		Mostrar_TamanoLinea(root, count);
		printf("Hay un total de% d grupo (s) por delante del grupo '%s'\n", count, name);
	}
	else
		printf("Error: el grupo '%s' no est� en la lista\n", name);
}


/* ------------------------------------------------------------- */
/**
	*@brief Funcion para mostrar la informacion de la caja.
	*@return total en los grupos de la linea.
	*/
void Muestra_Informacion(Node *root){
  int i = 1;
	while(root != NULL){
		printf("Grupo %d:\n\tNombre: %s\n\tTamano: %d\n", i, root->Name, root->Size);
		if( root->Status == TRUE )
			printf("\tEstado: Formado en una caja \n\n");
		else
			printf("\tEstado: linea de espera\n\n");
		root = root->next;
		i++;
	}
	printf("Hay un total de %d grupos en la lista de espera\n", i-1);
}


/* ------------------------------------------------------------- */
}/**
	*@brief Funcion para mostrar la informacion de todos los grupos de las cajas
	*@return informacion de salida. 
	*/
void Mostrar (Node *root){
	clearToEoln();
 	printf ("Mostrar informaci�n sobre todos los grupos\n");

 	//c�digo para realizar esta operaci�n aqu�
	Muestra_Informacion(root);
}
#endif
