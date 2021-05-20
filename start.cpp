#include<iostream>
#include"banker.h"
#include"random.h"
using namespace std;

int main()
{
    int a, b, c;
    int process;
    int tmp;
    Banker* bk;
    Random* rd;
    queue<int> q;
    cout<<"请选择要执行的算法："<<endl;
    cout<<"1、银行家算法"<<endl;
    cout<<"2、随机分配算法"<<endl;
    cin>>tmp;
    switch(tmp) {
        case 1:
            bk = new Banker();
            bk->input();
            try {
                q = bk->run();
                cout<<"执行队列为:"<<endl;
                while(!q.empty()) {
                    cout<<q.front()<<" ";
                    q.pop();
                }
                cout<<endl;
            } catch(std::string e) {
                cout<<"程序阻塞"<<endl;
            }
            break;
        case 2:
            rd = new Random();
            rd->input();
            if(rd->run()) cout<<"运行完毕"<<endl;
            else cout<<"资源分配失败，进程堵塞"<<endl;
            break;
    }
    return 0;
}