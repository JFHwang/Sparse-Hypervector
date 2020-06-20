#include "trainer.h"


template <unsigned long bitnum>
binaryHV<bitnum>* trainer<bitnum>::genHV(std::string filename, std::map<char, binaryHV<bitnum>*> &letterHVs) {
    integerHV<bitnum> accum = integerHV<bitnum>();
    binaryHV<bitnum> * result;

    // Open and read from language file
    std::ifstream languageFile(filename);

    char letter;
    std::string window;

    // Parse file
    while(languageFile.get(letter)) {
        
        // If a letter has not been seen before, create a custom letter hypervector for it.
        if (letterHVs[letter] == nullptr) {
            binaryHV<bitnum>* newCharHV = new binaryHV<bitnum>();
            newCharHV->populate(SPARSITY);
            letterHVs[letter] = newCharHV;
        }

        // Shift window
        window += letter;
        if(window.size() > WINDOWSIZE) {
            window.erase(0,1);
        }

        binaryHV<bitnum> permutationHV = binaryHV<bitnum>();

        // Parse window
        for(int i = 0; i < window.size(); i++) {

            // Implement viewing window letter vector combining here.
            binaryHV<bitnum> tmp = (*(letterHVs[window[i]]) << i);
            permutationHV |= tmp;
            
        }
        
        accum += permutationHV;
    }
    languageFile.close();
    result = thresh(accum, 0);

    return result;
}


// Converts accumulation vector into a binary Hypervector
template <unsigned long bitnum>
binaryHV<bitnum>* trainer<bitnum>::thresh(integerHV<bitnum> accum, int threshold) {

	binaryHV<bitnum> * result = new binaryHV<bitnum>();

    for(int i = 0; i < accum.size(); i++) {
        if(accum[i] > threshold) {
            result->set(i, true);
        } else {
            result->set(i, false);
        }
    }

	return result;
}

template class trainer<DIMENSION>;
