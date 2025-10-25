#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* link;
}*SET;

void insertToSet(SET *S, int data);
void deleteFromSet(SET *S, int data);
void populateSet(SET *S);
void printSet(SET S);
SET Union(SET A, SET B);
SET Intersection(SET A, SET B);
SET Difference(SET A, SET B);

int main(){
    SET A = NULL;
    SET B = NULL;

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

    SET U = Union(A, B);
    SET I = Intersection(A, B);
    SET D = Difference(A, B);

    printf("SET U (UNION of A and B)= ");
    printSet(U);
    printf("SET I (INTERSECTION of A and B)= ");
    printSet(I);
    printf("SET D (DIFFERENCE of A and B)= ");
    printSet(D);

    return 0;
}

void insertToSet(SET *S, int data){
    SET* trav;
    for(trav = S; (*trav) != NULL && (*trav)->data != data; trav = &(*trav)->link);
    if(*trav == NULL){
        SET newNode = malloc(sizeof(struct node));
        if(newNode != NULL){
            newNode->data = data;
            newNode->link = NULL;
            *trav = newNode;
        }
    }
}

void deleteFromSet(SET *S, int data){
    if(S != NULL){
        SET* trav;
        for(trav = S; (*trav) != NULL && (*trav)->data != data; trav = &(*trav)->link);
        if(trav != NULL){
            SET temp = (*trav);
            *trav = (*trav)->link;
            free(temp);
        }
    }
}

void populateSet(SET *S){
    int size;
    printf("How many elements? ");
    scanf("%d", &size);

    int data, ret;
    for(int i = 0; i < size; i++){
        printf("Enter element: ");
        scanf(" %d", &data);
        insertToSet(S, data);
    }

    printf("\n");
}

void printSet(SET S){
    printf("[ ");
    for(SET trav = S; trav != NULL; trav = trav->link){
        printf("%d ", trav->data);
    }
    printf(" ]\n");
}

SET Union(SET A, SET B){
    SET C = NULL;

    SET* trav = &C;

    for(SET curr = A; curr != NULL; curr = curr->link){
        SET newNode = malloc(sizeof(struct node));

        if(newNode != NULL){
            newNode->data = curr->data;
            newNode->link = NULL;
            *trav = newNode;
            trav = &(*trav)->link;
        }
    }
    
    for(SET curr = B; curr != NULL; curr = curr->link){
        insertToSet(&C, curr->data);
    }
    
    return C;
}

SET Intersection(SET A, SET B){
    SET C = NULL;

    SET* trav = &C;

    for(SET curr = A; curr != NULL; curr = curr->link){
        SET curr2;
        for(curr2 = B; curr2 != NULL && curr2->data != curr->data; curr2 = curr2->link);
        if(curr2 != NULL){
            SET newNode = malloc(sizeof(struct node));

            if(newNode != NULL){
                newNode->data = curr->data;
                newNode->link = NULL;
                *trav = newNode;
                trav = &(*trav)->link;
            }
        }
    }

    return C;
}

SET Difference(SET A, SET B){
    SET C = NULL;

    SET* trav = &C;

    for(SET curr = A; curr != NULL; curr = curr->link){
        SET curr2;
        for(curr2 = B; curr2 != NULL && curr2->data != curr->data; curr2 = curr2->link);
        if(curr2 == NULL){
            SET newNode = malloc(sizeof(struct node));

            if(newNode != NULL){
                newNode->data = curr->data;
                newNode->link = NULL;
                *trav = newNode;
                trav = &(*trav)->link;
            }   
        }
    }
    
    return C;
}