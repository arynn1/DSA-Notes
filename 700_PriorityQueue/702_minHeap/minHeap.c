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
void heapifyUp(minheap* mh, int child);
void heapsort(minheap *mh);

int main(){
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
        
        while(i > 0 && mh->heap[parent] < data){
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
    int min, i, j, LC, RC, temp;
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
        heapify(mh, swap);
    }
}

void heapifyUp(minheap* mh, int child){
 
}

void heapsort(minheap *mh){

}
