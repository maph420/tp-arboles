//arbol.c
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
	return (((Judoca)dato1)->edad > ((Judoca)dato2)->edad) ? 1 : 0 ;
}


void muestraPreOrder(Arbol a){
	if (!isEmpty(a)) {
    	printf("%s	%s	%d\n", ((Judoca)(a->dato))->nombre,((Judoca)(a->dato))->apellido,((Judoca)(a->dato))->edad);
    	muestraPreOrder(a->izq);
    	muestraPreOrder(a->der);
  	}
}

void muestraPreOrderParejas(Arbol a){
	if (!isEmpty(a)) {
		printf("%s	vs	%s	(%d)\n",((Pareja)a->dato)->participante1->nombre,((Pareja)a->dato)->participante2->nombre,((Pareja)a->dato)->estadoPareja);
		muestraPreOrderParejas(a->izq);
		muestraPreOrderParejas(a->der);
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

//esto en main.c o arbol.c ?
Arbol agrega_pareja(Arbol a, Judoca p1, Judoca p2, int estadoPareja, Comparar c) { 

	if (isEmpty(a)) {
        Pareja p = malloc(sizeof(_Pareja));
        a = malloc(sizeof(TNodo));
        p->participante1 = p1;
        p->participante2 = p2;
        p->estadoPareja = estadoPareja;

        a->dato = p;
	    a->izq = NULL;
	    a->der = NULL; 

  	}
	else {
		if (c(a->dato, estadoPareja)) 
            a->izq = agrega_pareja(a->izq,p1,p2,estadoPareja,c);
		else
            a->der = agrega_pareja(a->der,p1,p2,estadoPareja,c);
	}
	return a;
}



//el elemento mas a la derecha de la rama izquierda
Arbol buscaMayorDeMenores(Arbol a){ 
	if  (a->izq == NULL) {
    	return NULL;
  	}
  	else {
	    Arbol t;
    	for(t = a->izq; t->der != NULL; t = t->der);
    	return t;
  	}
}


Arbol elimina(Arbol a, void* dato) {
	if (isEmpty(a)) return NULL;
	if ( ((Judoca)a->dato)->edad != ((Judoca)dato)->edad ) {

		if (((Judoca)a->dato)->edad > ((Judoca)dato)->edad) {
			a->izq = elimina(a->izq, dato);
		}
    	else {	
			a->der = elimina(a->der, dato);
		}
  	} 
  	else {
  	//Estoy en el Nodo que se desea eliminar
	  if( ! strcmp(((Judoca)a->dato)->nombre,((Judoca)dato)->nombre) && ! strcmp(((Judoca)a->dato)->apellido,((Judoca)dato)->apellido)) {

  		//Caso 1: No tiene hijos
  		if (isEmpty(a->izq) && isEmpty(a->der))	 {	 
			free(a);
  			a = NULL;
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
			a->dato = t->dato;
			a->izq = elimina(a->izq,(Judoca)t->dato);
		  }
  	}
	  else {
		  a->izq = elimina(a->izq, dato); 
	  }

}
  	return a;
}
