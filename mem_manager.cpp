//Jacqueline Vermette

#include "MyMemory.h"



void print_menu() {



	cout << string(20, '=') << endl;
	cout << "d: memory dump" << endl;
	cout << "r: request memory" << endl;
	cout << "l: release memory" << endl;
	cout << "m: merge memory" << endl;
	cout << "x: quit program" << endl;
	cout << "Your choice: ";	
}



int main() {




    int num_blocks, block_size;
    cout << "Memory configuration:" << endl;
    cout << "Number of memory blocks: ";
    cin >> num_blocks;
    cout << "Memory block size: ";
    cin >> block_size;



   



    MyMemory memory_system(num_blocks, block_size);  




    char choice;


while (true){
    print_menu();
    cin >> choice;

switch (choice){


case 'd':
    memory_system.dump();
    break;

case 'r':{

    int len;
    cout << "Memory size: ";
    cin >> len;


int index = memory_system.req_mem(len);

if (index == -1){
cout << "Failed. No space" << endl;


}
else{

cout << "Memory allocation: " << index << endl;


}

break;

}


case 'l': {
    int index, len;
    cout << "Enter block index: ";

    cin >> index;
    cout << "Enter memory size to release: ";

    cin >> len;
                
                
if (memory_system.release_mem(index, len)){

    cout << "Memory released." << endl;


} 
else{
    cout << "Memory release failed." << endl;


}
                
    break;
}


case 'm':
    memory_system.merge_mem();

    break;

case 'x':
    return 0;  

default:
                cout << "Invalid. " << endl;
        }
    }

    return 0;
}
