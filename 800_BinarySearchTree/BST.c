#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <string.h>

// Define a constant for the width of each level
#define LEVEL_WIDTH 8

typedef struct node{
    int data;
    struct node* LC;
    struct node* RC;
} ctype, *BST;

// Function Prototypes
void insert(BST* T, int data);
void delete(BST* T, int data);
void makeNull(BST* T);
void printTree(const BST T);
BST* min(BST* T);

// Visualization Functions
// New signature includes a string for the vertical path lines
void visualizeTreeHelper(const BST T, const char* prefix, bool isLeft); 
void visualizeTree(const BST* T);


// --- CORE BST OPERATIONS (Unchanged) ---

void printTree(const BST T) {
    if (T != NULL) {
        printTree(T->LC);
        printf("%d ", T->data);
        printTree(T->RC);
    }
}

void makeNull(BST* T) {
    if (*T != NULL) {
        makeNull(&(*T)->LC);
        makeNull(&(*T)->RC);
        free(*T);
        *T = NULL;
    }
}

void insert(BST* T, int data){
    BST* trav = T;
    while(*trav != NULL){
        if((*trav)->data == data){
            return;
        } else if((*trav)->data < data){
            trav = &(*trav)->RC;
        } else {
            trav = &(*trav)->LC;
        }
    }
    
    BST newNode = malloc(sizeof(ctype));
    if (newNode == NULL) {
        perror("Failed to allocate memory for new node");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->LC = NULL;
    newNode->RC = NULL;
    *trav = newNode;
}

BST* min(BST* T){
    BST* trav;
    for(trav = T; (*trav)->LC != NULL; trav = &(*trav)->LC);
    return trav;
}

void delete(BST* T, int target){
    BST* trav = T;
    if(*trav == NULL){
        printf("Tree is empty! Cannot delete %d.\n", target);
        return;
    } 

    for(;*trav != NULL && (*trav)->data != target;
        trav = ((*trav)->data < target) ? &(*trav)->RC : &(*trav)->LC);
    
    if(*trav == NULL){
        printf("Element %d does not exist! Cannot delete.\n", target);
        return;
    } 

    if((*trav)->LC != NULL && (*trav)->RC != NULL){
        BST* successor = min(&(*trav)->RC);
        (*trav)->data = (*successor)->data;
        trav = successor; 
    } 
    
    BST temp = *trav;
    
    if((*trav)->LC == NULL){
        *trav = (*trav)->RC;
    } else {
        *trav = (*trav)->LC;
    }
    
    free(temp);
}


// --- ENHANCED VISUALIZATION FUNCTIONS ---

/**
 * @brief Prints the tree structure rotated 90 degrees with clear lines.
 * @param T The current node.
 * @param prefix A string representing the vertical path from the root.
 * @param isLeft True if the current node is a left child, false if it's a right child.
 */
void visualizeTreeHelper(const BST T, const char* prefix, bool isLeft) {
    if (T == NULL)
        return;
    
    // Calculate the length of the prefix string
    size_t prefix_len = prefix ? strlen(prefix) : 0;
    
    // Create the string for the next level's prefix
    // The buffer size must accommodate the current prefix + LEVEL_WIDTH + NULL terminator
    char next_prefix[prefix_len + LEVEL_WIDTH + 1];

    // 1. Process Right Child (printed 'up')
    // Update the prefix path: 
    // - If we came from a Left branch, the path continues with a '|'.
    // - If we came from a Right branch, the path is padded with spaces.
    // - If this is the root, the path starts empty.
    sprintf(next_prefix, "%s%s", prefix, isLeft ? "|       " : "        ");
    visualizeTreeHelper(T->RC, next_prefix, false);

    // 2. Print Current Node
    printf("%s", prefix); // Print the vertical path up to the current level
    if (prefix_len > 0) {
        printf("%s%s %d\n", 
               isLeft ? "`---" : "+---", 
               isLeft ? "" : (T->RC != NULL ? "" : ""), 
               T->data);
    } else {
        // Root Node
        printf("R--- %d\n", T->data);
    }

    // 3. Process Left Child (printed 'down')
    // Update the prefix path:
    // - If we came from a Right branch, the path continues with a '|'.
    // - If we came from a Left branch, the path is padded with spaces.
    // - If this is the root, the path starts empty.
    sprintf(next_prefix, "%s%s", prefix, isLeft ? "        " : "|       ");
    visualizeTreeHelper(T->LC, next_prefix, true);
}

/**
 * @brief Public function to display the tree structure.
 * Root is on the left. Right child is 'up', Left child is 'down'.
 */
void visualizeTree(const BST* T) {
    if (*T == NULL) {
        printf("(Empty Tree)\n");
        return;
    }
    // Call the helper: T, empty prefix, not technically a child (false)
    visualizeTreeHelper(*T, "", false); 
}


// --- DRIVER PROGRAM (Updated) ---

int main(){
    BST tree = NULL;
    printf("--- BST Driver Program ---\n\n");

    printf("1. INITIAL INSERTIONS\n");
    printf("Inserting: 50, 30, 70, 20, 40, 60, 80, 35, 45, 75, 85\n");
    insert(&tree, 50);
    insert(&tree, 30);
    insert(&tree, 70);
    insert(&tree, 20);
    insert(&tree, 40);
    insert(&tree, 60);
    insert(&tree, 80);
    insert(&tree, 35);
    insert(&tree, 45);
    insert(&tree, 75);
    insert(&tree, 85);
    
    printf("In-order Traversal: ");
    printTree(tree);
    printf("\n");

    printf("\nTree Structure (R = Root):\n");
    visualizeTree(&tree);
    printf("----------------------------------------------------------\n\n");

    printf("3. TESTING DELETION CASES\n");

    // Case 1: Delete a leaf node (20)
    printf("Case 1: Deleting a Leaf Node (20)\n");
    delete(&tree, 20);
    printf("Tree Structure:\n");
    visualizeTree(&tree);
    printf("----------------------------------------------------------\n\n");

    // Case 2a: Delete node with one child (left) - (40) becomes 35
    printf("Case 2a: Deleting Node with One right Child (30)\n");
    delete(&tree, 30);
    printf("Tree Structure:\n");
    visualizeTree(&tree);
    printf("----------------------------------------------------------\n\n");
    
    // Case 3a: Delete node with two children - (30). Successor is 35.
    printf("Case 3a: Deleting Node with Two Children (70). Successor is 75.\n");
    delete(&tree, 70);
    printf("Tree Structure:\n");
    visualizeTree(&tree);
    printf("----------------------------------------------------------\n\n");
    
    // Case 3b: Delete Root (50). Successor is 60.
    printf("Case 3b: Deleting Root Node with Two Children (50). Successor is 60.\n");
    delete(&tree, 50);
    printf("Tree Structure:\n");
    visualizeTree(&tree);
    printf("----------------------------------------------------------\n\n");

    // Case 3b: Delete Root (50). Successor is 60.
    printf("Case 3c: inserting 20\n");
    insert(&tree, 20);
    printf("Tree Structure:\n");
    visualizeTree(&tree);
    printf("----------------------------------------------------------\n\n");

    // Case 3b: Delete Root (50). Successor is 60.
    printf("Case 3d: Delete 35\n");
    delete(&tree, 35);
    printf("Tree Structure:\n");
    visualizeTree(&tree);
    printf("----------------------------------------------------------\n\n");

    printf("4. TESTING MAKE NULL\n");
    makeNull(&tree);
    printf("Tree after makeNull:\n");
    visualizeTree(&tree);
    printf("\n");

    return 0;
}