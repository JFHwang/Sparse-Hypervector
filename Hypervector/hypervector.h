#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <vector>

class binaryHypervector {
private:
	long long length;
	unsigned char * hypervector;
	unsigned char * buf;

public:
	binaryHypervector(long long length) {};
	binaryHypervector() {}
	int getLength();
	void populate(float sparsity);
	binaryHypervector& binaryHypervector::operator>>(int shift);
	binaryHypervector& binaryHypervector::operator<<(int shift);
	binaryHypervector& binaryHypervector::operator|(binaryHypervector v2);
	void binaryHypervector::operator|=(binaryHypervector v2);
	binaryHypervector& binaryHypervector::operator&(binaryHypervector v2);
	binaryHypervector& binaryHypervector::operator^(binaryHypervector v2);
	
};


void operator+=(std::vector<int>& v1, binaryHypervector v2);