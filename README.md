Statistics and Benford's Law Calculator

- Overview
This program provides comprehensive statistical analysis of a dataset and evaluates its conformity to Benford's Law. It reads data from a file or standard input, 
performs various statistical calculations, and checks for the expected distribution of leading digits as per Benford's Law.

- Features
Statistical Analysis:
- **Range Calculation:** Determines the minimum and maximum values in the dataset.
- **Mean Calculation:** Computes the arithmetic mean.
- **Median Calculation:** Calculates the median value.
- **Variance Calculation:** Measures the dispersion of the dataset.
- **Standard Deviation Calculation:** Computes the standard deviation.
- **Mode Identification:** Finds the mode(s) and their frequencies.


- Benford's Law Analysis:
- **Expected Frequencies:** Computes the expected frequencies of leading digits according to Benford's Law.
- **Actual Frequencies:** Calculates the actual frequencies of leading digits in the dataset.
- **Variance Calculation:** Determines the variance between actual and expected frequencies.
- **Standard Deviation Calculation:** Computes the standard deviation of the variance.
- **Relationship Assessment:** Assesses and describes the strength of the Benford relat

- Histogram Generation:
Generates and prints histograms for visual representation of data.

Usage:

- Command Line Options
[executable file] [--help | --fancy | --skipbad | --version] [file name]
--help: Displays usage instructions. ![image](https://github.com/Leen-ak/Benford-And-Stats-Calculator/assets/109052421/f8a16d60-c01b-4f1d-953c-6b62920b925d)
--fancy: Display the output at the console with ASCII characters. ![image](https://github.com/Leen-ak/Benford-And-Stats-Calculator/assets/109052421/0a0e5bef-c975-47d4-9a1b-69ac2391befe)
--skipbad: Skips invalid input values and continues processing. ![image](https://github.com/Leen-ak/Benford-And-Stats-Calculator/assets/109052421/7b555917-57eb-49c4-a304-3c6e96fda92f)
--version: Displays the program version. ![image](https://github.com/Leen-ak/Benford-And-Stats-Calculator/assets/109052421/579f2039-09f0-4481-9fc4-f7600a137fa0)

- Examples of using the program:
[executable file] [command line options] [file name to read from]
1. Command line options are optional.
2. If no file name is provided, the program will prompt the user to enter the data manually.

- Dependencies
C++11 or higher
Standard Library headers: <iostream>, <string>, <vector>, <fstream>, <sstream>, <algorithm>, <iomanip>, <limits>, <cctype>, <map>, <numeric>, <iterator>, <unordered_map>

- Author
Leen Aboukhali
