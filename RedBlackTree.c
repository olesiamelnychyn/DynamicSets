// moj-vyvazeny.c -- Olesia Melnychyn, 24.10.2019 13:57

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct red_black_node{
    bool colour;  // 0 - black, 1 - red
    int data; // value
    struct red_black_node *link[2]; //pointer at the left and right nodes
    struct red_black_node *parent; // pointer at the parent node
};

//utility functions
struct red_black_node* rotation_1 ( struct red_black_node *root, bool side );
struct red_black_node *rotation_2 ( struct red_black_node *root, bool side );
void print_node(struct red_black_node *node);
void rbt_printInorder(struct red_black_node* root, int *i);
struct red_black_node* find_grandpa(struct red_black_node *node);
struct red_black_node* find_uncle(struct red_black_node *node, bool *side_parent);
struct red_black_node* deleteTree_rbt(struct red_black_node** node);


struct red_black_node* rb_insert(struct red_black_node ** tree, struct red_black_node* parent, int val, bool *side ){ //simple insertion fo ordinar Binary Search Tree but with founding out side of the node under its parent

    if((*tree) == NULL){
        struct red_black_node *temp = NULL;
        temp = (struct red_black_node *) malloc (sizeof(struct red_black_node));
        temp->link[0] = NULL;
        temp->link[1] = NULL;
        temp->data = val;
        temp->colour=1;
        if(parent!=NULL)
            temp->parent = parent;
        else
            temp->parent = NULL;
        *tree = temp;
        return *tree;
    }
    if(val < (*tree)->data){
        *side = 0;
        return rb_insert(&(*tree)->link[0],*tree,  val, side);
    } else if(val > (*tree)->data) {
        *side = 1;
        return rb_insert(&(*tree)->link[1], *tree, val, side);
    } else
        return NULL;
}

void red_black_insert ( struct red_black_node **tree, int data ){
    bool side, side_parent;
    struct red_black_node *temp;
    temp = rb_insert(tree, NULL, data, &side); //simple insertion
    if(temp==NULL){ //if the tree already has a node with such value
        return;
    }
 
    if(temp == *tree){ //if the node is first so it is a root
        (*tree)->colour=0;
        return;
    }
    struct red_black_node *parent = temp->parent; //if its parent is a root we don't need to balance it
    if(parent == *tree){
        return;
    }
    
    struct red_black_node *grandpa = find_grandpa(temp), *grandgrandpa, *head;
    struct red_black_node *uncle =find_uncle(temp, &side_parent);

    while( parent!=NULL && parent->colour && grandpa!=NULL ){ //actual balncing
  
        if(uncle != NULL && uncle->colour){//if uncle is red - change colour
                uncle->colour = 0;          //(a - i) look down
                parent->colour = 0;         //(a - i)
                grandpa->colour = 1;      //(a - ii)
        } else if(uncle == NULL || !(uncle->colour) ){ //if uncle is black - change colour
            grandgrandpa = find_grandpa(parent);
            if(side_parent==side){ //Left-Left Case or Right-Right Case
                head = rotation_1(grandpa, !side);
            } else {                //Left-Right Case or Right-Left Case
                head = rotation_2(grandpa, side);
            }
            if(grandgrandpa!=NULL){ //adding pointer to a new subtree
                if(grandgrandpa->link[0] == grandpa){
                    grandgrandpa->link[0] = head;
                } else if(grandgrandpa->link[1] == grandpa){
                    grandgrandpa->link[1] = head;
                }
            } else{ //if there is no grandgrandpa then it is a root
                *tree = head;
                (*tree)->colour = 0;
                return;
            }
        }
            
        temp = grandpa; //getting ready for the checking next level of tree
        parent = temp->parent;
        grandpa = find_grandpa(temp);
        if(grandpa==NULL){
           break;
        }
        if(parent == grandpa->link[0])
              side_parent=0;
          else if (parent == grandpa->link[1])
              side_parent = 1;
        uncle = find_uncle(temp, &side_parent);
        if(parent->link[0]== temp){
            side=0;
        } else
            side = 1;
    }
        
    while(temp->parent!=NULL)
    temp = temp->parent;
    *tree = temp;
    (*tree)->colour = 0;
    return;
}

//rotate once
struct red_black_node* rotation_1 ( struct red_black_node *root, bool side ){ // 0 - left, 1- right
    struct red_black_node *temp =  (root)->link[!side];
    temp->parent = root->parent; //setting different pointers
    if(root->parent!=NULL){
        if(root->parent->link[0]== root)
            root->parent->link[0]= temp;
        else
            root->parent->link[1]= temp;
    }
    
    (root)->link[!side] = temp->link[side];
    if(temp->link[side] !=NULL)
        temp->link[side]->parent = root;
    root->parent = temp;
    temp->link[side] = (root);
    
    temp->colour=0;//setting colours
    (root)->colour = 1;
    return temp;
}

//rotate 2 times
struct red_black_node *rotation_2 ( struct red_black_node *root, bool side ){ // 0 - left, 1- right
    root->link[!side] = rotation_1 (root->link[!side], !side );
    return rotation_1( root, side );
}

struct red_black_node* red_black_search ( struct red_black_node *root, int data ){
 if (root == NULL || root->data == data)
     return root;
 if (root->data < data)
     return red_black_search(root->link[1], data);
 return red_black_search(root->link[0], data);
}

double rbt_do_smth(int N, int check){
    printf("\n\n\n********** My tree program **********\n");
    printf("Red Black Tree\n");
    struct red_black_node  * root =NULL;
    int rnd = 0;
    
    clock_t t;
    t = clock();
    for( int i = 0; i < N; i++)
    {
        rnd = (rand() % (3*N));
        red_black_insert(&root, rnd);
    }

    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("It took %f seconds to execute insertion of %d members\n", time_taken, N);
    if(check){
        printf("\nTree in order: \n");
        int i =0;
        rbt_printInorder(root, &i);
    }
    deleteTree_rbt(&root); //to free place
    root = NULL;
    
//    red_black_insert(&root, 7);
//    struct red_black_node  *temp =  red_black_search(root, 2);
//    rbt_print_node(temp);
//    rbt_printInorder(root);
    return time_taken;
}

struct red_black_node* find_grandpa(struct red_black_node *node){
    if(node == NULL || node->parent==NULL)
        return NULL;
    return node->parent->parent;
}

struct red_black_node* find_uncle(struct red_black_node *node, bool *side_parent){
    if(node == NULL)
        return NULL;
    struct red_black_node *grandpa = find_grandpa(node);
    if(grandpa!=NULL){
        if(grandpa->link[0] == node->parent){
            *side_parent = 0;
            return grandpa->link[1];
        }
        else{
            *side_parent = 1;
            return grandpa->link[0];
        }
    }else{
        *side_parent = 2;
        return NULL;
    }
}


void rbt_print_node(struct red_black_node *node, struct red_black_node **root){
    if(node!=NULL){
        printf("\n\n\nValue: %d\nColour: %d\n", node->data, node->colour);
        struct red_black_node *parent = node->parent;
        if((*root)->parent!=NULL)
            printf("Parent value: %d\nParent colour: %d\n", parent->data, parent->colour);
        if(node->link[0]!=NULL)
             printf("Left value: %d\nLeft colour: %d\n", node->link[0]->data, node->link[0]->colour);
        if(node->link[1]!=NULL)
        printf("Right value: %d\nRight colour: %d\n", node->link[1]->data, node->link[1]->colour);
    } else{
        printf("\n\n\nThere is no node in the tree with such value!!!!");
    }
}

void rbt_printInorder(struct red_black_node* root, int *i){
     if (root == NULL)
          return;
     rbt_printInorder(root->link[0], i);
    (*i)++;
    if(*i % 10 == 0 && *i!=0)
         printf("\n");
     printf("%d ", root->data);
     rbt_printInorder(root->link[1], i);
}

struct red_black_node* deleteTree_rbt(struct red_black_node** node)
{
    if (node == NULL) return *node;
    if((*node)->link[0]!=NULL)
       return deleteTree_rbt(&((*node)->link[0]));
    if((*node)->link[1]!=NULL)
        return deleteTree_rbt(&((*node)->link[1]));
    free(*node);
    return NULL;
}

// ^^^ Do following if color of x’s parent is not BLACK and x is not root.
// ^^^     a) If x’s uncle is RED (Grand parent must have been black from property 4)
// ^^^        (i) Change color of parent and uncle as BLACK.
// ^^^        (ii) color of grand parent as RED.
// ^^^        (iii) Change x = x’s grandparent, repeat steps 2 and 3 for new x.
// ^^^   b) If x’s uncle is BLACK, then there can be four configurations for x, x’s parent          (p) and x’s grandparent (g) (This is similar to AVL Tree)
// ^^^        (i) Left Left Case (p is left child of g and x is left child of p)
// ^^^        (ii) Left Right Case (p is left child of g and x is right child of p)
// ^^^        (iii) Right Right Case (Mirror of case i)
// ^^^        (iv) Right Left Case (Mirror of case ii)
