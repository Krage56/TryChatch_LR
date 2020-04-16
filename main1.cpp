#include <iostream>
#include "llist.h"
#include "Pipe.h"
#include "CharPtr.h"
#include <fstream>
#include <unistd.h>

using namespace std;
int main() {

    LList l;
    for(int i = 0; i < 5; ++i){
        l.push_back(i);
    }

    /*1*/
    try{
        while(true){
            l.push_back(1);
        }
    }
    catch (std::bad_alloc &exception){
            cout << "Process was stopped" << endl;
            sleep(60);//чтобы увидеть ошибку в консоли
    }
    return 0;
}
