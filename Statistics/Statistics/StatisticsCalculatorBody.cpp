/*
* Name:		Leen Aboukhalil
* Purpose:	The provided class handles command-line switches to display instructions, version information, and formatting options. It reads and validates numerical input from a file or standard input, 
			storing valid numbers in a vector while handling errors based on user-specified options. This ensures proper input processing and program functionality for statistical analysis.
* Date:		21/JUNE/2024
*/

#include "StatisticsCalculatorHeader.hpp"

/*
fn:		  help
brief:	  function for printing the instructions of the program
param:    nothing
return:   void
*/
void help() {
	std::cout << "usage:" << std::endl << "stats [--(help|fancy|skipbad|version)] [file name]\n" << std::endl;
	std::cout << "         --help         display instructions" << std::endl;
	std::cout << "         --fancy        use ASCII characters and colors in the console for better output" << std::endl;
	std::cout << "         --skipbad      skip bad input values" << std::endl;
	std::cout << "         --version      show version number" << std::endl;
}

/*
fn:		  switchesState
brief:	  function for checking it the user write any switches in the command line
param:    string vector, BoolSwitches object
return:   void
*/
void switchesState(std::vector<std::string>& args, BoolSwitches& switches) {
	std::vector<std::string>::iterator it;
	it = find(begin(args), end(args), "--help"); //if there is a --help switch then print the menu and exit the program
	if (it != end(args)) {
		help();
		args.erase(it);
		exit(EXIT_SUCCESS);
	}

	it = find(begin(args), end(args), "--version"); //if there is --version print the version and exit the program
	if (it != end(args)) {
		std::cout << "2024.0.0" << std::endl;
		args.erase(it);
		exit(EXIT_SUCCESS);
	}

	it = find(begin(args), end(args), "--skipbad"); //if there is --skipbad it will skip the bad input like <g> 
	if (it != end(args)) {							//and it will continue it will not exit the program
		switches.skipbad = true;
		args.erase(it);
	}

	it = find(begin(args), end(args), "--fancy"); //if there is --fancy it will make the output looks better
	if (it != end(args)) {
		switches.fancy = true;
		args.erase(it);
	}
}

/*
fn:		  readInput
brief:	  function for reading from the file or cin stream and checking if everything s is good, if everything is good
		  it will store the numbers in a vector
param:    istream, long double vector, and BoolSwitches object
return:   void
*/
void readInput(std::istream& inputFile, std::vector<long double>& numberVector, BoolSwitches& switches) {
	std::string input{};
	long double number{};

	try {
		while (inputFile >> input) {
			std::istringstream isnumber(input);

			//if isnumber the string stream did not converting to a long double that mean it is not a number 
			if (!(isnumber >> number)) {

				//it the length of the number was larger than what long double can handle it will be out of range 
				if (number > std::numeric_limits<std::streamsize>::max()) {
					std::cerr << "Error: Out of range <" << input << "> rejected\n";
					if (!switches.skipbad) {
						inputFile.clear();
						inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						continue;
					}
					else break; //if --skipbad switch was in commad line it will just print the first out of range 
					//but if it was not it will print all the numbers that cause out of range 
				}

				//if the vector is empty it will print an error message 
				if (numberVector.empty() && number < std::numeric_limits<std::streamsize>::max())
					std::cerr << "Error: invalid input <" << input << "> rejected\n" << "Data set is empty!" << std::endl;
				else if (number < std::numeric_limits<std::streamsize>::max())
					std::cerr << "Error: invalid input <" << input << "> rejected" << std::endl;

				//if skipbad was ture it will skip the bad input and continue the program else it will exit 
				if (switches.skipbad)
					continue;
				else
					exit(0);
			}

			//if everything is okay it will store what in string stream to number variable 
			isnumber >> number;

			//if it was the number less than zero skip it and continue 
			if (number < 1) {
				std::cerr << "Error: non-positive <" << number << "> rejected" << std::endl;
				continue;
			}
			else
				numberVector.push_back(number);
		}
	}
	catch (std::out_of_range e) {
		std::cout << e.what();
	}
}