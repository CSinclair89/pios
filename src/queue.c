#include "queue.h"
#include "rprintf.h"
#include "serial.h"

// initialize queue
void queueInit(struct Queue *queue) {
	queue->front = 0;
	queue->rear = -1;
	queue->size = 0;
}

// check is queue is empty
int queueIsEmpty(struct Queue *queue) {
	if (queue->size == 0) return 1;
	return 0;
}

int queueIsFull(struct Queue *queue) {
	if (queue->size == QUEUE_CAP) return 1;
	return 0;
}

void enqueue(struct Queue *queue, int val) {
	if (queueIsFull(queue) == 1) {
		esp_printf(putc, "Queue is full.\n");
		return;
	}
	queue->rear = (queue->rear + 1) % QUEUE_CAP;
	queue->data[queue->rear] = val;
	queue->size++;
	return;
}

int dequeue(struct Queue *queue) {
	if (queueIsEmpty(queue) == 1) return -1;
	int val = queue->data[queue->front];
	queue->front = (queue->front + 1) % QUEUE_CAP;
	queue->size--;
	return val;
}

int queuePeek(struct Queue *queue) {
	if (queueIsEmpty(queue) == 1) {
		esp_printf(putc, "Queue is empty.\n");
		return -1;
	}
	return queue->data[queue->front];
}

void queuePrint(struct Queue *queue) {
	if (queueIsEmpty(queue) == 1) {
		esp_printf(putc, "Queue is empty.\n");
		return;
	}
	for (int i = 0; i < queue->size; i++) {
		int idx = (queue->front + i) % QUEUE_CAP;
		esp_printf(putc, "%d ", queue->data[idx]);
	}
	esp_printf(putc, "\n");
}
