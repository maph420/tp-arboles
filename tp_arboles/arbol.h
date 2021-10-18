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

typedef int(*CompararNodos) ( void* dato1, Judoca dato2, Arbol* a1, Arbol* a2);


Arbol agrega(Arbol a, char* judocaNombre, char* judocaApellido, int judocaEdad, Comparar c);

void muestraPreOrder(Arbol a);

void compararNodo(Arbol a, CompararNodos c, Judoca nodoJudoca, Arbol* a2);

void compararArboles(Arbol a1, Arbol a2, CompararNodos c);

void testJudoca();

typedef void (* Destruir) (void * dato);
void arbol_destruir(Arbol arbolN, Destruir d);

Arbol elimina(Arbol a, int dato);


#endif /* __ARBOL_H__ */
