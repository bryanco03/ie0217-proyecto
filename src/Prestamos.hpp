#ifndef PRESTAMOS_HPP
#define PRESTAMOS_HPP

#include <string>

class Prestamos{
    protected:
        int duracionMeses;
        int cuotasPagadas = 0;
        double monto;
        float tasaInteres;
        std::string tipo;

    public:
        int ID;
        Prestamos(double monto, float tasaInteres, int duracionMeses, std::string tipo);
        void pagarCuota();
        void calcular();
};

#endif