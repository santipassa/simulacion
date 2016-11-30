//CPP:proyecto-ascensor/controlador.cpp
#if !defined controlador_h
#define controlador_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "proyecto-ascensor/includes/includes.h"


class controlador: public Simulator { 
// Declare the state,
// output variables
// and parameters
double sigma;
int pisoActual;
int pisoDestino;
int informeTablero;
int mensajeTablero;
int accionASC;


public:
	controlador(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif
