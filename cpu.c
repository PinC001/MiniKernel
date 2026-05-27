#include "sync.h"
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include "cpu.h"
#include "queue.h"
#include "metrics.h"


extern ready_queue_t ready_queue;
extern int generador_vivo;

void* cpu_loop(void *arg){
	
	int cpu_id = *(int*)arg;
	printf("La CPU %d fue iniciada\n", cpu_id);
	
	while(1){
		pthread_mutex_lock(&ready_queue.mutex);
		while(isQueueEmpty(&ready_queue) && generador_vivo == 1){
			pthread_cond_wait(&ready_queue.not_empty, &ready_queue.mutex);
		}
		if(isQueueEmpty(&ready_queue) && generador_vivo == 0){
			pthread_mutex_unlock(&ready_queue.mutex);
			break; 
		}
		pcb_t proceso = removeQueue(&ready_queue);
		pthread_mutex_unlock(&ready_queue.mutex);
		proceso.state = ESTADO_EJECUTANDO;
		int tiempo_ejecucion;
		if(proceso.remaining_time < QUANTUM){
			tiempo_ejecucion = proceso.remaining_time;
		} else {
			tiempo_ejecucion = QUANTUM;
		}
		usleep(tiempo_ejecucion * 100000);
		proceso.remaining_time -= tiempo_ejecucion;
		if(proceso.remaining_time == 0){
			proceso.state = ESTADO_FINALIZADO;
			printf("El proceso %d ha finalizado\n", proceso.pid);
			registrar_finalizacion(proceso);
		}
		if (proceso.remaining_time > 0 ) {
			proceso.state = ESTADO_LISTO;
			printf("Al proceso %d se le acabo su tiempo de ejecucion\n", proceso.pid);
			insertQueue(&ready_queue, proceso);
		}
	}
	printf("La CPU %d no encontro mas procesos y el generador fue apagado. Apagando CPU...\n", cpu_id);
	return NULL;
}
