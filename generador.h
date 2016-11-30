//CPP:proyecto-ascensor/includes/stoc1.cpp
//CPP:proyecto-ascensor/includes/mersenne.cpp
//CPP:proyecto-ascensor/generador.cpp
#if !defined generador_h
#define generador_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "proyecto-ascensor/includes/stoc1.h"
#include "proyecto-ascensor/includes/mersenne.h"
#include "proyecto-ascensor/includes/includes.h"


class generador: public Simulator { 
// Declare the state,
// output variables
// and parameters
double sigma;
int pisoGenerado;
int first;
StochasticLib1 *random;




















public:
	generador(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif
