#ifndef fbroker_h_
#define fbroker_h_
#include "struct.h"

//funcion que retorna el indice de la celda con mayor energia
int maximo(double *listaC, int numeroCeldas);

//funcion que imprime el grafico de barras
void imprimirGrafico(int * lineas, int nC, double *listaC, int posMax, int numeroProcesos);

//funcion que crea los pipes
void crearPipes(int numeroProcesos, int pipeWB[][2], int pipeBW[][2]);

//funcion que crea los workers
void workers(int numeroProcesos, int pipeWB[][2], int pipeBW[][2], char *argv[]);

//funcion que lee la informacion proporcionada por los workers
void leer(int numeroCeldas, int numeroProcesos, double *listaC, int pipeWB[][2], int *lineasTrabajadasPorWorker);

//funcion que envia la lineas que leeran los workers
void enviarLineas(const char *input, int chunks, int workers, int pipeBW[][2]);

//funcion que crea el archivo de salida
void crearArchivoSalida(double *listaC, int celdas, const char *output);

#endif // fbroker_h_