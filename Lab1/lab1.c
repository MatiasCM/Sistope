#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "funciones.h"
#include <ctype.h>

int main(int argc, char **argv){

    char option;
    char *archivoEntrada = NULL;
    char *archivoSalida = NULL;
    int numeroCeldas;
    int imprimir;
    int obligatorioN = 0;
    int obligatorioI = 0;
    int obligatorioO = 0;

    while ((option = getopt(argc, argv, "N:i:o:D")) != -1){
        switch (option){
            //N es el numero de celdas que contendra el arreglo de energia de particulas
            case 'N':
                sscanf(optarg,"%d", &numeroCeldas);
                obligatorioN = 1;
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

    if (obligatorioN == 0 || obligatorioI == 0 || obligatorioO == 0){
        printf("Faltan banderas\n");
        return 0;
    }

    if (numeroCeldas < 1){
        printf("El numero de celdas N tiene que ser mayor o igual a 1\n");
        return 0;
    }

    Particula * listaP;
    int n;
    int archivo;
    archivo = leerArchivo(archivoEntrada, &listaP, &n);
    if (archivo == 1){
        return 0;
    }

    double * celdas =(double*)malloc(sizeof(double)*(numeroCeldas));
    int i = 0;
    while(i < numeroCeldas){
        celdas[i] = 0;
        i++;
    }

    int posicionMaxima;
    posicionMaxima = energia(numeroCeldas, n, listaP, celdas);
    archivo=crearArchivo(archivoSalida, celdas, numeroCeldas, posicionMaxima, celdas[posicionMaxima]);
    if (archivo == 1){
        free(listaP);
        free(celdas);
        return 0;
    }

    if(imprimir == 1){
        imprimirGrafico(numeroCeldas, celdas, posicionMaxima);
    }

    free(listaP);
    free(celdas);

}