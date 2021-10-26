//main:c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbol.h"

void assign(char* line, Judoca judocaToAssign) {
            judocaToAssign->nombre = strdup(strtok(line,","));
            judocaToAssign->apellido = strdup(strtok(NULL,",")); // NULL is passed as first argument since strtok maintains a static pointer to your previous passed string
            judocaToAssign->edad = atoi(strtok(NULL,"\n"));
}

int funcionCompararJudocas ( void* dato1, int dato2 ) {
    return ( ((Judoca)dato1)->edad >= (int)dato2) ? 1 : 0 ; //>= ya que por convencion si un nodo es igual a otro, se coloca a la izquierda en el arbol
}

int funcionCompararJudocas2 ( void* dato1, int dato2 ) {
    return (  (int)dato2)>= ((Judoca)dato1)->edad ? 1 : 0 ; //>= ya que por convencion si un nodo es igual a otro, se coloca a la izquierda en el arbol
}

int funcionCompararParejas (void* dato1, int dato2) {
    return ( ((Pareja)dato1)->estadoPareja >= (int)dato2 ) ? 1 : 0 ;
}


int deltaEdades(void* dato1, void* dato2) {
int d = ( (((Judoca)dato1)->edad) >= ((Judoca)dato2)->edad ) ? ((Judoca)dato1)->edad - ((Judoca)dato2)->edad : ((Judoca)dato2)->edad - ((Judoca)dato1)->edad;
    return d;
}

int obtenerEstadoJudoca(void* j1, void* j2) {
    if ( ( ((Judoca)j1)->edad >= 18 && ((Judoca)j2)->edad < 18) || ( ((Judoca)j1)->edad < 18 && ((Judoca)j2)->edad >=18 ) ) {
        return 1;
    }
    else if ( ( ((Judoca)j1)->edad <18 && ((Judoca)j2)->edad <18 ) && (deltaEdades((Judoca)j1,(Judoca)j2) > 1) ) {
        return 2;
    }
    else if ( ( ((Judoca)j1)->edad >=18 && ((Judoca)j2)->edad >=18 ) && (deltaEdades((Judoca)j1,(Judoca)j2) > 2) ) {
        return 3;
    }
    else {
        return 0;
    }
}

Pareja parejaMinDiferenciaEdad (Judoca nodoAComparar, Arbol a) {
    Pareja p;
    if (!isEmpty(a)) { //recorro arbol 1 y me fijo el mejor matcheo con un elemento de arbol 2, sino el elemento mas chico
        if(obtenerEstadoJudoca((Judoca)a->dato,(Judoca)nodoAComparar) == 0 || ( (isEmpty(a->izq) && (isEmpty(a->der))) )) {
        p = malloc(sizeof(_Pareja));
        p->participante1 = nodoAComparar;
        p->participante2 = (Judoca)a->dato;
        p->estadoPareja = obtenerEstadoJudoca((Judoca)a->dato,(Judoca)nodoAComparar);
        return p;
        }
        else {
            if (nodoAComparar->edad >= ((Judoca)a->dato)->edad) {
                return parejaMinDiferenciaEdad(nodoAComparar,a->izq);
            }
            else {
                return parejaMinDiferenciaEdad(nodoAComparar,a->der);
            }
                
        }
    }
        else {
            return NULL; //esto ocurre si alguien se queda sin pareja
        }
            
}

void formarParejas(Arbol* a1, Arbol* a2, Arbol* a_resultante) {
    /*printf("arbol a1:\n"); descomentar para ver recorrido de arboles (1/3)
    muestraPreOrder(*a1);
    printf("arbol a2:\n");
    muestraPreOrder(*a2);*/
    Pareja p = parejaMinDiferenciaEdad((Judoca)((*a1)->dato),*a2);
    if(!p) return; //se llego al maximo numero de parejas formadas (lo restante de a1 o de a2 se quedara sin pareja)
    //printf("!!pareja encontrada: %s y %s\n",(p->participante1)->nombre,(p->participante2)->nombre); descomentar para ver recorrido de arboles (2/3)


    *a_resultante = agrega_pareja(*a_resultante,p->participante1,p->participante2,p->estadoPareja,funcionCompararParejas);

    /*printf("elimino %s de a1\n",((Judoca)p->participante1)->nombre); descomentar para ver recorrido de arboles (3/3)
    printf("elimino %s de a2\n",((Judoca)p->participante2)->nombre);*/
    *a1 = elimina(*a1,(Judoca)p->participante1);
    *a2 = elimina(*a2,(Judoca)p->participante2);

    if( (*a1) == NULL || (*a2) == NULL ) {
        return;
    }
    else {
        formarParejas(a1,a2,a_resultante);
    }
        
}



//declaro Arbol como puntero para modificar la referencia global, no solo la local de la función
int leerArch(char* nombreArchivo, Arbol* arbolEquipo1, Arbol* arbolEquipo2) { //se asume que los arboles se pasan declarados (NULL)

Judoca judoca=NULL;
judoca = malloc(sizeof(_Judoca));

char line[LONGITUD_MAX_LINEA];

// abrimos el archivo, con permisos de lectura
FILE* arch = fopen(nombreArchivo, "r");

if(!arch) {
    printf("no se pudo abrir archivo\n");
    return -1;
}

int arb = 0;
int line_count = 0;
    /*va a leer hasta que termine Equipo1 o, en su defecto, hasta que el archivo termine*/
    while (fgets(line, LONGITUD_MAX_LINEA, arch)) {
        /*si aparece la cadena Equipo1, la salteamos (queremos almacenar lo que le sigue)*/
        if ( ! strcmp(line,"Equipo1:\n")) {
            arb=1;
            continue; //reemplazar por bandera
        }
        /*si aparece la cadena Equipo2, la salteamos (queremos almacenar lo que le sigue)*/
        else if (! strcmp(line,"Equipo2:\n")) {
            arb=2;
            continue; //reemplazar por bandera
        }
            else {
                    if(arb==1) {
                        assign(line,judoca);
                        *arbolEquipo1 = agrega(*arbolEquipo1,judoca->nombre,judoca->apellido,judoca->edad,funcionCompararJudocas);
                    }
                    else if(arb==2) {
                        assign(line,judoca);
                        *arbolEquipo2 = agrega(*arbolEquipo2,judoca->nombre,judoca->apellido,judoca->edad,funcionCompararJudocas);
                    }
                    else 
                        return -1; //no pudo ser leido ningun arbol
                    
                line_count++;
            }
    }

    if ( ! fclose(arch) )
        printf("archivo leido joya\n\n");
    else 
        return -1; //archivo leido joyan't

    return 0;
}





//argv[1]->nombre arch entrada
//argv[2]->nombre arch salida

int main(int argc, char* argv[]) {
    Arbol a1, a2, arbolparejas;
    a1 = create();
    a2 = create();
    arbolparejas = create();

    if(leerArch(argv[1],&a1,&a2)<0) {
        printf("Hubo un problema al leer el archivo\n");
    }

muestraPreOrder(a1);
printf("-----\n");
muestraPreOrder(a2);
printf("-----\n");

formarParejas(&a1,&a2,&arbolparejas);

printf("parejas formadas:\n");
muestraPreOrderParejas(arbolparejas);
if(a1) {
    printf("--------------\nelementos sin matcheo de a1\n");
    muestraPreOrder(a1);
}
if(a2) {
    printf("--------------\nelementos sin matcheo de a2\n");
    muestraPreOrder(a2);
}
    printf("\nprograma retorna\n");
    return 0;
}


