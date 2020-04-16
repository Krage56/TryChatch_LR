//
// Created by krage56 on 16.04.2020.
//

#ifndef TRYCATCH_CHARPTR_H
#define TRYCATCH_CHARPTR_H


#include <cstddef>

class CharPtr {

public:
    explicit CharPtr(char* p = nullptr);
    ~CharPtr();
    explicit operator char* ();
    CharPtr&operator=(char*p);
    CharPtr& operator=(CharPtr& obj);
    CharPtr(CharPtr&obj);
    char* get();

private:
    char* _ptr;
    size_t* _count;
};


#endif //TRYCATCH_CHARPTR_H
