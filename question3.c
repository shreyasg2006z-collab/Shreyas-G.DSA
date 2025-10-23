#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Node structure
typedef struct Node {
    char data;
    int freq;
    struct Node *left, *right;
} Node;

// Queue for level order insertion/traversal
typedef struct Queue {
    Node* arr[MAX];
    int front, rear;
} Queue;

// Initialize queue
void initQueue(Queue *q) {
    q->front = q->rear = -1;
}

int isEmpty(Queue *q) {
    return q->front == -1;
}

void enqueue(Queue *q, Node *node) {
    if (q->rear == MAX - 1) return;
    if (q->front == -1) q->front = 0;
    q->arr[++q->rear] = node;
}

Node* dequeue(Queue *q) {
    if (isEmpty(q)) return NULL;
    Node* temp = q->arr[q->front];
    if (q->front == q->rear)
        q->front = q->rear = -1;
    else
        q->front++;
    return temp;
}

// Create a new node
Node* createNode(char ch) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = ch;
    newNode->freq = 1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Search for existing character in tree (level order)
Node* search(Node *root, char ch) {
    if (!root) return NULL;
    Queue q;
    initQueue(&q);
    enqueue(&q, root);

    while (!isEmpty(&q)) {
        Node* temp = dequeue(&q);
        if (temp->data == ch)
            return temp;
        if (temp->left) enqueue(&q, temp->left);
        if (temp->right) enqueue(&q, temp->right);
    }
    return NULL;
}

// Insert new character level-wise
void insert(Node **root, char ch) {
    if (*root == NULL) {
        *root = createNode(ch);
        return;
    }

    // Check if already exists
    Node *found = search(*root, ch);
    if (found) {
        found->freq++;
        return;
    }

    Queue q;
    initQueue(&q);
    enqueue(&q, *root);

    while (!isEmpty(&q)) {
        Node *temp = dequeue(&q);
        if (temp->left == NULL) {
            temp->left = createNode(ch);
            break;
        } else {
            enqueue(&q, temp->left);
        }

        if (temp->right == NULL) {
            temp->right = createNode(ch);
            break;
        } else {
            enqueue(&q, temp->right);
        }
    }
}

// Level order traversal to print character and frequency
void levelOrder(Node *root) {
    if (!root) return;
    Queue q;
    initQueue(&q);
    enqueue(&q, root);

    while (!isEmpty(&q)) {
        Node *temp = dequeue(&q);
        printf("(%c,%d) ", temp->data, temp->freq);
        if (temp->left) enqueue(&q, temp->left);
        if (temp->right) enqueue(&q, temp->right);
    }
}

int main() {
    char str[MAX];
    printf("Enter the input string: ");
    scanf("%99s", str);  // prevent overflow

    Node *root = NULL;

    for (int i = 0; i < strlen(str); i++) {
        insert(&root, str[i]);
    }

    printf("Level Order Traversal (char, freq):\n");
    levelOrder(root);
    printf("\n");

    return 0;
}
