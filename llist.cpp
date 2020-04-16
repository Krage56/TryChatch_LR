#include "llist.h"

#include <stdexcept>
#include <iostream>
#include <string>
#include <cstring>


void return_in_pos(std::fstream *file, bool pos){
    file->clear();
    pos ? file->seekg(0, std::ios_base::beg): file->seekg(0, std::ios_base::end);
}
LList::Container::Container(const int &value, LList::Container *next) {
    this->value = value;
    this->next = next;
}

LList::Container::~Container() {}

void LList::Container::insertNext(const int &value) {
    Container* newContainer = new Container(value, this->next);
    this->next = newContainer;
}

void LList::Container::insertNext(LList::Container *container) {
    Container* tmp = this->next;
    this->next = container;
    container->next = tmp;
}

void LList::Container::removeNext() {
    Container* removeContainer = this->next;
    Container* newNext = removeContainer->next;
    this->next = newNext;
    removeContainer->next = nullptr;
    delete removeContainer;
}


LList::LList() : _head(nullptr), _size(0){}

LList::~LList() {
    forceContainerDelete(_head);
}

void LList::push_back(int val) {

    if (_size == 0) {
        push_front(val);
    }
    else{
        insert_at(_size, val);
    }

}

void LList::push_front(int val) {
    _head = new Container(val, _head);
    ++_size;
}

size_t LList::size() const {
    return _size;
}

int &LList::operator[](size_t idx) {
    return getContainer(idx)->value;
}

LList::Container* LList::getContainer(const size_t pos) const
{
    if (pos < 0) {
        throw std::out_of_range("Index of required Container is "
                                "out of range\n");
    }
    else if (pos >= this->_size) {
        throw std::out_of_range("Index of required Container is"
                                "out of range\n");
    }

    Container* bufContainer = this->_head;
    for (int i = 0; i < pos; ++i) {
        bufContainer = bufContainer->next;
    }

    return bufContainer;
}

int LList::operator[](size_t idx) const {
    return getContainer(idx)->value;
}

void LList::erase_at(size_t idx) {
    if (idx < 0) {
        throw std::out_of_range("Index of required position is "
                                "out of range\n");
    }
    else if (idx > this->_size) {
        throw std::out_of_range("Index of required position is "
                                "out of range\n");
    }

    if (idx == 0) {
        Container* bufContainer = _head->next;
        delete _head;
        _head = bufContainer;
    }
    else {
        getContainer(idx - 1)->removeNext();
    }
    --_size;
}

void LList::insert_at(size_t idx, int val) {
    if (idx < 0) {
        throw std::out_of_range("Index of required position is "
                                "out of range\n");
    }
    else if (idx > this->_size) {
        throw std::out_of_range("Index of required position is "
                                "out of range\n");
    }

    if (idx == 0) {
        push_front(val);
    }
    else {
        getContainer(idx - 1)->insertNext(val);
        ++_size;
    }
}

void LList::pop_back(int val) {
    erase_at(_size - 1);
}

void LList::pop_front(int val) {
    Container* bufContainer = _head->next;
    delete _head;
    _head = bufContainer;
    --_size;
}

void LList::reverse() {
    if(_size > 1){
        Container *tmp;
        for(int i = 0; i < _size; ++i){
            tmp = getContainer(_size - 1);
            this->insertContainer(i, tmp);
        }
        //иначе петля в последнем элементе
        tmp->next = nullptr;
    }
}

void LList::insertContainer(const size_t pos, LList::Container *container) {
    if (pos < 0) {
        throw std::out_of_range("Index of required position is "
                                "out of range\n");
    }
    else if (pos > this->_size) {
        throw std::out_of_range("Index of required position is "
                                "out of range\n");
    }

    if (pos == 0) {
        Container *tmp = _head;
        _head = container;
        _head->next = tmp;
    }
    else {
        getContainer(pos - 1)->insertNext(container);
    }
}

void LList::forceContainerDelete(LList::Container *container) {
    if (container == nullptr) {
        return;
    }

    Container* nextDeleteContainer = container->next;
    delete container;
    forceContainerDelete(nextDeleteContainer);
}

void LList::operator>>(std::fstream &file) {
    Container *current = _head;
    try{
        while(current){
            file << current->value;
            file << "\n";
            current = current->next;
        }
        file << "What's the name of the game?";//условимся считать это завершением блока
        file << " It`s a pretty error!\n";//повредим конец файла
        return_in_pos(&file, true);
    }
    catch(std::ofstream::failure&){
        std::cout << "Can`t be written\n";
    }
}

void LList::operator<<(std::fstream &file) {
    //Container *current = _head;
    char buff[mem_block];
    std::string end("What's the name of the game?");
    Container* current = getContainer(_size - 1);
    try{
        int x;
        size_t pos = 0;
        file.getline(buff, mem_block - 1);
        while(strcmp(buff, end.c_str()) != 0){
            //считаем, что, если после числа идёт мусор, то число валидно,
            //если первая цифра в начале новой строки, иначе - это мусор
            //isdigit(buff[0])? x = atoi(buff): throw std::ifstream::failure(0);
            if(isdigit(buff[0])){
                x = atoi(buff);
            }
            else{
                throw std::ifstream::failure("Bad end of the file\n");
            }
            current->insertNext(x);
            current = current->next;
            ++_size;
            file.getline(buff, mem_block - 1);
        }
        return_in_pos(&file, true);
    }
    catch(std::ifstream::failure&){
        std::cout << "Can`t be red correctly\n";
        current = getContainer(_size - 2);
        current->removeNext();
    }

}
