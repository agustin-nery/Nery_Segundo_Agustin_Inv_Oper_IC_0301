/**
*@file rutanery.h
*@version 1.0
*@date 02/11/2020
*@author NerySegundoAgustin
*@title Funciones
*/

#ifndef __RUTANERY_H
#define __RUTANERY_H

#include <stdio.h>
#include <stdlib.h>
#define Nodo struct nodo
#define Arista struct arista
#define Lista struct pila


/** 
* @brief Esta es una estructura Nodo
* @param parametro de tipo entero visitado y terminado para los vertices por los cuales se pase.
* @param monto es la cantidad de el peso de los vertices por los cuales al hacer el recorrido se pueda llegar a el resultado.
* @param variable de tipo char esta me sirvio para guardar el numero de el vertice anterior por el que se paso.
*/
Nodo{
	char dato; 
	Nodo* siguiente;
	Arista* adyacencia; 
	int visitado,terminado;
	int monto;
	char anterior;
};


/**
* @brief estructura arista
* @param en esta solo declaramos una variable de tipo entero que nos va a ayudar a tener el peso de cada una.
*/
Arista{
	Nodo*vrt; 
	Arista*siguiente;
	int peso;
};
/**
* @brief estructura de lista 
* @param esta solo nos va a servir para llevar a cabo una de las listas de visualizacion para hacer los caminos de los nodos
*/
Lista{
	Nodo* dato;
	Lista*siguiente;
};

Nodo*inicio=NULL;
Lista*ini=NULL;
Lista*final=NULL; 
/**
* @brief funcion insertar nodo nos ayuda agregar un nuevo nodo si no lo contemplamos al principio
* @return el nodo ingresado a la cola de los nodos
*/
void insertarNodo();
/**
* @brief Agrega las aristas nuevas y lo que se hace e  asignar de donde a donde van y cual es su peso 
* @return valores de la matriz de una manera ordenada
*/
void agregarArista(Nodo*aux,Nodo*aux2,Arista*nuevo);
/**
* @brief Agrega una arista a los nodos que le indiquemos
* @return una arista con un peso
*/
void insertarArista();
/**
* @brief nos ayuda a visualizar la matriz y como esta esta conformada
* @return una impresion de la matriz creada
*/
void visualizarGrafo();
/**
* @brief Funcion auxliar en la funcion isertar aristas
* @return los valors de los pesos
*/
void insertarPila(Nodo* aux);
/**
* @brief Funcion auxliar en la funcion isertar aristas
* @return valores qye se tienen en la matrixz
*/
void insertarCola(Nodo* aux);
/**
* @brief nos retornaun vslor de la matriz
* @return ayuda en ña funcion de inseertar aristas
*/
Nodo*desencolar();
/**
* @brief funcion que nos ayuda a reiniciar el menu cuando una funcion ya es terminada 
* @return return
*/
void reiniciar();
/**
* @brief Funcion principal para encontrar la ruta mas corta.
* @return el posible camino si es que se encuentra algun camnino de ruta mas corta
*/
void dijkstra();

#endif
