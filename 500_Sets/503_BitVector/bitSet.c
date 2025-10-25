#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef int SET[MAX];

void insertToSet(SET *S, int data);
void deleteFromSet(SET *S, int data);
void populateSet(SET *S);
void printSet(SET S);
SET* Union(SET A, SET B);
SET* Intersection(SET A, SET B);
SET* Difference(SET A, SET B);

int main(){
    SET A = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    SET B = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    populateSet(&A);
    populateSet(&B);

    printf("SET A = ");
    printSet(A);
    printf("SET B = ");
    printSet(B);

    insertToSet(&A, 8);
    insertToSet(&A, 9);
    insertToSet(&B, 0);
    insertToSet(&B, 6);

    printf("SET A = ");
    printSet(A);
    printf("SET B = ");
    printSet(B);

    deleteFromSet(&A, 8);
    deleteFromSet(&A, 9);
    deleteFromSet(&B, 0);
    deleteFromSet(&B, 6);

    printf("SET A = ");
    printSet(A);
    printf("SET B = ");
    printSet(B);

    SET* C = Union(A, B);
    SET* D = Intersection(A, B);
    SET* E = Difference(A, B);

    printf("SET C = ");
    printSet(*C);
    printf("SET D = ");
    printSet(*D);
    printf("SET E = ");
    printSet(*E);

    return 0;
}

void insertToSet(SET *S, int data){
    if(data < MAX && data > -1){
        (*S)[data] = 1;
    }
}

void deleteFromSet(SET *S, int data){
    if(data < MAX && data > -1){
        (*S)[data] = 0;
    }
}

void populateSet(SET *S){
    int size;
    printf("How many elements?: ");
    scanf(" %d", &size);

    int curr;
    for(int i = 0; i < size; i++){
        printf("Enter element %d: ", i);
        scanf(" %d", &curr);
        (*S)[curr] = 1;
    }
}

void printSet(SET S){
    printf("[ ");
    for(int i = 0; i < MAX; i++){
        if(S[i] == 1){
            printf("%d ", i);
        }
    }
    printf("]\n");
}

SET* Union(SET A, SET B){
    SET* C = malloc(sizeof(SET));

    for(int i = 0; i < MAX; i++){
        if(A[i] == 1 || B[i] == 1){
            (*C)[i] = 1;
        }else{
            (*C)[i] = 0;
        }
    }

    return C;
}

SET* Intersection(SET A, SET B){
    SET* C = malloc(sizeof(SET));

    for(int i = 0; i < MAX; i++){
        if(A[i] == 1 && B[i] == 1){
            (*C)[i] = 1;
        }else{
            (*C)[i] = 0;
        }
    }

    return C;
}

SET* Difference(SET A, SET B){
    SET* C = malloc(sizeof(SET));

    for(int i = 0; i < MAX; i++){
        if(A[i] == 1 && B[i] != 1){
            (*C)[i] = 1;
        } else{
            (*C)[i] = 0;
        }
    }

    return C;
}