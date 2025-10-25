#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 10
#define EMPTY -1
#define FULL 1
#define DELETED 0

typedef struct{
    int data;
    int status;
    int link;
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
    for(int i = 0; i < MAX; i++){
        D->table[i].status = EMPTY;
        D->table[i].link = -1;
    }

    D->avail = MAX;

    for(int i = MAX; i < MAX*2; i++){
        D->table[i].link = i + 1;
    }
}

void insert(Dictionary* D, int data){
    int idx = hash(data);

    int* trav; 
    for(trav = &idx; D->table[*trav].link != -1; trav = &(D->table[*trav].link));

    if(D->table[*trav].status == EMPTY){
        D->table[*trav].data = data;
        D->table[*trav].status = FULL;
    } else {
        D->table[*trav].link = D->avail;
        D->table[D->avail].data = data;
        D->table[D->avail].status = FULL;
        D->table[D->avail].link = -1;
        D->avail = D->table[D->avail].link;
    }
}

void delete(Dictionary* D, int data){
    int idx = hash(data);

    int* trav; 
    for(trav = &idx; D->table[*trav].link != -1; trav = &(D->table[*trav].link));

    
}

bool member(Dictionary* D, int data){

}

void print(Dictionary* D){

}

void populateDict(Dictionary* D){

}