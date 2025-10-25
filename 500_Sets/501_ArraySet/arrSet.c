#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct{
    int elems[MAX];
    int size;
}SET;

void insertToSet(SET *S, int data);
void deleteFromSet(SET *S, int data);
void populateSet(SET *S);
void printSet(SET S);
SET Union(SET A, SET B);
SET Intersection(SET A, SET B);
SET Difference(SET A, SET B);

int main(){
    SET A, B;
    A.size = 0;
    B.size = 0;

    populateSet(&A);
    populateSet(&B);

    printf("SET A = ");
    printSet(A);
    printf("SET B = ");
    printSet(B);

    insertToSet(&A, 100);
    insertToSet(&A, 14);
    insertToSet(&B, 200);
    insertToSet(&B, 15);

    printf("SET A = ");
    printSet(A);
    printf("SET B = ");
    printSet(B);

    deleteFromSet(&A, 100);
    deleteFromSet(&A, 14);
    deleteFromSet(&B, 200);
    deleteFromSet(&B, 15);

    printf("SET A = ");
    printSet(A);
    printf("SET B = ");
    printSet(B);

    SET C = Union(A, B);
    SET D = Intersection(A, B);
    SET E = Difference(A, B);

    printf("SET C = ");
    printSet(C);
    printf("SET D = ");
    printSet(D);
    printf("SET E = ");
    printSet(E);

    return 0;
}

void insertToSet(SET *S, int data){
    if(S->size < MAX){
        int i;
        for(i = 0; i < S->size && S->elems[i] != data; i++);
        if(i == S->size){
            S->elems[S->size++] = data;
        }
    }
}

void deleteFromSet(SET *S, int data){
    if(S->size > 0){
        int i;
        for(i = 0; i < S->size && S->elems[i] != data; i++);
        if(i < S->size){
            S->size--;
            if(S->size > 0){
                S->elems[i] = S->elems[S->size];
            }
        }
    }
}

void populateSet(SET *S){
    int size;
    while(1){
        printf("How many elements? ");
        scanf("%d", &size);
        if(size > 0 && size <= MAX){
            break;
        }
        printf("Invalid Value, only input values from 1-10\n");
    }

    int data;
    while(S->size < size){
        printf("Enter element: ");
        scanf(" %d", &data);

        insertToSet(S, data);
    }
    printf("\n");
}

void printSet(SET S){
    printf("[ ");
    for(int i = 0; i < S.size; i++){
        printf("%d", S.elems[i]);
        if(i != S.size-1){
            printf(",");
        }
    }
    printf(" ]\n");
}

SET Union(SET A, SET B){
    SET C = A;
    for(int i = 0; i < B.size; i++){
        insertToSet(&C, B.elems[i]);
    }
    return C;
}

SET Intersection(SET A, SET B){
    SET C;
    C.size = 0;
    for(int i = 0; i < A.size; i++){
        int j;
        for(j = 0; j < B.size && A.elems[i] != B.elems[j]; j++);
        if(j != B.size){
            C.elems[C.size++] = A.elems[i];
        }
    }
    return C;
}

SET Difference(SET A, SET B){
    SET C = A;
    for(int i = 0; i < A.size; i++){
        int j;
        for(j = 0; j < B.size && A.elems[i] != B.elems[j]; j++);
        if(j != B.size){
            deleteFromSet(&C, B.elems[j]);
        }
    }
    return C;
}