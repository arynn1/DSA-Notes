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

void bubbleSort(Array*);
void selectionSort(Array*);
void insertionSort(Array*);
void combSort(Array*);
int* countingSort(Array*);
void shellSort(Array*);
void gnomeSort(Array*);
void printArray(Array);
void bucketSort(Array*);
void insertSorted(int, nodeptr*);
int bucketAssign(int, int);
int getMax(Array);

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
            bubbleSort(&arr);
            break;
        case 2:
            selectionSort(&arr);
            break;
        case 3:
            insertionSort(&arr);
            break;
        case 4: 
            combSort(&arr);
            break;
        case 5:
            arr.elems = countingSort(&arr);
            break;
        case 6: 
            shellSort(&arr);
            break;
        case 7: 
            gnomeSort(&arr);
            break;
        case 8: 
            bucketSort(&arr);
            break;
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

void combSort(Array* arr){
    int temp, gap;
    bool swapped = true; 

    gap = arr->size;

    while(gap > 1 || swapped){

        gap = gap / 1.3;
        if(gap < 1) gap = 1;

        swapped = false;

        for(int j = 0; j < arr->size && gap + j < arr->size; j++){
            if(arr->elems[j] > arr->elems[j+gap]){
                temp = arr->elems[j];
                arr->elems[j] = arr->elems[j+gap];
                arr->elems[j+gap] = temp;

                swapped = true;
            }
        }
    }
}

int* countingSort(Array* arr){
    int max, curr;

    int* result = malloc(arr->size * sizeof(int));

    max = arr->elems[0];
    curr = 1;
    while(curr < arr->size){
        if(arr->elems[curr] > max){
            max = arr->elems[curr];
        }
        curr++;
    }

    int countingLength = max + 1;
    int* countingArr = calloc(countingLength, sizeof(int));

    for(int i = 0; i < arr->size; i++){
        countingArr[arr->elems[i]]++;
    }

    int count = 0;
    for(int i = 0; i < countingLength; i++){
        countingArr[i] += count;
        count = countingArr[i];
    }

    for(int i = arr->size - 1; i >= 0; i--){
        countingArr[arr->elems[i]]--;
        result[countingArr[arr->elems[i]]] = arr->elems[i];
    }

    free(countingArr);
    return result;
}

void shellSort(Array* arr){
    int temp, gap, i, j;
    for(gap = arr->size / 2; gap > 0; gap = gap / 2){
        for(i = gap; i < arr->size; i++){
            temp = arr->elems[i];
            for(j = i; j >= gap && arr->elems[j - gap] > temp; j = j - gap){
                arr->elems[j] = arr->elems[j - gap];
            }
            arr->elems[j] = temp;
        }
    }
}

void gnomeSort(Array* arr){
    int temp, pos = 0;
    while(pos < arr->size){
        if(pos == 0 || arr->elems[pos] > arr->elems[pos - 1]){
            pos++;
        } else {
            temp = arr->elems[pos];
            arr->elems[pos] = arr->elems[pos - 1];
            arr->elems[pos - 1] = temp;
            pos--;
        }
    }
}

void bucketSort(Array* arr){
    Dictionary buckets;

    for(int i = 0; i < bucketSize; i++) buckets[i] = NULL;

    int max = getMax(*arr);
    if(max == 0) return;

    for(int i = 0; i < arr->size; i++){
        insertSorted(arr->elems[i], &(buckets[bucketAssign(arr->elems[i], max)]));
    }

    int currIdx = 0;
    for(int i = 0; i < 10; i++){
        nodeptr temp;
        while(buckets[i] != NULL){
            arr->elems[currIdx++] = buckets[i]->data;
            
            temp = buckets[i];
            buckets[i] = buckets[i]->link;
            free(temp); 
        }
    }
}

void insertSorted(int num, nodeptr* head){
    nodeptr* trav;
    for(trav = head; (*trav) != NULL && (*trav)->data <= num; trav = &(*trav)->link);
    
    nodeptr newNode = malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    newNode->data = num;
    newNode->link = *trav;
    *trav = newNode;
}

int bucketAssign(int num, int max){
    int index = (num * (bucketSize - 1)) / max;
    return index;
}

int getMax(Array arr){
    int max = arr.elems[0];
    for(int i = 1; i < arr.size; i++){
        if(arr.elems[i] > max) max = arr.elems[i];
    }
    return max;
}

void printArray(Array arr){
    printf("[ ");
    for(int i = 0; i < arr.size; i++){
        printf("%d ", arr.elems[i]);
    }
    printf("]");
}

// quick sort
// merge sort
// strand sort
// radix 
// tournament sort