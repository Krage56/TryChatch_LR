#include <iostream>
#include "llist.h"
#include "Pipe.h"
#include "CharPtr.h"
#include <fstream>
#include <unistd.h>

using namespace std;
int main() {
    /*2*/
    LList l;
    for(int i = 0; i < 5; ++i){
        l.push_back(i);
    }

    char file_name[mem_block];
    cin.getline(file_name, mem_block);//"../test.txt"
    fstream file;
    file.exceptions(std::fstream::failbit);
    try{
        file.open(file_name, ios_base::out | ios_base::in);
        l >> (file);//запись списка в файл
        l << file;//чтение списка из файла
    }
    catch(std::fstream::failure& ex){
        cout << "File can`t be opened or red or written" << endl;
    }
    return 0;
 }
