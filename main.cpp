#include<iostream>
#include<vector>
#include<chrono>
#include"stl/Vector.h"
using namespace Sakura::Stl;

int main()
{
    //std::cout<<"hello Sakura"<<std::endl;

    // v1.push_back(1);
    // v1.push_back(2);
    // v1.push_back(3);
    // v1.print();

    // v1.erase(v1.begin(),v1.begin()+2);
    // v1.print();

    /*测试*/
    //v1.pop_back();
    //v1.reserve(10);
    //v1.resize(6);
    //bool b=v1.empty();
    //std::cout<<v1.at(2) <<" "<<v1[0]<<std::endl;
    // std::cout<<v1.size()<<std::endl;
    //std::cout<<v1.data()<<std::endl;
    // for(Vector<int>::Iterator it=v1.begin();it!=v1.end();++it)
    // {
    //     std::cout<<(*it)<<std::endl; 
    // }
    //Vector<int>v2;
    // v2.push_back(4);
    // v2.push_back(5);
    // v2.print();
    // v1.swap(v2);
    // v1.print();
    // v2.print();

    /*测试insert性能*/
    // auto startTime=std::chrono::steady_clock::now();
    // const int max=10000;
    // //std::vector<int>v;
    // Vector<int>v;
    // for(int i=0;i<max;i++)
    // {
    //     v.insert(v.begin(),1);
    // }
    // auto endTime=std::chrono::steady_clock::now();

    // //毫秒级
    // double duration_millsecond=std::chrono::duration<double,std::milli>(endTime-startTime).count();
    // std::cout<<"run time: "<< duration_millsecond<<" ms"<<std::endl;

    /*测试erase性能*/
    //std::vector<int>v1;
    Vector<int>v1;
    const int max=10000;
    for(int i=0;i<max;i++)
    {
        v1.push_back(i);
    }
    auto startTime=std::chrono::steady_clock::now();
    for(int i=0;i<max;i++)
    {
        v1.erase(v1.begin());
    }
    auto endTime=std::chrono::steady_clock::now();
    double duration_millsecond=std::chrono::duration<double,std::milli>(endTime-startTime).count();
    std::cout<<"run time: "<< duration_millsecond<<" ms"<<std::endl;

    return 0;
}