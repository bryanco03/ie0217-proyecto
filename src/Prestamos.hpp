#ifndef PRESTAMOS_HPP
#define PRESTAMOS_HPP

#include <string>
#include <iostream>
#include <cmath>
#include <fstream>

class Prestamos{
    private:
        double monto, cuotaMensual;
        float tasaInteres;
        int duracionMeses;
        std::string tipo;
        int cuotasPagadas = 0;

    public:
        std::string estado = "En proceso de pago.";
        std::string ID;
        Prestamos(double monto, float tasaInteres, int duracionMeses,
                  std::string tipo, std::string ID);
        void pagarCuota();
        void calcular();
};

#endif