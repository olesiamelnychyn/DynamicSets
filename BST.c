// bvs.c -- Olesia Melnychyn, 24.10.2019 13:57

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Implementacia nevyvazeneho BVS patri do tohto suboru.
struct bin_tree {
int data;
struct bin_tree * right, * left;
};
typedef struct bin_tree node;

struct bin_tree* deleteTree(struct bin_tree** node);

void insert(node ** tree, int val){
    node *temp = NULL;
    if(!(*tree)){
        temp = (node *)malloc(sizeof(node));
        temp->left = temp->right = NULL;
        temp->data = val;
        *tree = temp;
        return;
    }

    if(val < (*tree)->data){
      insert(&(*tree)->left, val);
    } else if(val > (*tree)->data){
      insert(&(*tree)->right, val);
    }
}

node* search(node* root, int data){
  if (root == NULL || root->data == data)
      return root;
    
  if (root->data < data)
      return search(root->right, data);

  return search(root->left, data);
}

void printInorder(node* root, int *i){
     if (root == NULL)
          return;
     printInorder(root->left, i);
    (*i)++;
    if(*i % 10 == 0 && *i!=0)
         printf("\n");
     printf("%d ", root->data);
     printInorder(root->right, i);
}

double do_smth_bvs(int N, int check){
    printf("\n\n\n********** Binary Search Tree **********\n");
    
    node *root;
    root = NULL;
    int rnd = 0;
    
    clock_t t;
    t = clock();
          
    for(int i =0; i<N; i++){
        rnd = (rand() % (3*N));
        insert(&root, rnd);
    }
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("It took %f seconds to execute insertion of %d members\n", time_taken, N);
    if(check){
        int i =0;
        printInorder(root, &i);
    }
    deleteTree(&root);
    root = NULL;
return time_taken;
}

struct bin_tree* deleteTree(struct bin_tree** node){
    if (node == NULL) return *node;
    if((*node)->right!=NULL)
       return deleteTree(&((*node)->right));
    if((*node)->left!=NULL)
        return deleteTree(&((*node)->left));
    free(*node);
    return NULL;
}
