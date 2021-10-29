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

Arbol agrega_judoca(Arbol a, char* judocaNombre, char* judocaApellido, int judocaEdad, Comparar c) {

	if (isEmpty(a)) {
        Judoca j = malloc(sizeof(_Judoca));
        a = malloc(sizeof(TNodo));
		j->nombre = malloc(sizeof(char)*(strlen(judocaNombre)+1));
		strcpy(j->nombre,judocaNombre);
		j->apellido = malloc(sizeof(char)*(strlen(judocaApellido)+1));
		strcpy(j->apellido,judocaApellido);
        j->edad = judocaEdad;

        a->dato = j;
	    a->izq = NULL;
	    a->der = NULL;
		free(j->nombre);
		free(j->apellido);
		free(j);
		j=NULL;
  	}
	else {
		if (c(a->dato, judocaEdad)) 
            a->izq = agrega_judoca(a->izq,judocaNombre,judocaApellido,judocaEdad,c);
		else
            a->der = agrega_judoca(a->der,judocaNombre,judocaApellido,judocaEdad,c);
	}
	return a;
}

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
		free(p->participante1);
		free(p->participante2);
		free(p); 

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
			free(((Judoca)a->dato)->nombre);
			free(((Judoca)a->dato)->apellido);	 
			free(a->dato);
			free(a);
  			a = NULL;
  			return a;
			}
  		
  		//Caso 2: Un hijo 
  		else if (isEmpty(a->izq) || isEmpty(a->der)) {
  			Arbol t = (isEmpty(a->izq) ? a->der : a->izq);
			free(((Judoca)a->dato)->nombre);
			free(((Judoca)a->dato)->apellido);	 
			free(a->dato);
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

// libera toda la memoria de un arbol independientemente de su tipo (Judoca o Pareja en este caso)
void arbol_destruir (Arbol arbolN, Destruir d) {

	if(!isEmpty(arbolN)) {
		d((arbolN)->dato);
		arbol_destruir(arbolN->izq,d);
		arbol_destruir(arbolN->der,d);
		free(arbolN);
	}
	
}
