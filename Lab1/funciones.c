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
        if (fscanf(archivo, "%d %f", &listaP[i].posicion, &listaP[i].energia) != 2) {
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
    float E = (pow(10,3) * Ep)/(N*(sqrt(abs(j-i)+1)));
    
    if (E >= MIN_ENERGY) {
        return E;
    }
    
    return 0;
}

int energia(int c, int p, Particula *listaP, float *listaC) {
    // Inicializar listaC con valores de energía de celda en 0
    for (int i = 0; i < c; i++) {
        listaC[i] = 0;
    }

    // Calcular y acumular la energía para cada partícula en su celda correspondiente
    for (int j = 0; j < p; j++) {
        int celda = listaP[j].posicion;
        if (celda >= 0 && celda < c) {
            listaC[celda] += calcularEnergia(c, celda, listaP[j].posicion, listaP[j].energia);
        }
    }

    // Encontrar la celda con la energía máxima
    float max = 0;
    int pos = 0;
    for (int i = 0; i < c; i++) {
        if (listaC[i] > max) {
            max = listaC[i];
            pos = i;
        }
    }

    return pos;
}

int crearArchivo(char *nombre, float *celdas, int n, int posicion, float max) {
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

//un main que no hace nada para pruebas
/*int main(int argc, char **argv) {
    return 0;
}*/