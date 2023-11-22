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
void printear_matriz(matriz m, int n){
    int i, j;
    for(i = 0; i<n;i++){
        printf("\n");
        for(j = 0; j < n; j++){
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
        for(j = 0; j < (tam-2); j++){
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
        }
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

    printf("%12s%15s", "n", t);

    printf("%15s%.2f%15s%.2f%15s%.2f%5s\n", cotas_exp, inf,cotas_exp,
           fij, cotas_exp, sup,"K");
}


void grafo (double x, double y, double z){
    int n = 500;
    double t, t1, t2, cInf=0, cota=0, cSup=0;
    int K = 1000, tmenor500 = 0,k,m=6,i;
    matriz grafo;
    matriz distancias;
    imprimirTitulo(x, y, z);
    for (i = 0; i <=m; i++,n *= 2){
        grafo = crearMatriz(n);
        distancias = crearMatriz(n);
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
        liberarMatriz(grafo, n);
        liberarMatriz(distancias, n);
    }
}















/*bool test(matriz prueba, matriz referencia, int tam){
    int i, j;
    printf("Matriz antes de aplicar el algoritmo: \n");
    printear_matriz(prueba, tam);
    printf("\n");
    printf("Matriz referencia de distancias minimas: \n");
    printear_matriz(referencia, tam);

    for(i = 0; i < tam; i++){
        for(j = 0; j < tam; j++){
            if(prueba[i][j] != referencia[i][j])
                return false;
        }
    }
    return true;
}
bool testGlobal(){
    int aux[5][5] = {{0, 1, 8, 4, 7},
                     {1, 0, 2, 6, 5},
                     {8, 2, 0, 9, 5},
                     {4, 6, 9, 0, 3},
                     {7, 5, 5, 3, 0}};
    matriz m = crearMatriz(5);
    matriz ref = crearMatriz(5);
    matriz d = crearMatriz(5);
}*/


int main(){
    /* matriz m = crearMatriz(5);
     matriz d = crearMatriz(5);
     matriz ref = crearMatriz(5);
     m[0][0] = 0;
     m[0][1] = 1;
     m[0][2] = 8;
     m[0][3] = 4;
     m[0][4] = 7;

     m[1][0] = 1;
     m[1][1] = 0;
     m[1][2] = 2;
     m[1][3] = 6;
     m[1][4] = 5;

     m[2][0] = 8;
     m[2][1] = 2;
     m[2][2] = 0;
     m[2][3] = 9;
     m[2][4] = 5;

     m[3][0] = 4;
     m[3][1] = 6;
     m[3][2] = 9;
     m[3][3] = 0;
     m[3][4] = 3;

     m[4][0] = 7;
     m[4][1] = 5;
     m[4][2] = 5;
     m[4][3] = 3;
     m[4][4] = 0;
     printear_matriz(m, 5);
     printf("\n");
     dijkstra(m, d, 5);
     printf("\n");
     printear_matriz(m, 5);
     printf("\n\n");
     printear_matriz(d, 5);
     dijkstra(m, d, 5);*/
    int i;
    inicializar_semilla();
    for(i = 0; i < 3; i++){
        grafo(1.8, 2.0, 2.2);
    }
    return 0;
}


