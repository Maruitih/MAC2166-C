/***************************************************************/
/**                                                           **/
/**   Henrique Maruiti                             12610243   **/
/**   Exercicio-Programa 2                                    **/
/**   Professor:Yoshiharu Kohayakawa                          **/
/**   Turma: 01                                               **/
/**                                                           **/
/***************************************************************/

#include <stdio.h>
#include <math.h>
#include <float.h>

void read_data(double *x0, double *x1, double *x2, double *x3,
               double *v0, double *v1, double *v2, double *v3,
               double *m0, double *m1, double *m2, double *m3,
               double *T_max); /* Leitura da entrada */

double t(double x, double xx, double v, double vv); /*Tempo até a proxima colisao*/ 

double min(double a, double b, double c, int *i); /*Mínimo entre tres valores*/ 

double adv(double *x, double v, double t); /*Movimento uniforme e devolve o deslocamento*/ 

void resolve(double *v, double *vv, double m, double mm); /*Execuçao de uma colisao*/

void print_data(long c1, long c2, long c3,
                double x0, double x1, double x2, double x3,
                double v0, double v1, double v2, double v3,
                double d0, double d1, double d2, double d3); /*Impressao da saida*/ 

int main(){
    double T = 0.0, t_restante = 0; /*Variaveis de tempo*/ 
    double x0, x1, x2, x3, v0, v1, v2, v3, m0, m1, m2, m3, T_max; /*Funçao que faz a leitura da entrada*/
    double t1 = 0, t2 = 0, t3 = 0, intervalo; /*Tempo entre colisoes*/ 
    long c1 = 0, c2 = 0, c3 = 0; /*Numero de colisoes*/  
    int i = 0, colisao = 1; /*Tipos de colisoes*/ 
    double d0 = 0, d1 = 0, d2 = 0, d3 = 0; /*Deslocamento*/ 

    read_data( &x0, &x1, &x2, &x3,
               &v0, &v1, &v2, &v3,
               &m0, &m1, &m2, &m3,
               &T_max);
               
    while (T < T_max){
        t1 = t(x0, x1, v0, v1); /*Determinar o proximo evento E que ocorrerá*/ 
        t2 = t(x1, x2, v1, v2);
        t3 = t(x2, x3, v2, v3);

        intervalo = min(t1, t2, t3, &i); /*Intervalo de tempo ate o evento E*/
        if(intervalo == HUGE_VAL || T + intervalo > T_max){
            intervalo = 0;
            i = 0;
            t_restante = T_max - T;
            colisao = 0;
        }
        /*Casos de colisões*/
        if (i == 1){
            d0 = d0 + adv(&x0, v0, intervalo);/*Calculo de deslocamento*/
            d1 = d1 + adv(&x1, v1, intervalo);
            d2 = d2 + adv(&x2, v2, intervalo);
            d3 = d3 + adv(&x3, v3, intervalo);
            resolve(&v0, &v1, m0, m1);        /*Execuçao da Colisao*/
            c1++;                             /*Contagem de colisao*/
        }

        if (i == 2){
            d0 = d0 + adv(&x0, v0, intervalo);/*Calculo de deslocamento*/
            d1 = d1 + adv(&x1, v1, intervalo);
            d2 = d2 + adv(&x2, v2, intervalo);
            d3 = d3 + adv(&x3, v3, intervalo);
            resolve(&v1, &v2, m1, m2);        /*Execuçao da Colisao*/
            c2++;                             /*Contagem de colisao*/
        }

        if (i == 3){
            d0 = d0 + adv(&x0, v0, intervalo);/*Calculo de deslocamento*/
            d1 = d1 + adv(&x1, v1, intervalo);
            d2 = d2 + adv(&x2, v2, intervalo);
            d3 = d3 + adv(&x3, v3, intervalo);
            resolve(&v2, &v3, m2, m3);        /*Execuçao da Colisao*/
            c3++;                             /*Contagem de colisao*/
        }

        if(colisao == 0){
            d0 = d0 + adv(&x0, v0, t_restante);/*Calculo de deslocamento*/
            d1 = d1 + adv(&x1, v1, t_restante); 
            d2 = d2 + adv(&x2, v2, t_restante); 
            d3 = d3 + adv(&x3, v3, t_restante); 
        }   
        T = T + intervalo + t_restante;        
    }
    print_data(c1,c2,c3,
               x0,x1,x2,x3,
               v0,v1,v2,v3,
               d0,d1,d2,d3);

    if(t1 == HUGE_VAL && t2 == HUGE_VAL && t3 == HUGE_VAL){ /*Previsao de colisao*/
        printf("Nao ha mais colisoes\n");
    }
    else{
        printf("Ha colisoes remanescentes\n");
    }
    return 0;
    }

void read_data(double *x0, double *x1, double *x2, double *x3,
               double *v0, double *v1, double *v2, double *v3,
               double *m0, double *m1, double *m2, double *m3,
               double *T_max){
               scanf("%lf %lf %lf", x0, v0, m0);
               scanf("%lf %lf %lf", x1, v1, m1);
               scanf("%lf %lf %lf", x2, v2, m2);
               scanf("%lf %lf %lf", x3, v3, m3);
               scanf("%lf", T_max);
               }

double t(double x, double xx, double v, double vv){
    double L = 0.1, t;
    if(v > vv){
        t = (xx - x - L)/(v - vv);
    }
    else{
        t = HUGE_VAL;
    }
    return t;
}

double min(double a, double b, double c, int *i){
    double m;
    /*Determinar o valor de m*/
    m = a;
    if (b < m){
        m = b;
    }
    if(c < m){
        m = c;
    }
    /*Determinar o valor de i*/
    if( a == m){
        *i = 1;
    }
    if( a != m && b == m){
        *i = 2;
    }
    if( a != m && b != m){
        *i = 3;
    }
    return m;
}

double adv(double *x, double v, double t){
    double deslocamento, x_inicial;
    x_inicial = *x;
    *x = *x + (v*t);
    deslocamento = *x - x_inicial;
    if (deslocamento >= 0){
        return deslocamento;
    }
    else{
        deslocamento = deslocamento *(-1);
        return deslocamento;
    }
}

void resolve(double *v, double *vv, double m, double mm){
    double A;
    A = 2 * (*v * m + *vv * mm) / (m + mm);
    *v = A - *v;
    *vv = A - *vv;
}

void print_data(long c1, long c2, long c3,
                double x0, double x1, double x2, double x3,
                double v0, double v1, double v2, double v3,
                double d0, double d1, double d2, double d3){
                printf("Numero de colisoes por bloco: %ld %ld %ld\n", c1, c2, c3);
                printf("Numero total de colisoes: %ld\n", c1 + c2 + c3);
                printf("Colisoes dos dois blocos a direita: %ld\n", c2 + c3);
                printf("x0 = %f v0 = %f d0 = %f\n", x0, v0, d0);
                printf("x1 = %f v1 = %f d1 = %f\n", x1, v1, d1);
                printf("x2 = %f v2 = %f d2 = %f\n", x2, v2, d2);
                printf("x3 = %f v3 = %f d3 = %f\n", x3, v3, d3);
                }