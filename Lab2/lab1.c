#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <ctype.h>

int main(int argc, char **argv){

    char option;
    char *archivoEntrada = NULL;
    char *archivoSalida = NULL;
    int numeroCeldas;
    int imprimir;
    int numeroProcesos;
    int numeroChunks;
    int obligatorioN = 0;
    int obligatorioP = 0;
    int obligatorioI = 0;
    int obligatorioC = 0;
    int obligatorioO = 0;

    while ((option = getopt(argc, argv, "N:P:i:o:c:D")) != -1){
        switch (option){
            //N es el numero de celdas que contendra el arreglo de energia de particulas
            case 'N':
                sscanf(optarg,"%d", &numeroCeldas);
                obligatorioN = 1;
                break;
            //P es el numero de procesos (workers)
            case 'P':
                sscanf(optarg,"%d", &numeroProcesos);
                obligatorioP = 1;
                break;
            //i es el nombre del archivo de entrada
            case 'i':
                archivoEntrada= optarg;
                obligatorioI = 1;
                break;   
            //o es el nombre del archivo de salida                      
            case 'o':
                archivoSalida= optarg;
                obligatorioO = 1;
                break;
            //c es el numero de chunks
            case 'c':
                sscanf(optarg,"%d", &numeroChunks);
                obligatorioC = 1;
                break;
            //D es una bandera que muestra los "o"
            case 'D':
                imprimir = 1;
                break;
            
            //protocolo de correcion si es que se entrega una opcion invalida
            case '?':
                printf("Opcion invalida\n");
                return 1;
            default:
                abort();
        }
    }

    if (obligatorioN == 0 || obligatorioP == 0 || obligatorioI == 0 || obligatorioC == 0 || obligatorioO == 0){
        printf("Faltan banderas\n");
        return 0;
    }

    if (numeroCeldas < 1){
        printf("El numero de celdas N tiene que ser mayor o igual a 1\n");
        return 0;
    }

    if (numeroProcesos < 1){
        printf("El numero de procesos P tiene que ser mayor o igual a 1\n");
        return 0;
    }

    if (numeroChunks < 1){
        printf("El numero de chunks c tiene que ser mayor o igual a 1\n");
        return 0;
    }

}