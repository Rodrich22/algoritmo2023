//NOMBRES

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
    int i, tmp, j;
    bool seguir;
    do {
        incremento = incremento / 2;
        for (i = incremento; i < n; i++) {
            tmp = v[i];
            j = i;
            seguir = true;
            while (j - incremento >= 0 && seguir) {
                if (tmp < v[j - incremento]) {
                    v[j] = v[j - incremento];
                    j = j - incremento;
                } else {
                    seguir = false;
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

    if (i == 1) {
        strcpy(s, "SumaMax1");
    }
    else if (i == 2)
        strcpy(s, "SumaMax2");

    printf("\n--------%*s%*s--------\n",40,s,33,"");

    printf("%12s%15s%15s%.2f%15s%.2f%15s%.2f%5s\n", "n", t, c, inf,
           c, fij, c, sup, "K");

}
bool esOrdenado(int v[], int n){
    int i;
    for(i = 0; i < n; i++){
        if(v[i] > v[i+1])
            return false;
    }
    return true;
}
void ordenar(int v[], int n, bool ins){
    listar_vector(v, n);
    printf("\nordenado? %d\n", esOrdenado(v, n));
    if(ins){
        printf("\nOrdenacion por insercion\n");
        ord_ins(v, n);
    }
    else {
        printf("\nOrdenacion shell\n");
        ordenacionShell(v, n);
    }
    listar_vector(v, n);
    printf("\nordenado? %d\n\n", esOrdenado(v, n));
}
void test(int v[], int n, bool ins){
    printf("Inicializacion aleatoria\n");
    aleatorio(v, n);
    ordenar(v, n, ins);
    printf("Inicializacion ascendente\n");
    ascendente(v, n);
    ordenar(v, n, ins);
    printf("Inicializacion descendente\n");
    descendente(v, n);
    ordenar(v, n, ins);
}


void ord (void(*ordenacion)(int [],int), void (*inicializar) (int[], int), double x,double y,double z){
    int n = 500;
    int v[256000];
    double t, t1, t2, ta, tb, cInf=0, cota=0, cSup=0;
    int K = 1000, tmenor500 = 0,k,m=6,i;
    for (i = 0; i <=m; i++,n *= 2){
        inicializar(v,n);
        ta = microsegundos();
        ordenacion(v,n);
        tb = microsegundos();
        t = tb - ta;
        if (t < 500.0){
            ta = microsegundos();
            for (k = 0; k < K; k++){
                inicializar(v, n);
                ordenacion(v, n);
            }
            tb = microsegundos();
            t1 = tb-ta;
            ta = microsegundos();
            for (k = 0; k < K; k++)
                inicializar(v, n);
            tb = microsegundos();
            t2 = tb - ta;
            t = (t1-t2) / K;
            tmenor500 = 1;
        }
        calcularCotas(n,x,y,z,t,&cInf,&cota,&cSup);
        imprimirFila(tmenor500, n, t, cInf, cota, cSup);
        tmenor500 = 0;
    }
}
int main(){
    inicializar_semilla();
    int n = 10;
    int v[n];
    int i;
    //test(v, n, true);
    //test(v, n, false);

    for (i = 0; i <3 ; ++i) {
        imprimirTitulo(2, 1.8, 2, 2.2);
        //ord((void (*)(int *, int)) ord_ins, (void (*)(int *, int)) descendente, 1.8,2,2.2);
        ord((void (*)(int *, int)) ord_ins, (void (*)(int *, int)) aleatorio, 1.8,2,2.2);
    }
    printf("\n");

}