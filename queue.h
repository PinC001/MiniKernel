#ifndef QUEUE_H
#define QUEUE_H
#include <pthread.h>
#include "pcb.h"
#define MAX 100

typedef struct nodo {
	pcb_t proceso;
	struct nodo *siguiente;
} nodo_t;

typedef struct {
	nodo_t *front;
	nodo_t *rear;
	int size;
	pthread_mutex_t mutex;
	pthread_cond_t not_empty;

} ready_queue_t;

void initQueue(ready_queue_t*);
void insertQueue(ready_queue_t *q, pcb_t proceso);
pcb_t removeQueue(ready_queue_t *q);
int isQueueEmpty(ready_queue_t *q);


#endif
