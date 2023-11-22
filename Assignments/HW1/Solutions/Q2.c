#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for a node in the linked list
struct Node {
    char data[50];
    struct Node *next;
};

// Function to create a new node
struct Node *createNode(const char *data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    strcpy(newNode->data, data);
    newNode->next = NULL;
    return newNode;
}

// Function to insert a new node at the beginning of the list
void insertAtBeginning(struct Node **head, const char *data) {
    struct Node *newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

// Function to insert a new node at a specific index in the list
void insertAtIndex(struct Node **head, const char *data, int index) {
    if (index == 0) {
        insertAtBeginning(head, data);
        return;
    }

    struct Node *newNode = createNode(data);
    struct Node *current = *head;
    int currentIndex = 0;

    while (current != NULL && currentIndex < index - 1) {
        current = current->next;
        currentIndex++;
    }

    newNode->next = current->next;
    current->next = newNode;
}

void swapNodes(struct Node **head, const char *data1, const char *data2) {
    // If the data values are the same, no need to swap
    if (strcmp(data1, data2) == 0) {
        return;
    }

    // Initialize pointers for the nodes to be swapped and their predecessors
    struct Node *node1 = NULL;
    struct Node *node2 = NULL;
    struct Node *prev1 = NULL;
    struct Node *prev2 = NULL;
    struct Node *temp = *head;

    // Find nodes and their predecessors
    while (temp != NULL) {
        if (strcmp(temp->data, data1) == 0) {
            node1 = temp;
            break;
        }
        prev1 = temp;
        temp = temp->next;
    }

    temp = *head; // Reset temp to the head of the list

    while (temp != NULL) {
        if (strcmp(temp->data, data2) == 0) {
            node2 = temp;
            break;
        }
        prev2 = temp;
        temp = temp->next;
    }


    // If node1 is not the head of the list, update its predecessor's next pointer
    if (prev1 != NULL) {
        prev1->next = node2;
    } else {
        // If node1 is the head, update the head of the list
        *head = node2;
    }

    // If node2 is not the head of the list, update its predecessor's next pointer
    if (prev2 != NULL) {
        prev2->next = node1;
    } else {
        // If node2 is the head, update the head of the list
        *head = node1;
    }

    // Swap next pointers of the nodes
    struct Node *tempNext = node1->next;
    node1->next = node2->next;
    node2->next = tempNext;
}


// Function to delete a node with a given value from the list
void deleteNode(struct Node **head, const char *data) {
    struct Node *temp = *head;
    struct Node *prev = NULL;

    // Find the node to delete and keep track of the previous node
    while (temp != NULL && strcmp(temp->data, data) != 0) {
        prev = temp;
        temp = temp->next;
    }

    // If the node is found, delete it
    if (temp != NULL) {
        if (prev == NULL) {
            *head = temp->next;
        } else {
            prev->next = temp->next;
        }
        free(temp);
    }
}

// Function to display the elements of the list
void displayList(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        printf("%s ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    struct Node *head = NULL;
    int numInstructions;
    int listLength;
    char data[50];
    char data2[50];
    int idx;

    // Input the number of elements in the list from the user
    scanf("%d", &listLength);

    for (int i = 0; i < listLength; i++) {
        scanf("%s", data);
        insertAtIndex(&head, data, i);
    }

    // Input the number of instructions from the user
    scanf("%d", &numInstructions);

    for (int i = 0; i < numInstructions; i++) {
        char choice[10];
        scanf("%s", choice);

        if (strcmp(choice, "add") == 0) {
            scanf("%s", data);
            scanf("%d", &idx);
            insertAtIndex(&head, data, idx);
        } 
        else if (strcmp(choice, "delete") == 0) {
            scanf("%s", data);
            deleteNode(&head, data);
        } 
        else if (strcmp(choice, "swap") == 0) {
            scanf("%s", data);
            scanf("%s", data2);
            swapNodes(&head, data, data2);
        } 
        else {}
    }
    displayList(head);
    return 0;
}
