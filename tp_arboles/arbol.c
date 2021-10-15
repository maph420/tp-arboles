#include "arbol.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

void ingresarString(char **ptr) {
    char temp[255];
    scanf("%[^\n]%*c", temp);
    (*ptr) = malloc(sizeof(char) * (strlen(temp) + 1));
    strcpy((*ptr), temp);
}

Arbol create(){
  return NULL;
}

int isEmpty(Arbol a){
    return a==NULL;
}

Arbol agrega(Arbol a, Judoca dato, Comparar c) {
	if (isEmpty(a)) {
        printf("foo----\n");
        a = malloc(sizeof(TNodo));
        a->dato = (Judoca)dato;
	    a->izq = NULL;
	    a->der = NULL;
  	}
	else {
		if (c(a->dato, dato)>0) {
            printf("lado izquierdo\n");
            a->izq = agrega(a->izq, dato,c);
        }
		else {
            printf("lado derecho\n");
            a->der = agrega(a->der, dato,c);
            
        }
	}
	return a;
}

void muestraPreOrder(Arbol a) {
	if (!isEmpty(a)) {
    	printf("%d\n", (int)a->dato);
    	muestraPreOrder(a->izq);
    	muestraPreOrder(a->der);
  	}
}


int miComparar ( void* dato1, void* dato2 ) {
    if(((Judoca)dato1)->edad > ((Judoca)dato2)->edad)
        return 1;
    else 
        return 0;
}

void prueba() {
    printf("funcion prueba");
    int *i = malloc(sizeof(int)*5);
    *i = 5;
    printf("%d\n", i[0]);
}
void testJudoca() {


printf("test\n");

Judoca j=NULL, j2=NULL;

j = malloc(sizeof(Judoca));
j2 = malloc(sizeof(Judoca));

strcpy(j->nombre,"nombre");
strcpy(j->apellido,"apellido");
j->edad=15;

strcpy(j2->nombre,"nombre2");
strcpy(j2->apellido,"apellido2");
j2->edad=20;

printf("test2\n");

Arbol a = create();
printf("test3\n");

prueba();
a = agrega(a,j,miComparar);
//a = agrega(a,j2,miComparar);
printf("test4\n");

//muestraPreOrder(a);

}




void cargar_agenda(Pareja* pareja) {
*pareja = NULL;

char* nombreArchivo;
Judoca judocaLeido;

printf("Ingrese el nombre del archivo del cual cargar\n: ");
ingresarString(&nombreArchivo);


/*
char bufNombre[255], bufApellido[255], bufEdad[255];
FILE* arch = fopen(nombreArchivo, "r");

 if (arch != NULL) {
        
        //En el archivo, los contactos estan almacenados uno por linea, con todos los campos juntos separados por comas. Forma de un archivo:
        //Roberto,100025,robertthemail@roberto.com,Francia 354,robertotelegram,robertoig
        //Marcos,558756,marcosmail@marcos.com,Alem 4720,marcosTelegram,marcosig
       // Guadalupe,55997755,guadalupemail@gudalupe.com,Echeverria 12,guadalupeTelgram,guadalupeig
        
        while (fscanf(arch, "%[^,],%[^,],%[^,],%[^\n]%*c", bufNombre, bufApellido, bufEdad) != EOF) {
            judocaLeido->nombre = strdup(bufNombre);
            judocaLeido->apellido = strdup(bufApellido);
            judocaLeido->edad = strdup(bufEdad);

           //pareja = ;
        }

*/
}
