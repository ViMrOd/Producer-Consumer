// Run after exiting producer-consumer to avoid segmemtaion fault //

#include "buffer.h"

struct buff *shtab; // Shared memory //

int main()
{
	// Links to shared memory //
	int fd = shm_open("queue", O_RDWR, 0);
	shtab = mmap(NULL, sizeof(*shtab), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	
	// Destroys shared memory //
	shm_unlink("queue");
}
