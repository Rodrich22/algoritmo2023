#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#define TAM 256000

struct monticulo{
    int ultimo;
    int vector[TAM];
};

typedef struct monticulo *pmonticulo;

void inicializarMonticulo(pmonticulo* m){
    *m = NULL;
    (*m)->ultimo = 0;
}
bool MonticuloVacio(pmonticulo m){
    return m->ultimo == 0;
}
void intercambiar( int *x , int *y){
    int tmp;
    tmp = *x;
    *x = *y;
    *y = tmp;
}
void Flotar (pmonticulo* m, int i) {
    while (i > 0 && (*m)->vector[i / 2] < (*m)->vector[i]) {
        intercambiar(&((*m)->vector[i / 2]), &((*m)->vector[i]));
        i /= 2;
    }
}

void Hundir (pmonticulo* m , int i){
    int j;
    int HijoIzq;
    int HijoDer;
    do {
        HijoIzq = 2*i+1;
        HijoDer = 2*i+2;
        j = i;
        if(HijoDer <= (*m)->ultimo && (*m)->vector[HijoDer] > (*m)->vector[i])
            i = HijoDer;
        if(HijoIzq <= (*m)->ultimo && (*m)->vector[HijoIzq] > (*m)->vector[i]){
            i= HijoIzq;
        }
        intercambiar(&((*m)->vector[j]),&((*m)->vector[i]));
    } while (j == i);
}

void crearMonticulo(int v[], int n, pmonticulo* m) {
    int i;
    for (i = 0; i < n; i++) {
        (*m)->vector[i] = v[i];
    }
    (*m)->ultimo = v[i];
    for (i = (*m)->ultimo / 2; i > 0; i--)
        Hundir(m, i);
}
void listar_monticulo(int v[],int n){
    int i;
    printf("[");
    for(i=0;i<n;i++){
        printf("%5d\t",v[i]);
    }
    printf("]");
}
int marMenor(pmonticulo m);

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

void aleatorio(int v[],int n){
    int i, m=2*n+1;
    for (i = 0;  i < n; i++) {
        v[i]= (rand()%m)-n; //se generan numeros pseudoaleatorios entre -n y +n
    }
}



int main(){
    int v[10];
    int n = 10;
    inicializar_semilla();
    aleatorio(v, n);
    pmonticulo m;
    inicializarMonticulo(&m);
    crearMonticulo(v, n,&m);
    listar_monticulo(m->vector, m->ultimo);
    return 0;
}