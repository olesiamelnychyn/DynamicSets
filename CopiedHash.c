// cudzi-hash.c -- Olesia Melnychyn, 24.10.2019 13:57

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

// Source: https://neerc.ifmo.ru/wiki/index.php?title=Разрешение_коллизий
struct hashNode {
    int data;
    struct hashNode *next;
};

struct hashNode** hash_1;
struct hashNode* item;

int SIZE =0;
int prime = 2;

//utility functions:
bool check_prime(int x);
int find_prime(int N);
void printHash(void);
void printNode(struct hashNode * node);

int hashCode(int data) { //generating code(key)
   int key = 0;
    for (int i = data; i > 0; i/=SIZE){
        key = (key * prime) + i%SIZE;
    }
    return key%SIZE;
}

struct hashNode *hash1_search(int data) {
    int index = hashCode(data);
    struct hashNode *temp = hash_1[index];
    while(temp->next != NULL) {
        if(temp->data == data)
            return temp;
        temp= temp->next;
    }
    return NULL;
}

void hash1_insert(int data) {

    struct hashNode *item = (struct hashNode*) malloc(sizeof(struct hashNode)); //make a node to insert
    item->data = data;
    item->next = NULL;

    int index = hashCode(data); //find key
    if(hash_1[index]->data == -1){ //finding place to insert new node
          hash_1[index] = item;
    }else{
        struct hashNode *temp =hash_1[index];
        while( temp->next!= NULL && temp->next->data!=data) {
            temp=temp->next;
        }
        //here
        if(temp->next == NULL)
            temp->next=item;
    }
}

double cudzi_hash_do_smth(int N, int check) {
    printf("\n\n\n********** Borrowed hash program **********\n");
    printf("Solving the colision with chaining method\n");
    SIZE = N;
    (hash_1) = (struct hashNode**) malloc(SIZE*sizeof(struct hashNode*));
    for(int i = 0; i<SIZE; i++){
        hash_1[i]=(struct hashNode*) malloc(sizeof(struct hashNode));
        hash_1[i]->data = -1;
        hash_1[i]->next = NULL;
    }
    prime = find_prime(SIZE);

    int rnd = 0;

    clock_t t;
    t = clock();

    for(int i =0; i<SIZE; i++){
        rnd = (rand() % (3*SIZE));
        hash1_insert(rnd);

    }
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;

    printf("It took %f seconds to execute insertion of %d members\n", time_taken, SIZE);
    if(check){
        printf("\nMy hash:\n");
        printHash();
    }
    free(hash_1);
    hash_1=NULL;

//    hash1_insert(1, 20);
//    printHash();
//    printNode(hash1_search(3));
    return time_taken;
}

bool check_prime(int x){
    for(int i =2; i<x; i++)
        if(x%i == 0)
            return 0;
    return 1;
}

int find_prime(int N){
    while(true){
        if(check_prime(N))
            return N;
        N++;
    }
}

void printHash() {
  int i = 0;
     
  for(i = 0; i<SIZE; i++) {
    struct hashNode *temp = hash_1[i];
    printf("Key: %d --- ", i);
      while(temp!=NULL){
        printf("%d  ",temp->data);
          temp=temp->next;
      }
        
    printf("\n");
  }
}

void printNode(struct hashNode * node) {
    if(node!=NULL){
        printf("Data: %d  Key: %d\n", node->data, hashCode(node->data));
    } else{
        printf("There is no node with such value\n");
    }
}
