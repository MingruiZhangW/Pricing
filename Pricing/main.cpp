#include "SimulationPrice.h"
//#include <iostream>
#include <string>

//https://stackoverflow.com/questions/953710/inline-function-linker-error
template <typename T>
bool setValue(T &var);
void reset(
	double &spot,
	double &shortRate,
	unsigned long &numberOfPaths,
	double &annualizedVolatility,
	double &yearsToExpiry,
	bool &invalid_output
);

int main()
{
	SimulationPrice Price;

	std::cout << "Welcome to The BlackScholes Calculator" << std::endl;

	double spot{ 0.0 };
	double strike{ 0.0 };
	double shortRate{ 0.0 };
	double annualizedVolatility{ 0.0 };
	double yearsToExpiry{ 0.0 };
	unsigned long numberOfPaths { 0 };

	int CallPutType { 0 };
	bool invalid_output{ false };

	while (true) {

		std::cout << "Please enter the desired value for Spot" << std::endl;
		invalid_output = setValue<double>(spot);

		if (!invalid_output) {
			std::cout << "Inputted over 5 times, exit" << std::endl;
			invalid_output = true;
			break; 
		}
		Price.spot_Set(spot);

		std::cout << "Please enter the desired value for Strike" << std::endl;
		invalid_output = setValue<double>(strike);

		if (!invalid_output) {
			std::cout << "Inputted over 5 times, exit" << std::endl;
			invalid_output = true;
			break;
		}
		Price.strike_Set(strike);

		std::cout << "Please enter the desired value for ShortRate" << std::endl;
		invalid_output = setValue<double>(shortRate);

		if (!invalid_output) {
			std::cout << "Inputted over 5 times, exit" << std::endl;
			invalid_output = true;
			break;
		}
		Price.shortRate_Set(shortRate);

		std::cout << "Please enter the desired value for the Number Of Paths" << std::endl;
		invalid_output = setValue<unsigned long>(numberOfPaths);

		if (!invalid_output) {
			std::cout << "Inputted over 5 times, exit" << std::endl;
			invalid_output = true;
			break;
		}
		Price.numberOfPaths_Set(numberOfPaths);

		std::cout << "Please enter the desired value for AnnualizedVolatility" << std::endl;
		invalid_output = setValue<double>(annualizedVolatility);

		if (!invalid_output) {
			std::cout << "Inputted over 5 times, exit" << std::endl;
			invalid_output = true;
			break;
		}
		Price.annualizedVolatility_Set(annualizedVolatility);

		std::cout << "Please enter the desired value for YearsToExpiry" << std::endl;
		invalid_output = setValue<double>(yearsToExpiry);

		if (!invalid_output) {
			std::cout << "Inputted over 5 times, exit" << std::endl;
			invalid_output = true;
			break;
		}
		Price.yearsToExpiry_Set(yearsToExpiry);

		std::cout << "Price Call :" << Price.priceCallBySimulation() << std::endl;

		std::cout << "Would you like to do that again? -> Yes 1 , No 0, Invalid input will exit" << std::endl;
		int in;
		std::cin >> in;

		// Check for failed extraction
		if (std::cin.fail()) // has a previous extraction failed?
		{
			// yep, so let's handle the failure
			std::cin.clear(); // put us back in 'normal' operation mode
			std::cin.ignore(32767, '\n'); // and remove the bad input
			std::cout << "Oops, that input is invalid.  Exit.\n";
		}
		else
		{

			std::cin.ignore(32767, '\n'); // and remove the potential bad input
			if (in != 0 && in != 1) { std::cout << "Oops, that input is invalid. Exit \n"; break; }

		}

		if (in == 0) { std::cout << "Exit->>>>>>>>>" << std::endl; break; }
		if (in == 1) { std::cout << "Continue->>>>>>>>" << std::endl; }
		reset(spot, shortRate,numberOfPaths, annualizedVolatility, yearsToExpiry, invalid_output);

	}

	return 0;
}

template <typename T>
bool setValue(T &var) {

	int loop_count{ 0 };

	while (loop_count < 5) {

		std::cin >> var;

		// Check for failed extraction
		if (std::cin.fail()) // has a previous extraction failed?
		{
			// yep, so let's handle the failure
			std::cin.clear(); // put us back in 'normal' operation mode
			std::cin.ignore(32767, '\n'); // and remove the bad input
			std::cout << "Oops, that input is invalid.  Please try again.\n";
		}
		else
		{

			std::string name;
			std::getline(std::cin, name);
			if (name.empty() && var >= 0){

				return true;

			}
			std::cout << "Oops, that input is invalid.  Please try again.\n";
			// the user can't enter a meaningless double value, so we don't need to worry about validating that

		}
		loop_count++;
	}

	return false;
}

void reset(double &spot,
	double &shortRate,
	unsigned long &numberOfPaths,
	double &annualizedVolatility,
	double &yearsToExpiry,
	bool &invalid_output
) {

	spot = 0.0;
	shortRate = 0.0;
	numberOfPaths = 0;
	annualizedVolatility = 0.0;
	yearsToExpiry = 0.0;
	invalid_output = false;

}