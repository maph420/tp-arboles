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

typedef int(*CompararNodos) ( void* dato1, Judoca dato2);


Arbol agrega(Arbol a, char* judocaNombre, char* judocaApellido, int judocaEdad, Comparar c);

void muestraPreOrder(Arbol a);

void compararNodo(Arbol a, CompararNodos c, Judoca nodoJudoca);

void compararArboles(Arbol a1, Arbol a2, CompararNodos c);

void testJudoca();

Arbol elimina(Arbol a, int dato);

int asignarParejas(Arbol* a1, Arbol* a2, CompararNodos c); 
//retorna 1 si algun judoca de cualquiera de los arboles se quedo sin pareja (aun si ni siquiera pudieran jugar)
// 0 si todos tienen pareja y las parejas que no cumplen las condiciones tienen justificado el porqué

#endif /* __ARBOL_H__ */
