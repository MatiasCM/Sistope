#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "struct.h"

//funcion que calcula la energia de una particula en una celda
double energia(int celdas, double energiaInicial, int posicionCelda, double energiaParticula, int posicionParticula){
    const double factorEnergia = pow(10.0, 3.0);
    const double factorMinimo = pow(10.0, -3.0);

    double distancia = (double)(abs(posicionParticula - posicionCelda) + 1.0);

    if (distancia == 0.0) {
        // Evitar la división por cero
        return energiaInicial;
    }

    double energiaRepartida = (factorEnergia * energiaParticula) / (celdas * sqrt(distancia));
    double energiaMinima = factorMinimo / celdas;

    return (energiaRepartida >= energiaMinima) ? (energiaInicial + energiaRepartida) : energiaInicial;
}

//funcion que crea el archivo de salida
void crearArchivo(double *arreglo, int numeroCeldas, char *fileName){
    FILE *fp = fopen(fileName, "a");
    for (int i = 0; i < numeroCeldas; i++){
        fprintf(fp, "%lf\n", arreglo[i]);
    }
    fclose(fp);
}

int main(int argc, char const *argv[]){
    int numeroCeldas = atoi(argv[1]);
    int pid = getpid();
    char fileName[50];
    sprintf(fileName, "worker%d.txt", pid);

    double *arregloCeldas = (double *)malloc(numeroCeldas * sizeof(double)); 

    char buffer[50];
    int lineas = 0;
    for (;;) {
        if (read(STDIN_FILENO, buffer, sizeof(buffer)) > 0) {
            if (strcmp(buffer, "FIN") == 0) {
                break;
            }

            int posicion;
            double energiaP;

            sscanf(buffer, "%d %lf", &posicion, &energiaP);

            for (int j = 0; j < numeroCeldas; j++) {
                arregloCeldas[j] = energia(numeroCeldas, arregloCeldas[j], j, energiaP, posicion);
            }

            lineas++;
        }
    }
    FILE *archivo = fopen(fileName, "w");
    for (int j = 0; j < numeroCeldas; j++)
    {
        fprintf(archivo, "%lf\n", arregloCeldas[j]);
    }

    crearArchivo(arregloCeldas, numeroCeldas, fileName);
    write(STDOUT_FILENO, &lineas, sizeof(int));
    write(STDOUT_FILENO, fileName, sizeof(fileName));
    free(arregloCeldas);
    return 0;
}