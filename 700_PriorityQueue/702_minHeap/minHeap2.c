#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct{
    int heap[MAX];
    int lastIdx;
}minheap;

void makeNull(minheap* mh);
void insert(minheap* mh, int data);
int deleteMin(minheap* mh);
int getMin(minheap *mh);
void heapifyDown(minheap* mh, int root);
void heapsort(minheap *mh, int arr[], int size);
void printHeap(minheap *mh);
void printTreeRecursive(minheap *mh, int index, int level);
void printHeapTree(minheap *mh);

int main(){
    minheap myHeap;
    makeNull(&myHeap);

    // Test 1: Manual Insertion
    printf("--- Test 1: Manual Insertions ---\n");
    insert(&myHeap, 15);
    insert(&myHeap, 3);
    insert(&myHeap, 8);
    insert(&myHeap, 1);  
    insert(&myHeap, 20);
    insert(&myHeap, 9); // Added more nodes for better visualization
    insert(&myHeap, 12);
    
    printf("\n[Flat Array View]: ");
    printHeap(&myHeap); 

    printf("\n[Tree View (Sideways)]:\n");
    printf("(Rotate head left to see the pyramid)\n");
    printHeapTree(&myHeap);

    printf("\nExtracted Min: %d\n", deleteMin(&myHeap)); 
    
    printf("\n[Tree View after Extraction]:\n");
    printHeapTree(&myHeap);

    // Test 2: Heapsort
    printf("\n--- Test 2: Heapsort Function ---\n");
    // Note: Heapsort will overwrite the existing heap content
    int unsortedData[] = {50, 10, 30, 5, 20, 80, 1};
    int size = sizeof(unsortedData) / sizeof(unsortedData[0]);

    printf("Input Array: ");
    for(int i=0; i<size; i++) printf("%d ", unsortedData[i]);
    printf("\n");

    heapsort(&myHeap, unsortedData, size);

    printf("Sorted Result: ");
    printHeap(&myHeap); 
    // Note: Since this uses MinHeap + Append-to-End, the order is DESCENDING.
    
    return 0;
}

void makeNull(minheap* mh){
    mh->lastIdx = -1;
}

void insert(minheap* mh, int data){
    if(mh->lastIdx < MAX){
        int child = ++mh->lastIdx;
        int parent = (child-1) / 2;

        while(child > 0 && data < mh->heap[parent]){
            mh->heap[child] = mh->heap[parent];
            child = parent;
            parent = (child - 1) / 2;
        }

        mh->heap[child] = data;
    } else {
        printf("Queue is full.\n");
        return;
    }
}

int deleteMin(minheap* mh){
    if(mh->lastIdx != -1){
        int min = mh->heap[0];
        mh->heap[0] = mh->heap[mh->lastIdx--];
        
        if(mh->lastIdx >= 0){
            heapifyDown(mh, 0);
        }

        return min;
    } else {
        printf("Queue is empty.\n");
        return -1;
    }
}

int getMin(minheap *mh){
    if(mh->lastIdx != -1){
        return mh->heap[0];
    }
}

void heapifyDown(minheap* mh, int root){
    int LC = (root * 2) + 1;
    int RC = LC + 1;
    int swap = root;

    if(LC <= mh->lastIdx && mh->heap[swap] > mh->heap[LC]){swap = LC;}
    if(RC <= mh->lastIdx && mh->heap[swap] > mh->heap[RC]){swap = RC;}

    if(swap != root){
        int temp = mh->heap[swap];
        mh->heap[swap] = mh->heap[root];
        mh->heap[root] = temp;
        heapifyDown(mh, swap);
    }
}

void heapsort(minheap *mh, int arr[], int size){
    if(size < MAX && mh->lastIdx < MAX){
        for(int i = 0; i < size; i++){
            mh->heap[i] = arr[i];
        }
        mh->lastIdx = size-1;

        int root = (mh->lastIdx - 1) / 2;
        while(root >= 0){
            heapifyDown(mh, root);
            root--;
        }

        int n = mh->lastIdx;
        for(int i = 0; i <= n; i++){
            int min = deleteMin(mh);
            if(min == -1) break;
            mh->heap[mh->lastIdx + 1] = min;
        }
        mh->lastIdx = n;
    } else {
        printf("Its too big! It wont fit!");
        return;
    }
}

void printHeap(minheap *mh){
    printf("[ ");
    for(int i = 0; i <= mh->lastIdx; i++){
        printf("%d ", mh->heap[i]);
    }
    printf("]\n");
}

void printTreeRecursive(minheap *mh, int index, int level) {
    if (index > mh->lastIdx) {
        return;
    }

    printTreeRecursive(mh, (index * 2) + 2, level + 1);

    printf("\n");
    for (int i = 0; i < level; i++) {
        printf("\t");
    }
    printf("%d", mh->heap[index]);

    printTreeRecursive(mh, (index * 2) + 1, level + 1);
}

void printHeapTree(minheap *mh) {
    if (mh->lastIdx == -1) {
        printf("Empty Heap\n");
    } else {
        printTreeRecursive(mh, 0, 0);
        printf("\n");
    }
}