#ifndef fworker_h_
#define fworker_h_
#include "struct.h"

//Entradas: cantidad de celdas (int), energia inicial de la celda (double), posicion de la celda (int), energia de la particula (double), posicion de la particula (int)
//Salida: energia obtenida de la celda impactada por la particula (double)
//Descripcion: funcion que calcula la energia de una particula en una celda
double energia(int celdas, double energiaInicial, int posicionCelda, double energiaParticula, int posicionParticula);

//Entradas: arreglo de celdas (double), cantidad de celdas (int), archivo de salida (char)
//Salida: void
//Descripcion: funcion que crea el archivo de salida
void crearArchivo(double *arreglo, int numeroCeldas, char *fileName);

#endif // fworker_h_