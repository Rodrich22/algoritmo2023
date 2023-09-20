#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>

double microsegundos(){
    printf("probando");
    printf("probando otra vez");
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
        v[i]= (rand()%m) -n; //se generan numeros pseudoaleatorios entre -n y +n
    }
}
int sumaSubMAx1(int v[] , int n){ //On2
    int i,j;
    int sumaMAx=0,estaSuma;
    for (i = 0; i < n ; ++i) {
        estaSuma = 0;
        for (j = i ; j < n ; ++j) {
            estaSuma = estaSuma + v[j];
            if(estaSuma > sumaMAx){
                sumaMAx = estaSuma;
            }
        }
    }
    return sumaMAx;
}
int sumaSubMax2(int v[], int n){
    int i,j;
    int estaSuma=0, sumaMax = 0;
    for (j = 0; j <  n; ++j) {
        estaSuma = estaSuma + v[j];
        if(estaSuma > sumaMax){
            sumaMax = estaSuma;
        }else if( estaSuma < 0){
            estaSuma = 0;
        }
    }
    return sumaMax;
}
void listar_vector(int v[],int n){
	
	printf("[ ");
	for(int i=0;i<n;i++){
		printf("%d\t",v[i]);
		}
	printf("]");   

}
void test1(){
    int i, n=5;
    int v[][5]={
            {15,-2,-5,-4,16},
            {7,-5,6,7,-7},
            {4,0,9,2,5},
            {-9,2,-5,-4,6},
            {9,-2,1,-7,-1},
            {-2,-1,-9,-7,-1}
    };
}
void test2(){
    int i,a,b;
    int v[9];
    printf("hola--");
    printf("test\n");
    printf("%33s%15s%15s\n", "", "\t\t\t\t\t\tsumaSubMax1", "\tsumaSubMax2");
    for (i = 0;  i<10 ;i++) {
        aleatorio(v,9);
        listar_vector(v,9);
        a= sumaSubMAx1(v,9);
        b= sumaSubMax2(v,9);
        printf("%15d%15d\n",a,b);
    }
}
int main(){
    inicializar_semilla();
    //test1();
    test2();
    return 0;
}
