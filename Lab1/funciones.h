#ifndef funciones_h_
#define funciones_h_
#include "struct.h"

int leerArchivo(char *nombre , Particula **lista, int * cantidad);

float calcularEnergia(int N, int i, int j, float Ep);

int energia(int c, int p, Particula *listaP, float *listaC);

int crearArchivo(char *nombre, float *celdas, int n, int posicion, float max);

#endif // funciones_h_