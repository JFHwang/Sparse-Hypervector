#include "binaryHV.h"


template <unsigned long bitnum>
binaryHV<bitnum>::binaryHV() : hv(std::bitset<bitnum>(0x0)) {}


template <unsigned long bitnum>
binaryHV<bitnum>::binaryHV(std::bitset<bitnum> hv) : hv(hv) {}


template <unsigned long bitnum>
size_t binaryHV<bitnum>::size() {
    return (size_t)this->len;
}


template <unsigned long bitnum>
void binaryHV<bitnum>::populate(float sparsity) {

	std::srand(time(nullptr));
	this->hv.reset();

	unsigned long numOnes = sparsity * bitnum;

	while(this->hv.count() < numOnes) {
		this->hv[std::rand() % bitnum] = true;
	}

	return;
}


template <unsigned long bitnum>
double binaryHV<bitnum>::distance(binaryHV<bitnum> &v2) {
    std::bitset<bitnum> count = this->hv ^ v2.hv;
    unsigned long distance = count.count();
    
    return distance;
}


template <unsigned long bitnum>
binaryHV<bitnum> binaryHV<bitnum>::operator<<(int shift) {
    return binaryHV<bitnum>(this->hv << shift);
}


template <unsigned long bitnum>
binaryHV<bitnum> binaryHV<bitnum>::operator>>(int shift) {
    return binaryHV<bitnum>(this->hv >> shift);
}


template <unsigned long bitnum>
binaryHV<bitnum> binaryHV<bitnum>::operator|(binaryHV<bitnum> &v2) {
    return binaryHV<bitnum>(this->hv | v2.hv);
}


template <unsigned long bitnum>
binaryHV<bitnum> binaryHV<bitnum>::operator&(binaryHV<bitnum> &v2) {
    return binaryHV<bitnum>(this->hv & v2.hv);
}


template <unsigned long bitnum>
binaryHV<bitnum> binaryHV<bitnum>::operator^(binaryHV<bitnum> &v2) {
    return binaryHV<bitnum>(this->hv ^ v2.hv);
}


template <unsigned long bitnum>
bool binaryHV<bitnum>::get(unsigned long index) {
    return this->hv[index];
}


template <unsigned long bitnum>
void binaryHV<bitnum>::set(unsigned long index, bool val) {
    this->hv[index] = val;
    return;
}


template <unsigned long bitnum>
binaryHV<bitnum>& binaryHV<bitnum>::operator|=(binaryHV<bitnum> &v2) {
    this->hv |= v2.hv;
    return *this;
}


template <unsigned long bitnum>
binaryHV<bitnum>& binaryHV<bitnum>::operator&=(binaryHV<bitnum> &v2) {
    this->hv &= v2.hv;
    return *this;
}


template <unsigned long bitnum>
binaryHV<bitnum>& binaryHV<bitnum>::operator^=(binaryHV<bitnum> &v2) {
    this->hv ^= v2.hv;
    return *this;
}



template class binaryHV<DIMENSION>;
