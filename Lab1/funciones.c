#include <stdio.h>
#include <stdlib.h>
//#include "funciones.h"
#include "struct.h"

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
        if (fscanf(archivo, "%d %d", &listaP[i].posicion, &listaP[i].energia) != 2) {
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

//ecuacion de energia
float calcularEnergia(int N, int i, int j, float Ep) {
    float MIN_ENERGY = pow(10, -3) / N;
    float E = (pow(10, 3) * Ep) / N * (sqrt(abs(j - i) + 1));
    
    if (E >= MIN_ENERGY) {
        return E;
    }
    
    return 0;
}