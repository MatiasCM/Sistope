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

    while ((option = getopt(argc, argv, "N:i:o:D")) != -1){
        switch (option){
            //N es el numero de celdas que contendra el arreglo de energia de particulas
            case 'N':
                sscanf(optarg,"%d", &numeroCeldas);
                break;
            //i es el nombre del archivo de entrada
            case 'i':
                archivoEntrada= optarg;
                break;   
            //o es el nombre del archivo de salida                      
            case 'o':
                archivoSalida= optarg;
                break;
            //D es una bandera que muestra los "o"
            case 'D':
                //cosas
                break;
            
            //protocolo de correcion si es que se entrega una opcion invalida
            case '?':
                if (optopt == 'N' || optopt == 'i' || optopt == 'o' || optopt == 'D'){
                    fprintf(stderr, "Opcion -%c requiere un argumento.\n", optopt);
                }
                else if (isprint(optopt)){
                    fprintf(stderr, "Opcion desconocida `-%c'.\n", optopt);
                }
                else{
                    fprintf(stderr, "Opcion con caracter desconocido `\\x%x'.\n", optopt);
                }
                return 1;
            default:
                abort();
        
        }
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

    float * celdas =(float*)malloc(sizeof(float)*(numeroCeldas));
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

    free(listaP);
    free(celdas);

}