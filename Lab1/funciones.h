#ifndef funciones_h_
#define funciones_h_
#include "struct.h"

int leerArchivo(char *nombre , Particula **lista, int * cantidad);

double calcularEnergia(int N, int i, int j, double Ep);

int energia(int c, int p, Particula *listaP, double *listaC);

int crearArchivo(char *nombre, double *celdas, int n, int posicion, double max);

void imprimirGrafico(int nC, double * listaC, int posMax);

#endif // funciones_h_