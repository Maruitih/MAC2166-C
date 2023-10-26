/***************************************************************/
/**                                                           **/
/**   Henrique Maruiti                             12610243   **/
/**   Exercício-Programa 1b                                   **/
/**   Professor:Yoshiharu Kohayakawa                          **/
/**   Turma: 01                                               **/
/**                                                           **/
/***************************************************************/

#include <stdio.h>
int main(){
    int num = 0, fib1 = 0, fib2 = 1, fib3 = 0, seq = 1, digito = 0, soma = 0;

    scanf("%d",&num);
    if(num == 0){
        scanf("%d",&num);
        while(num != 0){
            fib1 = 0;
            fib2 = 1;
            fib3 = 0;
            seq = 1;
            while(fib3 <= num){
                fib3 = fib1 + fib2;
                fib1 = fib2;
                fib2 = fib3;
                seq ++;
            }
            printf("1");
            num = num - fib1;
            while(seq != 3){
                fib2 = fib1;
                fib1 = fib3 - fib2;
                fib3 = fib2;
                if(num - fib1 < 0){
                    printf("0");
                }
                else{
                    num -= fib1;
                    printf("1");
                }
                seq--;
            }
            printf("\n");
            scanf("%d",&num);
            }
        return 0;
        }    
    if(num == 1){
        scanf("%d",&num);
        while(num != 0){
            while (num != 0){
                fib1 = 0;
                fib2 = 1;
                fib3 = 0;
                seq = 0;
                while(fib3 <= num){
                    fib3 = fib1 + fib2;
                    fib1 = fib2;
                    fib2 = fib3;
                    seq ++;
                }
                num = num - fib1;
                seq = seq - 1;
                if (num > 0){
                    printf("F_%d (%d) + ", seq, fib1);
                }
                else {
                    printf("F_%d (%d)\n", seq, fib1);
                }
            }
        scanf("%d",&num);
        }
        return 0;
    }
    if(num == 2){
        scanf("%d",&num);
        while(num != 0){
            fib1 = 0;
            fib2 = 1;
            fib3 = 0;
            seq = 1;
            soma = 0;
            while(num != 0){
                fib3 = fib1 + fib2;
                fib1 = fib2;
                fib2 = fib3;
                seq++;
                digito = num%10;
                num = num/10;
                if(digito == 1){
                    soma += (digito * fib2);
                }
            }
            printf("%d\n",soma);
            scanf("%d",&num);
        }
        return 0;
    }
    return 0;
}