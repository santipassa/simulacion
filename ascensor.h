//CPP:proyecto-ascensor/ascensor.cpp
#if !defined ascensor_h
#define ascensor_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "proyecto-ascensor/includes/includes.h"


class ascensor: public Simulator { 
// Declare the state,
// output variables
// and parameters
double sigma;
int piso;
public:
	ascensor(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif
