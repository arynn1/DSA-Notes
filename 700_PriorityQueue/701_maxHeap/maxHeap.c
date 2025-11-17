#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct{
    int heap[MAX];
    int lastIdx;
}minheap;

void makeNull(minheap* mh);
void insert(minheap* mh, int data);
void deleteMin(minheap* mh);
void getMin(minheap *mh);
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
    }
}

void deleteMin(minheap* mh){
    int min, i, j, LC, RC, temp;
    if(mh->lastIdx == -1){
        min = mh->heap[0];
        mh->heap[0] = mh->heap[mh->lastIdx--];

        i = 0;
        while((2 * i) + 1 <= mh->lastIdx){
            LC = (2 * i) + 1;
            RC = (2 * i) + 2;
            j = LC;

            if(RC <= mh->lastIdx && mh->heap[RC] < mh->heap[j]){
                j = RC;
            }

            if(mh->heap[i] > mh->heap[j]){
                temp = mh->heap[i];
                mh->heap[i] = mh->heap[j];
                mh->heap[j] = temp;
            } else {
                break;
            }
        }
        return min;
    }
}

void getMin(minheap *mh){
    if(mh->lastIdx != -1){
        return mh->heap[0];
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