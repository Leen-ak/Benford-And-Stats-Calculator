/*
* Name:		Leen Aboukhalil
* Purpose:	The FrequencyCalculator class is designed to compute and manage frequency distributions for a given set of numerical data. It includes methods to calculate:
			1. Expected Frequencies: Computes the theoretical expected frequencies of leading digits according to Benford's Law.
			2. Raw Frequencies: Determines the frequency of each leading digit in the input data set.
			3. Actual Frequencies: Normalizes the raw frequencies to obtain percentage representations.
			These computations facilitate the analysis of data distributions and their adherence to expected statistical patterns.
* Date:		21/JUNE2024
*/

#pragma once
#include "StatisticsCalculatorHeader.hpp"


class FrequencyCalculator {
public:

	/*
	fn:		  expectedFrequencies
	brief:	  function for calculating the expected frequencies
	param:    unordered_map<unsigned int, long double>
	return:   void
	*/
	void expectedFrequencies(std::unordered_map<unsigned int, long double>& expMap) {
		for (int d = 1; d < 10; ++d)
			expMap[d] = log10(1 + 1.0 / d) * 100;
	}

	/*
	fn:		  rowFrequencies
	brief:	  function for calculating the row frequencies
	param:    vector<long double>, map<unsigned int, long double>
	return:   void
	*/
	void rowFrequencies(const std::vector<long double>& frequencyVector, std::map<unsigned int, long double>& frequencyMap) {
		for (long double entry : frequencyVector) {
			auto digit = entry / pow(10, static_cast<unsigned>(log10(entry))); //to find the leading digit
			frequencyMap[digit]++;
		}
	}

	/*
	fn:		  actualFrequencies
	brief:	  function for calculating actualFrequencies
	param:    vector<long double>, map<unsigned int, long double>, unordered_map<unsigned int, long double>
	return:   void
	*/
	void actualFrequencies(const std::vector<long double>& frequencyVector, std::map<unsigned int, long double>& rawFrequencyMap, std::unordered_map<unsigned int, long double>& actualFrequencyMap) {
		long double sumFrequency{};
		auto it = actualFrequencyMap.begin();

		for (int i = 1; i < 10; ++i) //to make sure the 9 columns will be there even if threr is less than 9 frequencies 
			actualFrequencyMap[i] = 0;

		for (int i = 1; i < 10; ++i)
			actualFrequencyMap[i] = rawFrequencyMap[i] / frequencyVector.size() * 100;
	}
};