//main:c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbol.h"


//maso lo que faltaria es hacer la salida prolija, liberar memoria y hacer mas lejible el codigo

void assign(char* line, Judoca judocaToAssign) {
            judocaToAssign->nombre = strdup(strtok(line,","));
            judocaToAssign->apellido = strdup(strtok(NULL,",")); // NULL is passed as first argument since strtok maintains a static pointer to your previous passed string
            judocaToAssign->edad = atoi(strtok(NULL,"\n"));
}

int funcionCompararJudocas ( void* dato1, int dato2 ) {
    return ( ((Judoca)dato1)->edad >= (int)dato2) ? 1 : 0 ; //>= ya que por convencion si un nodo es igual a otro, se coloca a la izquierda en el arbol
}

int funcionCompararParejas (void* dato1, int dato2) {
    return ( ((Pareja)dato1)->estadoPareja >= (int)dato2 ) ? 1 : 0 ;
}

int deltaEdades(void* dato1, void* dato2) {
return ( (((Judoca)dato1)->edad) >= ((Judoca)dato2)->edad ) ? ((Judoca)dato1)->edad - ((Judoca)dato2)->edad : ((Judoca)dato2)->edad - ((Judoca)dato1)->edad;
}

int obtenerEstadoJudoca(void* j1, void* j2) {
    if ( ( ((Judoca)j1)->edad >= 18 && ((Judoca)j2)->edad < 18) || ( ((Judoca)j1)->edad < 18 && ((Judoca)j2)->edad >=18 ) )
        return PAREJA_ENTRE_MAYOR_Y_MENOR;

    else if ( ( ((Judoca)j1)->edad <18 && ((Judoca)j2)->edad <18 ) && (deltaEdades((Judoca)j1,(Judoca)j2) > 1) )
        return PAREJA_MENOR_EXCEDE_DIFERENCIA_EDAD;

    else if ( ( ((Judoca)j1)->edad >=18 && ((Judoca)j2)->edad >=18 ) && (deltaEdades((Judoca)j1,(Judoca)j2) > 2) ) 
        return PAREJA_MAYOR_EXCEDE_DIFERENCIA_EDAD;  

    else 
        return PAREJA_VALIDA;
}

Pareja parejaMinDiferenciaEdad (Judoca nodoAComparar, Arbol a, Judoca mejorMatch) {
    Pareja p;
    if (!isEmpty(a)) { //recorro arbol 1 y me fijo el mejor matcheo con un elemento de arbol 2, sino el elemento mas chico
        if(mejorMatch == NULL) {
            mejorMatch = (Judoca)a->dato;
            //printf("primer recorrido: mejormatch: %s\n",((Judoca)a->dato)->nombre);
        }
        else if (deltaEdades((Judoca)nodoAComparar,(Judoca)a->dato) < deltaEdades((Judoca)nodoAComparar,(Judoca)mejorMatch)) {
            //printf("nuevo mejormatch: %s\n",((Judoca)a->dato)->nombre);
            mejorMatch = (Judoca)a->dato;
        }
        /*else {
            printf("delta edades con el mejor match: %d\n",deltaEdades((Judoca)nodoAComparar,(Judoca)mejorMatch));
            printf("delta edades con nodo actual (%s / %d): %d\n",((Judoca)a->dato)->nombre,((Judoca)a->dato)->edad,deltaEdades((Judoca)nodoAComparar,(Judoca)a->dato));
        }*/
            if (nodoAComparar->edad >= ((Judoca)a->dato)->edad) {
                return parejaMinDiferenciaEdad(nodoAComparar,a->izq,mejorMatch); //compara solo hasta aca, luego es NULL
            }
            else {
                return parejaMinDiferenciaEdad(nodoAComparar,a->der,mejorMatch);
            }
                
    }        
    else {
        p = malloc(sizeof(_Pareja));
        p->participante1 = nodoAComparar;
        p->participante2 = mejorMatch;
        p->estadoPareja = obtenerEstadoJudoca((Judoca)nodoAComparar,(Judoca)mejorMatch);
        return p;
    }
}

void formarParejas(Arbol* a1, Arbol* a2, Arbol* a_resultante) {
    Judoca aux_match = NULL;
    Pareja pareja_formada = parejaMinDiferenciaEdad((Judoca)((*a1)->dato),*a2,aux_match);
    //if(pareja_formada == NULL) return; //se llego al maximo numero de parejas formadas (lo restante de a1 o de a2 se quedara sin pareja)

    *a_resultante = agrega_pareja(*a_resultante,pareja_formada->participante1,pareja_formada->participante2,pareja_formada->estadoPareja,funcionCompararParejas);

    *a1 = elimina(*a1,(Judoca)pareja_formada->participante1);
    *a2 = elimina(*a2,(Judoca)pareja_formada->participante2);

    if ( isEmpty(*a1) || isEmpty(*a2) ) 
        return;
    else 
        formarParejas(a1,a2,a_resultante);
}



//declaro Arbol como puntero para modificar la referencia global, no solo la local de la función
int leerArch(char* archivo_entrada, Arbol* arbolEquipo1, Arbol* arbolEquipo2) { //se asume que los arboles se pasan declarados (NULL)

Judoca judoca=NULL;
judoca = malloc(sizeof(_Judoca));

char line[LONGITUD_MAX_LINEA];

// abrimos el archivo, con permisos de lectura
FILE* arch = fopen(archivo_entrada, "r");

if(!arch) {
    printf("no se pudo abrir archivo\n");
    return -1;
}

int numeroArbol = 0;
int esLineaDeEquipo=0;
    /*va a leer hasta que termine Equipo1 o, en su defecto, hasta que el archivo termine*/
    while (fgets(line, LONGITUD_MAX_LINEA, arch)) {
        esLineaDeEquipo=0;

        /*si aparece la cadena Equipo1, la salteamos (queremos almacenar lo que le sigue)*/
        if ( ! strcmp(line,"Equipo1:\n")) {
            numeroArbol=1;
            esLineaDeEquipo=1;
        }

        /*si aparece la cadena Equipo2, la salteamos (queremos almacenar lo que le sigue)*/
        else if (! strcmp(line,"Equipo2:\n")) {
            numeroArbol=2;
            esLineaDeEquipo=1;
        }

            else {
                    if(numeroArbol==1 && !esLineaDeEquipo) {
                        assign(line,judoca);
                        *arbolEquipo1 = agrega(*arbolEquipo1,judoca->nombre,judoca->apellido,judoca->edad,funcionCompararJudocas);
                    }
                    else if(numeroArbol==2 && !esLineaDeEquipo) {
                        assign(line,judoca);
                        *arbolEquipo2 = agrega(*arbolEquipo2,judoca->nombre,judoca->apellido,judoca->edad,funcionCompararJudocas);
                    }
                    else 
                        return -1; //no pudo ser leido ningun arbol
            }
    }

    if ( ! fclose(arch) )
        printf("\nEl archivo se ha leido correctamente\n");
    else 
        return -1; //archivo no leido

    return 0;
}



char* mensajeEstado(estadoDePareja est) {
    switch (est)
    {
    case PAREJA_ENTRE_MAYOR_Y_MENOR:
        return "Pareja entre mayor y menor\n";
    break;
    case PAREJA_MENOR_EXCEDE_DIFERENCIA_EDAD:
        return "Pareja de menores con mas de 1 año de diferencia\n";
    break;
    case PAREJA_MAYOR_EXCEDE_DIFERENCIA_EDAD:
        return "Pareja de mayores con mas de 2 años de diferencia\n";
    break;
    case PAREJA_VALIDA:
        return "Pareja Valida\n";
    break;
    default:
        return NULL;
        break;
    }
}

void recorrer_y_guardar_pareja(Arbol arbolparejas, FILE* arch) {
    if (!isEmpty(arbolparejas)) {
        estadoDePareja estado = ((Pareja)arbolparejas->dato)->estadoPareja;
        char* mensajeEstadoPareja = mensajeEstado(estado);
        fprintf(arch, "\t%s %s\t\t%10s\t\t%s %s\t\t%s\t\t\n",((Pareja)arbolparejas->dato)->participante1->nombre,((Pareja)arbolparejas->dato)->participante1->apellido,"vs",((Pareja)arbolparejas->dato)->participante2->nombre,((Pareja)arbolparejas->dato)->participante2->apellido,mensajeEstadoPareja);
        recorrer_y_guardar_pareja(arbolparejas->izq,arch);
        recorrer_y_guardar_pareja(arbolparejas->der,arch);
    }
}

void recorrer_y_guardar_arbol(Arbol arbolparejas, FILE* arch) {
    if(!isEmpty(arbolparejas)){
        fprintf(arch,"\t%s %s (%d %s)\n",((Judoca)arbolparejas->dato)->nombre,((Judoca)arbolparejas->dato)->apellido,((Judoca)arbolparejas->dato)->edad,"años");
        recorrer_y_guardar_arbol(arbolparejas->izq,arch);
        recorrer_y_guardar_arbol(arbolparejas->der,arch);
    }

}


void guardar_parejas(Arbol a1, Arbol a2, Arbol arbolparejas, char* archivo_salida) {
    /*abrimos archivo, esta vez con permisos de escritura*/
    FILE* arch = fopen(archivo_salida,"w");
    if (arch != NULL) {
        fprintf(arch,"%s\n","\t-----Parejas formadas-----\t");
        recorrer_y_guardar_pareja(arbolparejas,arch);
        
    if (a1 != NULL) {
        fprintf(arch,"%s\n","\t-----Participantes sin pareja-----\t");
        recorrer_y_guardar_arbol(a1,arch);
    }
    else if (a2 != NULL) {
        fprintf(arch,"%s\n","\t-----Participantes sin pareja-----\t");
        recorrer_y_guardar_arbol(a2,arch);
    }

         if ( ! fclose(arch))
            printf("\nEl archivo se ha guardado con exito\n");
            else printf("Hubo un problema al guardar el archivo.\n");
    }
    else printf("Hubo un problema al guardar el archivo.\n");
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

    formarParejas(&a1,&a2,&arbolparejas);
    guardar_parejas(a1,a2,arbolparejas,argv[2]);

    ///printf("\n...\n");
}


