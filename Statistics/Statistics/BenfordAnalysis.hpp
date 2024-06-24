/*
* Name:		Leen Aboukhalil
* Purpose:	The BenfordCalculation class is designed to evaluate the adherence of a dataset to Benford's Law. It includes methods to:
			1. NBVariance: Calculate the variance between the actual and expected frequencies of leading digits.
			2. NBDeviation: Compute the standard deviation based on the calculated variance.
			3. NBRelationShip: Determine and describe the strength of the relationship to Benford's Law based on the standard deviation, with optional fancy formatting for output.
			These computations help in analyzing the conformity of data to the expected Benford distribution, providing insights into data authenticity and anomalies.
* Date:		21/JUNE/2024
*/

#include "FrequencyCalculatorHeader.hpp"
#include "StatisticsCalculatorHeader.hpp"

class BenfordCalculation {
public:

	/*
	fn:		  NBVariance
	brief:	  function for calculating NBVariance
	param:    unordered_map<unsigned int, long double>, unordered_map<unsigned int, long double>
	return:   long double
	*/
	long double NBVariance(const std::unordered_map<unsigned int, long double>& actualFrequency, const std::unordered_map<unsigned int, long double>& expectedFrequencies) {
		long double variance{};
		for (unsigned i = 1; i < 10; ++i) {
			variance += pow((actualFrequency.at(i) / expectedFrequencies.at(i) - 1.0), 2);
		}

		variance *= (1.0 / 9.0);
		return variance;
	}

	/*
	fn:		  NBDeviation
	brief:	  function for calculating NB standard deviation
	param:    long double
	return:   long double
	*/
	long double NBDeviation(long double nbvariance) const {
		return sqrt(nbvariance);
	}

	/*
	fn:		  NBRelationShip
	brief:	  function for finding the relationship of the NB standard deviation
	param:   long double, BoolSwitches object, Histogram object
	return:   void
	*/
	void NBRelationShip(const long double nbDivision, const BoolSwitches& switches, Histogram& color) const {
		constexpr double veryStrongRelationship = 0.1;
		constexpr double strongRelationship = 0.2;
		constexpr double moderateRelationship = 0.35;
		constexpr double weakRelationship = 0.5;

		if (switches.fancy)	color.setColor(4); //change the color font to red

		if (nbDivision < veryStrongRelationship)
			std::cout << "There is a very strong Benford relationship." << std::endl;
		else if (nbDivision < strongRelationship)
			std::cout << "There is a strong Benford relationship." << std::endl;
		else if (nbDivision < moderateRelationship)
			std::cout << "There is a moderate Benford relationship." << std::endl;
		else if (nbDivision < moderateRelationship)
			std::cout << "There is a weak Benford relationship." << std::endl;
		else if (nbDivision >= 0.5)
			std::cout << "There is not a Benford relationship." << std::endl;

		if (switches.fancy) 	color.resetColor(); //reset the color to white 
	}
};


