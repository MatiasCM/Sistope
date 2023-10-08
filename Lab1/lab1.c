#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

int main(int argc, char **argv){

    char option;
    char *archivoEntrada;
    char *archivoSalida;
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
          
        
        }
    }

    if (numeroCeldas < 1){
        printf("El numero de celdas N tiene que ser mayor o igual a 1\n");
        return 0;
    }
}