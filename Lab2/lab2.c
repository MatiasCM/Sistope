#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>
#include "struct.h"

int main(int argc, char *argv[]){

    char option;
    char archivoEntrada[100];
    char archivoSalida[100];
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
                strcpy(archivoEntrada, optarg);
                // Verificacion del archivo de entrada
                FILE *fp = fopen(archivoEntrada, "r");
                if (fp == NULL){ // Verificamos que el archivo exista
                    printf("El archivo indicado en -i no existe.\n");
                    exit(0);
                }

                if (fgetc(fp) == EOF){ // Verificamos que el archivo no este vacio
                    printf("El archivo indicado en -i está vacío.\n");
                    exit(0);
                }
                fclose(fp);
                obligatorioI = 1;
                break;   
            //o es el nombre del archivo de salida                      
            case 'o':
                strcpy(archivoSalida, optarg);
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

    int pid = fork(); 
    if (pid == 0){
        char N[100];
        char P[100];
        char c[100];
        char D[100];
        sprintf(N, "%d", numeroCeldas);
        sprintf(P, "%d", numeroProcesos);
        sprintf(c, "%d", numeroChunks);
        sprintf(D, "%d", imprimir);
        char *args[] = {"./broker", N, P, archivoEntrada, archivoSalida, c, D, NULL};
        execv(args[0], args);
        exit(0);
    }
    wait(NULL);

    return 0;

}