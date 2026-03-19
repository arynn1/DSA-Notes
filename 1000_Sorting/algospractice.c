#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node{
    int data;
    struct Node* link;
} nodetype, *nodeptr;

typedef struct{
    int size;
    int* elems;
} Array;

void bubbleSort(Array*);
void selectionSort(Array*);
void insertionSort(Array*);
void printArray(Array);

int main(){    
    Array arr;
    printf("Enter size of array: ");
    scanf("%d", &arr.size);

    arr.elems = malloc(arr.size * sizeof(int));
    if(arr.elems == NULL){
        printf("Memory allocation failed.\n");
        return 1;
    }

    for(int i = 0; i < arr.size; i++){
        printf("Enter element [%d] of array: ", i+1);
        scanf("%d", &arr.elems[i]);
    }

    int choice;
    printf("--------Which sorting algorithm?--------\n1 - bubble sort\n2 - selection sort\n3 - insertion sort\n----------------------------------------\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch(choice){
        case 1: 
            bubbleSort(&arr);
            break;
        case 2:
            selectionSort(&arr);
            break;
        case 3:
            insertionSort(&arr);
        default:
            printf("Invalid choice\n");
    }
    printArray(arr);

    free(arr.elems);
    return 0;
}

void bubbleSort(Array* arr){
    int temp;
    for(int i = 0; i < arr->size; i++){
        int max = arr->size - i - 1;
        for(int j = 0; j < max; j++){
            if(arr->elems[j] > arr->elems[j + 1]){
                temp = arr->elems[j];
                arr->elems[j] = arr->elems[j + 1];
                arr->elems[j + 1] = temp;
            }
        }
    }
}

void selectionSort(Array* arr){
    int temp, min;
    for(int i = 0; i < arr->size; i++){
        min = i;
        for(int j = i + 1 ; j < arr->size; j++){
            if(arr->elems[j] < arr->elems[min]){
                min = j;
            }
        }
        temp = arr->elems[i];
        arr->elems[i] = arr->elems[min];
        arr->elems[min] = temp;
    }
}

void insertionSort(Array* arr){
    int temp, j;
    for(int i = 1; i < arr->size; i++){
        temp = arr->elems[i];
        for(j = i; j > 0 && arr->elems[j - 1] > temp; j--){
            arr->elems[j] = arr->elems[j - 1];
        }
        arr->elems[j] = temp;
    }
}

void printArray(Array arr){
    printf("[ ");
    for(int i = 0; i < arr.size; i++){
        printf("%d ", arr.elems[i]);
    }
    printf("]");
}

