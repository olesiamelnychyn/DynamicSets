// moj-hash.c -- Olesia Melnychyn, 24.10.2019 13:57

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Vlastna implementacia hashovania.
int vector = 0;
int off = 3;
// ...
struct myHashNode {
    int key;
    int data;
};

//utility functions:
void my_hash_print(int N, int *hash);

void init_hash(int N, int** hash){
    *hash = (int*)malloc(off*N*sizeof(int));
    for(int i =0; i<off*N; i++)
        (*hash)[i]=0;
}

int found_key(int value, int n){ //key formula
    int data = value;
    int key = 0;
    while(data>0){
        key += data % n;
        data = (data/n);
    }
    key = n - key % n;
    return off*key;
}

int * my_hash_insert(int value, int *n, int *hash){
    int key = found_key(value, *n);

     while((hash)[key]!=0 && (hash)[key]!=value){ //finding free place to insert
            key++;
            key%=(off*(*n));
        }
    if((hash)[key]!=value){
        (hash)[key]=value;
        vector++;
    }
    
    if(vector>(*n*off/2)){
        
        hash= (int *) realloc (hash, (*n)*2*off*sizeof(int));
    
        for(int i = *n*off; i<*n*off*2; i++)
            (hash)[i]=0;
        
        for(int i = *n*off-1; i>=0; i--){
            int pom =hash[i];
            hash[i]=0;
            hash[i*2-i%off] =pom;
        }

        off *=2;
        // free(hash3);
    }
    return hash;
}

int my_hash_search(int value, int n, int* hash){
    int key = found_key(value, n);
    int key2 = key;
    while(hash[key2]!=value && key2!=(key+3)%n){
        key2++;
        key2%=n;
    }
    return key2;
}

double my_hash_do_smth(int n, int check){
    printf("\n\n\n\n********** My hash program **********\n");
    printf("Finding the most close free place\n");
    int *hash;
    init_hash(n, &hash);
    
    int rnd = 0;
    
    clock_t t;
    t = clock();
       
    for(int i =0; i<2*n; i++){
        rnd = (rand() % (3*n));
        hash = my_hash_insert(rnd, &n, hash);
    }
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
       
    printf("It took %f seconds to execute insertion of %d members\n", time_taken, n);
    if(check){
        printf("\nMy hash:\n");
        my_hash_print(n, hash);
    }
    free(hash);
    hash= NULL;
//    my_hash_insert(2, 98, n, &hash);
//    my_hash_print(n, &hash);
//    print_key(my_hash_search(98, n, hash), n, hash);
    return time_taken;
}

void my_hash_print(int N, int *hash){
    for(int i =0; i<N*off; i++){
        printf("%d - ", hash[i]);
        if(i % 15 == 0 && i!=0)
            printf("\n");
    }
    printf("\n\n\n");
}

void print_key(int i, int n, int *hash){
    if(i!=n)
        printf("hash[%d] = %d\nkey = %d", i/3, hash[i], found_key(hash[i], n));
    else
        printf("There is no such value in hash table\n");
}

//void init_hash(int N, struct myHashNode*** hash){ //make a hash table with size 3*N
//    *hash = (struct myHashNode**)malloc(3*N*sizeof(struct myHashNode*));
//    for(int i =0; i<3*N; i++){
//        (*hash)[i] = malloc(sizeof(struct myHashNode));
//        (*hash)[i]->key=0;
//    }
//}
//void my_hash_print(int N, int * hash){
//    for(int i =0; i<N; i++){
//        for(int j = 0; j<3; j++)
//            printf("(%d,%d)    ", (hash)[i], (hash)[i*3+j]->data );
//        printf("\n");
//    }
//    printf("\n\n\n");
//}
//void printHash(int N, int * hash) {
//  int i = 0;
//
//  for(i = 0; i<SIZE; i++) {
//    struct hashNode *temp = hash_1[i];
//    printf("Key: %d --- ", i);
//      while(temp!=NULL){
//        printf("%d  ",temp->data);
//          temp=temp->next;
//      }
//
//    printf("\n");
//  }
//}
//
//void print_key( struct myHashNode* node){
//    if(node!=NULL)
//        printf("(%d,%d)\n", node->key, node->data);
//    else
//        printf("There is no such value in hash table\n");
//}
//struct myHashNode* my_hash_search(int value, int n,struct myHashNode** hash){
//    int index = found_key(value, n);
//    while((hash)[index]->key!=0){
//        if((hash)[index]->data==value)
//                return (hash)[index];
//        index++;
//    }
//    return NULL;
//}

//void my_hash_insert(int key,int value,  int n, struct myHashNode*** hash){ //insert function
//    struct myHashNode* new = malloc(sizeof(struct myHashNode));
//    new->data = value;
//    new->key = key;
//    int index = found_key(value, n);
//    while((*hash)[index]->key!=0){
//        index++;
//        index%=(3*n);
//    }
//
//    (*hash)[index]=new;
//}
