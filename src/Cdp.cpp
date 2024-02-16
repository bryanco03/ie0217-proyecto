# include "Cdp.hpp"

CDP::CDP(double monto, float tasaIntereses, double duracionAnnos, std::string ID){

    // Se almacenan los valores recibidos por parte del usuario
    this->monto = monto;
    this->tasaIntereses = tasaIntereses;
    this->duracionAnnos = duracionAnnos;
    this->ID = ID;

}

void CDP::calcularGanancia(){

    /* 
    A partir de los datos recibidos se calculara la ganancia que
    recibira el cliente, se utiliza la formula que se encontro
    durante la investigacion para calcular el CDP, el metodo pow()
    se utiliza para realizar potencias en C++
    */
    montoGanado = monto * pow((1 + (tasaIntereses / 1)), 1 * duracionAnnos);

}

double CDP::getCdp(){
    // Devuelve el valor del monto ganado
    return montoGanado;
}