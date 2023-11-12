#ifndef fbroker_h_
#define fbroker_h_
#include "struct.h"

//Entradas: arreglo de celdas (double), cantidad de celdas (int)
//Salida: indice de la celda con mayor energia (int)
//Descripcion: funcion que retorna el indice de la celda con mayor energia
int maximo(double *listaC, int numeroCeldas);

//Entradas: arreglo de lineas trabajadas por worker (int), cantidad de celdas (int), arreglo de celdas (double), indice de la celda con mayor energia (int), cantidad de workers (int)
//Salida: void
//Descripcion: funcion que imprime el grafico normalizado
void imprimirGrafico(int * lineas, int nC, double *listaC, int posMax, int numeroProcesos);

//Entradas: cantidad de workers (int), pipeline worker to broker, pipeline broker to worker, 
//Salida: void
//Descripcion: funcion que crea los workers
void workers(int numeroProcesos, int pipeWB[][2], int pipeBW[][2], char *argv[]);

//Entradas: cantidad de celdas (int), cantidad de procesos (int), arreglo de celdas (double), pipeline worker to broker, arreglo de lineas trabajadas por worker (int)
//Salida: void
//Descripcion: funcion que lee la informacion proporcionada por los workers
void leer(int numeroCeldas, int numeroProcesos, double *listaC, int pipeWB[][2], int *lineasTrabajadasPorWorker);

//Entradas: archivo de entrada (char), cantidad de chunks (int), cantidad de procesos(int), pipeline broker to worker
//Salida: void
//Descripcion: funcion que envia la lineas que leeran los workers
void enviarLineas(const char *input, int chunks, int workers, int pipeBW[][2]);

//Entradas: arreglo de celdas (double), cantidad de celdas (int), archivo de salida (char)
//Salida: void
//Descripcion: funcion que crea el archivo de salida
void crearArchivoSalida(double *listaC, int celdas, const char *output);

#endif // fbroker_h_