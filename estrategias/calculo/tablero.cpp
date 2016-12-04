#include "tablero.h"
void tablero::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//      %Name% is the parameter name
//	%Type% is the parameter type
turno=1;
first=1;
estadoAntA2=LIBRE;
estadoAntA1=LIBRE;
sigma=INF;
c1=0;
c2=0;
ultimoPisoDestino1=0;
ultimoPisoDestino2=0;
pisoSalida=0;
sumatoriaTiempos=0;
printLog("ESTRATEGIA UTILIZADA: ASCENSOR MAS CERCANO AL PROXIMO PISO\n");
}
double tablero::ta(double t) {
//This function returns a double.
return sigma;
}
void tablero::dint(double t) {
sigma=INF;
}
void tablero::dext(Event x, double t) {
///////////////////////////////////////////
//ESTRATEGIA: LE MANDA LOS PEDIDOS AL ASCENSOR MAS CERCANO DEL PROXIMO PISO
///////////////////////////////////////////
//TIMESTAMP de correccion: 23300312
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition
// puerto 0: GENERADOR
// puerto 1: CONTROLADOR 1
// puerto 2 : CONTROLADOR 2
int puerto = x.port;
int valor = *((int*)x.value); 
int distanciaAlProximoA1,distanciaAlProximoA2;
if(puerto==PUERTO0){//el generador me envia un piso al que debo ir
	//encolo lo que entra
	printLog("TIEMPO ARRIBO %lf\n",t);
	printLog("ENTRA AL TABLERO DESDE EL GENERADOR: %i\n",valor);
	Tpedido p1;
	p1.valor=valor;
	p1.ta=t;
	cola.push(p1);
	if(first==1){// SIEMPRE EMPIEZA EL PRIMERO (da igual)
		first=0;
		turno=1;
		sigma=0;
	}else{
		sigma=INF;
	}
//ENTRA ALGO PROVENIENTE DE LOS CONTROLADORES
}else if(puerto==PUERTO1){ //INFORME DE ESTADO DE ASCENSOR DESDE EL CONTROLADOR_1
	estadoAntA1=valor;
	if(valor==LIBRE){
		if(cola.empty()){
			sigma=INF;//no hay nada en la cola, por lo tanto espero
		}else{
			//calculo las distancias para ambos
			distanciaAlProximoA1=abs(cola.front().valor-ultimoPisoDestino1);
			distanciaAlProximoA2=abs(cola.front().valor-ultimoPisoDestino2);
			if(distanciaAlProximoA1<=distanciaAlProximoA2){//si la distancia es menor le toca
				turno=1;
				sigma=0;
			}else if(estadoAntA2==LIBRE){//si la distancia es mayor y el otro estaba libre se lo doy al otro
				turno=2;
				sigma=0;
			}else{	//si no se cumple que la distancia sea menor y el otro este libre espero
				sigma=INF;
			}
		}
	}else{// si el ascensor informo que esta ocupado espero
		sigma=INF;
	}

}else if(puerto==PUERTO2){
	estadoAntA2=valor;
	if(valor==LIBRE){
		if(cola.empty()){
			sigma=INF;//no hay nada en la cola, por lo tanto espero
		}else{
			//calculo las distancias para ambos
			distanciaAlProximoA1=abs(cola.front().valor-ultimoPisoDestino1);
			distanciaAlProximoA2=abs(cola.front().valor-ultimoPisoDestino2);
			if(distanciaAlProximoA1>=distanciaAlProximoA2){//si la distancia es menor le toca
				turno=2;
				sigma=0;
			}else if(estadoAntA1==LIBRE){//si la distancia es mayor y el otro estaba libre se lo doy al otro
				turno=1;
				sigma=0;
			}else{	//si no se cumple que la distancia sea menor y el otro este libre espero
				sigma=INF;
			}
		}
	}else{// si el ascensor informo que esta ocupado espero
		sigma=INF;
	}





}
}
Event tablero::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)
//manda lo que tiene encolado
Tpedido tope =cola.front();
cola.pop();
if(turno==1){
	pisoSalida=tope.valor;
	c1++;
	ultimoPisoDestino1=tope.valor;
	printLog("TABLERO LE MANDA AL CONTROLADOR 1 %i\n",tope.valor);
	printLog("TIEMPO EN COLA %lf\n",t-tope.ta);
	sumatoriaTiempos+=t-tope.ta;
	return Event(&pisoSalida,PUERTO0);
}else if (turno==2){
	pisoSalida=tope.valor;
	c2++;
	ultimoPisoDestino2=tope.valor;
	printLog("TABLERO LE MANDA AL CONTROLADOR 1 %i\n",tope.valor);
	printLog("TIEMPO EN COLA %lf\n",t-tope.ta);
	sumatoriaTiempos+=t-tope.ta;
	return Event(&pisoSalida,PUERTO1);
}
}
void tablero::exit() {
//Code executed at the end of the simulation.
printLog("CANTIDAD DE PEDIDOS ENVIADOS A C1: %i\n",c1);
printLog("CANTIDAD DE PEDIDOS ENVIADOS A C2: %i\n",c2);
printLog("TIEMPO MEDIO EN COLA: %lf\n",(sumatoriaTiempos/(c1+c2)));
}
