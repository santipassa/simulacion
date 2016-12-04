//CPP:proyecto-ascensor/tablero.cpp
#if !defined tablero_h
#define tablero_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "proyecto-ascensor/includes/includes.h"


class tablero: public Simulator { 
// Declare the state,
// output variables
// and parameters
struct Tpedido {
	int valor;
	double ta;
};

std::queue<Tpedido> cola;
double sigma;
int turno;
int firstA1;
int firstA2;
int estadoAntA2;
int estadoAntA1;
int c1,c2;
int pisoSalida;
double sumatoriaTiempos;


public:
	tablero(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif
