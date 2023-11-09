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

enum INICIALIZAR{
    ALEATORIO,ASCENDENTE,DESCENDENTE
};
enum FUNCION{
    CREAR, ORDENAR
};
typedef struct monticulo * pmonticulo;


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
void ascendente(int v [], int n) {
    int i;
    for (i=0; i < n; i++)
        v[i] = i+1;
}

void descendente(int v [], int n){
    int i;
    for(i=0;i<n;i++)
        v[i]=n-i;
}

double microsegundos(){
    struct timeval t;
    if(gettimeofday(&t,NULL)<0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

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
    return m->ultimo < 0;
}
void intercambiar(int* x , int* y){
    int tmp;
    tmp = *x;
    *x = *y;
    *y = tmp;
}

void Hundir (pmonticulo* m , int i){
    int j;
    int HijoIzq;
    int HijoDer;
    do {
        HijoIzq = 2*i+1;
        HijoDer = 2*i+2;
        j = i;
        if(HijoDer <= (*m)->ultimo && (*m)->vector[HijoDer] < (*m)->vector[i])
            i = HijoDer;
        if(HijoIzq <= (*m)->ultimo && (*m)->vector[HijoIzq] < (*m)->vector[i]){
            i = HijoIzq;
        }
        intercambiar(&((*m)->vector[j]), &((*m)->vector[i]));
    } while (j != i);
}

int quitarMenor(pmonticulo* m){
    int x;
    if (MonticuloVacio(*m)){
        printf("Monticulo vacio\n");
        exit(EXIT_FAILURE);

    }else{
        x = (*m)->vector[0];
        (*m)->vector[0] = (*m)->vector[(*m)->ultimo];
        (*m)->ultimo--;
        if ((*m)->ultimo >= 0)
            Hundir(m, 0);

    }
    return x;
}

void crearMonticulo(const int v[], int n, pmonticulo* m) {
    int i;
    for (i = 0; i < n; i++) {
        (*m)->vector[i] = v[i];
    }
    (*m)->ultimo = n-1;
    for (i = ((*m)->ultimo) / 2; i >= 0; i--)
        Hundir(m, i);
}

void listar_vector(int v[],int n){
    int i;
    printf("[");
    for(i=0;i<n;i++) {
        printf("%5d\t", v[i]);
    }

    printf("]");
}

void OrdenarPorMonticulos(int v[], int n){
    pmonticulo M;

    int i;
    inicializarMonticulo(&M);
    crearMonticulo(v, n, &M);
    for(i=0;i<n;i++) {
        v[i] = quitarMenor(&M);
    }
    free(M);
}

bool esMonticulo(const int vector[], int ultimo) {
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
void calcularCotas(double *cInf,double *cota,double *cSup, double x, double y,
                   double z, double n, double t, enum FUNCION op) {
    if(op == CREAR) {
        *cInf = t / pow(n, x);
        *cota = t / pow(n, y);
        *cSup = t / pow(n, z);
    }
    else{
        *cInf = t / pow(n, x);
        *cota = t / (n * log(n));
        *cSup = t / pow(n, z);
    }
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

void imprimirTitulo(double inf, double fij, double sup, enum FUNCION op
        , enum INICIALIZAR in) {

    char s[46];
    char t[] = "t(n)";
    char cotas_exp[] = "t(n) /n^";
    char cotas_log[] = "t(n) / n log n";

    if (op == CREAR)
        strcpy(s, " Crear monticulo con inicializacion ");
    else
        strcpy(s, " Ordenacion por monticulo con inicializacion ");

    printf("\n%*s%*s%*s%*s\n", 22, "", 40, s, 0,
           in == ALEATORIO ? "aleatoria" : in == ASCENDENTE ?
                                           "ascendente" : "descendente", 10, "");
    printf("\n");

    printf("%12s%15s", "n", t);

    printf("%15s%.2f", cotas_exp, inf);
    if(op == CREAR)
        printf("%15s%.2f", cotas_exp, fij);
    else
        printf("%19s%s", cotas_log, "");

    printf("%15s%.2f%5s\n", cotas_exp, sup,"K");

}



double menor500(void (*inicializacion) (int[], int),
                enum FUNCION funcion, int n, int v[]) {
    double ta, tb, t1, t2, t;
    int k, K = 1000;
    pmonticulo M;
    inicializarMonticulo(&M);
    if (funcion == ORDENAR) {
        ta = microsegundos();
        for (k = 0; k < K; k++) {
            inicializacion(v, n);
            OrdenarPorMonticulos(v, n);
        }
    }
    else {
        ta = microsegundos();
        for (k = 0; k < K; k++) {
            crearMonticulo(v, n, &M);
        }
    }
    tb = microsegundos();
    if (funcion == ORDENAR) {
        t1 = tb - ta;
        ta = microsegundos();
        for (k = 0; k < K; k++)
            inicializacion(v, n);
        tb = microsegundos();
        t2 = tb - ta;
        t = (t1 - t2) / K;
    }
    else
        t = (tb - ta) / K;
    return t;
}


void ord (void (*inicializacion) (int[], int),
          enum FUNCION op, enum INICIALIZAR in, double x,
          double y, double z){
    int n = 500;
    int v[TAM];
    pmonticulo M;
    double t, t1, t2,cInf=0, cota=0, cSup=0;
    int tmenor500 = 0,m=9,i;
    inicializarMonticulo(&M);

    imprimirTitulo(x, y, z, op, in);
    for (i = 0; i <=m; i++,n *= 2){
        inicializacion(v,n);
        if(op == CREAR) {
            t1 = microsegundos();
            crearMonticulo(v, n, &M);
        }
        else {
            t1 = microsegundos();
            OrdenarPorMonticulos(v, n);
        }
        t2 = microsegundos();
        t = t2 - t1;
        if (t < 500.0){
            t = menor500(inicializacion, op, n, v);
            tmenor500 = 1;
        }
        calcularCotas(&cInf, &cota, &cSup, x, y, z, n, t, op);
        imprimirFila(tmenor500, n, t, cInf, cota, cSup);
        tmenor500 = 0;
    }
    free(M);
}
bool esOrdenado(const int v[], int n){
    int i;
    for(i = 0; i < n; i++){
        if(v[i] > v[i+1])
            return false;
    }
    return true;
}
void ordenar(int v[], int n){
    listar_vector(v, n);
    printf("\nOrdenado? %d\n", esOrdenado(v, n));
    OrdenarPorMonticulos(v, n);
    listar_vector(v, n);
    printf("\nOrdenado? %d\n", esOrdenado(v, n));
}

void test(){
    int n = 10;
    int v[n];
    pmonticulo M;
    inicializarMonticulo(&M);
    aleatorio(v, n);
    crearMonticulo(v, n, &M);
    printf(esMonticulo(M->vector, M->ultimo)? "El monticulo se ha creado correctamente\n":"El monticulo no se ha creado correctamente\n");
    printf("Inicializacion aleatoria\n");
    aleatorio(v, n);
    ordenar(v, n);
    printf("Inicializacion ascendente\n");
    ascendente(v, n);
    ordenar(v, n);
    printf("Inicializacion descendente\n");
    descendente(v, n);
    ordenar(v, n);
    free(M);
}

int main(){
    int i;
    inicializar_semilla();
    //test();

    for (i = 0; i < 3; i++) {
        ord(descendente, CREAR, DESCENDENTE, 0.7, 1.0, 1.3);
        ord(ascendente, CREAR, ASCENDENTE, 0.7, 1.0, 1.3);
        ord(aleatorio, CREAR, ALEATORIO, 0.8, 1.0, 1.2);
        ord(descendente, ORDENAR, DESCENDENTE, 0.9, 1.0, 1.5);
        ord(ascendente, ORDENAR, ASCENDENTE, 0.9, 1.0, 1.5);
        ord(aleatorio, ORDENAR, ALEATORIO, 0.9, 1.0, 1.5);
    }
    return 0;
}
