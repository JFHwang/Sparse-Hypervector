#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "hypervector.h"

#define BUFSIZE 1024*1024
#define DIMENSION 10'000
#define SPARSITY .2
#define WINDOWSIZE 4

int main()
{

	std::map <char, binaryHypervector> letterHVs;
	std::map<std::string, binaryHypervector> languageHVs;
	
	std::vector<std::string> languages = {"filename1", "filename2", "filename3"};
	std::vector<std::string> testfiles = { "testfile1", "testfile2", "testfile3" };

	// Training
	for (std::string language : languages) {
		languageHVs[language] = *genHV(language, letterHVs);
	}
/*
	// Testing
	for (std::string testfile : testfiles) {
		binaryHypervector test = *genHV(testfile, letterHVs);

		// Make a prediction
		double minDist = INT32_MAX;
		std::string prediction;
		for (std::string language : languages) {
			double dist = languageHVs[language].distance(test);
			if (dist < minDist) {
				minDist = dist;
				prediction = language;
			}
		}
		fprintf(stderr, "Test file %s is of the language %s\n", testfile, prediction);
	}
	*/
}






binaryHypervector* genHV(std::string filename, std::map<char, binaryHypervector>& letterHVs) {
	int error = 0;
	unsigned char buf[BUFSIZE];
	std::vector<int> accum(DIMENSION);
	binaryHypervector permutationHV(DIMENSION);

	FILE * fh = fopen(filename.c_str(), "r");
	if (fh == NULL) { error = 1; goto errorhandling; }

	// Keep looping 1 buffer at a time until EoF
	int bytesread = BUFSIZE;
	while (bytesread == BUFSIZE) {
		bytesread = fread(buf, sizeof(char), BUFSIZE, fh);
/*
		for (int i = 0; i < bytesread; i++) {
			// If a letter has not been seen before, create a custom letter hypervector for it.
			if (letterHVs.find(buf[i]) == letterHVs.end()) {
				letterHVs[buf[i]] = binaryHypervector(DIMENSION);
				letterHVs[buf[i]].populate(SPARSITY);
			}

			// Implement viewing window/ letter vector combining here.
			for (int j = 0; j < WINDOWSIZE; j++) {
				permutationHV |= letterHVs[buf[j]] << j;
			}
			accum += permutationHV;
		}
*/
	}
	fclose(fh);

	binaryHypervector* result = thresh(accum);
	return result;


errorhandling:
	if (error == 1) { fprintf(stderr, "Error! Failed to open file"); }
}






// Converts accumulation vector into a binary Hypervector
binaryHypervector* thresh(std::vector<int> count) {
	binaryHypervector* result = new binaryHypervector(DIMENSION);
	int threshhold = 0;

	// This function removes items in count which are too small
	for (int i = 0; i < count.size(); i++) {
		if (count[i] > threshhold) {
			(*result)[i / 8] |= (0x01 << (7 - (i % 8)));
		}
	}
	return result;
}













