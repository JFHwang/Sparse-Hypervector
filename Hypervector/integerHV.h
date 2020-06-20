#ifndef INTEGERHV_H
#define INTEGERHV_H

#include "utils.h"
#include "binaryHV.h"
#include <vector>
#include <map>

template <unsigned long bitnum>
class integerHV : Ihypervector {

    private:

        unsigned long len = bitnum;
        std::vector<int> hv;

    public:

        integerHV();
        ~integerHV() {}

        size_t size() override;
        void populate(float sparsity) override;

        double distance(integerHV<bitnum> v);

        int& operator[](unsigned long index);

        // Interactions with binaryHV
        integerHV<bitnum>& operator+=(binaryHV<bitnum> v);
};


#endif /* INTEGERHV_H */