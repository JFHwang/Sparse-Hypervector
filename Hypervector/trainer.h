#ifndef TRAINER_H
#define TRAINER_H

#include "binaryHV.h"
#include "integerHV.h"
#include <string>
#include <iostream>
#include <fstream>

template <unsigned long bitnum>
class trainer {
    public:
        trainer() {}
        ~trainer() {}
        
        void genHV();
        binaryHV<bitnum>* genHV(std::string filename, std::map<char, binaryHV<bitnum>*> &letterHVs);
        binaryHV<bitnum>* thresh(integerHV<bitnum> accum, int threshold);
};

#endif /* TRAINER_H */