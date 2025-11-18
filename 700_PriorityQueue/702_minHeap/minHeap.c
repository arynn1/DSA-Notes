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
    int i, temp, parent;

    if(mh->lastIdx < MAX){
        i = ++mh->lastIdx;
        parent = (i-1) / 2;
        
        while(i > 0 && mh->heap[parent] > data){
            mh->heap[i] = mh->heap[parent];
            i = parent;
            parent = (i-1) / 2;
        }

        mh->heap[i] = data;
    } else {
        printf("queue is full.");
    }
}

int deleteMin(minheap* mh){
    int min, i;
    if(mh->lastIdx != -1){
        min = mh->heap[0];
        mh->heap[0] = mh->heap[mh->lastIdx--];

        if(mh->lastIdx >= 0){
            i = 0;
            heapifyDown(mh, i);
        } 
        return min;
    } else {
        printf("queue is empty.");
        return -1;
    }
}

int getMin(minheap *mh){
    if(mh->lastIdx != -1){
        return mh->heap[0];
    } else {
        printf("queue is empty.");
        return -1;
    }
}

void heapifyDown(minheap* mh, int root){
    int LC = (root * 2) + 1;
    int RC = (root * 2) + 2;
    int swap = root;

    if(LC <= mh->lastIdx && mh->heap[LC] < mh->heap[swap]) swap = LC;
    if(RC <= mh->lastIdx && mh->heap[RC] < mh->heap[swap]) swap = RC;
    
    if(swap != root){
        int temp = mh->heap[root];
        mh->heap[root] = mh->heap[swap];
        mh->heap[swap] = temp;
        heapifyDown(mh, swap);
    }
}

void heapsort(minheap *mh, int arr[], int size){
    if(size > MAX){
        printf("Array too large!\n");
        return; 
    }

    if(mh->lastIdx < MAX){
        //Step 1: insert all elements into the heap and turn it into a valid heap
        for(int i = 0; i < size; i++){
        mh->heap[i] = arr[i];
        }
        mh->lastIdx = size - 1;
        
        int root = (mh->lastIdx - 1) / 2;
        while(root >= 0){
            heapifyDown(mh, root);
            root--;
        }
        //Step 2: repeatedly delete minimum element and append to the end of the heap
        int n = mh->lastIdx;
        for(int i = 0; i <= n; i++){
            int min = deleteMin(mh);
            if(min == -1) break;
            mh->heap[mh->lastIdx + 1] = min;
        }
        mh->lastIdx = n;
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