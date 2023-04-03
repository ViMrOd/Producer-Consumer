# Producer-Consumer
Implementation of the producer-consumer problem in C with threads and semaphores

This program demonstrates the producer-consumer problem with shared memory and semaphores in C.  The shared memory is handled in buffer.h. Here the table and semaphores are defined along with the table size. In producer.c, the shared memory space is defined along with the producer thread. In consumer.c, the consumer thread is defined and also linked to the shared memory defined in producer.c.

To run the programs, run gcc producer.c -pthread -lrt -o producer to compile producer, gcc consumer.c -pthread -lrt -o consumer to compile consumer, then ./producer & ./consumer & to run the programs. 

Upon successful compilation and running, the producer thread should produce two random integers between 0 and 99 and place them in the shared memory buffer. When the buffer is full, the consumer thread should read both and print them. This process will continue until the user kills the programs.

When the programs are killed by either exiting out of the terminal or running the pkill producer & pkill consumer command, the shared memory still exists and must be destroyed otherwise a segmentation fault will occur when ./producer & ./consumer & is run. To avoid this, cleanup.c is included which links to the shared memory and destroys it. To compile, run gcc cleanup.c -lrt -o cleanup. After killing producer and consumer, run ./cleanup. After this, ./producer & ./consumer & can be run successfully.  It should look something like the provided photo.
