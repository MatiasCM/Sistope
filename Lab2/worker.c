#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "struct.h"
#include "fworker.h"

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
