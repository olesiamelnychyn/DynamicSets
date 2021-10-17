// cudzi-vyvazeny.c -- Olesia Melnychyn, 24.10.2019 13:57

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Source: https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
// An AVL tree node
struct avl_node{
    int data;
    struct avl_node *link[2];
    int height;
};

//utility funktions:
int height(struct avl_node *N);
int max(int a, int b);
struct avl_node* newNode(int data);
int checkHeights(struct avl_node *N);
void avl_print_node(struct avl_node *node);
void avl_printInorder(struct avl_node* root, int *i);
struct avl_node* deleteTree_avl(struct avl_node** node);

struct avl_node *rotate(struct avl_node *a, int side){
    struct avl_node *b = a->link[!side], *z = a->link[!side]->link[side];
    b->link[side] = a; //actual rotation
    a->link[!side] = z;

    a->height = max(height(a->link[!side]), height(a->link[side]))+1; //change heights
    b->height = max(height(b->link[!side]), height(b->link[side]))+1;
    
    return b; // b is new root
}

struct avl_node* avl_insert(struct avl_node* root, int data){
    if (root == NULL)
        return(newNode(data));
    if (data < root->data)
        root->link[0] = avl_insert(root->link[0], data);
    else if (data > root->data)
        root->link[1] = avl_insert(root->link[1], data);
    else                     //there can't be nodes with equal values
        return root;

    root->height = 1 + max(height(root->link[0]), height(root->link[1])); //change height of parent
    int diff_heights = checkHeights(root); //variable to check if the tree is unbalanced

    if (diff_heights > 1 && data < root->link[0]->data)     // Left-Left Case
        return rotate(root, 1);
    else if (diff_heights < -1 && data > root->link[1]->data)     // Right-Right Case
        return rotate(root, 0);
    else if (diff_heights > 1 && data > root->link[0]->data){    // Left-Right Case
        root->link[0] = rotate(root->link[0], 0);
        return rotate(root, 1);
    } else if (diff_heights < -1 && data < root->link[1]->data){    // Right-Left Case
        root->link[1] = rotate(root->link[1], 1);
        return rotate(root, 0);
    } else
        return root;
}

struct avl_node* avl_search ( struct avl_node *root, int data ){
 if (root == NULL || root->data == data)
     return root;
 if (root->data < data)
     return avl_search(root->link[1], data);
 return avl_search(root->link[0], data);
}

double do_smth_avl(int N, int check)
{
    printf("\n\n\n\n********** Borrowed tree program **********\n");
    printf("AVL Tree\n");
    struct avl_node *root = NULL;
    int rnd = 0;
   
    clock_t t;
    t = clock();
          
    for(int i =0; i<N; i++){
         rnd = (rand() % (3*N));
         root = avl_insert(root, rnd);
    }
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("It took %f seconds to execute insertion of %d members\n", time_taken, N);
    if(check){
        printf("\nTree in order: \n");
        int i =0;
        avl_printInorder(root, &i);
    }
    deleteTree_avl(&root);
    root = NULL;
//    struct avl_node *temp = avl_search(root, 20);
//    avl_print_node(temp);
//    avl_printInorder(root);
return time_taken;
}

int height(struct avl_node *N){
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b){
    if(a>b)
        return a;
    else
        return b;
}

struct avl_node* newNode(int data){
    struct avl_node* temp = (struct avl_node*)
                        malloc(sizeof(struct avl_node));
    temp->data = data;
    temp->link[0] = NULL;
    temp->link[1] = NULL;
    temp->height = 1;
    return(temp);
}

// Check heights
int checkHeights(struct avl_node *N){
    if (N == NULL)
        return 0;
    return height(N->link[0]) - height(N->link[1]);
}

void avl_printInorder(struct avl_node* root, int *i){
    
     if (root == NULL)
          return;
    
    avl_printInorder(root->link[0], i);
    (*i)++;
    if(*i % 10 == 0 && *i!=0)
         printf("\n");
    printf("%d ", root->data);
    avl_printInorder(root->link[1], i);
}

void avl_print_node(struct avl_node *node){
    if(node!=NULL){
        printf("\n\n\nValue: %d\n", node->data);
        if(node->link[0]!=NULL)
             printf("Left value: %d\n", node->link[0]->data);
        if(node->link[1]!=NULL)
            printf("Right value: %d\n", node->link[1]->data);
    }
    else{
        printf("There is no node in the tree with such value");
    }
}

struct avl_node* deleteTree_avl(struct avl_node** node){
    if (node == NULL) return *node;
    if((*node)->link[0]!=NULL)
       return deleteTree_avl(&((*node)->link[0]));
    if((*node)->link[1]!=NULL)
        return deleteTree_avl(&((*node)->link[1]));
    free(*node);
    return NULL;
}
