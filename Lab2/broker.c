#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "struct.h"
#include <sys/wait.h>
#include <time.h>
#include "fbroker.h"

int main(int argc, char *argv[]){

    int numeroCeldas = atoi(argv[1]);
    int numeroProcesos = atoi(argv[2]);
    
    char entrada[100];
    strcpy(entrada, argv[3]);
    char salida[100];
    strcpy(salida, argv[4]);

    int numeroChunks = atoi(argv[5]);
    int imprimir = atoi(argv[6]);

    //pipes
    int pipeWB[numeroProcesos][2]; //pipe worker -> broker
    int pipeBW[numeroProcesos][2]; //pipe broker -> worker

    for (int i = 0; i < numeroProcesos; i++){
        if (pipe(pipeWB[i]) == -1 || pipe(pipeBW[i]) == -1){
            printf("No se pudo crear el pipe\n");
            exit(0);
        }
    }
    workers(numeroProcesos, pipeWB, pipeBW, argv);    
    enviarLineas(entrada, numeroChunks, numeroProcesos, pipeBW);
    

    wait(NULL);

    double *listaC = (double *)malloc(numeroCeldas * sizeof(double));
    int *lineasWorker = (int *)malloc(numeroProcesos * sizeof(int));


    leer(numeroCeldas, numeroProcesos, listaC, pipeWB, lineasWorker);

    //cerrarPipes(numeroProcesos, pipeWB, pipeBW); 
    for (int i = 0; i < numeroProcesos; i++){
        close(pipeWB[i][0]);
        close(pipeBW[i][1]);
    }      

    crearArchivoSalida(listaC, numeroCeldas, salida);  


    if (imprimir == 1)
    {
        int pos = maximo(listaC, numeroCeldas);
        //mostrar_resultado(lineasWorker, listaC, numeroCeldas, numeroProcesos);
        imprimirGrafico(lineasWorker, numeroCeldas, listaC, pos, numeroProcesos);
    }

    free(listaC);
    free(lineasWorker);
    return 0;

}
