#include "MyMemory.h"








MyMemory::MyMemory(int num, int len) : max_index(num - 1), block_size(len){
    for (int i = 0; i < num; ++i){

        mlist.push_back(MyMemoryBlock(i, len));

    }
}





MyMemory::~MyMemory(){
    

}



void MyMemory::resize(int num, int len){

if (!mlist.empty()){


    mlist.clear(); 

}

    max_index = num - 1;
    block_size = len;

for (int i = 0; i < num; ++i){

    mlist.push_back(MyMemoryBlock(i, len));

}
}


int MyMemory::req_mem(int len){


for (auto itr = mlist.begin(); itr != mlist.end(); ){


    if (itr->get_length() >= len){

        int index = itr->get_index();

    if (itr->allocate_mem(len) == len){

        if (itr->get_length() == 0){

            itr = mlist.erase(itr);  
} 
else{

++itr;
}

return index;

}
}

++itr;  

}
    return -1; 
}




bool MyMemory::release_mem(int ind, int len){


if (ind < 0 || ind > max_index || len <= 0 || len > block_size){


return false; 
}

    
for (auto itr = mlist.begin(); itr != mlist.end(); ++itr){

    if (itr->get_index() == ind){


    itr->free_mem(len);
    return true;
}
}

    
MyMemoryBlock newBlock(ind, len);
auto itr = mlist.begin();
while (itr != mlist.end() && itr->get_index() < ind){

++itr;
}


mlist.insert(itr, newBlock);

return true;
}



void MyMemory::merge_mem(){


for (auto itr = mlist.begin(); itr != mlist.end(); ){


    auto next_itr = itr;
    ++next_itr; 

if (next_itr != mlist.end() && (itr->get_length() + next_itr->get_length() <= block_size)){


itr->free_mem(next_itr->get_length());
next_itr = mlist.erase(next_itr);


}
else{

 ++itr; 
        }
    }
}


void MyMemory::dump() const{


for (auto itr = mlist.begin(); itr != mlist.end(); ++itr){


    std::cout << "Index: " << itr->get_index() << ", Length: " << itr->get_length() << std::endl;

    }
}




MyMemoryBlock::MyMemoryBlock(int ind, int len) : index(ind), length(len){


}


int MyMemoryBlock::get_length() const{


return length;
}


int MyMemoryBlock::get_index() const{

return index;
}


int MyMemoryBlock::allocate_mem(int len){


if (len > length){


        return -1; 
} 
else{

    length -= len; 
    return len; 

    }
}


void MyMemoryBlock::free_mem(int len){
    length += len; 
}
