#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef unsigned char SET;

void initSet(SET*);
void displaySet(SET);
void insert(SET*, int);
bool member(SET, int);
void delete(SET*, int);
SET unionSet(SET, SET);
SET intersectionSet(SET, SET);
SET differenceSet(SET, SET);

int main(){
    SET A, B, U, I, D;
    initSet(&A);
    initSet(&B);
    int arrA[] = {1,4,0,7};
    int arrB[] = {3,5,2,4};
    
    int lengthA = sizeof(arrA) / sizeof(int);
    for(int i = 0; i < lengthA; i++){
        insert(&A, arrA[i]);
    }
    printf("SET A: ");
    displaySet(A);
    
    int lengthB = sizeof(arrB) / sizeof(int);
    for(int i = 0; i < lengthB; i++){
        insert(&B, arrB[i]);
    }
    printf("SET B: ");
    displaySet(B);
    
    printf("\nInserting 2 into SET A...\n");
    insert(&A, 2);
    printf("NEW SET A: ");
    displaySet(A);
    
    printf("\nInserting 6 into SET B...\n");
    insert(&B, 6);
    printf("NEW SET B: ");
    displaySet(B);
    
    printf("\nIs 0 a member of SET A?\n");
    if(member(A, 0)){
        printf("0 is a member of A!\n");
        printf("\nDeleting 0 from SET A...\n");
        delete(&A, 0);
        printf("NEW SET A: ");
        displaySet(A);
    }else{
        printf("0 is not a member of A.");
    }
    
    printf("\nIs 6 a member of SET B?\n");
    if(member(B, 6)){
        printf("6 is a member of B!\n");
        printf("\nDeleting 3 from SET B...\n");
        delete(&B, 3);
        printf("NEW SET B: ");
        displaySet(B);
    }else{
        printf("6 is not a member of B.\n");
    }
    
    U = unionSet(A, B);
    I = intersectionSet(A, B);
    D = differenceSet(A, B);
    printf("\nSET U (union of A and B): ");
    displaySet(U);
    printf("SET I (intersection of A and B): ");
    displaySet(I);
    printf("SET D (difference of A and B): ");
    displaySet(D);
    
    
    return 0;
}

void initSet(SET* s){
    *s = '\0';
}

void displaySet(SET s){
    unsigned int curr, i;
    printf("{");
    for(i = 1 << (sizeof(SET) * 8) - 1, curr = 7; i != 0; i >>= 1, curr--){
        if((s & i) != 0){
            printf("%u, ", curr);
        }
    }
    printf("\b\b}\n");
}

void insert(SET* s, int X){
    unsigned int mask = 1 << X;
    *s = (*s) | mask;
}

bool member(SET s, int X){
    unsigned int mask = 1 << X;
    return (s & mask) > 0;
}

void delete(SET* s, int X){
    unsigned int mask = 1 << X;
    *s = (*s) & (~mask);
}

SET unionSet(SET A, SET B){
    SET C; initSet(&C);
    C = A | B;
    return C;
}

SET intersectionSet(SET A, SET B){
    SET C; initSet(&C);
    C = A & B;
    return C;
}

SET differenceSet(SET A, SET B){
    SET C; initSet(&C);
    C = A & (~B);
    return C;
}