#include "generador.h"
void generador::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//      %Name% is the parameter name
//	%Type% is the parameter type
random = new StochasticLib1(3);
sigma = random -> exponential(9);
pisoGenerado = random -> uniform(0,9);//(pb,pa)





}
double generador::ta(double t) {
return sigma;
}
void generador::dint(double t) {

pisoGenerado = random -> uniform(0,9);
sigma = random -> exponential(9);




}
void generador::dext(Event x, double t) {

}
Event generador::lambda(double t) {
return Event(&pisoGenerado,PUERTO0);

}
void generador::exit() {


}
