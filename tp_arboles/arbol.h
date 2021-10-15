#ifndef __ARBOL_H__
#define __ARBOL_H__

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

typedef int (*Comparar) ( void * dato1, void * dato2 );

Arbol agrega(Arbol a, Judoca dato, Comparar c);

void muestraPreOrder(Arbol a);

typedef void (*Destruir) ( void * dato );


void arbol_destruir ( Arbol arbolN, Destruir d );

void cargar_agenda(Pareja* pareja);

void testJudoca();

#endif /* __ARBOL_H__ */