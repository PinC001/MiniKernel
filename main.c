#include "sync.h"
#include <unistd.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include "cpu.h"
#include <pthread.h>
#include "pcb.h"
#include "queue.h"
#include "metrics.h"


ready_queue_t ready_queue;
int siguiente_pid = 1;
int generador_vivo = 1;

void* generador_procesos(void *arg){
	int max_procesos = 20;
	int procesos_creados = 0;
	
	while(procesos_creados < max_procesos){
		int tiempo_espera = rand() % 4 + 1;
		usleep(tiempo_espera * 100000);
		
		pcb_t nuevo_proceso;
		nuevo_proceso.pid = siguiente_pid;
		siguiente_pid++;
		nuevo_proceso.burst_time = rand() % 7 + 1;
		nuevo_proceso.remaining_time = nuevo_proceso.burst_time;
		nuevo_proceso.priority = 1;
		nuevo_proceso.arrival_time = rand() % 6;
		nuevo_proceso.state = ESTADO_LISTO;
		
		insertQueue(&ready_queue, nuevo_proceso);
		printf("El proceso PID %d con Burst Time %d fue creado\n", nuevo_proceso.pid, nuevo_proceso.burst_time);
		
		procesos_creados++;
	}
	pthread_mutex_lock(&ready_queue.mutex); 
	generador_vivo = 0;
	
	pthread_cond_broadcast(&ready_queue.not_empty); 
	pthread_mutex_unlock(&ready_queue.mutex);
	
	printf("Se alcanzo el limite de %d procesos. Apagando generador...\n", max_procesos);
	return NULL;
}

int main (int argc, char *argv[]) {
	
	pthread_t hilos_cpu[N_CPUS];
	int cpu_ids[N_CPUS];
	pthread_t hilo_generador;
	srand(time(NULL));
	initQueue(&ready_queue);
	
	pthread_create(&hilo_generador, NULL, generador_procesos, NULL);
	for(int i = 0; i < N_CPUS; i++){
		cpu_ids[i] = i;
		pthread_create(&hilos_cpu[i], NULL, cpu_loop, &cpu_ids[i]);
	}
	pthread_join(hilo_generador, NULL);
	for(int i = 0; i < N_CPUS; i++){
		pthread_join(hilos_cpu[i], NULL);
	}
	mostrar_reporte();
	
	return 0;
}

