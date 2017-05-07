/*************************************************************************
	> File Name: demo.c
	> Author: Qichao
	> Created Time: Sat 24 Oct 2015 05:01:39 PM CST
 ************************************************************************/

#include <stdio.h>
#include "demo.h"

#ifdef TEST
static int exter_static_cnt = 2;
int extcount = 0;
#endif


int cal(int a, int b)
{
#ifdef TEST
    static int inter_static_cnt = 0;

	exter_static_cnt++;
    inter_static_cnt++; 
	extcount++; 

	printf("inter_static_cnt = %d, inter_static_cnt = %d, extcount = %d\n", inter_static_cnt, inter_static_cnt, extcount);
	return ((a << b) + (b << a) + inter_static_cnt - exter_static_cnt) * extcount;
#else
	return ((a << b) + (b << a));
#endif

}

