#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbol.h"

void assign(char* line, Judoca judocaToAssign) {
            judocaToAssign->nombre = strdup(strtok(line,","));
            judocaToAssign->apellido = strdup(strtok(NULL,",")); // NULL is passed as first argument since strtok maintains a static pointer to your previous passed string
            judocaToAssign->edad = atoi(strtok(NULL,"\n"));
}


int funcionCompararEdadesJudoca ( void* dato1, int dato2 ) {
    return ( ((Judoca)dato1)->edad >= (int)dato2 ) ? 1 : 0 ; //>= ya que por convencion si un nodo es igual a otro, se coloca a la izquierda en el arbol
}


int funcionComparaNodos(void* dato1, Judoca dato2, Arbol* a1, Arbol* a2) {
    int delta = ( (((Judoca)dato1)->edad) >= ((Judoca)dato2)->edad ) ? ((Judoca)dato1)->edad - ((Judoca)dato2)->edad : ((Judoca)dato2)->edad - ((Judoca)dato1)->edad;
    if(((Judoca)dato1)->edad >= 18 && ((Judoca)dato2)->edad >= 18)
        if (delta<=2) {
            printf("Se encontro matcheo (delta: %d)",delta);
            printf("    entre %s y %s\n",((Judoca)dato1)->nombre,((Judoca)dato2)->nombre);
            //*a1 = elimina(*a1,((Judoca)dato1)->edad);
            //*a2 = elimina(*a2,((Judoca)a2)->edad);
            /*printf("arbol1:\n");
            muestraPreOrder(*a1);
            printf("arbol2:\n");
            muestraPreOrder(*a2);*/
            return 1;
    }
        else {
            //printf("delta excedido, %d (%s y %s)\n",delta,((Judoca)dato1)->nombre,((Judoca)dato2)->nombre);
            return 0;
        }
    else if(((Judoca)dato1)->edad < 18 && ((Judoca)dato2)->edad < 18)
            if (delta<=1) {
            printf("Se encontro matcheo (delta: %d)\n",delta);
            printf("Matcheo entre %s y %s\n",((Judoca)dato1)->nombre,((Judoca)dato2)->nombre);
            //*a1 = elimina(*a1,((Judoca)dato1)->edad);
            //*a2 = elimina(*a2,((Judoca)a2)->edad);
            return 1;
    }
            else {
                //printf("delta excedido, %d (%s y %s)\n",delta,((Judoca)dato1)->nombre,((Judoca)dato2)->nombre);
                return 0;
            }
    else return 0;
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
            arb++;
            continue;
        }
        /*si aparece la cadena Equipo2, la salteamos (queremos almacenar lo que le sigue)*/
        else if (! strcmp(line,"Equipo2:\n")) {
            arb++;
            continue;
        }
            else {
                    if(arb==1) {
                        assign(line,judoca);
                        *arbolEquipo1 = agrega(*arbolEquipo1,judoca->nombre,judoca->apellido,judoca->edad,funcionCompararEdadesJudoca);
                    }
                    else if(arb==2) {
                        assign(line,judoca);
                        *arbolEquipo2 = agrega(*arbolEquipo2,judoca->nombre,judoca->apellido,judoca->edad,funcionCompararEdadesJudoca);
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

    //muestraPreOrder(*arbolEquipo1); 
    //printf("retorna\n");
    return 0;
}




//argv[1]->nombre arch entrada
//argv[2]->nombre arch salida

int main(int argc, char* argv[]) {
    Arbol a1, a2;
    a1 = create();
    a2 = create();
    if(leerArch(argv[1],&a1,&a2)<0) {
        printf("Hubo un problema al leer el archivo\n");
    }

muestraPreOrder(a1);
printf("-----\n");
muestraPreOrder(a2);
printf("-----\n");
compararArboles(a1,a2,funcionComparaNodos);
//testJudoca();

}


