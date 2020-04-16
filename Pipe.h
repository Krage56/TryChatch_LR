//
// Created by krage56 on 16.04.2020.
//

#ifndef TRYCATCH_PIPE_H
#define TRYCATCH_PIPE_H
#define mem_block 1025

#include <cstdio>

class Pipe {
    FILE* _pipe;
public:
    Pipe(FILE* ptr);
    ~Pipe();
    operator FILE* ();
    FILE* release(Pipe& obj);//передача данных в не иниц-ый объект
    Pipe&operator=(FILE* pipe);
    FILE* operator->();
    FILE* get();
    void clear();
private:
    explicit Pipe(Pipe &obj);
    Pipe& operator=(Pipe &obj);
};


#endif //TRYCATCH_PIPE_H
