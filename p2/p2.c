//NOMBRES

#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
enum p2 {
    ALEATORIO,ASCENDENTE,DESCENDENTE
};
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

void calcularCotas( double *cInf,double *cota,double *cSup ,int n, double x,double y,double z,double t, bool ins){
    if(ins) {
        *cInf = t / pow(n, x);
        *cota = t / pow(n, y);
        *cSup = t / pow(n, z);
    }
    else{
        /*cInf = t / (n * log2(n));
        *cota = t / (n * log(n));
        *cSup = t / pow(n, z);
         */
    }
}
void asignarCotas(double *cInf,double *cota,double *cSup ,enum p2 f,int n, int t ,bool ins){
    if(ins){
        if(f == ASCENDENTE){
            calcularCotas(cInf,cota,cSup,n,0.8,1.0,1.2,t, ins);
        }
        if( f == DESCENDENTE){
        calcularCotas(cInf,cota,cSup,n,1.8,2.0,2.2,t, ins);
        }
        if( f == ALEATORIO) {
        calcularCotas(cInf,cota,cSup,n,1.8,2.0,2.2,t, ins);
        }
    }
    else{
        if(f == ASCENDENTE){
            calcularCotas(cInf,cota,cSup,n,0.8,1.0,1.2,t, ins);
        }
        if( f == DESCENDENTE){
            calcularCotas(cInf,cota,cSup,n,1.8,2.0,2.2,t, ins);
        }
        if( f == ALEATORIO) {
            calcularCotas(cInf,cota,cSup,n,1.8,2.0,2.2,t, ins);
        }
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

void imprimirTitulo(bool ins, double inf, double fij, double sup, enum p2 f) {

    char s[45];
    char t[] = "t(n)";
    char cotas_ins[10];
    char cotas_shell[10];

    if (ins) {
        strcpy(s, "Ordenacion por insercion con inicializacion ");
        strcpy(cotas_ins, "t(n) /n^");
    } else {
        strcpy(s, "Ordenacion shell con inicializacion ");
        strcpy(cotas_shell, "t(n) /");

    }
    printf("\n--------%*s%*s%*s%*s--------\n",15, "",40,s,0,f == ALEATORIO?"aleatoria":f == ASCENDENTE?"ascendente":"descendente", 10 ,"");
    printf("%12s%15s", "n",t);
    if(ins)
        printf("%15s%.2f%15s%.2f%15s%.2f\n", cotas_ins, inf,
               cotas_ins, fij, cotas_ins, sup);
    else
        printf("%10s n log2 n %10s n log n %12s n^1.0\n", cotas_shell,
               cotas_shell, cotas_shell);


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


void ord (void(*ordenacion)(int [],int), void (*inicializar) (int[], int), enum p2  f, bool ins){
    imprimirTitulo(ins, 1.8, 2, 2.2, f);
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
        asignarCotas(&cInf,&cota,&cSup ,f,n,t ,ins);
        imprimirFila(tmenor500, n, t, cInf, cota, cSup);
        tmenor500 = 0;
    }
}
int main(){
    inicializar_semilla();
    int n = 10;
    int i;
    //test(v, n, true);
    //test(v, n, false);
    bool ins = true;
    //for (i = 0; i <3 ; ++i) {
        ord((void (*)(int *, int)) ord_ins, (void (*)(int *, int)) descendente, DESCENDENTE, true);
        ord((void (*)(int *, int)) ord_ins, (void (*)(int *, int)) ascendente, ASCENDENTE, true);
        ord((void (*)(int *, int)) ord_ins, (void (*)(int *, int)) aleatorio, ALEATORIO, true);
        ord((void (*)(int *, int)) ordenacionShell, (void (*)(int *, int)) descendente, DESCENDENTE, false);
        ord((void (*)(int *, int)) ordenacionShell, (void (*)(int *, int)) ascendente, ASCENDENTE, false);
        ord((void (*)(int *, int)) ordenacionShell, (void (*)(int *, int)) aleatorio, ALEATORIO, false);

    //}
    printf("\n");
    /*
     *     switch (f) {
            case DESCENDENTE:
                strcpy(c, "t(n) / n log2 n");
                break;
            case ALEATORIO:
                strcpy(c, "t(n) / n log n");
                break;
            default:
                strcpy(c, "t(n) / n")


        }
    }

    printf("\n--------%*s%*s%*s--------\n",40,s,0,f == ALEATORIO?"aleatoria":f == ASCENDENTE?"ascendente":"descendente", 10, "");

    printf("%12s%15s", ins? "%15s%.2f%15s%.2f%15s%.2f%5s\n":"log ", "n", t, c, inf,
           c, fij, c, sup : "K");
     */

}