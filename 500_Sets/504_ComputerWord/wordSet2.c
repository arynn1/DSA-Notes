#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 16
#define MAX_ELEM (MAX_SIZE - 1)


typedef unsigned short SET;

void initSet(SET* S);
void insertToSet(SET *S, int data);
void deleteFromSet(SET *S, int data);
bool member(SET S, int data);
void populateSet(SET *S);
void printSet(SET S);
SET Union(SET A, SET B);
SET Intersection(SET A, SET B);
SET Difference(SET A, SET B);

int main(){
    SET setA, setB, setC;
    
    SET setD = 70;
    printSet(setD);

    printf("--- Computer Word Set Driver ---\n");
    
    initSet(&setA);
    initSet(&setB);
    
    printf("\nInitializing sets A and B to empty.\n");

    printf("\n*** Populating Set A ***\n");
    populateSet(&setA);
    
    printf("\n*** Populating Set B ***\n");
    populateSet(&setB);

    printf("\n================================================\n");
    printf("Final Set A: ");
    printSet(setA);
    printf("Final Set B: ");
    printSet(setB);
    printf("================================================\n");

    
    setC = Union(setA, setB);
    printf("UNION (A | B) Result: ");
    printSet(setC);

    setC = Intersection(setA, setB);
    printf("INTERSECTION (A & B) Result: ");
    printSet(setC);

    setC = Difference(setA, setB);
    printf("DIFFERENCE (A & ~B) Result: ");
    printSet(setC);
    
    if (setA != 0 || setB != 0) {
        printf("\n*** Testing Insert Operation ***\n");
        printf("Is element 5 in set A?\n");
        if(!member(setA, 5)){
            printf("5 is not an element of set A.\n");
            printf("Inserting element 5 into Set A.\n");
            insertToSet(&setA, 5);
            printf("Set A after insert: ");
            printSet(setA);
        } else {
            printf("5 is an element of set A.\n");
        }

        printf("\n*** Testing Delete Operation ***\n");
        printf("Is element 7 in set B?\n");
        if(member(setB, 7)){
            printf("7 is an element of set B.\n");
            printf("Deleting element 7 from Set B.\n");
            deleteFromSet(&setB, 7);
            printf("Set B after delete: ");
            printSet(setB);
        } else {
            printf("7 is not an element of set B.\n");
        }
    }

    return 0;
}

void initSet(SET* S){
    *S = '\0';
}

void insertToSet(SET *S, int data){
    unsigned int mask = 1 << data;
    *S = (*S) | mask;
}

void deleteFromSet(SET *S, int data){
    unsigned int mask = 1 << data;
    *S = (*S) & (~mask);
}

bool member(SET S, int data){
    unsigned int mask = 1 << data;
    return (S & mask) > 0;
}

void populateSet(SET *S){
    int size;
    while(true){
        printf("Enter number of elements (1-%d): ", MAX_SIZE);
        if(scanf(" %d", &size) == -1 || size < 1 || size > MAX_SIZE){
            printf("Invalid size, try again.\n");
        } else {
            break;
        }
    }

    int data; int i = 0;
    while(i < size){
        printf("Element [%d]: ", i+1);
        if(scanf(" %d", &data) == -1 || data < 0 || data > MAX_ELEM){
            printf("Invalid input (0-%d), try again.\n", MAX_ELEM);
        } else {
            insertToSet(S, data);
            i++;
        }
    }

}

void printSet(SET S){
    unsigned int i, curr;
    printf("[ ");
    for(i = 1 << (sizeof(SET) * 8) - 1, curr = MAX_ELEM; i != 0; i >>= 1, curr--){
        if((S & i) != 0){
            printf("%u, ", curr);
        }
    }
    printf("\b\b]\n");
}

SET Union(SET A, SET B){
    return A | B;
}

SET Intersection(SET A, SET B){
    return A & B;
}

SET Difference(SET A, SET B){
    return A & (~B);
}