/*
* Name:		Leen Aboukhalil
* Purpose:	The Stat class provides statistical functions to compute the range, mean, median, variance, standard deviation, and mode of a given set of numbers.
			It also includes functions for printing these statistics. The class helps to analyze a vector of long double values, 
			offering various descriptive statistics essential for data analysis.
* Date:		21/JUNE/2024
*/

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <cctype>
#include <map>
#include <numeric>
#include <iterator>
#include <unordered_map>

//a struct for switched 
struct BoolSwitches
{
	bool skipbad = false;
	bool userInput = false;
	bool longGraph = false;
	bool fancy = false;
};

class Stat {
public:
	/*
	fn:		findRange
	brief:	function for finding the range of min and max of the vector
	param:  long double vector
	return: nothing (void)
	*/
	void findRange(const std::vector<long double>& numberVector) const {
		auto [min, max] = std::minmax_element(numberVector.begin(), numberVector.end());
		std::cout << "Range = [" << *min << " .. " << *max << "]" << std::endl;
	}

	/*
	fn:		findMean
	brief:	function for finding the mean of a set of numbers
	param:  long double vector
	return: long double
	*/
	long double findMean(const std::vector<long double>& numberVector) const {
		return std::accumulate(numberVector.begin(), numberVector.end(), 0.0L) / numberVector.size();
	}

	/*
	fn:		findMedian
	brief:	function for finding the median of a set of numbers
	param:    long double vector
	return:   long double
	*/
	long double findMedian(std::vector<long double>& numberVector) {

		std::sort(numberVector.begin(), numberVector.end());
		size_t size = numberVector.size();

		if (size % 2 == 0)
			return (numberVector[size / 2 - 1] + numberVector[size / 2]) / 2.0;
		else
			return numberVector[size / 2];
	}

	/*
	fn:		variance
	brief:	function for finding the variance of a set of numbers
	param:    long double vector
	return:   long double
	*/
	long double variance(const std::vector<long double>& numberVector) const {

		long double mean = findMean(numberVector);
		long double squaredResult{};
		long double sum{};

		for (size_t i = 0; i < numberVector.size(); ++i) {
			squaredResult = pow((numberVector[i] - mean), 2);
			sum += squaredResult;
		}
		return sum / numberVector.size();
	}

	/*
	fn:		StandardDivision
	brief:	function for finding the Standard division of a set of numbers
	param:    long double vector
	return:   long double
	*/
	long double StandardDivision(const std::vector<long double>& numberVector) const {
		return std::sqrt(variance(numberVector));
	}

	/*
	fn:		findMode
	brief:	function for finding the mode of a set of numbers
	param:    long double vector
	return:   map <long double, long double>
	*/
	std::map<long double, long double> findMode(std::vector<long double>& numberVector) {
		std::map<long double, long double> modeMap;
		std::map<long double, long double> frequencyMap;
		long double maxFrequency{ 0.0L };

		//count the frequency of each element in the vector 
		for (const auto& number : numberVector)
			++frequencyMap[number];

		for (const auto& entry : frequencyMap) {
			if (entry.second > maxFrequency)
				maxFrequency = entry.second;
		}

		for (const auto& entry : frequencyMap) {
			if (entry.second == maxFrequency)
				modeMap.insert(entry);
		}

		if (modeMap.size() * maxFrequency == numberVector.size()) //checking if there is no mode 
			return{};

		return modeMap;
	}

	/*
	fn:		printMode
	brief:	function for printing the mode and frequencies
	param:    Stat object, long double vector
	return:   void
	*/
	void printMode(Stat& stat, std::vector<long double>& numberVector) {
		std::map<long double, long double> modeMap = stat.findMode(numberVector);
		auto it = modeMap.begin();
		size_t countSize = modeMap.size();

		if (!modeMap.empty()) {
			std::cout << "\nMode = { ";
			for (auto& mode : modeMap) {
				std::cout << mode.first;
				if (countSize == modeMap.size() && countSize > 1) {
					countSize--;
					std::cout << ", ";
				}
			}
			std::cout << " }x" << it->second << "\n\n\n"; //printing the frequencies of the mode 
		}
		else
			std::cout << "\nMode = { no mode }\n\n";
	}

	long double standardDeviation(Stat stat, const std::vector<long double>& numberVector) {
		return sqrt(stat.variance(numberVector));
	}
};


/*
fn:		  help
brief:	  function for printing the menu of the program, it is a switch like --help
param:    nothing
return:   void
*/
void help();

/*
fn:		  switchesState
brief:	  we have three switches(--help, --version, --fancy, skipbad), so the function is to check if there is any of the switches
		  in the command line
param:    string vector, and BoolSwitches object
return:   void
*/
void switchesState(std::vector<std::string>& args, BoolSwitches& switches);

/*
fn:		  readInput
brief:	  function for reading the input from the user if it is from a file or cin stream, and with some validation
param:    istream, long double vector, and BoolSwitches object
return:   void
*/
void readInput(std::istream& inputFile, std::vector<long double>& numberVector, BoolSwitches& switches);

