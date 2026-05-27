#ifndef PTHREAD_H
#define PTHREAD_H

// 1. Tipos de datos simulados básicos
typedef int pthread_t;
typedef int pthread_mutex_t;

typedef struct {
	int variable_control; 
} pthread_cond_t;

#define PTHREAD_MUTEX_INITIALIZER 0

// 2. Funciones de Hilos y Mutexes usando 'static inline'
static inline int pthread_create(pthread_t *thread, void *attr, void *(*start_routine)(void*), void *arg) {
	return 0; 
}

static inline int pthread_join(pthread_t thread, void **retval) {
	return 0;
}

static inline int pthread_mutex_init(pthread_mutex_t *mutex, void *attr) {
	return 0;
}

static inline int pthread_mutex_lock(pthread_mutex_t *mutex) {
	return 0; 
}

static inline int pthread_mutex_unlock(pthread_mutex_t *mutex) {
	return 0;
}

// 3. Funciones de Variables de Condición usando 'static inline'
static inline int pthread_cond_init(pthread_cond_t *cond, void *attr) {
	if (cond) cond->variable_control = 0;
	return 0;
}

static inline int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex) {
	return 0;
}

static inline int pthread_cond_signal(pthread_cond_t *cond) {
	return 0;
}

#endif
