#ifndef BINARYHV_H
#define BINARYHV_H

#include "utils.h"
#include "Ihypervector.h"
#include <map>
#include <bitset>
#include <iostream>
#include <time.h>


template <unsigned long bitnum>
class binaryHV : Ihypervector {

    private:
        size_t len = bitnum;
        std::bitset<bitnum> hv;

    public:
        binaryHV();
        binaryHV(std::bitset<bitnum> hv); 
        ~binaryHV() {}

        size_t size() override;
        void populate(float sparsity) override;

        double distance(binaryHV<bitnum> &v);

        binaryHV<bitnum> operator>>(int shift);
        binaryHV<bitnum> operator<<(int shift);

        binaryHV<bitnum> operator|(binaryHV<bitnum> &v2);
        binaryHV<bitnum> operator&(binaryHV<bitnum> &v2);
        binaryHV<bitnum> operator^(binaryHV<bitnum> &v2);

        bool get(unsigned long index);
        void set(unsigned long index, bool val);

        binaryHV<bitnum>& operator|=(binaryHV<bitnum> &v2);
        binaryHV<bitnum>& operator&=(binaryHV<bitnum> &v2);
        binaryHV<bitnum>& operator^=(binaryHV<bitnum> &v2);
        
        friend std::ostream& operator<<(std::ostream& os, binaryHV<bitnum> &v) {
            return os << v.hv;
        }
};


#endif /* BINARYHV_H */