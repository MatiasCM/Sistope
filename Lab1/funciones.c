#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include "struct.h"
#include <math.h>

int leerArchivo(char *nombre, Particula **lista, int *cantidad) {
    int n;
    Particula *listaP = NULL;

    FILE *archivo = fopen(nombre, "r");
    if (archivo == NULL) {
        printf("El archivo de entrada no existe o está corrompido\n");
        return 1;
    }

    if (fscanf(archivo, "%d", &n) != 1) {
        printf("Error al leer el número de partículas\n");
        fclose(archivo);
        return 1;
    }

    listaP = (Particula *)malloc(sizeof(Particula) * n);
    if (listaP == NULL) {
        printf("Error de asignación de memoria\n");
        fclose(archivo);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (fscanf(archivo, "%d %f", &listaP[i].posicion, &listaP[i].energia) != 2) {
            printf("Error al leer los datos de la partícula %d\n", i + 1);
            free(listaP);
            fclose(archivo);
            return 1;
        }
    }

    *lista = listaP;
    *cantidad = n;

    fclose(archivo);
    return 0;
}

//ecuacion de energia
float calcularEnergia(int N, int i, int j, float Ep) {
    float MIN_ENERGY = pow(10, -3) / N;
    float E = (pow(10,3) * Ep)/(N*(sqrt(abs(j-i)+1)));
    
    if (E >= MIN_ENERGY) {
        return E;
    }
    
    return 0;
}

/*int energia(int nC, int nP, Particula *listaP, float *listaC) {
    // Inicializar la listaC con ceros
    for (int i = 0; i < nC; i++) {
        listaC[i] = 0.0;
    }

    // Inicializar un arreglo para registrar los cambios en listaC
    int cambios[nC];
    for (int i = 0; i < nC; i++) {
        cambios[i] = 0;
    }

    // Calcular la energía para cada partícula y acumularla en la celda correspondiente
    for (int j = 0; j < nP; j++) {
        int celda = listaP[j].posicion;
        float energia = listaP[j].energia;

        // Acumular la energía en la celda correspondiente
        listaC[celda] += calcularEnergia(nC, celda, listaP[j].posicion, energia);

        // Registrar el cambio en la celda
        cambios[celda] = 1;
    }

    // Encontrar la celda con la energía máxima
    float max = listaC[0];
    int pos = 0;

    for (int i = 1; i < nC; i++) {
        if (listaC[i] > max) {
            max = listaC[i];
            pos = i;
        }
    }

    // Realizar los cambios en listaC
    for (int i = 0; i < nC; i++) {
        if (cambios[i] == 1) {
            listaC[i] = max;
        }
    }

    return pos;
}*/





int energia(int nC, int nP, Particula * listaP, float * listaC){

    //doble ciclo que recorre las celdas y particulas y le asigna la energia celda por celda
	for(int i = 0 ; i < nC; i++){
		for(int j = 0 ; j < nP; j++){
            //Acumular energia
			listaC[i] = listaC[i]  + calcularEnergia(nC,i,listaP[j].posicion, listaP[j].energia );
        }
	}

    int pos = 0;
    float max = listaC[0]; // Inicializar con el valor de la primera celda
    for (int i = 1; i < nC; i++) { // Comenzar desde la segunda celda
        if (listaC[i] > max) {
            max = listaC[i];
            pos = i;
        }
    }
    return pos;
  
}

int crearArchivo(char *nombre, float *celdas, int n, int posicion, float max) {
    // Se abre el archivo en modo escritura
    FILE *archivo = fopen(nombre, "wt");
    
    // Se comprueba que el archivo no sea nulo
    if (archivo == NULL) {
        printf("No se ha podido abrir el fichero\n");
        return 1;
    }

    // Se escribe la energía de las celdas y se cierra el archivo
    fprintf(archivo, "%d %f\n", posicion, max);
    for (int i = 0; i < n; i++) {
        fprintf(archivo, "%d %f\n", i, celdas[i]);
    }

    fclose(archivo);
    return 0;
}

//un main que no hace nada para pruebas
/*int main(int argc, char **argv) {
    return 0;
}*/