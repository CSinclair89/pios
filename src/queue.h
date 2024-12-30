#ifndef QUEUE_H
#define QUEUE_H

#define QUEUE_CAP 128

struct Queue {
	int data[QUEUE_CAP];
	int front;
	int rear;
	int size;
};

void queueInit(struct Queue *queue);
int queueIsFull(struct Queue *queue);
int queueIsEmpty(struct Queue *queue);
void enqueue(struct Queue *queue, int val);
int dequeue(struct Queue *queue);
int queuePeek(struct Queue *queue);
void queuePrint(struct Queue *queue);

#endif
