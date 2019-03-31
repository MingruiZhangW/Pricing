#include "Process.h"

Process::Process(double r,
				 double sigma,
				 double T,
				 double S0) :
				 m_r(r),
				 m_sigma(sigma),
				 m_T(T),
				 m_S0(S0)
{}

double Process::bachelier_process() {

	m_ST = m_S0 * exp(m_r*m_T) + m_sigma * sqrt((exp(2 * m_r*m_T) - 1.) / 2. / m_r)*randomnumber();
	return m_ST;

}

double Process::randomnumber() {

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