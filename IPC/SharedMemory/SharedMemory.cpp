//
// Created by Administrator on 2020/7/5.
//

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <iostream>
int main()
{
    boost::interprocess::shared_memory_object shdmem(boost::interprocess::open_or_create,"Highscore", boost::interprocess::read_write);
    shdmem.truncate(1024);
    boost::interprocess::mapped_region region(shdmem, boost::interprocess::read_write);
    int* i = static_cast<int*>(region.get_address());
    std::cout << *i << std::endl;
    getchar();
    return 0;
}