#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include "struct.h"
#include <math.h>

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

double calcularEnergia(int N, int i, int j, double Ep) {
    double MIN_ENERGY = pow(10, -3) / N;
    double E = (pow(10,3) * Ep)/(N*(sqrt(abs(j-i)+1)));
    
    if (E >= MIN_ENERGY) {
        return E;
    }
    
    return 0;
}

int energia(int nC, int nP, Particula * listaP, double * listaC){

    //doble ciclo que recorre las celdas y particulas y le asigna la energia celda por celda
	for(int i = 0 ; i < nC; i++){
		for(int j = 0 ; j < nP; j++){
            //Acumular energia
			listaC[i] = listaC[i]  + calcularEnergia(nC,i,listaP[j].posicion, listaP[j].energia );
        }
	}

    int pos = 0;
    double max = listaC[0]; // Inicializar con el valor de la primera celda
    for (int i = 1; i < nC; i++) { // Comenzar desde la segunda celda
        if (listaC[i] > max) {
            max = listaC[i];
            pos = i;
        }
    }
    return pos;
  
}

int crearArchivo(char *nombre, double *celdas, int n, int posicion, double max) {
    // Se abre el archivo en modo escritura
    FILE *archivo = fopen(nombre, "wt");
    
    // Se comprueba que el archivo no sea nulo
    if (archivo == NULL) {
        printf("No se ha podido abrir el fichero\n");
        return 1;
    }

    // Se escribe la energía de las celdas y se cierra el archivo
    fprintf(archivo, "%d %f\n", posicion, max);
    for (int i = 0; i < n; i++) {
        fprintf(archivo, "%d %f\n", i, celdas[i]);
    }

    fclose(archivo);
    return 0;
}

void imprimirGrafico(int nC, double * listaC, int posMax){
    double max=listaC[posMax];
    for(int i=0;i<nC;i++){
        double energiaNormalizada = (listaC[i]*50)/max;
        printf("%d %lf |",i,listaC[i]);
        for(int j=0;j<(int)energiaNormalizada;j++){
            printf("o");
        }
        printf("\n");
    }
}