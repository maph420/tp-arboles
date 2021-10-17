#ifndef __ABB_H__
#define __ABB_H__

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

Arbol agrega(Arbol a, char* judocaNombre, char* judocaApellido, int judocaEdad, Comparar c);

void muestraPreOrder(Arbol a);

void testJudoca();

#endif /* __ARBOL_H__ */
