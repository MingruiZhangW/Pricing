#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>

class Process
{
public:

	Process(double r,
			double sigma,
			double T,
			double S0
	);
	~Process();

	double bachelier_process();
	double mean_reverting_process();

	//Getter
	double ST_Get() {
	
		return m_ST;

	}

private:

	double m_r;
	double m_sigma;
	double m_T; 
	double m_S0;
	double m_ST;

	double randomnumber();

};

#endif // !PROCESS_H

