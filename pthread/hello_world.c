#include <pthread.h>
#include <stdio.h>
#define NUM_THREADS 5

void *PrintHello(void *threadid)
{
	long tid;
	tid = (long)threadid;
	printf("Hello World! I'm in thread# %ld\n", tid);
	pthread_exit(NULL);
}

int main(void)
{
	pthread_t threads[NUM_THREADS];
	for(long t=0; t<NUM_THREADS; t++) {
		printf("In main: creating thread %ld\n", t);
		int rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
		if (rc) {
			printf("ERRORl return code from pthread_create() is %d\n", rc);
			return 1;
		}
	}

	pthread_exit(NULL);
}
