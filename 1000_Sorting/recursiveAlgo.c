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

int* mergeSort(int*, int);
int* merge(int*, int*, int, int);
void quickSort(int*, int, int);
int partition(int*, int, int, int);
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

    
    printf("Enter element of the array: ");

    for(int i = 0; i < arr.size; i++){
        scanf("%d", &arr.elems[i]);
    }

    int choice;
    printf("--------Which sorting algorithm?--------\n1 - merge sort\n2 - quick sort\n----------------------------------------\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch(choice){
        case 1: 
            arr.elems = mergeSort(arr.elems, arr.size);
            break;
        case 2: 
            quickSort(arr.elems, 0, arr.size - 1);
            break;
        default:
            printf("Invalid choice\n");
    }
    printArray(arr);

    free(arr.elems);
    return 0;
}

int* mergeSort(int* arr, int size){
    int sizeA, sizeB;

    if(size == 1)return arr;

    sizeA = size / 2;
    sizeB = (size % 2 == 0) ? sizeA : sizeA + 1;

    int* arrA = calloc(sizeof(int), sizeA); 
    int* arrB = calloc(sizeof(int), sizeB); 

    int i = 0, j = 0;
    while(i < sizeA){
        arrA[i] = arr[i];
        i++;
    }

    while(i < size){
        arrB[j++] = arr[i++];
    }

    arrA = mergeSort(arrA, sizeA);
    arrB = mergeSort(arrB, sizeB);

    int* result = merge(arrA, arrB, sizeA, sizeB);

    free(arrA);
    free(arrB);

    return result;
}

int* merge(int* arrA, int* arrB, int sizeA, int sizeB){
    int* outputArr = calloc(sizeof(int), sizeA + sizeB);
    
    int a = 0, b = 0, count = 0;
    bool isAFull = false;

    while(a < sizeA && b < sizeB){
        if(arrA[a] <= arrB[b]){
            outputArr[count++] = arrA[a++];
        } else {
            outputArr[count++] = arrB[b++];
        }
    }

    while(a < sizeA){
        outputArr[count++] = arrA[a++];
    }

    while(b < sizeB){
        outputArr[count++] = arrB[b++];
    }
    
    return outputArr;
}

void quickSort(int* arr, int start, int end){
    
    if(start >= end) return;

    int center = start + (end - start) / 2;

    int pivot = start;
    if(arr[start] <= arr[center] && arr[center] <= arr[end]) pivot = center;
    if(arr[start] <= arr[end] && arr[end] <= arr[center]) pivot = end;

    pivot = partition(arr, start, end, pivot);

    quickSort(arr, start, pivot - 1);
    quickSort(arr, pivot + 1, end);
}

int partition(int* arr, int start, int end, int pivot){
    if(start == end && end == pivot) return pivot;

    int temp = arr[end];
    arr[end] = arr[pivot];
    arr[pivot] = temp;
    pivot = end;

    int storeIndex = start;

    for(int i = start; i <= end; i++){
        if(arr[i] < arr[pivot]){
            temp = arr[i];
            arr[i] = arr[storeIndex];
            arr[storeIndex++] = temp;
        }
    }

    temp = arr[pivot];
    arr[pivot] = arr[storeIndex];
    arr[storeIndex] = temp;

    return storeIndex;
}

void printArray(Array arr){
    printf("[ ");
    for(int i = 0; i < arr.size; i++){
        printf("%d ", arr.elems[i]);
    }
    printf("]");
}

// tournament
// heap
// strand
// radix

