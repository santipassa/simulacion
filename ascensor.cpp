#include "ascensor.h"
void ascensor::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//      %Name% is the parameter name
//	%Type% is the parameter type
piso=0;
sigma=INF;

}
double ascensor::ta(double t) {
//This function returns a double.
return sigma;
}
void ascensor::dint(double t) {
sigma=INF;
}
void ascensor::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition
//COMO LA VELOCIDAD ES CONSTANTE ES DE 1 PISO CADA 2 SEG SIGMA VALE 2.
int mensajeEntrante= *((int*)x.value);

if( mensajeEntrante==SUBIR){
	sigma=2;
	piso=piso+1;
	
	
}else if (mensajeEntrante==BAJAR){
	sigma=2;
	piso=piso-1;
}else{//entra la orden de parar
	sigma=INF;
}
}
Event ascensor::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)
printLog("PISO INFORMADO POR ASCENSOR %i\n",piso);
return Event(&piso,PUERTO0);
}
void ascensor::exit() {
//Code executed at the end of the simulation.

}
