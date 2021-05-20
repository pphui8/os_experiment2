#ifndef _STRUCTURE_
#define _STRUCTURE_

#define MAX 100

#include<cstring>
#include<iostream>

struct REC {
    int A;
    int B;
    int C;
};
 
struct PCB {
    //进程号，外部标识符
	int id;
    //状态
	std::string state;
    //需求总量
	REC max;
    //还需要资源数量
	REC need;
    //已分配量
	REC allocation;
};

#endif  //_STRUCTURE_