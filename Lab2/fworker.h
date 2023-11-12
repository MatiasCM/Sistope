#ifndef fworker_h_
#define fworker_h_
#include "struct.h"

//funcion que calcula la energia de una particula en una celda
double energia(int celdas, double energiaInicial, int posicionCelda, double energiaParticula, int posicionParticula);

//funcion que crea el archivo de salida
void crearArchivo(double *arreglo, int numeroCeldas, char *fileName);

#endif // fworker_h_