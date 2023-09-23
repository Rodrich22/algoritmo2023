#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>


double microsegundos(){
    struct timeval t;
    if(gettimeofday(&t,NULL)<0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}
/*
Funcion para imprimir los resultados en la tabla
*/
void imprimirFila(int k, int n, double t, double cI, double c, double cS){

    char as;

    if (k == 1)
        as = '*';
    else
        as = '-';

    printf("%12d%15.3f%15.6f%15.6f%15.6f%5c\n", n, t, cI, c, cS, as);

}

/*
Funcion para imprimir el titulo de la tabla
*/
void imprimirTitulo(int i){

    char s[12];
    char t[] = "Tiempo";
    char cI[] = "Cota Inf.";
    char c[] = "Cota";
    char cS[] = "Cota Sup.";

    if (i == 1)
        strcpy(s, "SumaMAx1");
    else if (i == 2)
        strcpy(s, "SumaMAx2");

    printf("\n--------%*s%*s--------\n",40,s,25,"");

    printf("%10s%17s%15s%15s%15s%5s\n", "n", t, cI , c, cS, "K");

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
        v[i]= (rand()%m) -n; //se generan numeros pseudoaleatorios entre -n y +n
    }


}
void sum1 (){

    int n = 250;
    int *v;
    double t, t1, t2, cInf, cota, cSup;
    int K = 1000, tmenor500 = 0;

    for (int i = 0; i <=7; i++){
        v = (int *)malloc(sizeof(int) * n);
        aleatorio(v,n);
       // printf("\n");
     //   listar_vector(v, n);
        t1 = microsegundos();
        sumaSubMax1(v,n);
        n *= 2;
        t2 = microsegundos();

        t = t2 - t1;

        if (t < 500.0){

            t1 = microsegundos();

            for (int k = 0; k < K; k++)
                sumaSubMax1(v,n);

            t2 = microsegundos();

            t = (t2 - t1) / K;

            tmenor500 = 1;
        }
        free(v);
        //printf("%d\t", n);

        cInf = t / pow(n,1.8);
        cota = t / pow(n,2);
        cSup = t / pow(n,2.2) ;


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

    inicializar_semilla();
    imprimirTitulo(1);

    sum1();

    //test1();
    //test2();
    return 0;
}
