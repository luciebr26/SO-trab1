// C Program to demonstrate how to Implement a queue
#include "queue.h"

// Function to initialize the queue
void initializeQueue(Queue *q)
{
    q->front = 0;
    q->rear = 0;
}

// Function to check if the queue is empty
bool isEmpty(Queue *q)
{
    return (q->front == q->rear);
}

// Function to check if the queue is full
bool isFull(Queue *q)
{
    return (q->rear + 1) % MAX_SIZE == q->front;
}

// Function to add an element to the queue (Enqueue
// operation)
void enqueue(Queue *q, int value)
{
    if (isFull(q))
    {
        printf("Queue is full\n");
        return;
    }
    q->items[q->rear] = value;
    q->rear = (q->rear + 1) % MAX_SIZE;
}

// Function to remove an element from the queue (Dequeue
// operation)
int dequeue(Queue *q)
{
    if (isEmpty(q))
    {
        printf("Queue is empty\n");
        return -1;
    }
    int value = q->items[q->front];
    q->front = (q->front + 1) % MAX_SIZE;

    return value;
}

// Function to get the element at the front of the queue
// (Peek operation)
int peek(Queue *q)
{
    if (isEmpty(q))
    {
        printf("Queue is empty\n");
        return -1; // return some default value or handle
                   // error differently
    }
    return q->items[q->front];
}

// Function to print the current queue
void printQueue(Queue *q)
{
    if (isEmpty(q))
    {
        printf("Queue is empty\n");
        return;
    }

    printf("Current Queue: ");
    for (int i = q->front; i < q->rear; i++)
    {
        printf("%d ", q->items[i]);
    }
    printf("\n");
}
