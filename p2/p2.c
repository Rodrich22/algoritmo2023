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
		v[i] = i+1;
}

void descendente(int v [], int n){
	int i;
	for(i=0;i<n;i++)
		v[i]=n-i;
}
void listar_vector(int v[],int n){
    int i;
    printf("[");
    for(i=0;i<n;i++){
        printf("%5d\t",v[i]);
    }
    printf("]");
}


void ord_ins (int v[], int n){
	int i,j,x;
	for(i=1; i<n;i++){
		x=v[i];
		j=i-1;
		
	while (j>=0 && v[j] >x){
		v[j+1] = v[j];
		j=j-1;
	}
	v[j+1]= x;
	}
}

void ordenacionShell(int v[], int n) {
    int incremento = n;
    do {
        incremento = incremento / 2;
        for (int i = incremento + 1; i <= n; i++) {
            int tmp = v[i];
            int j = i;
            int seguir = 1;
            while (j - incremento > 0 && seguir) {
                if (tmp < v[j - incremento]) {
                    v[j] = v[j - incremento];
                    j = j - incremento;
                } else {
                    seguir = 0;
                }
            }
            v[j] = tmp;
        }
    } while (incremento > 1);
}

void calcularCotas(int n, double x,double y,double z,double t,
                   double *cInf,double *cota,double *cSup){
    *cInf = t / pow(n,x);
    *cota = t / pow(n,y);
    *cSup = t / pow(n,z) ;
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


void ord (void(*func)(int [],int),double x,double y,double z, bool it){

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
        calcularCotas(n,x,y,z,t,&cInf,&cota,&cSup);
        imprimirFila(tmenor500, n, t, cInf, cota, cSup);
        tmenor500 = 0;
    }
}
int main(){
    int i;
    inicializar_semilla();
    for (i = 0; i <3 ; ++i) {
        imprimirTitulo(1, 1.8, 2, 2.2);
        ord((void (*)(int *, int)) ord_ins,1.8,2,2.2,false);}
    printf("\n");
}