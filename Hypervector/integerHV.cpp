#include "integerHV.h"


template <unsigned long bitnum>
integerHV<bitnum>::integerHV() : len(bitnum), hv(bitnum, 0) {}

// TODO: This is currently a stub
template <unsigned long bitnum>
size_t integerHV<bitnum>::size() {
    return this->hv.size();
}

// TODO: This is currently a stub
template <unsigned long bitnum>
void integerHV<bitnum>::populate(float sparsity) {
    return;
}

// TODO: This is currently a stub
template <unsigned long bitnum>
double integerHV<bitnum>::distance(integerHV<bitnum> v) {
    return 0;
}

// TODO: Check if this works
template <unsigned long bitnum>
int& integerHV<bitnum>::operator[](unsigned long index) {
    return this->hv[index];
}



// Interactions with binaryHV
template <unsigned long bitnum>
integerHV<bitnum>& integerHV<bitnum>::operator+=(binaryHV<bitnum> v) {

    for(int i = 0; i < this->size(); i++) {
        if(v.get(i)) {
            this->hv[i]++;
        }
    }
    return *this;
}

template class integerHV<DIMENSION>;
