#ifndef MY_MEMORY_HPP
#define MY_MEMORY_HPP



#include "List.h"      
#include<iostream>




using namespace cop4530;



class MyMemoryBlock{

private:

    int index;
    int length;

public:
   

    MyMemoryBlock(int ind = 0, int len = 0);

   
    int get_length() const;

    int get_index() const;

    int allocate_mem(int len);

    void free_mem(int len);
};



#endif  






class MyMemory{
        


public:

    MyMemory(int num = 0, int len = 0);

    

    ~MyMemory();

  

    void resize(int num = 100, int len = 100);

    int req_mem(int len);

    bool release_mem(int ind, int len);

    void merge_mem();

    void dump() const;



    private:
    List<MyMemoryBlock> mlist; 
    int max_index;             
    int block_size;  


};

