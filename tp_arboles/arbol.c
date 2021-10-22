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

Arbol agrega_pareja(Arbol a, Judoca p1, Judoca p2, int estadoPareja, Comparar c) { //Judoca es un puntero !!!, pasar datos como args separados

	if (isEmpty(a)) {
        Pareja p = malloc(sizeof(_Pareja));
        a = malloc(sizeof(TNodo));
        p->participante1 = p1;
        p->participante2 = p2;
        p->estadoPareja = estadoPareja;
		printf("se asigna participante 1: %s, participante 2: %s\n",p->participante1->nombre,p->participante2->nombre);

        a->dato = p;
	    a->izq = NULL;
	    a->der = NULL; 
		//printf("%s\n",((Pareja)a->dato)->participante1->nombre);

  	}
	else {
		if (c(a->dato, estadoPareja)) 
            a->izq = agrega_pareja(a->izq,p1,p2,estadoPareja,c);
		else
            a->der = agrega_pareja(a->der,p1,p2,estadoPareja,c);
	}
	printf("muestrapreorderparejas\n");
	muestraPreOrderParejas(a);
	return a;
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
  		//Caso 1: No tiene hijos
  		if (isEmpty(a->izq) && isEmpty(a->der))	 {
			if( ! strcmp(((Judoca)a->dato)->nombre,((Judoca)dato)->nombre) && ! strcmp(((Judoca)a->dato)->apellido,((Judoca)dato)->apellido)) {
			free(a);
  			a = NULL;
  			return a;
			}
		  }
  		
  		//Caso 2: Un hijo 
  		else if (isEmpty(a->izq) || isEmpty(a->der)) {
			if( ! strcmp(((Judoca)a->dato)->nombre,((Judoca)dato)->nombre) && ! strcmp(((Judoca)a->dato)->apellido,((Judoca)dato)->apellido)) {
  			Arbol t = (isEmpty(a->izq) ? a->der : a->izq);
  			free(a);
  			a = t;
  			return a;
			}
  		}
  		//Caso 3: 2 hijos
  		else {
  			//Encuentro el nodo que tengo que poner en su lugar, en este caso, es el mayor de los menores
			if( ! strcmp(((Judoca)a->dato)->nombre,((Judoca)dato)->nombre) && ! strcmp(((Judoca)a->dato)->apellido,((Judoca)dato)->apellido)) { //para no borrar accidentalmente un nodo con una persona de la misma edad
  			Arbol t = buscaMayorDeMenores(a);
  			((Judoca)a->dato)->edad = ((Judoca)t->dato)->edad;
			((Judoca)a->dato)->nombre = ((Judoca)t->dato)->nombre;
			((Judoca)a->dato)->apellido = ((Judoca)t->dato)->apellido; 
  			//Borro el nodo duplicado que quedó
  			a->izq=elimina(a->izq, ((Judoca)t->dato));

			}
		  }
  	}
  	return a;
}


/*borrar despues esta funcion*/
void testJudoca() {

Judoca j=NULL;
Judoca j2=NULL;
Judoca j3=NULL;


//char bufNombre[50];
//char bufApe[50];

Arbol a = create();

a = agrega(a,"nombre","apellido",20,miComparar);
a = agrega(a,"nombre2","apellido2",21,miComparar);
a = agrega(a,"nombre3","apellido3",15,miComparar);

printf("muestraPreOrder:\n");
muestraPreOrder(a);
}



/*cola*/
Cola cola_crear() {
Cola c = malloc(sizeof(struct _Cola));
c->primero = -1; 
c->ultimo = -1;
return c;
}

int cola_es_vacia(Cola c) {
    return c->primero==(-1);
}

int cola_primero(Cola c) {
    return c->primero;
}

void cola_encolar(Cola c, void* d) {
    if((c->primero == 0 && c->ultimo == MAX_COLA-1) || c->primero == c->ultimo+1){ /*no queda ningun espacio por utilizar.*/
        printf("\nexcedido tamanio de cola\n");
        //printf("intento: encolo: %d, primero: %d, ultimo: %d\n",d,c->primero,c->ultimo);
        return;
    }
    if(c->primero == -1){ /**pregunto si la cola esta vacia, en caso de estarla hago que el primer y el ultimo indice apunten a 0**/
        c->primero = 0; 
        c->ultimo = 0;
    }
    else{
        if(c->ultimo == MAX_COLA-1) /*cuando el ultimo indice este por alcanzar el limite de elementos, lo hacemos volver al principio*/
            c->ultimo = 0;
        else c->ultimo++;
    }
    
    //printf("encolo: %d, primero: %d, ultimo: %d\n",d,c->primero,c->ultimo);
    c->datos[c->ultimo] = d;
}

void cola_desencolar(Cola c) {
    if(c->primero == -1){    /*pregunto si la cola esta vacia*/   
        printf("no hay elementos por desencolar\n");
        return;
    }
    //printf("\nelemento a eliminar: %d\n",c->datos[c->primero]);
    if(c->primero == c->ultimo){ /*desencolo el unico elemento de la cola, por lo cual los indices deben quedar apuntando a la nada*/
        c->primero = -1;
        c->ultimo = -1;
    }
    else{
        if(c->primero == MAX_COLA-1){   /*cuando el indice del primer elemento esta por alcanzar el limite, lo hacemos volver al principio*/
            c->primero = 0;
        }
        else c->primero++;
    }
}

void cola_imprimir(Cola c) {
    int i_primero = c->primero;
    int i_ultimo = c->ultimo;

    if(i_primero <= i_ultimo){              /*en caso de que ninguno los ultimos elementos haya sido puesto al principio*/
        while(i_primero <= i_ultimo){       /*^^basicamente, la cantidad de elementos encolados es menor a la del limite de elementos aceptado*/
            printf("%s\n",((Judoca)c->datos[i_primero])->nombre);
            i_primero++;
        }
    }
        else {                  
                while(i_primero <= MAX_COLA-1){ /*imprimo primero a la derecha del primero*/
                    printf("%s\n",((Judoca)c->datos[i_primero])->nombre);
                    i_primero++;
                }
            i_primero = 0;
            while(i_primero <= i_ultimo){ /*imprimo a la izquierda del primero*/
                printf("%s\n",((Judoca)c->datos[i_primero])->nombre);
                    i_primero++;
            }

        }
    }

void cola_destruir(Cola c) {
    free(c);
}
