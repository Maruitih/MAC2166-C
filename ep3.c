/***************************************************************/
/**                                                           **/
/**   Henrique Maruiti                             12610243   **/
/**   Exercicio-Programa 3                                    **/
/**   Professor:Yoshiharu Kohayakawa                          **/
/**   Turma: 01                                               **/
/**                                                           **/
/***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_PIXELS 1000000
#define rand2166() (rand2166f(-1))
#define srand2166(seed) (rand2166f((seed)))
#define AA 16807
#define MM 2147483647

void output_image(int col, int row, int v_max, int image[]);
void read_image(int *col, int *row, int *v_max, int image[]);
void encode(int col, int row, int v_max, int image[], int key);
void decode(int col, int row, int v_max, int image[], int key, int decoded[]);
void decode_in_loco(int col, int row, int v_max, int image[], int key);
void decode_brute_force(int col, int row, int v_max, int image[], int max_key);
double entropy(int v_max, int N, int image[]);
int rand2166f(int seed);

int main (int argc, char *argv[]){
    int col, row, v_max;
    int image[MAX_PIXELS];
    int key = atoi(argv[2]);
    int task = atoi(argv[1]);
    char keyword[2];

    scanf("%c %c", &keyword[0], &keyword[1]);
    printf("%c%c\n", keyword[0], keyword[1]);
    read_image(&col, &row, &v_max, image);
    if(task == 0){
        encode(col, row, v_max, image, key);
    }
    if(task == 1){
        decode_in_loco(col, row, v_max, image, key);
    }
    if(task == 2){
        decode_brute_force(col, row, v_max, image, key);
    }
    output_image(col, row, v_max, image);
    return 0;
}

void output_image(int col, int row, int v_max, int image[]){
    int i = 0, row_1 = 0, col_1 = 0;
    printf("%d %d\n", col, row);
    printf("%d\n", v_max);
    for(row_1 = 0; row_1 < row; row_1++){
        for(col_1 = 0; col_1 < col; col_1++){
            printf("%d ", image[i]);            
            i++;
        }
        printf("\n");
    }
}

void read_image(int *col, int *row, int *v_max, int image[]){
    int i = 0;
    scanf("%d %d", col, row);
    scanf("%d", v_max);
    for(i = 0; i < (*col * *row); i++){
        scanf("%d", &image[i]);
    }
}

void encode(int col, int row, int v_max, int image[], int key){
    int i = 0;
    srand2166(key);
    for(i = 0; i < (col * row); i++){
        image[i] = (image[i] + (rand2166() % (v_max + 1))) % (v_max + 1);
    }
}

void decode(int col, int row, int v_max, int image[], int key, int decoded[]){
    int i = 0;
    srand2166(key);
    for(i = 0; i < (col * row); i++){
        decoded[i] = (image[i] - (rand2166() % (v_max + 1)) + (v_max + 1)) % (v_max + 1);
    }
}

void decode_in_loco(int col, int row, int v_max, int image[], int key){
    int i = 0;
    srand2166(key);
    for(i = 0; i < (col * row); i++){
        image[i] = (image[i] - (rand2166() % (v_max + 1)) + (v_max + 1)) % (v_max + 1);
    }
}

void decode_brute_force(int col, int row, int v_max, int image[], int max_key){
    int decoded[MAX_PIXELS], N = col * row, correct_key = 0, min_key = 0;
    double entropy_min = HUGE_VAL, entropy_1 = 0;
    for(min_key = 0; min_key <= max_key; min_key++){
        decode(col, row, v_max, image, min_key, decoded);
        entropy_1 = entropy(v_max, N, decoded);
        if(entropy_min > entropy_1){
            entropy_min = entropy_1;
            correct_key = min_key;
        }
    }
    decode_in_loco(col, row, v_max, image, correct_key);
}

double entropy(int v_max, int N, int image[]){
    int v = 0, i = 0;
    double entropy = 0, F_i, P_i;
    for(v = 0; v <= v_max; v++){
        F_i = 0;
        for(i = 0; i < N; i++){
            if(v == image[i]){
                F_i++;
            }
        }
        P_i = F_i/ N;
        if(P_i > 0){
            entropy = entropy + (P_i * log(1/P_i));
        }
    }
    return entropy;
}

int rand2166f(int seed) {
static long r;
if (seed >= 0) {
r = seed;
return 0;
}
r = (r * AA) % MM;
return r;
}