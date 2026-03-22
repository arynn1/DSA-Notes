#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#define bucketSize 10

typedef struct Node{
    int data;
    struct Node* link;
} nodetype, *nodeptr;

typedef nodeptr Dictionary[bucketSize];

typedef struct{
    int size;
    int* elems;
} Array;


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
    printf("--------Which sorting algorithm?--------\n1 - bubble sort\n2 - selection sort\n3 - insertion sort\n4 - comb sort\n5 - counting sort\n6 - shell sort\n7 - gnome sort\n8 - bucket sort\n----------------------------------------\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch(choice){
        case 1: 
            // bubbleSort(&arr);
            break;
        default:
            printf("Invalid choice\n");
    }
    printArray(arr);

    free(arr.elems);
    return 0;
}

// merge
// quick
// tournament
// heap 
// strand
// radix

