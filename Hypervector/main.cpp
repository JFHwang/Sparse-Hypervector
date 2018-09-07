#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "hypervector.h"

int main()
{
	char filename[256];
	const long long dimension = 10'000;	// Number of items in hypervector
	const float sparsity = .2;		// Number of 1's within hypervector
	const int windowSize = 4;
	std::map <char, binaryHypervector> letterHV;

	binaryHypervector permutationHV(dimension);
	std::map<std::string, binaryHypervector> languageHVs;
	std::vector<int> count(dimension);
	std::vector<std::string> languages = {"filename1", "filename2", "filename3"};
	int error;
	const long long bufsize = 1024 * 1024;	// 1 Megabyte buffer?
	unsigned char buf[bufsize];

	// Training
	for (std::string language : languages) {
		FILE * fh = fopen(language.c_str(), "r");
		if (fh == NULL) { error = 1; goto errorhandling; }

		// Keep looping 1 buffer at a time until EoF
		int bytesread = bufsize;
		while (bytesread == bufsize) {
			bytesread = fread(buf, sizeof(char), bufsize, fh);

			for (int i = 0; i < bytesread; i++) {

				// If a letter has not been seen before, create a custom hypervector for it.
				if (letterHV.find(buf[i]) == letterHV.end()) {
					letterHV[buf[i]] = binaryHypervector(dimension);
					letterHV[buf[i]].populate(sparsity);
				}

				// Implement viewing window/ letter vector combining here.
				for (int j = 0; j < windowSize; j++) {
					permutationHV |= letterHV[buf[j]] << j;
				}
				count += permutationHV;
			}
		}
		languageHVs[language] = thresh(count);
		fclose(fh);
	}



	// Testing
	std::vector<std::string> testfiles = { "testfile1", "testfile2", "testfile3" };

	for (std::string file : testfiles) {
		FILE * fh = fopen(file.c_str(), "r");
		if (fh == NULL) { error = 1; goto errorhandling; }

		// Keep looping 1 buffer at a time until EoF
		int bytesread = bufsize;
		while (bytesread == bufsize) {
			bytesread = fread(buf, sizeof(char), bufsize, fh);

			for (int i = 0; i < bytesread; i++) {

				// If a letter has not been seen before, skip it.
				if (letterHV.find(buf[i]) == letterHV.end()) {
					continue;
				}

				// Implement viewing window/ letter vector combining here.
				for (int j = 0; j < windowSize; j++) {
					permutationHV |= letterHV[buf[j]] << j;
				}
				count += permutationHV;
			}
		}
		fclose(fh);

		// Make a prediction
		binaryHypervector test = thresh(count);
		double minDist = INT32_MAX;
		std::string prediction;
		for (std::string language : languages) {
			double dist = distance(languageHVs[language], test);
			if (dist < minDist) {
				minDist = dist;
				prediction = language;
			}
		}
		fprintf(stderr, "Test file %s is of the language %s\n", file, prediction);
	}



errorhandling:
	if (error == 1) { fprintf(stderr, "Error! Failed to open file"); }
}






double distance(binaryHypervector v1, binaryHypervector v2) {
	// Implement a metric for distance here
}

binaryHypervector& thresh(std::vector<int> count) {
	// This function removes items in count which are too small
}





/*
* Function: cudaRNG
*		Uses CUDA helper functions to generate numerous random numbers
*
* binaryHypervector: The binary hypervector containing the initial values.
*
*/
void cudaRNG(unsigned char * binaryHypervector) {


}

void parallelXOR(unsigned char * binaryHypervector) {


}