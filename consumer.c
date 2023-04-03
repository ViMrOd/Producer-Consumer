#include "buffer.h"

struct buff *shtab;

int out = 0;

void* consumer(void* thd)
{
	while(1) {
		// Enters critical section if table not empty and has mutex lock //
		sem_wait(&shtab->full);
		sem_wait(&shtab->mutex);
		
		// Critical Section //
		int tmp = shtab->table[out];
		sleep(1.5);
		printf("Comsumer consumed %d from slot %d\n", tmp, out);
		out = (out + 1) % BUFFER_SIZE;
		
		if(out == 0)
			sem_post(&shtab->empty); // If table is empty exits C.S lets producer enter //
		else
			sem_post(&shtab->full); // Table is not empty, stays in C.S //
		
		sem_post(&shtab->mutex); // Resets mutex //
	}
	return NULL;
}

int main()
{	
	sleep(1); // Wait to make sure shared memory initialized
	
	// Links to shared memory created by producer //
	int fd = shm_open("queue", O_RDWR, 0);
	shtab = mmap(NULL, sizeof(*shtab), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	
	// Initializes Thread //
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, consumer, NULL);
	pthread_join(thread_id, NULL);
	
	//sem_post(&shtab->s4);

	return 0;
}

