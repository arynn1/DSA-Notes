#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 10

typedef enum{
    FULL,
    EMPTY,
}Status;

typedef struct{
    int data;
    Status status;
}nodeType;

typedef struct{
    nodeType table[MAX*2];
    int avail;
}Dictionary;

int hash(int data);
void initDict(Dictionary* D);
void insert(Dictionary* D, int data);
void delete(Dictionary* D, int data);
bool member(Dictionary* D, int data);
void print(Dictionary* D);
void populateDict(Dictionary* D);

int main(){
    Dictionary A;
    initDict(&A);
    int choice, data;
    bool running = true;

    printf("Welcome to the Linear Hashing Dictionary Test Driver!\n");

    while (running) {
        printf("\n--- Dictionary Menu (Table Size: %d) ---\n", MAX);
        printf("[1] Populate Dictionary (Interactive Initial Input)\n");
        printf("[2] Insert Element\n");
        printf("[3] Delete Element\n");
        printf("[4] Check Membership (Member)\n");
        printf("[5] Print Dictionary\n");
        printf("[0] Exit\n");
        printf("Enter choice: ");

        if (scanf(" %d", &choice) != 1) {
            printf("\n--- Invalid input. Please enter a number. ---\n");
            while (getchar() != '\n'); 
            continue;
        }

        switch (choice) {
            case 1:
                populateDict(&A);
                break;
            case 2:
                printf("Enter element to insert: ");
                if (scanf(" %d", &data) == 1) {
                    insert(&A, data);
                    printf("-> Inserted %d (Hash Index: %d).\n", data, hash(data));
                }
                break;
            case 3:
                printf("Enter element to delete: ");
                if (scanf(" %d", &data) == 1) {
                    printf("-> Checking for %d...\n", data);
                    if (member(&A, data)) {
                        delete(&A, data);
                        printf("-> Deleted %d.\n", data);
                    } else {
                        printf("-> %d is not in the dictionary. Nothing deleted.\n", data);
                    }
                }
                break;
            case 4:
                printf("Enter element to check: ");
                if (scanf(" %d", &data) == 1) {
                    if (member(&A, data)) {
                        printf("-> %d IS a member of the dictionary.\n", data);
                    } else {
                        printf("-> %d IS NOT a member of the dictionary.\n", data);
                    }
                }
                break;
            case 5:
                printf("\n--- CURRENT DICTIONARY STATE ---\n");
                print(&A);
                printf("------------------------------\n");
                break;
            case 0:
                running = false;
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 0 and 5.\n");
        }
    }
    return 0;
}

int hash(int data){
    return data % MAX;
}

void initDict(Dictionary* D){
    for(int i = 0; i < MAX*2; i++){
        D->table[i].status = EMPTY;
    }
    D->avail = MAX;
}

void insert(Dictionary* D, int data){
    int idx = hash(data);
    if(D->table[idx].status == FULL){
        if(D->table[idx].data != data){
            int i;
            for(i = D->avail; i < MAX*2 && D->table[i].data != data; i++);  
            if(i < MAX*2){
                for(int j = D->avail; j < MAX*2; j++){
                    if(D->table[j].status == EMPTY){
                        D->table[j].data = data;
                        D->table[j].status = FULL;
                        break;
                    } else {
                        printf("Dictionary is Full.\n");
                    }
                }
            }
        } else {
            printf("Element %d is in the Dictionary.\n", data);
        }
    } else {
        D->table[idx].data = data;
        D->table[idx].status = FULL;
    }
}

void delete(Dictionary* D, int data){
    int idx = hash(data);
    if(D->table[idx].status == FULL && D->table[idx].data == data){
        int i;
        for(i = D->avail; i < MAX*2 && D->table[i].data != data; i++);  
        if(i < MAX*2){
            D->table[i].status = EMPTY;
        } else {
            printf("Element %d is not in the Dictionary.\n", data);
        }
    } else {
        D->table[idx].status = EMPTY;
    }
}

bool member(Dictionary* D, int data){
    int idx = hash(data);
    
}

void print(Dictionary* D){
    
}

void populateDict(Dictionary* D){
    
}