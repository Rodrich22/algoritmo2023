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
		v[i] = i;
}

void descendente(int v [], int n){
	int i;
	for(i=0;i<n;i++)
		v[i]=n-i;
}


void ord_ins (int v[], int n){
	int i,j,x;
	for(i=1; i<n-1;i++){
		x=v[i];
		j=i-1;
		
	while (j>=0 && v[j] >x){
		v[j+1] = v[j];
		j=j-1;
	}
	v[j+1]= x;
	}
	


}
