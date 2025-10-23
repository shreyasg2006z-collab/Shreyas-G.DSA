#include <stdio.h>
#include <stdlib.h>

// Define structure for a song node
struct Node {
    int songID;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int songID) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->songID = songID;
    newNode->next = NULL;
    return newNode;
}

// Function to print the playlist
void printPlaylist(struct Node* head) {
    while (head != NULL) {
        printf("%d", head->songID);
        if (head->next != NULL)
            printf(" -> ");
        head = head->next;
    }
    printf("\n");
}

// Function to reverse playlist segment from position m to n
struct Node* reversePlaylistSegment(struct Node* head, int m, int n) {
    if (head == NULL || m == n)
        return head;

    struct Node dummy;
    dummy.next = head;
    struct Node* prev = &dummy;

    // Move prev to node before segment starts
    for (int i = 1; i < m; i++) {
        if (prev == NULL) return head;
        prev = prev->next;
    }

    struct Node* start = prev->next;       // start of segment
    struct Node* then = start->next;       // node after start

    // Reverse nodes between m and n
    for (int i = 0; i < n - m; i++) {
        start->next = then->next;
        then->next = prev->next;
        prev->next = then;
        then = start->next;
    }

    return dummy.next;
}

// Only one main() here
int main() {
    // Create sample playlist: 101 -> 102 -> 103 -> 104 -> 105 -> 106 -> 107
    struct Node* head = createNode(101);
    head->next = createNode(102);
    head->next->next = createNode(103);
    head->next->next->next = createNode(104);
    head->next->next->next->next = createNode(105);
    head->next->next->next->next->next = createNode(106);
    head->next->next->next->next->next->next = createNode(107);

    printf("Original playlist:\n");
    printPlaylist(head);

    int m = 2, n = 5;
    head = reversePlaylistSegment(head, m, n);

    printf("\nModified playlist after reversing positions %d to %d:\n", m, n);
    printPlaylist(head);

    return 0;
}