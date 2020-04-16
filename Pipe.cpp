//
// Created by krage56 on 16.04.2020.
//

#include <iostream>
#include "Pipe.h"

Pipe::Pipe(FILE *ptr): _pipe(ptr){}

Pipe::~Pipe(){
    if( _pipe ) pclose(_pipe);
    std::cout << "Pipe destructor" << std::endl;
}

FILE *Pipe::release(Pipe &obj) {
    if(!obj._pipe){
        obj._pipe = _pipe;
        _pipe = nullptr;
        return obj._pipe;
    }
    return nullptr;
}

Pipe &Pipe::operator=(FILE *pipe) {
    if(_pipe){
       pclose(_pipe);
    }
    _pipe = pipe;
}

void Pipe::clear() {
    if(_pipe){
        pclose(_pipe);
    }
    _pipe = nullptr;
}

FILE *Pipe::operator->() {
    return _pipe;
}

FILE *Pipe::get() {
    return _pipe;
}

Pipe::operator FILE *()  { return _pipe; }
