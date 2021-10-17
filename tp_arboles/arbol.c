#include "abb.h"
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


void muestraPreOrder(Arbol a){
	if (!isEmpty(a)) {
    	printf("%d\n", ((Judoca)(a->dato))->edad);
    	muestraPreOrder(a->izq);
    	muestraPreOrder(a->der);
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
