#ifndef SIMULATION_PRICE
#define SIMULATION_PRICE

#include <cstdlib>
#include <cmath>
#include <iostream>

class SimulationPrice {

public:

	SimulationPrice(
		double yearsToExpiry,
		double strike,
		double spot,
		double annualizedVolatility,
		double shortRate,
		unsigned long numberOfPaths);
	SimulationPrice();

	double priceCallBySimulation();

	//Getter & Setter 
	void yearsToExpiry_Set(double yearsToExpiry);
	double yearsToExpiry_Get();
	void strike_Set(double strike);
	double strike_Get();
	void spot_Set(double spot);
	double spot_Get();
	void annualizedVolatility_Set(double annualizedVolatility);
	double annualizedVolatility_Get();
	void shortRate_Set(double shortRate);
	double shortRate_Get();
	void numberOfPaths_Set(unsigned long numberOfPaths);
	unsigned long numberOfPaths_Get();
	void type_Set(int type);
	int type_Get();
	void UpperLevel_Set(double UpperLevel);
	double UpperLevel_Get();
	void LowerLevel_Set(double LowerLevel);
	double LowerLevel_Get();

private:

	double m_yearsToExpiry;
	double m_strike;
	double m_spot;
	double m_annualizedVolatility;
	double m_shortRate;
	unsigned long m_numberOfPaths;
	double m_UpperLevel;
	double m_LowerLevel;
	int m_type;

	double normalDensity(double x);
	double cumulativeNormal(double x);
	double getOneGaussianByBoxMuller();
	double Cal_Change(double spot, int type);

};

#endif // !SIMULATION_PRICE
