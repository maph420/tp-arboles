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
