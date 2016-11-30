#include "controlador.h"
void controlador::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//      %Name% is the parameter name
//	%Type% is the parameter type

//los el ascensor comienza en planta baja
pisoActual=0;
pisoDestino=0;
informeTablero=0;
mensajeTablero=0;
accionASC=0;
sigma=INF;

}
double controlador::ta(double t) {
//This functioretun returns a double.
return sigma;
}
void controlador::dint(double t) {
if(informeTablero==1){
	sigma=0;
}else{
	sigma=INF;
}
}
void controlador::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition
// por el puerto 0 de salida se comunica con el ascensor
int puerto = x.port;
int valor = *((int*)x.value);
if (puerto==PUERTO0){//ingresa algo desde el tablero
	pisoDestino= valor;
	printLog("ENTRA DESDE EL TABLERO AL CONTORLADOR : %i\n",pisoDestino);
	sigma=0;
}else if (puerto==PUERTO1){// ascensor informa piso
	pisoActual=valor;
	sigma=0;
}
}
Event controlador::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)
if(informeTablero==1){//le aviso al tablero que el ascensor ya paro asi le manda otro pedido
	informeTablero=0;	
	return Event(&mensajeTablero, PUERTO0);
}else{ 
	printLog("CONTROLADOR INFORMA: PISO ACTUAL: %i PISO DESTINO: %i \n",pisoActual,pisoDestino);
	informeTablero=1;
	if(pisoActual==pisoDestino){ //le aviso al ascensor que pare
		accionASC=PARAR;
		mensajeTablero=LIBRE;
		return Event(&accionASC, PUERTO1);
	}else if (pisoActual>pisoDestino){
		accionASC=BAJAR;
		mensajeTablero=OCUPADO;
		return Event(&accionASC, PUERTO1);
	}else{
		accionASC=SUBIR;
		mensajeTablero=OCUPADO;
		return Event(&accionASC, PUERTO1);
	}
}


}
void controlador::exit() {
//Code executed at the end of the simulation.

}
