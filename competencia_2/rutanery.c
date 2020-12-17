/**
*@file rutanery.c
*@version 1.0
*@date 02/11/2020
*@author NerySegundoAgustin
*@title Funciones que se implementan
*/

#include "RUTANERY.h"

/**
*@brief funcion insertar nodo es para agregar un nuevo nodo de acuerdo a la matriz  que se crea
@return un nodo que se usa para la matriz y encontrar el camino
*/
void insertarNodo(){
    Nodo* aux;
	Nodo* nuevo=(Nodo*)malloc(sizeof(Nodo));
	fflush(stdin);
	printf("Ingrese el vertice--->");
	scanf("%c",&nuevo->dato);
	nuevo->siguiente=NULL;
    nuevo->adyacencia=NULL;
    nuevo->visitado=nuevo->terminado=0;
    nuevo->monto=-1;
    nuevo->anterior=0;
    /**
* @brief nuevo nos ayuda a conocer el valor de la varibla de tipo enter
* @return los valores de el valor y el nodo anterior
*/
    if(inicio==NULL){
        inicio=nuevo;
    }else{
        aux=inicio;
        while(aux->siguiente!=NULL){
            aux=aux->siguiente;
        }
        aux->siguiente=nuevo;
      }
 
 }
 /**
*@brief funcion insertar nodo es para agregar un nuevo nodo de acuerdo a la matriz  que se crea
@return un nodo que se usa para la matriz y encontrar el camino
*/
void insertarArista(){   
    char ini, fin;
    Arista* nuevo=(Arista*)malloc(sizeof(Arista));
    nuevo->siguiente=NULL;
    Nodo* aux;
	Nodo* aux2;
    if(inicio==NULL){
         printf("Error: El grafo está vacio\n");
         return;
    }
    fflush(stdin);
    /**
*@brief el usuario ingresa la matriz de los vertices a donde van y cual es su peso
@return inicio y fin de los nodos
*/
    printf("Ingresar Nodo Inicial y Final:");
    scanf("%c %c",&ini,&fin);
    printf("Ingresar Peso de la arista:");
    scanf("%i",&nuevo->peso);
    /**
    *@brief valor de la arista 
    *@return peso de cada vertice
    */
    aux=inicio;
    aux2=inicio;
     /**
    *@brief mientras se encuentre un valor verdadero  
    *@return el suguiente paso
    */
    while(aux2!=NULL){
        if(aux2->dato==fin){
            break;
        }
        aux2=aux2->siguiente;
    }
     /**
    *@brief si no encuentra unn valor verdadero 
    *@return un error al no encontrar el vertice
    */
    if(aux2==NULL){
    	printf("Error:Vertice no encontrado\n");
    	return;
	}
	/**
    *@brief agregar una nueva arista 
    */
    while(aux!=NULL){
        if(aux->dato==ini){
            agregarArista(aux,aux2,nuevo);
            return;
        }
        aux = aux->siguiente;
    }
    if(aux==NULL)
    	printf("Error:Vertice no encontrado\n");
}
/**
    *@brief funcion Agregar una arista 
    *@return un error al no encontrar el vertice
    */
void agregarArista(Nodo* aux,Nodo* aux2,Arista* nuevo){
    Arista* a;
    if(aux->adyacencia==NULL){   
	    aux->adyacencia=nuevo;
        nuevo->vrt=aux2;
    }else{   
	    a=aux->adyacencia;
        while(a->siguiente!=NULL)
            a=a->siguiente;
        nuevo->vrt=aux2;
        a->siguiente=nuevo;
    }
}
/**
* @brief Funcion para ver la matriz que se creo
* @todo nos perminte ver la matriz con la que estamos trabajando
*/
void visualizarGrafo(){
    Nodo*aux=inicio;
    Arista* ar;
    printf("Nodos\n");
    while(aux!=NULL){   
	    printf("%c:    ",aux->dato);
        if(aux->adyacencia!=NULL){
            ar=aux->adyacencia;
            while(ar!=NULL){ 
			    printf(" %c",ar->vrt->dato);
                ar=ar->siguiente;
            }
        }
        printf("\n");
        aux=aux->siguiente;
    }
    printf("\n");
}

/**
* @brief Funcion para incertar los datos
* @return los datos ingresados por el usuario los primeros dato que entran son los primeros que salen
*/
void insertarPila(Nodo* aux){
	Lista*nuevo=(Lista*)malloc(sizeof(Lista));
	nuevo->dato=aux;
	nuevo->siguiente=NULL;
	if(ini==NULL){
		ini=nuevo;
		final=nuevo;
	}else{
	   nuevo->siguiente=ini;
	   ini=nuevo;    	
	}
}

/**
* @brief Funcion para incertar los datos
* @return los datos ingresados por el usuario 
*/
void insertarCola(Nodo*aux){
	Lista*nuevo=(Lista*)malloc(sizeof(Lista));
	nuevo->dato=aux;
	nuevo->siguiente=NULL;
	if(ini==NULL){
		ini=nuevo;
		final=nuevo;
	}else{
		final->siguiente=nuevo;
		final=nuevo;
	}
}
/**
* @brief Funcion para incertar los datos
* @return los datos ingresados por el usuario 
*/
Nodo*desencolar(){
	Lista*aux;
	if(ini==NULL){
		return NULL;
	}else{
		aux=ini;
		ini=ini->siguiente;
		aux->siguiente=NULL;
		if(ini==NULL)
		final=NULL;
	}
	Nodo*resultado=aux->dato;
	free(aux);
	return resultado;
}

	/**
* @brief Funcion Reiniciar ya que estamos haciendo uso de casos en el metodo main
* @paramParametro nodo*aux cuando termina unn caso lo reinicia al menu principal
* @paramParametro terminado sucede el reinicio cuando se termina la ejecucion del caso
*/
void reiniciar(){
	if(inicio!=NULL){
		Nodo*aux=inicio;
		while(aux!=NULL){
			aux->visitado=aux->terminado=0;
		    aux=aux->siguiente;
		}
	}
}
	/**
* @brief Funcion DIjkstra para encontrar la ruta mas corta
* @todo esta funcion es la principal ya que nos ayuda a encontrar la ruta entre dos variables las cuales fueron definidasd como a y b
*/
void dijkstra(){
	Nodo*aux=inicio;
	char a,b;
	fflush(stdin);
	/**
* @brief Funcion DIjkstra para encontrar la ruta mas corta
* @paramParametro a para el nodo inical
* @paramParametro b para el nodo final 
* @paramterminado para determinar si existe
*/
	printf("Ingresar Nodo Inicial y Final--->");
	scanf("%c %c",&a,&b);
	while(aux!=NULL){
		if(aux->dato==a){
			aux->terminado=1;
			aux->monto=0;
			break;
		}
		aux=aux->siguiente;
	}
	/**
    *@brief mienstras no se encuentre un vertice verdadero
    *@return un error al no encontrar el vertice
    */
	if(aux==NULL){
		printf("Vertice no encontrado\n");
		return;
	}
	while(aux!=NULL){
		Arista*a=aux->adyacencia;
		 /**
* @brief mientras de la funcion dijkstra 
* @todo Dlo que se hace aqui es comparar si su trayecto es igual al que tenia antes y si es menor se va a cambiar si no no.
*/
	    while(a!=NULL){
		    if(a->vrt->monto==-1 || (aux->monto+a->peso)<a->vrt->monto){
		    	a->vrt->monto=aux->monto+a->peso;
		        a->vrt->anterior=aux->dato;
			}
		    a=a->siguiente;
	    }
	    aux=inicio;
	    Nodo*min=inicio;
	    /**
* @brief mientras minimo sea 0 o terminado en uno se iriaa recorriendo 
* @todo debe de tener un nodo establecido anteriormente
*/
	    while(min->anterior==0 || min->terminado ==1)
	    min=min->siguiente;
	    /**
* @brief mientras de la funcion dijkstra 
* @todo Dlo que se hace aqui es comparar si su trayecto es igual al que tenia antes y si es menor se va a cambiar si no no.
*/
		while(aux!=NULL){
	    	if(aux->monto<min->monto && aux->terminado==0 && aux->anterior!=0)
	    	min=aux;
	    	aux=aux->siguiente;
	    	
		}
		aux=min;
		aux->terminado=1;
		if(aux->dato==b)
		break;
	}
	while(aux->anterior!=0){
		insertarPila(aux);
		char temp=aux->anterior;
		aux=inicio;
		while(aux->dato!=temp){
		   aux=aux->siguiente;	
		}
	}
	insertarPila(aux);
	while(ini!=NULL){
		printf("Felicidades encontraste un camino\n");
		printf("%c ",desencolar()->dato);
	}
		printf("\n");
	reiniciar();
}
