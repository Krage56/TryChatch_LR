//
// Created by krage56 on 16.04.2020.
//

#include "CharPtr.h"
#include <iostream>
using namespace std;

CharPtr::CharPtr(char *p): _ptr(p){
    _count = new size_t;
    *_count = 1;
}

CharPtr::~CharPtr() {
    --(*_count);
    if(*_count == 0){
        delete _ptr;
        delete _count;
    }
    _ptr = nullptr;
    _count = nullptr;
    cout << "CharPtr destructor\n";
}

CharPtr &CharPtr::operator=(char *p) {
    --(*_count);
    if(*_count == 0){
        delete _ptr;
        delete _count;
    }
    _count = new size_t;
    *_count = 1;
    _ptr = p;
    return *this;
}

CharPtr &CharPtr::operator=(CharPtr &obj){
    --(*_count);
    if(*_count == 0){
        delete _ptr;
        delete _count;
    }
    _count = obj._count;
    _ptr = obj._ptr;
    ++(*_count);
    return *this;
}

CharPtr::CharPtr(CharPtr &obj) {
    _count = obj._count;
    _ptr = obj._ptr;
    ++(*_count);
}

char *CharPtr::get() {
    return _ptr;
}

CharPtr::operator char *() {
    return _ptr;
}

