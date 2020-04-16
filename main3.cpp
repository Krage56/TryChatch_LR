#include <iostream>
#include "llist.h"
#include "Pipe.h"
#include "CharPtr.h"
#include <fstream>
#include <unistd.h>

using namespace std;
int main(){
 /*3*/
    CharPtr buff(new char[mem_block]);
    try{
        Pipe texts = popen("cat ../*.txt", "r");

        //покажем, что метод release работает
        Pipe test(nullptr);
        texts.release(test);
        //покажем, что объект test не пуст
        do{
            fgets(buff.get(),  mem_block - 1, test.get());
            cout << buff.get() << endl;
        }while(test.get()->_IO_read_ptr != test.get()->_IO_read_end);

        //вернём указатели на место, чтобы test можно было снова прочитать
        test.get()->_IO_read_ptr = test.get()->_IO_read_base;
        //покажем, как работает совместное владение ресурсами CharPtr
        cout <<"_________________" << endl;
        //Создадим ещё один CharPtr и присвоим ему контроль над той же строкой
        CharPtr example = buff;
        cout << example.get() << endl;
        //сделаем то же самое с уже инициализированным объектом
        CharPtr localBuf(new char[mem_block]);
        localBuf = example;
        //вызовем исключение, если оно не вызвалось ранее и увидим, как отработали деструкторы
        double x = stod(example.get());
    }
    catch(std::invalid_argument&e){
        cout << "Произошла ошибка, её инициализировал объект ";
        cout << e.what() << endl;
    }


    cout << "Содержимое буфера соответствует последнему заполнению,"
            " хотя объект example удалён: " << buff.get() << endl;
    return 0;
  }
