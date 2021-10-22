//arbol.h
#ifndef __ARBOL_H__
#define __ARBOL_H__
#define LONGITUD_MAX_LINEA 255



#include <stddef.h>

typedef struct {
char *nombre, *apellido;
int edad;
} _Judoca;
typedef _Judoca* Judoca;

typedef struct {
Judoca participante1, participante2;
int estadoPareja;
} _Pareja;
typedef _Pareja *Pareja;

typedef struct _TNodo {
  void *dato;
  struct _TNodo *izq, *der;
} TNodo;
typedef TNodo* Arbol;

Arbol create();

int isEmpty(Arbol a);

typedef int (*Comparar) ( void * dato1, int dato2 );

typedef int(*CompararNodos) ( void* dato1, void* dato2 );


Arbol agrega(Arbol a, char* judocaNombre, char* judocaApellido, int judocaEdad, Comparar c);

Arbol agrega_pareja(Arbol a, Judoca p1, Judoca p2, int estadoPareja, Comparar c);

void muestraPreOrder(Arbol a);

void muestraPreOrderParejas(Arbol a);

//int compararNodo(Arbol a, CompararNodos c, Judoca nodoJudoca, Arbol a2);

//int compararArboles(Arbol a1, Arbol a2, CompararNodos c);

void testJudoca();

Arbol elimina(Arbol a, void* dato);

int funcionComparaNodos(void* dato1, void* dato2);

//int asignarParejas(Arbol* a1, Arbol* a2, CompararNodos c); 

//retorna 1 si algun judoca de cualquiera de los arboles se quedo sin pareja (aun si ni siquiera pudieran jugar)
// 0 si todos tienen pareja y las parejas que no cumplen las condiciones tienen justificado el porqué

#define MAX_COLA 50
typedef struct _Cola {
void* datos[MAX_COLA];
int primero, ultimo;
} *Cola;

Cola cola_crear(); /*crea e inicializa una nueva cola vacía.*/

int cola_es_vacia(Cola c);  /*determina si la cola está vacía*/

int cola_primero(Cola c); /*toma una cola y devuelve el elemento en la primera posición*/

void cola_encolar(Cola c, void* d); /*toma una cola y un elemento y agrega el elemento al fin de la cola*/

void cola_desencolar(Cola c); /*toma una cola y elimina su primer elemento.*/

void cola_imprimir(Cola c); /*toma una cola y la imprime en orden.*/

void cola_destruir(Cola c); /*libera la memoria requerida para la cola.*/



#endif /* __ARBOL_H__ */
