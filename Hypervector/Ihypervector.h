#ifndef IHYPERVECTOR_H
#define IHYPERVECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <vector>


class Ihypervector {
	public:
		Ihypervector() {}
		virtual ~Ihypervector() {}

		virtual size_t size() = 0;
		virtual void populate(float sparsity) = 0;
		
		//virtual unsigned char& hypervector::operator[](unsigned long index);
};


//void operator+=(std::vector<int>& v1, hypervector v2);

#endif /* IHYPERVECTOR_H */
