#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "utils.h"
#include "binaryHV.h"
#include "trainer.h"



int main()
{
	// Both languages and letters are represented by a single binary HV
	std::map<char, binaryHV<DIMENSION>*> letterHVs;
	std::map<char, char> tmp2;
	std::map<std::string, binaryHV<DIMENSION>*> languageHVs;
	
	std::vector<std::string> languages = { "HDC-Language-Recognition/training_texts/afr.txt" };
	std::vector<std::string> testfiles = { "testfile1", "testfile2", "testfile3" };

	// Training
	trainer<DIMENSION>* train = new trainer<DIMENSION>();

	for (std::string language : languages) {

		languageHVs[language] = train->genHV(language, letterHVs);
		std::cerr << "Print stuff" << std::endl;
		std::cerr << "Trained vector is " << languageHVs[language] << std::endl;
		
	}
	std::cerr << "Print stuff" << std::endl;
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
}
	*/
