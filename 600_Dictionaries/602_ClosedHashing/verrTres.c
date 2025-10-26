#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 10

typedef enum{
    EMPTY,
    FULL
}Status;

typedef struct{
    int data;
    Status status;
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

    int i;
    for(i = MAX; i < (MAX*2 - 1); i++){                                                                                                                                    
        D->table[i].status = EMPTY;
        D->table[i].link = i + 1;
    }
    D->table[i].status = EMPTY;
    D->table[i].link = -1;
}

void insert(Dictionary* D, int data){
    int idx = hash(data);

    int* trav; 
    for(trav = &idx; D->table[*trav].link != -1 && D->table[*trav].data != data; trav = &(D->table[*trav].link));

    if(D->table[*trav].data != data){
        if(D->table[*trav].status == EMPTY){
            D->table[*trav].data = data;
            D->table[*trav].status = FULL;
        } else {
            int temp = D->avail;
            D->table[*trav].link = D->avail;
            D->avail = D->table[temp].link;
            D->table[temp].link = -1;
            D->table[temp].data = data;
            D->table[temp].status = FULL;
        }
    }
}

void delete(Dictionary* D, int data){
    int idx = hash(data);

    int* trav; 
    for(trav = &idx; D->table[*trav].link != -1 && D->table[*trav].data != data; trav = &(D->table[*trav].link));

    if(D->table[*trav].data == data){
        int temp;
        if(*trav != idx){
            temp = *trav;
            *trav = D->table[temp].link;
            D->table[temp].status = EMPTY;
            D->table[temp].link = D->avail;
            D->avail = temp;
        } else {
            temp = D->table[*trav].link;
            D->table[*trav].data = D->table[temp].data;
            D->table[*trav].link = D->table[temp].link;
            D->table[temp].link = D->avail;
            D->table[temp].status = EMPTY;
            D->avail = temp;
        } 
    }
}

bool member(Dictionary* D, int data){
    int idx = hash(data);

    int trav;
    for(trav = idx; D->table[trav].link != -1 && D->table[trav].data != data; trav = D->table[trav].link);
    return (D->table[trav].data == data && D->table[trav].status == FULL) ? true : false;
}

void print(Dictionary* D){
    printf("Hash:\n");
    for(int i = 0; i < MAX; i++){
        printf("[%d]: ", i);
        for(int j = i; j != -1; j = D->table[j].link){
            if(D->table[j].status == FULL){
                printf("%d ", D->table[j].data);
            } else {
                printf("<empty> ");
            }
        }
        printf("\n");
    }
}

void populateDict(Dictionary* D){
    int size;
    while(true){
        printf("Enter Number of elements (max 20): ");
        if(scanf(" %d", &size) == -1 || size < 0 || size > MAX*2){
            printf("Invalid input. try again.\n");
        } else {
            break;
        }
    }

    int data;
    for(int i = 0; i < size; i++){
        printf("Enter element [%d]: ", i);
        if(scanf(" %d", &data) != -1 && data > -1){
            insert(D, data);
        }
    }
}