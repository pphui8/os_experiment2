#ifndef _BANKER_
#define _BANKER_

#include"structure.h"
#include<queue>

class Banker;

bool is_finished(Banker& b);
void print(Banker& b);

class Banker {
public:
    Banker() = default;
    void input();
    std::queue<int> run();
private:
    REC system;
    int process_num;
    PCB alloca_matrix[MAX];
    std::queue<int> pro_queue;

    friend bool is_finished(Banker& b);
    friend void print(Banker& b);
};

inline bool
is_finished(Banker& b)
{
    for(PCB p : b.alloca_matrix) if(p.state == "false") return false;
    return true;
}

inline void
print(Banker& b)
{
    std::cout<<"......................................................................\n"<<std::endl;
	printf("\n当前状态：   {可利用量：[%d %d %d]}\n\n", b.system.A , b.system.B, b.system.C);
	std::cout<<"进程号   需求总量     已分配      还需求量    状态\n"<<std::endl;
	for(int i = 0; i < b.process_num; ++i) {
        std::cout<<b.alloca_matrix[i].id<<"     "<<b.alloca_matrix[i].state<<"     ["<<b.alloca_matrix[i].max.A<<","<<b.alloca_matrix[i].max.B
        <<","<<b.alloca_matrix[i].max.C<<"]     ["<<b.alloca_matrix[i].allocation.A<<","<<b.alloca_matrix[i].allocation.B<<","<<b.alloca_matrix[i].allocation.C
        <<"]     ["<<b.alloca_matrix[i].need.A<<","<<b.alloca_matrix[i].need.B<<","<<b.alloca_matrix[i].need.C<<"]"<<std::endl;
	}
	std::cout<<"......................................................................\n"<<std::endl;
}

inline void
Banker::input()
{
    std::cout<<"请输入三种资源的总量(available)"<<std::endl;
    std::cin>>system.A>>system.B>>system.C;
    std::cout<<"请输入进程数量:"<<std::endl;
    std::cin>>process_num;
    std::cout<<"请输入每个进程需要的资源总量:"<<std::endl;
    for(int i = 0; i < process_num; ++i) std::cin>>alloca_matrix[i].max.A>>alloca_matrix[i].max.B>>alloca_matrix[i].max.C;
    std::cout<<"请输入每个进程已分配的的资源总量:"<<std::endl;
    for(int i = 0; i < process_num; ++i) {
        std::cin>>alloca_matrix[i].allocation.A>>alloca_matrix[i].allocation.B>>alloca_matrix[i].allocation.C;
        alloca_matrix[i].need.A = alloca_matrix[i].max.A - alloca_matrix[i].allocation.A;
        alloca_matrix[i].need.B = alloca_matrix[i].max.B - alloca_matrix[i].allocation.B;
        alloca_matrix[i].need.C = alloca_matrix[i].max.C - alloca_matrix[i].allocation.C;
        alloca_matrix[i].state = "false";
        alloca_matrix[i].id = i;
    }
}

inline std::queue<int>
Banker::run()
{
    bool runable = true;
    while(!is_finished(*this)) {
        runable = true;
        //如果遍历一遍发现没有进程可以运行就阻塞
        for(int i = 0; i < process_num; ++i) {
            if(alloca_matrix[i].state == "true") continue;
            else {
                runable = false;
                //判断是否可分配
                if(system.A >= alloca_matrix[i].need.A &&
                system.B >= alloca_matrix[i].need.B &&
                system.C >= alloca_matrix[i].need.C) {
                    system.A += alloca_matrix[i].allocation.A;
                    system.B += alloca_matrix[i].allocation.B;
                    system.C += alloca_matrix[i].allocation.C;
                    alloca_matrix[i].state = "true";
                    pro_queue.push(i);
                    print(*this);
                }
                else continue;
            }
        }
        if(runable) {
            print(*this);
            std::cout<<"程序阻塞！"<<std::endl;
            throw std::string("woring");
            return pro_queue;
        }
    }
    return pro_queue;
}

#endif  //_BANKER_