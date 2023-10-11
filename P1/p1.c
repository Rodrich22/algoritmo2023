#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
double microsegundos(){

    struct timeval t;
    if(gettimeofday(&t,NULL)<0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
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

void imprimirTitulo(int i, double inf, double fij, double sup){

    char s[12];
    char t[] = "t(n)";
    char c[] = "t(n) /n^";
    if (i == 1)
        strcpy(s, "SumaMax1");
    else if (i == 2)
        strcpy(s, "SumaMax2");

    printf("\n--------%*s%*s--------\n",40,s,33,"");

    printf("%12s%15s%15s%.2f%15s%.2f%15s%.2f%5s\n", "n", t, c, inf,
           c, fij, c, sup, "K");

}

void inicializar_semilla(){

    srand(time(NULL));
    /*se establece la semilla de una nueva serie de enteros pseudo-aleatorios*/
}

int sumaSubMax1(const int v[] , int n){ //On2
    int i,j;
    int sumaMAx=0,estaSuma;
    for (i = 0; i < n ; i++) {
        estaSuma = 0;
        for (j = i ; j < n ; j++) {
            estaSuma = estaSuma + v[j];
            if(estaSuma > sumaMAx){
                sumaMAx = estaSuma;
            }
        }
    }
    return sumaMAx;
}
int sumaSubMax2(int v[], int n){
    int j;
    int estaSuma=0, sumaMax = 0;
    for (j = 0; j <  n; ++j) {
        estaSuma += v[j];
        if(estaSuma > sumaMax)
            sumaMax = estaSuma;
        else if( estaSuma < 0)
            estaSuma = 0;
    }
    return sumaMax;
}

void listar_vector(int v[],int n){
    int i;
    printf("[");
    for(i=0;i<n;i++){
        printf("%5d\t",v[i]);
    }
    printf("]");
}

void aleatorio(int v[],int n){
    int i, m=2*n+1;
    for (i = 0;  i < n; i++) {
        v[i]= (rand()%m)-n; //se generan numeros pseudoaleatorios entre -n y +n
    }
}

void imprimirCotas(int *n, double *x,double *y,double *z,double *t,
                   double *cInf,double *cota,double *cSup){
    *cInf = *t / pow(*n,*x);
    *cota = *t / pow(*n,*y);
    *cSup = *t / pow(*n,*z) ;
}

void sum1 (void(*func)(int [],int),double x,double y,double z, bool it){

    int n = 500;
    int v[256000];
    double t, t1, t2, cInf=0, cota=0, cSup=0;
    int K = 1000, tmenor500 = 0,k,m=6,i;
    if (it==true)
        m=9;
    for ( i = 0; i <=m; i++,n *= 2){
        aleatorio(v,n);
        t1 = microsegundos();
        func(v,n);
        t2 = microsegundos();
        t = t2 - t1;
        if (t < 500.0){
            t1 = microsegundos();
            for (k = 0; k < K; k++)
                func(v,n);
            t2 = microsegundos();
            t = (t2 - t1) / K;
            tmenor500 = 1;
        }
        imprimirCotas(&n,&x,&y,&z,&t,&cInf,&cota,&cSup);
        imprimirFila(tmenor500, n, t, cInf, cota, cSup);
        tmenor500 = 0;
    }
}
void test1(){
    int i = 0, j, n = 5;
    int aux[n];
    int v[] =
            {-9, 2, -5, -4, 6,
             4, 0, 9, 2, 5,
             -2, -1, -9, -7, -1,
             9, -2, 1, -7, -8,
             15, -2, -5, -4, 16,
             7, -5, 6, 7, -7};
    printf("\n%*s--------%*s%*s--------\n\n",7,"",15,"Test 1",10,"");
    printf("\t%*s\t%*s\n",17,"Secuencia",25,"Resultado");
    while(i<28){
        for(j = 0; j < n; j++){
            aux[j] = v[i];
            i++;
        }
        listar_vector(aux, n);
        printf("\t%5d\n", sumaSubMax1(aux, n));
    }
}
void test2(){
    int i,a,b;
    int v[9];
    printf("\n%*s--------%*s%*s--------\n\n",30,"",15,"Test 2",10,"");
    printf("%33s%15s%15s\n", "", "\t\t\t\t\t\tsumaSubMax1", "\tsumaSubMax2");
    for (i = 0;  i<10 ;i++) {
        aleatorio(v,9);
        listar_vector(v,9);
        a= sumaSubMax1(v,9);
        b= sumaSubMax2(v,9);
        printf("%15d%15d\n",a,b);
    }
}
int main(){
    int i;
    inicializar_semilla();
    for (i = 0; i <3 ; ++i) {
        imprimirTitulo(1, 1.8, 2, 2.2);
        sum1((void (*)(int *, int)) sumaSubMax1,1.8,2,2.2,false);}
    printf("\n");
    for (i = 0; i < 3 ; ++i) {
        imprimirTitulo(2, 0.8, 1, 1.2);
        sum1 ((void (*)(int *, int)) sumaSubMax2, 0.8, 1, 1.2,true);
    }


    //test1();
    //test2();
    return 0;
}
