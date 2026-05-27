# MiniKernel - Planificador de Procesos Multiprocesador

Este proyecto consiste en la simulación de un MiniKernel que implementa un planificador de CPU multiprocesador utilizando el algoritmo de planificación **Round Robin**. El sistema consta de un generador de procesos y simula la ejecución concurrente en múltiples CPUs compartiendo una cola de procesos listos (*Ready Queue*).

## Estructura del Proyecto

El repositorio está organizado siguiendo la estructura estándar requerida:

* **include/**: Contiene los archivos de cabecera (`.h`).
* **src/**: Contiene el código fuente principal (`.c`).
* **tests/**: Directorio destinado a las pruebas del sistema.
* **Makefile**: Archivo de automatización para la compilación del proyecto.
* **README.md**: Documentación general del proyecto.

## Requisitos

* Sistema Operativo basado en Linux (o WSL en Windows).
* Compilador de C (`gcc`).
* Librería de hilos POSIX (`pthread`).

## Compilación y Ejecución

Para compilación limpia y automática de todos los módulos estructurados, ejecute el siguiente comando en la raíz del proyecto:

```bash make
