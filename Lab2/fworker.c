#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "struct.h"
#include "fworker.h"

//Entradas: cantidad de celdas (int), energia inicial de la celda (double), posicion de la celda (int), energia de la particula (double), posicion de la particula (int)
//Salida: energia obtenida de la celda impactada por la particula (double)
//Descripcion: funcion que calcula la energia de una particula en una celda
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

//Entradas: arreglo de celdas (double), cantidad de celdas (int), archivo de salida (char)
//Salida: void
//Descripcion: funcion que crea el archivo de salida
void crearArchivo(double *arreglo, int numeroCeldas, char *fileName){
    FILE *fp = fopen(fileName, "a");
    for (int i = 0; i < numeroCeldas; i++){
        fprintf(fp, "%lf\n", arreglo[i]);
    }
    fclose(fp);
}