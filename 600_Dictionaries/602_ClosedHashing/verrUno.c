#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 10

typedef enum{
    FULL,
    EMPTY,
    DELETED
}Status;

typedef struct{
    int data;
    Status status;
}nodeType;

typedef nodeType Dictionary[MAX];

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
        (*D)[i].status = EMPTY;
    }
}

void insert(Dictionary* D, int data){
    int idx = hash(data);
    for(int i = idx; i < MAX; i = (i+1) % MAX){
        if((*D)[i].status != FULL && (*D)[i].status != DELETED){
            (*D)[i].data = data;
            (*D)[i].status = FULL;
            break;
        } else if((i+1) % MAX == idx){
            printf("Dictionary is full. Cannot insert %d.\n", data);
            break;
        }
    }
}

void delete(Dictionary* D, int data){
    int idx = hash(data);
    for(int i = idx; i < MAX; i = (i+1) % MAX){
        if((*D)[i].status == FULL && (*D)[i].data == data){
            (*D)[i].status = DELETED;
            break;
        }else if((i+1) % MAX == idx){
            printf("Element is not in Dictionary.\n");
            break;
        }
    }
}

bool member(Dictionary* D, int data){
    int idx = hash(data);
    for(int i = idx; i < MAX; i = (i+1) % MAX){
        if((*D)[i].status == FULL && (*D)[i].data == data){
            return true;
        }
    }
    return false;
}

void print(Dictionary* D){
    for(int i = 0; i < MAX; i++){
        if((*D)[i].status == FULL){
            printf("Index [%d]: %d\n", i, (*D)[i].data);
        } else if((*D)[i].status == DELETED){
            printf("Index [%d]: <deleted>\n", i);
        } else {
            printf("Index [%d]: <empty>\n", i);
        }
    }
}

void populateDict(Dictionary* D){
    int size;
    while(true){
        printf("Enter number of elements to insert (max %d): ", MAX);
        if(scanf(" %d", &size) == -1 || size < 1 || size > MAX){
            printf("Invalid size. Try again.\n");
        }else break;

    }
    int data;
    for(int i = 0; i < size; i++){
        printf("Enter element %d: ", i+1);
        scanf(" %d", &data);
        insert(D, data);
    }
}