#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include "struct.h"
#include <math.h>

//Entradas: nombre del archivo de entrada (char), arreglo de particulas (Particula), cantidad de particulas (int)
//Salida: int 0/1
//Descripcion: lee un archivo de tipo FILE y almacena en un arreglo de Particulas la informacion de cada una (posicion y energia)
int leerArchivo(char *nombre, Particula **lista, int *cantidad) {
    int n;
    Particula *listaP = NULL;

    FILE *archivo = fopen(nombre, "r");
    if (archivo == NULL) {
        printf("El archivo de entrada no existe o está corrompido\n");
        return 1;
    }

    if (fscanf(archivo, "%d", &n) != 1) {
        printf("Error al leer el número de partículas\n");
        fclose(archivo);
        return 1;
    }

    listaP = (Particula *)malloc(sizeof(Particula) * n);
    if (listaP == NULL) {
        printf("Error de asignación de memoria\n");
        fclose(archivo);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (fscanf(archivo, "%d %lf", &listaP[i].posicion, &listaP[i].energia) != 2) {
            printf("Error al leer los datos de la partícula %d\n", i + 1);
            free(listaP);
            fclose(archivo);
            return 1;
        }
    }

    *lista = listaP;
    *cantidad = n;

    fclose(archivo);
    return 0;
}

//Entradas: numero de celdas (int), indice de la celda (int), posicion de la particula (int), energia de la particula (double)
//Salida: energia obtenida (double)
//Descripcion: calcula mediante la formula, la energia que va a recibir cada celda de una particula correspondiente
double calcularEnergia(int N, int i, int j, double Ep) {
    float MIN_ENERGY = pow(10, -3) / N;
    double E = (pow(10,3) * Ep)/(N*(sqrt(abs(j-i)+1)));
    
    if (E >= MIN_ENERGY) {
        return E;
    }
    
    return 0;
}

//Entradas: numero de celdas (int), numero de particulas (int), arreglo de particulas (Particula), arreglo de celdas (double)
//Salida: posicion de la celda con mayor energia acumulada (int)
//Descripcion: calcula la energia acumulada de cada celda y luego identifica la celda con mayor energia
int energia(int nC, int nP, Particula * listaP, double * listaC){

	for(int i = 0 ; i < nC; i++){
		for(int j = 0 ; j < nP; j++){
			listaC[i] = listaC[i]  + calcularEnergia(nC,i,listaP[j].posicion, listaP[j].energia );
        }
	}

    int pos = 0;
    double max = listaC[0];
    for (int i = 1; i < nC; i++) {
        if (listaC[i] > max) {
            max = listaC[i];
            pos = i;
        }
    }
    return pos;
  
}

//Entradas: nombre del archivo de salida (char), arreglo de celdas (double), numero de celdas (int), 
//posicion de la celda con mayor energia (int), celda con la mayor energia (double)
//Salida: int 1/0
//Descripcion: crea un archivo de salida donde se imprime cada celda con su energia acumulada, imprimiendo primero la con mayor energia
int crearArchivo(char *nombre, double *celdas, int n, int posicion, double max) {
    FILE *archivo = fopen(nombre, "wt");

    if (archivo == NULL) {
        printf("No se ha podido abrir el fichero\n");
        return 1;
    }

    fprintf(archivo, "%d %f\n", posicion, max);
    for (int i = 0; i < n; i++) {
        fprintf(archivo, "%d %f\n", i, celdas[i]);
    }

    fclose(archivo);
    return 0;
}

//Entradas: numero de celdas (int), arreglo de celdas (double), posicion de la celda con mayor energia (int)
//Salida: void
//Descripcion: imprime por consola un grafico normalizado de las energias en cada celda
void imprimirGrafico(int nC, double *listaC, int posMax){
    double max = listaC[posMax];
    for(int i = 0; i < nC; i++){
        double energiaNormalizada = (listaC[i]*50)/max;
        printf("%d %f| ",i,listaC[i]);
        for(int j = 0; j < (int)energiaNormalizada; j++){
            printf("o");
        } 
        printf("\n");
    }
}