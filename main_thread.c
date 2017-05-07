/*************************************************************************
	> File Name: main.c
	> Author: Qichao
	> Created Time: Sat 24 Oct 2015 05:04:34 PM CST
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include "demo.h"


int main(void)
{
	pid_t fpid;
#ifdef TEST
    extcount++;
    printf("This is in Test mode\n");
	printf("extcount = %d\n", extcount);
#endif
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

#if 0
	printf("Call cal(1,1) = %08x\n", cal(1,1));
	printf("Call cal(2,1) = %08x\n", cal(2,1));
	printf("Call cal(3,1) = %08x\n", cal(3,1));
#endif

    return 0;
}
