#include<stdio.h>
#include <pthread.h>
#include<stdlib.h>
#include "metrics.h"

int procesos_terminados = 0;
double total_retorno = 0;
double total_espera = 0;
pthread_mutex_t metricas_mutex = PTHREAD_MUTEX_INITIALIZER;

void registrar_finalizacion(pcb_t proceso) {
	
	double retorno = proceso.burst_time + rand() % 3;
	double espera = retorno - proceso.burst_time;
	pthread_mutex_lock(&metricas_mutex);
	procesos_terminados++;
	total_retorno += retorno;
	total_espera += espera;
	pthread_mutex_unlock(&metricas_mutex);
}

void mostrar_reporte(void){
	if(procesos_terminados > 0) {
		double promedio_retorno = (total_retorno/procesos_terminados);
		double promedio_espera = (total_espera/procesos_terminados);
		printf("El tiempo promedio de procesos terminados es de: %.2f\n", promedio_retorno);
		printf("El tiempo promedio de procesos en espera es de: %.2f\n", promedio_espera);
	} else {
		printf("No se finalizo ningun proceso.");
	}
}
