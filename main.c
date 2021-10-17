#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// documentation: https://drive.google.com/file/d/1421MTPleZozzPpuWaUXk3sVd3BIKaCZB/view?usp=sharing

extern double rbt_do_smth(int N, int check);
extern double do_smth_avl(int N, int check);
extern double my_hash_do_smth(int n, int check);
extern double cudzi_hash_do_smth(int N, int check);
extern double do_smth_bvs(int N, int check);
void print_type(int i);
void get_time(int j,int i, double ***sec, int check);

int main(int argc, const char * argv[]) {
    int N[5] = {1000, 5000, 7000,10000, 15000};


    int check=0;
    printf("Would you like to see an example how this program works? (0 - no, 1 - yes): ");
    scanf("%d", &check);
    if(check){
        do_smth_bvs(50, check);
        rbt_do_smth(50, check);
        do_smth_avl(50, check);
        my_hash_do_smth(50, check);
        cudzi_hash_do_smth(50, check);
        check = 0;
    }
    
    double **sec;
    sec =(double**) malloc (5 * sizeof(double));
    for(int i =0; i<5; i++){
        sec[i] = (double*) malloc( 5* sizeof(double));
    }

    for(int i =0; i<5; i++){
       get_time(i, N[i], &(sec), check);
    }

    printf("\n\n\n  Result:\n\n                     ");
    for(int i =0; i<5; i++){
        printf("%d                 ", N[i]);
    }

    printf("k=15\n\n");
    for(int i =0; i<5; i++){
        print_type(i);
        for (int j=0; j<5; j++) {
            printf("%f             ", sec[i][j]);
        }
        printf("%f\n\n", sec[i][4]/sec[i][0]);
    }
    printf("\n\n");
//    my_hash_do_smth(10);
    return 0;
}

void get_time(int j,int i, double ***sec, int check){
    (*sec)[0][j]=do_smth_bvs(i, check);
    (*sec)[1][j]=rbt_do_smth(i, check);
    (*sec)[2][j]=do_smth_avl(i, check);
    (*sec)[3][j]=my_hash_do_smth(i, check);
    (*sec)[4][j]=cudzi_hash_do_smth(i, check);
}

void print_type(int i){
    switch (i) {
        case 0:{
            printf("  BST                ");
            break;
        }case 1:{
            printf("  Red-Black Tree     ");
            break;
        }case 2:{
            printf("  AVL Tree           ");
            break;
        }case 3:{
            printf("  My hash            ");
            break;
        }case 4:{
            printf("  Borrowed hash      ");
            break;
        }
    }
}
