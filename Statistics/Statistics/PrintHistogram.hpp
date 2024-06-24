/*
* Name:		Leen Aboukhalil
* Purpose:	In summary, the Histogram class is a utility for creating and displaying histograms that visually represent statistical data. 
			It includes options for enhanced visual output through the use of colors and ASCII characters, making the data easier to understand and interpret, 
			especially in the context of Newcomb-Benford's Law analysis.
* Date:		21/JUNE/2024
*/

#pragma once
#include "StatisticsCalculatorHeader.hpp"
#include "FrequencyCalculatorHeader.hpp"
#include <windows.h> 


class Histogram {
public:

	/*
	fn:		  printNBStat
	brief:	  function for printing the table of the frequencies
	param:    vector <long double>, map<unsigned int, long double>, unordered_map<unsigned int, long double>,
			  unordered_map<unsigned int, long double>, BoolSwitches object
	return:   void
	*/
	void printNBStat(const std::vector<long double>& numberVecctor,
		const std::map<unsigned int, long double>& rawFrequency,
		const std::unordered_map<unsigned int, long double>& expectedFrequency,
		const std::unordered_map<unsigned int, long double>& actualFrequency,
		BoolSwitches& switches) {

		printHeader(switches);

		if (longGraph(actualFrequency)) //there is 2 graph it depends of the frequencs if the frequency is bigger than 50
			switches.longGraph = true;  //it will print the longGraph whic is from 0 to 100

		printGraphLabels(switches);
		printGraphBar(expectedFrequency, actualFrequency, switches);
		printFooter(switches);
	}

private:
	static constexpr int DEFAULT_COLOR = 7; //to store white color
	static constexpr int COLOR_BLUE = 3; //to store blue color 
	static constexpr int GRAPH_CHAR = 254u; //to store an ASCII character 
	static constexpr int GRAPH_CHAR_SIMPLE = '#';
	static constexpr int GRAPH_CHAR_HEADER = '205'; //to store an ASCII character 

public:

	/*
	fn:		  programName
	brief:	  function for printing the program name with some validation
	param:    vector<long double>, BoolSwitches object
	return:   void
	*/
	void programName(std::vector<long double>& numberVector, BoolSwitches& switches) {
		if (numberVector.empty()) {
			std::cerr << "Data set is empty!\n";
			exit(0);
		}

		if (switches.fancy) {
			setColor(COLOR_BLUE);
			std::cout << "\nStandard Analysis\n";
			for (int i = 0; i < 66; ++i)
				std::cout << (char)205;   //to print an ASCII character 
			std::cout << std::endl;
			resetColor();
		}
		else if (!switches.fancy)
			std::cout << "\nStandard Analysis\n" << "==============================================================" << std::endl;
	}

	void printHeader(BoolSwitches& switches) {
		if (!switches.fancy) {
			std::cout << "\nStats (2024.0.0), Leen Aboukhalil" << std::endl;
			std::cout << "==============================================================" << std::endl;
		}
		else if (switches.fancy) {
			setColor(COLOR_BLUE);
			std::cout << "\nStats (2024.0.0), Leen Aboukhalil" << std::endl;
			for (int i = 0; i < 66; ++i)
				std::cout << (char)205;
			std::cout << std::endl;
		}

		if (switches.userInput)
			std::cout << "Enter real numbers. Terminate input with ^Z" << std::endl;

		if (switches.fancy)
			resetColor();
	}

	/*
	fn:		  setColor
	brief:	  function for changing the color font of the console font
	param:    int
	return:   void
	*/
	void setColor(int color) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, color);
	}

	/*
	fn:		  resetColor
	brief:	  function for changing the color of the font to white
	param:    nothing
	return:   void
	*/
	void resetColor() {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
	}

	/*
	fn:		  printProgramEnd
	brief:	  function for printing the footer of the program
	param:    BoolSwitches object
	return:   void
	*/
	void printProgramEnd(const BoolSwitches& switches) {
		if (switches.fancy) {
			setColor(COLOR_BLUE);
			for (int i = 0; i < 66; ++i)
				std::cout << (char)205;
			std::cout << std::endl << std::endl << std::endl;
			resetColor();
		}
		else if (switches.fancy)
			std::cout << "================================================================\n\n\n";
	}

	/*
	fn:		  printHeader
	brief:	  function for printing the header of the program
	param:    BoolSwitches object
	return:   void
	*/
	void printHeader(const BoolSwitches& switches) {
		if (!switches.fancy)
			std::cout << "Newcomb - Benford's Law Analysis\n================================================================\n\n";
		else if (switches.fancy) {
			setColor(COLOR_BLUE);
			std::cout << "Newcomb - Benford's Law Analysis\n";
			for (int i = 0; i < 66; ++i)
				std::cout << (char)GRAPH_CHAR_HEADER;
			std::cout << std::endl;
			resetColor();
		}
	}

	/*
	fn:		  longGraph
	brief:	  function for checking if we are using the long or short graph
	param:    unordered_map<unsigned int, long double>
	return:   bool
	*/
	bool longGraph(const std::unordered_map <unsigned int, long double>& actualFrequency) {
		unsigned count{};
		for (int i = 1; i < 10; i++) {
			if (actualFrequency.at(i) >= 50.0) {
				count++;
			}
		}
		if (count > 0) return true;
		else return false;
	}

	/*
	fn:		  printGraphLabels
	brief:	  function for printing graph labels based on it is long or short and if there is a switch or not
	param:    BoolSwitches object
	return:   void
	*/
	void printGraphLabels(const BoolSwitches& switches) {
		if (switches.longGraph && !switches.fancy)
			std::cout << "    exp digit   freq   0  10  20  30  40  50  60  70  80  90  100\n----------------------+---+---+---+---+---+---+---+---+---+---+" << std::endl;
		else if (!switches.longGraph && !switches.fancy)
			std::cout << "    exp digit   freq   0      10      20      30      40      50\n----------------------+---+---+---+---+---+---+---+---+---+---+" << std::endl;
		else if (switches.longGraph && switches.fancy) {
			std::cout << "    exp digit   freq  0   10  20  30  40  50  60  70  80  90  100" << std::endl;
			fancy();
		}
		else if (!switches.longGraph && switches.fancy) {
			std::cout << "    exp digit   freq   0      10      20      30      40       50\n";
			fancy();
		}
	}

	/*
	fn:		  fancy
	brief:	  function for making the output better with some ASCII characters
	param:    nothing
	return:   void
	*/
	void fancy() const {
		char c1 = char(196);
		char c2 = char(194);
		for (int i = 0; i < 22; ++i)
			std::cout << c1;
		for (int i = 0; i < 11; ++i)
			std::cout << c2 << c1 << c1 << c1;
		std::cout << std::endl;
	}

	/*
	fn:		  printGraphBar
	brief:	  function for printing graph bar characters
	param:    unordered_map<unsigned int, long double>, unordered_map<unsinged int, long double>, BoolSwitches object
	return:   void
	*/
	void printGraphBar(const std::unordered_map<unsigned int, long double>& expectedFrequency, const std::unordered_map<unsigned int, long double>& actualFrequency, const BoolSwitches& switches) {
		for (int i = 1; i < 10; ++i) {
			std::cout << std::fixed << std::setprecision(2);
			std::cout << std::right << std::setw(6) << expectedFrequency.at(i) << "% [" << i << "] = " << std::setw(6) << actualFrequency.at(i) << "% |";
			auto hashtagWeight = switches.longGraph ? 2.5 : 1.25;
			auto hashValue = static_cast<int>(floor(actualFrequency.at(i) / hashtagWeight));

			if (switches.fancy) {
				setColor(COLOR_BLUE);
				std::string hashChar(hashValue, static_cast<char>(GRAPH_CHAR));
				std::cout << hashChar << std::endl;
				resetColor();
			}
			else if (!switches.fancy) {
				std::string hashChar(hashValue, '#');
				std::cout << hashChar << std::endl;
			}
		}
	}

	/*
	fn:		  printFooter
	brief:	  function for printing the footer of the program
	param:    BoolSwitches object
	return:   void
	*/
	void printFooter(const BoolSwitches& switches) {
		if (switches.fancy) {
			for (int i = 0; i < 66; ++i)
				std::cout << (char)196;
			std::cout << std::endl;
		}
		else if (!switches.fancy)
			std::cout << "--------------------- +---+---+---+---+---+---+---+---+---+---+\n";
	}
};
