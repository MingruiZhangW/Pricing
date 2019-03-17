#include "SimulationPrice.h"

const double OneOverRootTwoPi = 0.398942280401433;

SimulationPrice::SimulationPrice(
	double yearsToExpiry,
	double strike,
	double spot,
	double annualizedVolatility,
	double shortRate,
	unsigned long numberOfPaths):
	m_yearsToExpiry(yearsToExpiry),
	m_strike(strike),
	m_spot(spot),
	m_annualizedVolatility(annualizedVolatility),
	m_shortRate(shortRate)
{}

SimulationPrice::SimulationPrice() :
	m_yearsToExpiry(0.0),
	m_strike(0.0),
	m_spot(0.0),
	m_annualizedVolatility(0.0),
	m_shortRate(0) 
{}

double SimulationPrice::priceCallBySimulation()
{
	const double variance = m_annualizedVolatility * m_annualizedVolatility * m_yearsToExpiry;
	const double rootVariance = sqrt(variance);
	const double itoCorrection = -0.5 * variance;

	const double movedSpot = m_spot * exp(m_shortRate * m_yearsToExpiry + itoCorrection);
	double runningSum = 0.0;

	for (unsigned long i = 0; i < m_numberOfPaths; i++)
	{
		const double thisGaussian = getOneGaussianByBoxMuller(); // generate one normal variable
		double thisSpot = movedSpot * exp(rootVariance * thisGaussian);
		double intrinsicValue = thisSpot - m_strike;
		double thisPayoff = intrinsicValue > 0. ? intrinsicValue : 0.;
		runningSum += thisPayoff;
	}

	const double mean = runningSum / m_numberOfPaths;
	const double result = mean * exp(-m_shortRate * m_yearsToExpiry);

	return result;
}

// probability density for a standard Gaussian distribution
double SimulationPrice::normalDensity(double x)
{
	return OneOverRootTwoPi * exp(-x * x / 2);
}


// standard normal cumulative distribution function
double SimulationPrice::cumulativeNormal(double x)
{
	static double a[5] = { 0.319381530,
						  -0.356563782,
						   1.781477937,
						  -1.821255978,
						   1.330274429 };

	double result;

	if (x < -7.0)
		result = normalDensity(x) / sqrt(1. + x * x);

	else
	{
		if (x > 7.0)
			result = 1.0 - cumulativeNormal(-x);
		else
		{
			double tmp = 1.0 / (1.0 + 0.2316419*fabs(x));

			result = 1 - normalDensity(x)*
				(tmp*(a[0] + tmp * (a[1] + tmp * (a[2] + tmp * (a[3] + tmp * a[4])))));

			if (x <= 0.0)
				result = 1.0 - result;

		}
	}

	return result;
}



double SimulationPrice::getOneGaussianByBoxMuller()
{
	double result;

	double x;
	double y;

	double sizeSquared;
	do
	{
		x = 2.0*rand() / static_cast<double>(RAND_MAX) - 1;
		y = 2.0*rand() / static_cast<double>(RAND_MAX) - 1;
		sizeSquared = x * x + y * y;
	} while
		(sizeSquared >= 1.0);

	result = x * sqrt(-2 * log(sizeSquared) / sizeSquared);

	return result;

}

void SimulationPrice::yearsToExpiry_Set(double yearsToExpiry) {

	m_yearsToExpiry = yearsToExpiry;

}

double SimulationPrice::yearsToExpiry_Get() {

	return m_yearsToExpiry;

}

void SimulationPrice::strike_Set(double strike) {

	m_strike = strike;

}

double SimulationPrice::strike_Get() {

	return m_strike;

}

void SimulationPrice::spot_Set(double spot) {

	m_spot = spot;

}

double SimulationPrice::spot_Get() {

	return m_spot;

}

void SimulationPrice::annualizedVolatility_Set(double annualizedVolatility) {

	m_annualizedVolatility = annualizedVolatility;

}

double SimulationPrice::annualizedVolatility_Get() {

	return m_annualizedVolatility;

}

void SimulationPrice::shortRate_Set(double shortRate) {

	m_shortRate = shortRate;

}

double SimulationPrice::shortRate_Get() {

	return m_shortRate;

}

void SimulationPrice::numberOfPaths_Set(unsigned long numberOfPaths) {

	m_numberOfPaths = numberOfPaths;

}

unsigned long SimulationPrice::numberOfPaths_Get() {

	return m_numberOfPaths;

}