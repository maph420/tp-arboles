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

int funcionComparar ( void* dato1, int dato2 ) {
    return ( ((Judoca)dato1)->edad >= (int)dato2 ) ? 1 : 0 ; //>= ya que por convencion si un nodo es igual a otro, se coloca a la izquierda en el arbol
}

int funcionCompararPareja (void* dato1, int dato2) {
    return ( ((Pareja)dato1)->estadoPareja >= (int)dato2 ) ? 1 : 0 ;
}



void encolarArbol(Cola cola, Arbol arbol_a_encolar) {
    if(!(isEmpty(arbol_a_encolar))) {
        cola_encolar(cola,arbol_a_encolar->dato);
        encolarArbol(cola,arbol_a_encolar->izq);
        encolarArbol(cola,arbol_a_encolar->der);
    }
}



int deltaEdades(void* dato1, void* dato2) {
int d = ( (((Judoca)dato1)->edad) >= ((Judoca)dato2)->edad ) ? ((Judoca)dato1)->edad - ((Judoca)dato2)->edad : ((Judoca)dato2)->edad - ((Judoca)dato1)->edad;
return d;
}


int compararArboles(Arbol a1, Arbol a2, CompararNodos c, Arbol* arbolDeParejas) { //recorremos arbol a2, pasandole en cada vuelta un nodo distinto a la funcion que analiza r/arbol1
Cola cola_a1 = cola_crear();
Cola cola_a2 = cola_crear();



    /*printf("arbol1\n");
    muestraPreOrder(a1);
    printf("arbol2\n");
    muestraPreOrder(a2);*/

encolarArbol(cola_a1,a1);

Judoca judocaTop_a1, judocaTop_a2, bestMatch;
//int cond=0, encontroEnArbol1=0;

while(cola_a1->primero != -1) { //esto recorre la cola con los elementos de arbol 1
    //encontroEnArbol1=0;
    judocaTop_a1 = ((Judoca)cola_a1->datos[cola_a1->primero]);
    encolarArbol(cola_a2,a2);
    bestMatch = ((Judoca)cola_a2->datos[cola_a2->primero]);

    while(cola_a2->primero != -1) { //aca adentro puedo comparar los distintos elem de las colas

        judocaTop_a2 = ((Judoca)cola_a2->datos[cola_a2->primero]);

        printf("comparo edad %s (%d) con edad %s (%d)\n",judocaTop_a1->nombre,judocaTop_a1->edad,judocaTop_a2->nombre,judocaTop_a2->edad);
        printf("delta:%d\n",deltaEdades(judocaTop_a1,judocaTop_a2));
        if(deltaEdades(judocaTop_a1,judocaTop_a2) < deltaEdades(judocaTop_a1,bestMatch)) {

            printf("antiguo best match: %s(%d), nuevo best match: %s(%d)\n",bestMatch->nombre,bestMatch->edad,judocaTop_a2->nombre,judocaTop_a2->edad);
            bestMatch = judocaTop_a2;
        }
            

        cola_desencolar(cola_a2);

    }
    Pareja p = malloc(sizeof(_Pareja));
    p->participante1 = judocaTop_a1;
    p->participante2 = bestMatch;
    p->estadoPareja = 1;
    printf("---pareja formada: %s(%d) y %s(%d)\n",p->participante1->nombre,p->participante1->edad,p->participante2->nombre,p->participante2->edad);
    *arbolDeParejas = agrega_pareja(*arbolDeParejas,judocaTop_a1,bestMatch,1,funcionCompararPareja);

    a1 = elimina(a1,judocaTop_a1);
    a2 = elimina(a2,bestMatch);

    cola_desencolar(cola_a1);
}

    
    printf("\narbol de parejas\n");
    muestraPreOrderParejas(*arbolDeParejas);

    printf("termina\n");
	return 0;
}



int funcionComparaNodos(void* dato1, void* dato2) {

    int delta = ( (((Judoca)dato1)->edad) >= ((Judoca)dato2)->edad ) ? ((Judoca)dato1)->edad - ((Judoca)dato2)->edad : ((Judoca)dato2)->edad - ((Judoca)dato1)->edad;

    if( ((Judoca)dato1)->edad >= 18 && ((Judoca)dato2)->edad >= 18 ) {
        if (delta<=2) {
            printf("Se encontro matcheo (delta: %d)",delta);
            printf("-entre %s y %s\n",((Judoca)dato1)->nombre,((Judoca)dato2)->nombre);           
            

            printf("retorna la funcion\n");
            return 1;
        }
    }

    else if( ((Judoca)dato1)->edad < 18 && ((Judoca)dato2)->edad < 18 ) {
        if (delta<=1) {
            printf("Se encontro matcheo (delta: %d)",delta);
            printf("-entre %s y %s\n",((Judoca)dato1)->nombre,((Judoca)dato2)->nombre);
            return 1;
        }
}
    return 0;
}


//declaro Arbol como puntero para modificar la referencia global, no solo la local de la función
int leerArch(char* nombreArchivo, Arbol* arbolEquipo1, Arbol* arbolEquipo2) { //se asume que los arboles se pasan declarados (NULL)

Judoca judoca=NULL;
judoca = malloc(sizeof(_Judoca));

char line[LONGITUD_MAX_LINEA];

/*abrimos el archivo, con permisos de lectura*/
FILE* arch = fopen(nombreArchivo, "r");

if(!arch) {
    printf("no se pudo abrir archivo\n");
    return -1;
}
    //char primerLinea[LONGITUD_MAX_LINEA];
    //fscanf(arch, "%[^\n]", primerLinea);

int arb = 0;
int line_count = 0;
    /*va a leer hasta que termine Equipo1 o, en su defecto, hasta que el archivo termine*/
    while (fgets(line, LONGITUD_MAX_LINEA, arch)) {
        /*si aparece la cadena Equipo1, la salteamos (queremos almacenar lo que le sigue)*/
        if ( ! strcmp(line,"Equipo1:\n")) {
            arb=1;
            continue;
        }
        /*si aparece la cadena Equipo2, la salteamos (queremos almacenar lo que le sigue)*/
        else if (! strcmp(line,"Equipo2:\n")) {
            arb=2;
            continue;
        }
            else {
                    if(arb==1) {
                        assign(line,judoca);
                        *arbolEquipo1 = agrega(*arbolEquipo1,judoca->nombre,judoca->apellido,judoca->edad,funcionComparar);
                    }
                    else if(arb==2) {
                        assign(line,judoca);
                        *arbolEquipo2 = agrega(*arbolEquipo2,judoca->nombre,judoca->apellido,judoca->edad,funcionComparar);
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
    Arbol a1, a2, arbol_parejas;
    a1 = create();
    a2 = create();
    arbol_parejas = create();

    if(leerArch(argv[1],&a1,&a2)<0) {
        printf("Hubo un problema al leer el archivo\n");
    }

muestraPreOrder(a1);
printf("-----\n");
muestraPreOrder(a2);
printf("-----\n");

compararArboles(a1,a2,funcionComparaNodos,&arbol_parejas);

    printf("\nprograma retorna\n");
    return 0;
}


