#ifndef QUEUE_H
#define QUEUE_H

#define QUEUE_CAP 128

struct Queue {
	int data[QUEUE_CAP];
	int front;
	int rear;
	int size;
};

void init_queue(struct Queue *queue);
int isFull(struct Queue *queue);
int isEmpty(struct Queue *queue);
void enqueue(struct Queue *queue, int val);
int dequeue(struct Queue *queue);
int peek(struct Queue *queue);
void printQueue(struct Queue *queue);

#endif
