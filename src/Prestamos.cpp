#include "Prestamos.hpp"

Prestamos::Prestamos(double monto, float tasaInteres, int duracionMeses, std::string tipo)
    : monto(monto), tasaInteres(tasaInteres), duracionMeses(duracionMeses), tipo(tipo) {
    /* Incluir la ecuación para los préstamos y la escritura en el archivo .csv */
}

void Prestamos::pagarCuota(){
    /* Se lee el archivo y se pone como pagado la última cuota sin pagar, si es la última se establece como pagado. */
}

void Prestamos::calcular(){
    /* Se imprime la información del prestamo. */
}