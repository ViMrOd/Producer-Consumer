#ifndef BUFFER_H
#define BUFFER_H 

#include <sys/mman.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define BUFFER_SIZE 2

struct buff {
	sem_t mutex, full, empty, s4;
	int table[BUFFER_SIZE];
};

#endif

