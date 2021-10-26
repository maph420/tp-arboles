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

Arbol elimina(Arbol a, void* dato);


void testJudoca();


#endif /* __ARBOL_H__ */
