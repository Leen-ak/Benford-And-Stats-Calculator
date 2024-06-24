/*
* Name:		Leen Aboukhalil
* Purpose:	The main function orchestrates the statistical analysis of numerical data from either a file or user input. It handles command-line switches, reads input data, 
			and utilizes various classes (Stat, Histogram, FrequencyCalculator, BenfordCalculation) to compute and display descriptive statistics, frequency distributions, and compliance with Benford's Law. 
			It ensures robust error handling and supports enhanced output formatting based on user preferences.
* Date:		21/JUNE/2024
*/

#include "StatisticsCalculatorHeader.hpp"
#include "FrequencyCalculatorHeader.hpp"
#include "PrintHistogram.hpp"
#include "BenfordAnalysis.hpp"

int main(int argc, char* argv[]) {
	std::vector<std::string> args(argv + 1, argv + argc);
	std::vector<long double> numberVector;
	std::vector<std::string>::iterator it;
	BoolSwitches switches;
	size_t extention{};
	std::string fileName{};
	std::fstream input(fileName);
	Histogram histogram;
	Stat stat;
	FrequencyCalculator freq;
	BenfordCalculation benfCal;
	std::map<unsigned int, long double> rawFrequencyMap;
	std::unordered_map<unsigned int, long double> expectedFrequencyMap;
	std::unordered_map<unsigned int, long double> actualFrequencyMap;

	try {

		for (const auto& file : args) {
			extention = file.find('.'); 					//finding the name of the file which usually have (.) with it
			if (extention != std::string::npos) {
				fileName = file;
			}
			else if ((file[0] != '-') && (file[1] != '-'))  //if we did not find a file and it is not a switch then it is not a file name
				fileName = file;							//so storing what the user type to print it with the error message 
		}
		switchesState(args, switches);	//calling the method to check if there is any switches in command line

		if (!fileName.empty()) { //checking for the file if it exsit open the file to read from and if it is not
			input.open(fileName); //throw an error 
			if (!input) {
				throw std::runtime_error("File not found <" + fileName + ">");
			}
		}

		if (input.good() || std::cin.good()) {			   //when the input or cin stream is in a good stream start the program
			if (args.size() > 0) {						   //if the args vector bigger than 0 that means there is a file name
				switches.userInput = false;				   //userInput set to false to read from input stream not from cin stream
				readInput(input, numberVector, switches);  //a method to read from the file with some validation and then store it in numberVector
				histogram.programName(numberVector, switches);
			}
			else {
				switches.userInput = true;				   //else set userInput to true to read from the cin stream
				histogram.printHeader(switches);		   //method to print the header of the program 
				switches.userInput = false;				   //then set it to false after reading	
				readInput(std::cin, numberVector, switches);//readInput to read form cin stream with some validation and then store to numberVector
				histogram.programName(numberVector, switches);//prining the name of the program 
			}

			auto element = [](const std::vector<long double>& v) { //a lambda function to print the size of the vector 
				std::cout << "\n# Elements = " << v.size() << std::endl;
				};
			element(numberVector);								 //call the function to print it to the console 
			stat.findRange(numberVector);						 //findRange method to find the min and max value in the vecotr
			std::cout << "Arithmetic mean = " << stat.findMean(numberVector) << std::endl;
			std::cout << "Arithmetic median = " << stat.findMedian(numberVector) << std::endl;
			std::cout << "Variance = " << stat.variance(numberVector) << std::endl;
			std::cout << "Standard Deviation = " << stat.StandardDivision(numberVector) << std::endl;
			stat.printMode(stat, numberVector);
			freq.expectedFrequencies(expectedFrequencyMap);
			freq.rowFrequencies(numberVector, rawFrequencyMap);
			freq.actualFrequencies(numberVector, rawFrequencyMap, actualFrequencyMap);
			histogram.printNBStat(numberVector, rawFrequencyMap, expectedFrequencyMap, actualFrequencyMap, switches); //printing a table have the result of NBStat
			std::cout << std::fixed << std::setprecision(5);	//make the result 5 decimal places 
			long double nbvariance = benfCal.NBVariance(actualFrequencyMap, expectedFrequencyMap);
			std::cout << "Variance  = " << nbvariance * 100 << "%\n";
			long double nbdeviation = benfCal.NBDeviation(nbvariance);
			std::cout << "Std. Dev. = " << nbdeviation * 100 << "%\n";
			benfCal.NBRelationShip(nbdeviation, switches, histogram);
			histogram.printProgramEnd(switches);
		}
	}
	catch (const std::runtime_error& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
}

