#include<stdlib.h>
#include<stdio.h>
#include "queue.h"

void initQueue(ready_queue_t *q){
	q->front = NULL;
	q->rear = NULL;
	q->size = 0;
	
	pthread_mutex_init(&q->mutex, NULL);
	pthread_cond_init(&q->not_empty, NULL);
}
	
void insertQueue(ready_queue_t *q, pcb_t proceso){
	nodo_t *nuevo_nodo = (nodo_t*) malloc(sizeof(nodo_t));
	nuevo_nodo->proceso = proceso;
	nuevo_nodo->siguiente = NULL;
	pthread_mutex_lock(&q->mutex);
	
	if (q->front == NULL){
		q->front = nuevo_nodo;
		q->rear = nuevo_nodo;
	} else {
		q->rear->siguiente = nuevo_nodo;
		q->rear = nuevo_nodo;
	}
	
	q->size++;
	pthread_mutex_unlock(&q->mutex);
	
	pthread_cond_signal(&q->not_empty);
}

pcb_t removeQueue(ready_queue_t *q){
	nodo_t *temp = q->front;
	pcb_t proceso = temp->proceso;
	q->front = q->front->siguiente;
	if(q->front == NULL){
		q->rear = NULL;
	}
	free(temp);
	q->size--;
	return proceso;
}
	
int isQueueEmpty(ready_queue_t *q) {
	return (q->front == NULL);
}
