/*************************************************************************
	> File Name: main.c
	> Author: Qichao
	> Created Time: Sat 24 Oct 2015 05:04:34 PM CST
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<sys/types.h>

#include "demo.h"


pthread_t main_tid;


void * func(void * arg)
{
	int i;

	for (i = 0; i < 400; i++) {
		sleep(2);
		printf("Index %d, Son process: Call cal(%d,1) = %08x\n", i, i, cal(i,1));
	}

	return NULL;
}

int main(void)
{
#ifdef TEST
    extcount++;
    printf("This is in Test mode\n");
	printf("extcount = %d\n", extcount);
#endif
#ifdef MULTI_PROCESS
	pid_t fpid;
	fpid = fork();
	if (fpid < 0) {
		printf("Fork error!\n");
	} else if (fpid == 0) { // sub process
		int i = 0;
		for (i = 0; i < 100; i++) {
			printf("Index %d, Son process: Call cal(%d,1) = %08x\n", i, i, cal(i,1));
		}
	} else { // sub process
		int j = 0;
		for (j = 0; j < 100; j++) {
			printf("Index %d, Father process: Call cal(%d,1) = %08x\n", j, j, cal(j,1));
		}
	}
#endif

#ifdef MULTI_THREAD
	pthread_t ftid;
	int err;
	int j = 0;
	// fpid = getpid();
	ftid = pthread_self();

	err = pthread_create(&ftid, NULL, func, (void *)0);
	if (0 != err) {
		printf("Create thread error %s\n", strerror(err));
	}
	// start_routine(1);
	pthread_join(ftid, NULL);

	for (j = 0; j < 100; j++) {
		printf("Index %d, Father process: Call cal(%d,1) = %08x\n", j, j, cal(j,1));
	}
#endif

#if 0
	printf("Call cal(1,1) = %08x\n", cal(1,1));
	printf("Call cal(2,1) = %08x\n", cal(2,1));
	printf("Call cal(3,1) = %08x\n", cal(3,1));
#endif

    return 0;
}
