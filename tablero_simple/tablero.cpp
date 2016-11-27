#include "tablero.h"
void tablero::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);

//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//      %Name% is the parameter name
//	%Type% is the parameter type
//estado inicial en espera de que alguien lo interrumpa
sigma=INF;
//ES UNA VARIABLE DE CONTROL PARA QUE LA PRIMERA VEZ ENTRE
first=1;





}
double tablero::ta(double t) {
return sigma;

}
void tablero::dint(double t) {
//se queda en espera hasta recibir otro evento
sigma=INF;
}
void tablero::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition
// puerto 0: generador
// puerto 1: ascensor
int puerto = x.port;
int valor = *((int*)x.value); 
printLog("INGRESA AL TABLERO %i POR EL PUERTO %i \n",valor,puerto);
if(puerto==PUERTO0){//el generador me envia un piso al que debo ir
	//encolo lo que entra
	cola.push(valor);
	
	if(first==1){
		sigma=0;
		first=0;
	}else{
		sigma=INF;
	}
//ENTRA ALGO PROVENIENTE DEL CONTROLADOR
}else if(puerto==PUERTO1){ //INFORME DE ESTADO DE ASCENSOR DESDE EL CONTROLADOR
	if (valor==LIBRE){
		if(cola.empty()){
		
		sigma=INF;
	}else{
		sigma=0;
	}
}
}else{
	sigma=INF;
}

}
Event tablero::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)
//manda lo que tiene encolado
int tope =cola.front();
cola.pop();
printLog("ENVIE AL CONTROLADOR \n");
return Event(&tope,PUERTO0);
}
void tablero::exit() {
//Code executed at the end of the simulation.

}
