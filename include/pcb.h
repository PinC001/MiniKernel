#ifndef PCB_H
#define PCB_H

#define ESTADO_LISTO 0
#define ESTADO_EJECUTANDO 1
#define ESTADO_FINALIZADO 3

typedef struct {
	int pid;
	int burst_time;
	int remaining_time;
	int priority;
	int arrival_time;
	int state;
} pcb_t;

#endif
