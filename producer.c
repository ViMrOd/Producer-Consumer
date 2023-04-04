#include <ctype.h>
#include <time.h>
#include "buffer.h"

struct buff *shtab; // Shared Memory //

int in = 0; // Slot producing to //

void* producer(void* thd)
{
	while(1){
		srand(time(NULL));
		int tmp = rand() % 100;
		
		// Enters critical section if table not full and has mutex lock //
		sem_wait(&shtab->empty); 
		sem_wait(&shtab->mutex);
		
		// Critical Section //
		shtab->table[in] = tmp;
		sleep(1.5);
		printf("Producer produced %d in slot %d\n", tmp, in);
		in = (in + 1) % BUFFER_SIZE;;
		
		if(in == 0)
			sem_post(&shtab->full); // If table is full lets exits C.S lets consumer enter //
		else
			sem_post(&shtab->empty); // Table is not full, stays in C.S //
			
		sem_post(&shtab->mutex); // Reset Mutex //
	}
	return NULL;
}

int main()
{	
	// Create the shared memory between producer and consumer //
	int fd = shm_open("queue", O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR);
	ftruncate(fd, sizeof(struct buff));
	shtab = mmap(NULL, sizeof(*shtab), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	shmctl(fd, IPC_RMID, 0);
	
	// Initialize Semaphores //
	sem_init(&shtab->mutex, 1, 1); 
	sem_init(&shtab->full, 1, 0); 
	sem_init(&shtab->empty, 1, 1);
	
	// Create Threads //
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, producer, NULL);
	pthread_join(thread_id, NULL);

	return 0;
}

