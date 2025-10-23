#include <stdio.h>

#define MAX 10

int queue[MAX];
int front = -1, rear = -1;

void addCall(int callID) {
    if (rear == MAX - 1) {
        printf("Queue Overflow! Cannot add call %d\n", callID);
        return;
    }
    if (front == -1)
        front = 0;
    queue[++rear] = callID;
    printf("Call added: %d\n", callID);
}

void removeCall() {
    if (front == -1 || front > rear) {
        printf("Queue Underflow! No calls to remove.\n");
        return;
    }
    printf("Call removed: %d\n", queue[front++]);
}

void displayQueue() {
    if (front == -1 || front > rear) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Current Calls in Queue: ");
    for (int i = front; i <= rear; i++)
        printf("%d ", queue[i]);
    printf("\n");
}

int main() {
    addCall(101);
    addCall(102);
    addCall(103);
    displayQueue();
    removeCall();
    displayQueue();

    return 0;
}
