#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "struct.h"
#include <sys/wait.h>
#include <time.h>
#include "fbroker.h"

#define LECTURA 0
#define ESCRITURA 1

//Entradas: arreglo de celdas (double), cantidad de celdas (int)
//Salida: indice de la celda con mayor energia (int)
//Descripcion: funcion que retorna el indice de la celda con mayor energia
int maximo(double *listaC, int numeroCeldas) {
    if (numeroCeldas <= 0) {
        // Manejo de caso especial para listas vacías o de tamaño no válido
        return -1; // o algún otro valor que indique que la lista está vacía o no es válida
    }

    int indiceMaximo = 0;
    for (int i = 1; i < numeroCeldas; i++) {
        if (listaC[i] > listaC[indiceMaximo]) {
            indiceMaximo = i;
        }
    }
    return indiceMaximo;
}

//Entradas: arreglo de lineas trabajadas por worker (int), cantidad de celdas (int), arreglo de celdas (double), indice de la celda con mayor energia (int), cantidad de workers (int)
//Salida: void
//Descripcion: funcion que imprime el grafico normalizado
void imprimirGrafico(int * lineas, int nC, double *listaC, int posMax, int numeroProcesos){
    for (int i = 0; i < numeroProcesos; i++){
        printf("Worker %d: %d lineas leidas\n", i + 1, lineas[i]);
    }

    double max = listaC[posMax];
    for(int i = 0; i < nC; i++){
        double energiaNormalizada = (listaC[i]*50)/max;
        printf("%d %f| ",i,listaC[i]);
        for(int j = 0; j < (int)energiaNormalizada; j++){
            printf("o");
        } 
        printf("\n");
    }
}

//Entradas: cantidad de workers (int), pipeline worker to broker, pipeline broker to worker, 
//Salida: void
//Descripcion: funcion que crea los workers
void workers(int numeroProcesos, int pipeWB[][2], int pipeBW[][2], char *argv[]) {
    for (int i = 0; i < numeroProcesos; i++) {
        pid_t pid = fork();

        if (pid == -1) {
            // Manejo de error al realizar el fork
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) { // Proceso hijo
            close(pipeWB[i][0]);
            close(pipeBW[i][1]);

            dup2(pipeWB[i][1], STDOUT_FILENO);
            dup2(pipeBW[i][0], STDIN_FILENO);

            char *args[] = {"./worker", argv[1], NULL};
            execv(args[0], args);

            // En caso de que execv falle, se llegará a esta línea
            perror("Execv failed");
            exit(EXIT_FAILURE);
        } else { // Proceso padre
            close(pipeWB[i][1]);
            close(pipeBW[i][0]);
        }
    }
}

//Entradas: cantidad de celdas (int), cantidad de procesos (int), arreglo de celdas (double), pipeline worker to broker, arreglo de lineas trabajadas por worker (int)
//Salida: void
//Descripcion: funcion que lee la informacion proporcionada por los workers
void leer(int numeroCeldas, int numeroProcesos, double *listaC, int pipeWB[][2], int *lineasTrabajadasPorWorker) {
    for (int i = 0; i < numeroProcesos; i++) {
        int lineasTrabajadas;
        read(pipeWB[i][LECTURA], &lineasTrabajadas, sizeof(int));
        lineasTrabajadasPorWorker[i] = lineasTrabajadas;

        char archivoWorker[50];
        read(pipeWB[i][LECTURA], archivoWorker, sizeof(archivoWorker));

        FILE *fp = fopen(archivoWorker, "r");
        if (fp == NULL) {
            perror("Error abriendo el archivo del worker");
            continue;
        }

        for (int j = 0; j < numeroCeldas; j++) {
            double valor;
            if (fscanf(fp, "%lf", &valor) != 1) {
                perror("Error leyendo desde el archivo del worker");
                // Puedes agregar más lógica de manejo de errores según sea necesario
                break;
            }
            listaC[j] += valor;
        }
        fclose(fp);
        remove(archivoWorker);
    }
}

//Entradas: archivo de entrada (char), cantidad de chunks (int), cantidad de procesos(int), pipeline broker to worker
//Salida: void
//Descripcion: funcion que envia la lineas que leeran los workers
void enviarLineas(const char *input, int chunks, int workers, int pipeBW[][2]){
    int cantidadParticulas, workerRandom, i;
    int lineasLeidas = 0;
    char buffer[50];

    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    srand(ts.tv_nsec ^ ts.tv_sec);

    FILE *archivoParticulas = fopen(input, "r");
    if (archivoParticulas == NULL){
        printf("Error al abrir el archivo de entrada\n");
        exit(0);
    }

    fscanf(archivoParticulas, "%d", &cantidadParticulas);

    fgets(buffer, sizeof(buffer), archivoParticulas);

    for (; lineasLeidas < cantidadParticulas; lineasLeidas++) {
    if ((lineasLeidas % chunks) == 0) {
        workerRandom = rand() % workers;
    }

    fgets(buffer, sizeof(buffer), archivoParticulas);
    write(pipeBW[workerRandom][ESCRITURA], buffer, sizeof(buffer));
    }

    fclose(archivoParticulas);

    for (i = 0; i < workers; i++)
    {
        write(pipeBW[i][ESCRITURA], "FIN", sizeof("FIN"));
    }
}

//Entradas: arreglo de celdas (double), cantidad de celdas (int), archivo de salida (char)
//Salida: void
//Descripcion: funcion que crea el archivo de salida
void crearArchivoSalida(double *listaC, int celdas, const char *output) {
    FILE *archivoSalida = fopen(output, "w");
    if (archivoSalida == NULL) {
        perror("Error al crear el archivo de salida");
        exit(EXIT_FAILURE);
    }

    int celdaEnergiaMaxima = maximo(listaC, celdas);

    fprintf(archivoSalida, "%d %lf\n", celdaEnergiaMaxima, listaC[celdaEnergiaMaxima]);

    for (int i = 0; i < celdas; i++) {
        fprintf(archivoSalida, "%d %lf\n", i, listaC[i]);
    }

    fclose(archivoSalida);
}