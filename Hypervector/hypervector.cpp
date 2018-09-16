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
	return;
}

double binaryHypervector::distance(binaryHypervector v) {
	// Implement a metric for distance here
}

/* TODO
  Figure out how to handle returns for all operator overloads returning binaryHypervector type.
  Is there really no choice other than to allocate an entire new hypervector?
*/

// Shift functions need some reworking. Return value isn't correct.
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

// These sets of functions assume that the lengths of the vectors match. TODO: Add error handling later
binaryHypervector& binaryHypervector::operator|(binaryHypervector v2) {
	// Implement bitwise or here
	binaryHypervector& result = binaryHypervector(length);
	for (int i = 0; i < length; i++) {
		result[i] = hypervector[i] | v2.hypervector[i];
	}
	return result;
}


// 
void binaryHypervector::operator|=(binaryHypervector v2) {
	// Implement bitwise or= here
	for (int i = 0; i < length; i++) {
		hypervector[i] |= v2.hypervector[i];
	}
}

binaryHypervector& binaryHypervector::operator&(binaryHypervector v2) {
	// Implement bitwise and here
	binaryHypervector& result = binaryHypervector(length);
	for (int i = 0; i < length; i++) {
		result[i] = hypervector[i] & v2.hypervector[i];
	}
	return result;
}
 
binaryHypervector& binaryHypervector::operator^(binaryHypervector v2) {
	// Implement bitwise xor here
	binaryHypervector& result = binaryHypervector(length);
	for (int i = 0; i < length; i++) {
		result[i] = hypervector[i] ^ v2.hypervector[i];
	}
	return result;
}

// This function is weird since it returns a reference to the whole char rather than the specified bit
unsigned char& binaryHypervector::operator[](int index) {
	return hypervector[index];
}

// Global operator overloads
void operator+=(std::vector<int>& v1, binaryHypervector v2)
{
	// Add binary hypervector to vector.
	for (int i = 0; i < v2.getLength() / 8; i++) {
		for (int bitnum = 0; bitnum < 8; bitnum++) {
			v1[i*8 + bitnum] += static_cast<int>(v2[i] | (1 << bitnum));
		}
	}
}

