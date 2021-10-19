#include "arbol.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

Arbol create(){
  return NULL;
}

int isEmpty(Arbol a){
    return a==NULL;
}

int miComparar ( void* dato1, int dato2 ) {
    return ( ((Judoca)dato1)->edad >= (int)dato2 ) ? 1 : 0 ; //>= ya que por convencion si un nodo es igual a otro, se coloca a la izquierda en el arbol
}

int miComparaNodos(void* dato1, Judoca dato2) {
	return (((Judoca)dato1)->edad >= ((Judoca)dato2)->edad) ? 1 : 0 ;
}


void muestraPreOrder(Arbol a){
	if (!isEmpty(a)) {
    	printf("%s	%s	%d\n", ((Judoca)(a->dato))->nombre,((Judoca)(a->dato))->apellido,((Judoca)(a->dato))->edad);
    	muestraPreOrder(a->izq);
    	muestraPreOrder(a->der);
  	}
}


//compara Judoca dado con cada uno de los nodos del arbol, devuelve 1 en caso de matchear, sino 0
void compararNodo(Arbol a, CompararNodos c, Judoca nodoJudoca) {
	if(!isEmpty(a)) {
		if(c(a->dato,nodoJudoca)) {
			//return 1; esto puede servir luego, lo de retornar para que no siga buscando, ya que ya habria encontrado un matcheo valido
		}
			compararNodo(a->izq,c,nodoJudoca);
			compararNodo(a->der,c,nodoJudoca);
	}
	//return 0;
}

void compararArboles(Arbol a1, Arbol a2, CompararNodos c) { //recorremos arbol a2, pasandole en cada vuelta un nodo distinto a la funcion que analiza r/arbol1
	if(!isEmpty(a2)) {
		compararNodo(a1,c,(Judoca)a2->dato);
		compararArboles(a1,a2->izq,c);
		compararArboles(a1,a2->der,c);	
	}
}


Arbol agrega(Arbol a, char* judocaNombre, char* judocaApellido, int judocaEdad, Comparar c) { //Judoca es un puntero !!!, pasar datos como args separados

	if (isEmpty(a)) {
        /*sizeof(Judoca) reservaria tamaño para el puntero a la estructura, no para la estructura :p*/
        Judoca j = malloc(sizeof(_Judoca));
        a = malloc(sizeof(TNodo));
        j->nombre = strdup(judocaNombre);
        j->apellido = strdup(judocaApellido);
        j->edad = judocaEdad;

        a->dato = j;
	    a->izq = NULL;
	    a->der = NULL;
  	}
	else {
		if (c(a->dato, judocaEdad)) 
            a->izq = agrega(a->izq,judocaNombre,judocaApellido,judocaEdad,c);
		else
            a->der = agrega(a->der,judocaNombre,judocaApellido,judocaEdad,c);
	}
	return a;
}

/*borrar despues esta funcion*/
void testJudoca() {

Judoca j=NULL;
Judoca j2=NULL;
Judoca j3=NULL;


char bufNombre[50];
char bufApe[50];

Arbol a = create();

a = agrega(a,"nombre","apellido",20,miComparar);
a = agrega(a,"nombre2","apellido2",21,miComparar);
a = agrega(a,"nombre3","apellido3",15,miComparar);

printf("muestraPreOrder:\n");
muestraPreOrder(a);
}


Arbol buscaMayorDeMenores(Arbol a){ /*el elemento mas a la derecha de la rama izquierda*/
	if  (a->izq == NULL) {
    	return NULL;
  	}
  	else {
	    Arbol t;
    	for(t = a->izq; t->der != NULL; t = t->der);
    	return t;
  	}
}


Arbol elimina(Arbol a, int dato) {
	if (isEmpty(a)) return NULL;
	if ( ((Judoca)a->dato)->edad != dato ) {
		//printf("%d != %d\n",((Judoca)a->dato)->edad,dato);
		if (((Judoca)a->dato)->edad > dato) {
			//printf("- %d mayor a %d, izquierda\n",((Judoca)a->dato)->edad,dato);
			//printf("izquierda (%d > %d)\n",((Judoca)a->dato)->edad,dato);
			a->izq = elimina(a->izq, dato);
		}
    	else {	
			//printf("- %d menor a %d, derecha\n",((Judoca)a->dato)->edad,dato);
			//printf("derecha (%d < %d)\n",((Judoca)a->dato)->edad,dato);
			a->der = elimina(a->der, dato);
		}
  	} 
  	else {
  	//Estoy en el Nodo que se desea eliminar
  		//Caso 1: No tiene hijos
  		if (isEmpty(a->izq) && isEmpty(a->der))	 {
			free(a);
  			a = NULL;
			printf("despues de la asignacion s/hijos\n");
  			return a;
		  }
  		
  		//Caso 2: Un hijo 
  		else if (isEmpty(a->izq) || isEmpty(a->der)) {
  			Arbol t = (isEmpty(a->izq) ? a->der : a->izq);
  			free(a);
  			a = t;
  			return a;
  		}
  		//Caso 3: 2 hijos
  		else {
  			//Encuentro el nodo que tengo que poner en su lugar, en este caso, es el mayor de los menores
  			Arbol t = buscaMayorDeMenores(a);
  			((Judoca)a->dato)->edad = ((Judoca)t->dato)->edad;
  			//Borro el nodo duplicado que quedó
  			a->izq=elimina(a->izq, ((Judoca)t->dato)->edad);
		  }
  	}
  	return a;
}
