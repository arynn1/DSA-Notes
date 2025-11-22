#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
    int data;
    struct node* LC;
    struct node* RC;
}ctype, *BST;

void insert(BST* T, int data);
void delete(BST* T, int target);
void makeNull(BST* T);
BST* min(BST* T);

int main(){
    return 0;
}

void makeNull(BST* T){
    if (*T != NULL) {
        makeNull(&(*T)->LC);
        makeNull(&(*T)->RC);
        free(*T);
        *T = NULL;
    }
}

void insert(BST* T, int data){
    BST* trav = T;
    while(*trav != NULL){
        if((*trav)->data == data){
            printf("Element already in tree\n");
            return;
        } else if((*trav)->data < data){
            trav = &(*trav)->RC;
        } else{
            trav = &(*trav)->LC;
        }
    }

    BST newNode = malloc(sizeof(ctype));
    if(newNode == NULL){
        printf("Memory Allocation Failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->LC = NULL;
    newNode->RC = NULL;
    *trav = newNode;
}

void delete(BST* T, int target){
    BST* trav = T;
    if(*trav != NULL){
        for(; *trav != NULL && (*trav)->data != target; 
            trav = ((*trav)->data < target) ? &(*trav)->RC : &(*trav)->LC);

        if((*trav)->LC != NULL && (*trav)->RC != NULL){
            BST* successor = min(&(*trav)->RC);
            (*trav)->data = (*successor)->data;
            trav = successor
        }

        BST temp = *trav;
        *trav = ((*trav)->LC != NULL) ? *trav = (*trav)->LC : *trav = (*trav)->RC;
        free(temp);

    } else {
        printf("Tree is Empty!\n");
        return;
    } 
}

BST* min(BST* T){
    BST* trav;
    for(trav = T; *trav != NULL && (*trav)->LC != NULL; trav = &(*trav)->LC);
    return trav;
}