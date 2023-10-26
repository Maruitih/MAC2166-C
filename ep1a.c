/***************************************************************/
/**                                                           **/
/**   Henrique Maruiti                             12610243   **/
/**   Exercício-Programa 1a                                   **/
/**   Professor:Yoshiharu Kohayakawa                          **/
/**   Turma: 01                                               **/
/**                                                           **/
/***************************************************************/

#include <stdio.h>

int main(){
    int num = 0, soma = 0, digito = 0, base = 1;
    scanf("%d",&num);
    while (num != 0){
    soma = 0;
    base = 1;    
        while (num != 0){
            digito = num % 10;
            soma += digito*base;
            num = num/10;
            base *= 3;       
        }
    printf("%d\n",soma);
    scanf("%d",&num);
    }
    return 0;
}