//Daniel Rivera Bonilla
//Rodrich Antaya Huamani
//Hugo Correa Blanco

#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#define TAM_MAX 1000

typedef int** matriz;

double microsegundos(){
    struct timeval t;
    if(gettimeofday(&t,NULL)<0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void inicializar_semilla(){

    srand(time(NULL));
    /*se establece la semilla de una nueva serie de enteros pseudo-aleatorios*/
}

matriz crearMatriz(int n) {
    int i;
    matriz aux;
    if ((aux = malloc(n*sizeof(int *))) == NULL)
        return NULL;
    for (i=0; i<n; i++)
        if ((aux[i] = malloc(n*sizeof(int))) == NULL)
            return NULL;
    return aux;
}

void iniMatriz(matriz m, int n) {
    int i, j;
    for (i=0; i<n; i++)
        for (j=i+1; j<n; j++)
            m[i][j] = rand() % TAM_MAX + 1;
    for (i=0; i<n; i++)
        for (j=0; j<=i; j++)
            if (i==j)
                m[i][j] = 0;
            else
                m[i][j] = m[j][i];
}

void liberarMatriz(matriz m, int n) {
    int i;
    for (i=0; i<n; i++)
        free(m[i]);
    free(m);
}

void printear_matriz(matriz m, int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        printf("\n");
        for (j = 0; j < n; j++) {
            printf("%d\t", m[i][j]);
        }
    }
}



void dijkstra (matriz grafo, matriz distancias, int tam) {
    int n, i, j, w, min, v = 0;
    int *noVisitados = malloc(tam * sizeof(int));
    for (n = 0; n < tam; n++) {
        for (i = 0; i < tam; i++) {
            noVisitados[i] = 1; //lo marca como no visitado
            distancias[n][i] = grafo[n][i];
        }
        noVisitados[n] = 0;
        j = 0;
        do{
            min = TAM_MAX+1;
            for (i = 0; i < tam; i++) {
                if (noVisitados[i] && distancias[n][i] < min) {
                    min = distancias[n][i];
                    v = i;
                }
            }
            noVisitados[v] = 0;
            for (w = 0; w < tam; w++) {
                if (noVisitados[w] && (distancias[n][w] > (distancias[n][v] + grafo[v][w])))
                    distancias[n][w] = distancias[n][v] + grafo[v][w];
            }
            j++;
        } while (j < (tam-2));
    }
    free(noVisitados);
}


void calcularCotas(double *cInf,double *cota,double *cSup, double x, double y,
                   double z, double n, double t) {
    *cInf = t / pow(n, x);
    *cota = t / pow(n, y);
    *cSup = t / pow(n, z);
}


void imprimirFila(int k, int n, double t,
                  double cI, double c, double cS){
    char as;
    if (k == 1)
        as = '*';
    else
        as = '-';
    printf("%12d%15.3f%19.6f%19.6f%19.6f%5c\n", n, t, cI, c, cS, as);
}


void imprimirTitulo(double inf, double fij, double sup) {

    char s[22];
    char t[] = "t(n)";
    char cotas_exp[] = "t(n) /n^";

    strcpy(s, "Algoritmo de Dijkstra");
    printf("\n%*s%*s\n", 22, "", 40, s);
    printf("\n");
    printf("%12s%15s", "n", t);

    printf("%15s%.2f%15s%.2f%15s%.2f%5s\n", cotas_exp, inf,cotas_exp,
           fij, cotas_exp, sup,"K");
}


void grafo (double x, double y, double z){
    int n = 10;
    double t, t1, t2, cInf=0, cota=0, cSup=0;
    int K = 1000, tmenor500 = 0, k, m=6 ,i;
    matriz grafo;
    matriz distancias;
    grafo = crearMatriz(640);
    distancias = crearMatriz(640);
    imprimirTitulo(x, y, z);
    for (i = 0; i <=m; i++,n *= 2){
        iniMatriz(grafo, n);
        t1 = microsegundos();
        dijkstra(grafo, distancias, n);
        t2 = microsegundos();
        t = t2 - t1;
        if (t < 500.0){
            t1 = microsegundos();
            for (k = 0; k < K; k++){
                dijkstra(grafo, distancias, n);
            }
            t2 = microsegundos();
            t = (t2-t1) / K;
            tmenor500 = 1;
        }
        calcularCotas(&cInf, &cota, &cSup, x, y, z, n, t );
        imprimirFila(tmenor500, n, t, cInf, cota, cSup);
        tmenor500 = 0;
    }
    liberarMatriz(grafo, 640);
    liberarMatriz(distancias, 640);
}


void copiar_matriz(matriz grafo, matriz referencia,
                   int tam, int matriz_grafo [tam][tam], int matriz_referencia[tam][tam]){
    int i, j;
    for(i = 0; i < tam; i++){
        for(j = 0; j < tam; j++){
            grafo[i][j] = matriz_grafo[i][j];
            referencia[i][j] = matriz_referencia[i][j];
        }
    }
}


bool test(matriz prueba, matriz referencia, int tam){
    int i, j;
    matriz distancias = crearMatriz(tam);
    printf("Matriz antes de aplicar el algoritmo: \n\n");
    printear_matriz(prueba, tam);
    printf("\n\n");
    printf("Matriz referencia de distancias minimas: \n");
    printear_matriz(referencia, tam);
    printf("\n\n");
    dijkstra(prueba, distancias, tam);
    printf("Matriz resultante: \n");
    printear_matriz(distancias, tam);
    printf("\n\n");
    for(i = 0; i < tam; i++){
        for(j = 0; j < tam; j++){
            if(distancias[i][j] != referencia[i][j])
                return false;
        }
    }
    liberarMatriz(distancias, tam);
    return true;
}


void testGlobal() {

    int aux1[5][5] = {{0, 1, 8, 4, 7},
                      {1, 0, 2, 6, 5},
                      {8, 2, 0, 9, 5},
                      {4, 6, 9, 0, 3},
                      {7, 5, 5, 3, 0}};

    int ref1[5][5] = {{0, 1, 3, 4, 6},
                      {1, 0, 2, 5, 5},
                      {3, 2, 0, 7, 5},
                      {4, 5, 7, 0, 3},
                      {6, 5, 5, 3, 0}};
    int aux2[4][4] = {{0, 1, 4, 7},
                      {1, 0, 2, 8},
                      {4, 2, 0, 3},
                      {7, 8, 3, 0}};

    int ref2[4][4] = {{0, 1, 3, 6},
                      {1, 0, 2, 5},
                      {3, 2, 0, 3},
                      {6, 5, 3, 0}};

    matriz grafo = crearMatriz(5);
    matriz referencia = crearMatriz(5);
    matriz grafo2 = crearMatriz(4);
    matriz referencia2 = crearMatriz(4);

    copiar_matriz(grafo, referencia, 5, aux1, ref1);
    printf(test(grafo, referencia, 5) ? "El algoritmo funciona\n\n" : "El algortimo no funciona\n\n");
    copiar_matriz(grafo2, referencia2, 4, aux2, ref2);
    printf(test(grafo2, referencia2, 4) ? "El algoritmo funciona\n\n" : "El algortimo no funciona\n\n");

    liberarMatriz(grafo, 5);
    liberarMatriz(referencia, 5);
    liberarMatriz(grafo2, 4);
    liberarMatriz(referencia2, 4);
}

int main(){
    int i;
    inicializar_semilla();
    //testGlobal();
    for(i = 0; i < 3; i++){
        grafo(2.8, 2.87, 3.2);
    }
    printf("\n");
    return 0;
}


