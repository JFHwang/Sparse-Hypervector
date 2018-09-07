#include "hypervector.h"

// Binary Hypervector Class

binaryHypervector::binaryHypervector(long long length) {
	this->length = length;
	this->hypervector = new unsigned char[length / 8];
	this->buf = new unsigned char[length / 8];	// Allocate extra space for operations
}


int binaryHypervector::getLength() {
	return length;
}


/*
 * populate:
 *		This function populates a binaryHypervector with random 1's and 0's
 * 
 * sparsity:	The fraction of bits in the binaryHypervector which are 1's
 *
 * return:		void
 */
void binaryHypervector::populate(float sparsity) {

	/*
	This is old code which needs reworking

	for (int i = 0; i < numReps; i++) {
		int bit = rand() % 10000;
		unsigned char byte = hypervector[bit / 8];
		unsigned char desiredBit = 1 << (bit % 8);

		// If bit has already been selected, reloop
		if (byte & desiredBit) {
			i--;
			// If bit has not been selected, mark it
		}
		else {
			byte |= desiredBit;
		}

	}
	*/
	return void;
}

binaryHypervector& binaryHypervector::operator>>(int shift) {
	unsigned char curBit, prevBit;
	memset(buf, 0, length*sizeof(char));	// Reset buf

	for (int i = 0; i < length; i++) {
		buf[(shift/8+i)%length] = hypervector[i] >> shift%8;		// Remaining contents
		buf[(shift/8+i+1)%length] |= hypervector[i] << (8-(shift%8));	// Contents shifted out
	}
	unsigned char * tmp = hypervector;	// Swap buffer pointers so hypervector pointer points to valid data
	hypervector = buf;
	buf = tmp;
}

binaryHypervector& binaryHypervector::operator<<(int shift) {
	unsigned char curBit, prevBit;
	memset(buf, 0, length * sizeof(char));	// Reset buf

	for (int i = 0; i < length; i++) {
		buf[(shift/8+i)%length] = hypervector[i] << shift % 8;	// Remaining contents
		buf[(shift/8+i-1)%length] |= hypervector[i] >> (8 - (shift % 8));	// Contents shifted out
	}
	unsigned char * tmp = hypervector;	// Swap buffer pointers so hypervector pointer points to valid data
	hypervector = buf;
	buf = tmp;
}

binaryHypervector& binaryHypervector::operator|(binaryHypervector v2) {
	// Implement bitwise or here
}

void binaryHypervector::operator|=(binaryHypervector v2) {
	// Implement bitwise or= here
}

binaryHypervector& binaryHypervector::operator&(binaryHypervector v2) {
	// Implement bitwise and here
}

binaryHypervector& binaryHypervector::operator^(binaryHypervector v2) {
	// Implement bitwise xor here
}

// Global operator overloads
void operator+=(std::vector<int>& v1, binaryHypervector v2)
{
	// Add binary hypervector to vector.
}
