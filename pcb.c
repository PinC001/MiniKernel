#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "pcb.h"
#define MAX 100

	void dormirAleatorio(){
		int tiempo = rand() % 10 + 1;
		sleep(tiempo);
	}

	pcb_t* crearProceso(int pid, int burst_time, int priority, int arrival_time, int state) {
		pcb_t *proceso = (pcb_t*) malloc(sizeof(pcb_t));
		
		proceso->pid = pid;
		proceso->burst_time = rand() % 6 + 1;
		proceso->remaining_time = proceso.burst_time;
		proceso->priority = priority;
		proceso->arrival_time = rand() % 7;
		proceso->state = state;
		
		return proceso;
	}
