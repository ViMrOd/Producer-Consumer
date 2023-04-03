#include "buffer.h"

struct buff *shtab;

int main()
{
	int fd = shm_open("queue", O_RDWR, 0);
	shtab = mmap(NULL, sizeof(*shtab), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	shm_unlink("queue");
}
