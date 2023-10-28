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

typedef struct monticulo * pmonticulo;

void inicializarMonticulo(pmonticulo* m){
    *m = malloc(sizeof(struct monticulo));
    if(*m == NULL){
        printf("Error al asignar memoria\n");
        free(m);
    }
    else
        (*m)->ultimo = 0;
}
bool MonticuloVacio(pmonticulo m){
    return m->ultimo == 0;
}
void intercambiar(int* x , int* y){
    int tmp;
    tmp = *x;
    *x = *y;
    *y = tmp;
}
void Flotar (pmonticulo m, int i) {
    while (i > 0 && m->vector[i / 2] < m->vector[i]) {
        intercambiar(&m->vector[i / 2], &m->vector[i]);
        i /= 2;
    }
}

void Hundir (pmonticulo m , int i){
    int j;
    int HijoIzq;
    int HijoDer;
    do {
        HijoIzq = 2*i+1;
        HijoDer = 2*i+2;
        j = i;
        if(HijoDer <= m->ultimo && m->vector[HijoDer] < m->vector[i])
            i = HijoDer;
        if(HijoIzq <= m->ultimo && m->vector[HijoIzq] < m->vector[i]){
            i = HijoIzq;
        }
        intercambiar(&m->vector[j], &m->vector[i]);
    } while (j != i);
}

int quitarMenor(pmonticulo m){
    int x;
    if (MonticuloVacio(m)){
        printf("Error");
        exit(EXIT_FAILURE);

    }else{
        x = m->vector[0];
        m->vector[0] = m->vector[m->ultimo];
        m->ultimo = m->ultimo -1 ;
        if (m->ultimo >= 0)
            Hundir(m, 0);

    }
    return x;
}

void crearMonticulo(const int v[], int n, pmonticulo m) {
    int i;
    for (i = 0; i < n; i++) {
        m->vector[i] = v[i];
    }
    m->ultimo = n-1;
    for (i = (m->ultimo) / 2; i >= 0; i--)
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

void OrdenarPorMonticulos(int v[], int n, pmonticulo m){
    int i=0;
    crearMonticulo(v, n, m);
    for(i=n-1;i<n;i++)
        v[i]=quitarMenor(m);
}


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
bool test(const int vector[], int ultimo) {
    int HijoIzq, HijoDer, i = 0;
    while (i != ultimo / 2) {
        HijoIzq = 2 * i + 1;
        HijoDer = 2 * i + 2;
        if (vector[HijoIzq] < vector[i] || vector[HijoDer] < vector[i])
            return false;
        i++;
    }
    return true;
}





int main(){
    int v[12] = {6, -12, 9, -2, 3, -3, -12, 1, -4, 6, 5, 0};
    int n = 12;
    //inicializar_semilla();
    //aleatorio(v, n);
    listar_monticulo(v, n);
    printf("\n");
    pmonticulo m;
    inicializarMonticulo(&m);
    printf(test(v, n-1)? "Yes\n":"No\n");
    crearMonticulo(v, n,m);
    printf(test(m->vector, m->ultimo)? "Yes\n":"No\n");
    listar_monticulo(m->vector, m->ultimo+1);
    printf("\n");
    quitarMenor(m);
    listar_monticulo(m->vector, m->ultimo+1);
    return 0;
}