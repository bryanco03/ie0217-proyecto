#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <vector>
#include "Prestamos.hpp"
#include "cdp.hpp"
using namespace std;

struct Cuenta
{
    double dinero;
    bool esDolar;
};

class Usuario{
public:
    Usuario(unsigned long int identificacion);  
    vector<Cuenta> cuentas;
    unsigned long int identificacion;
    vector<Prestamos> prestamos;
    vector<CDP> cdps;

    vector<Cuenta> getCuentas();
    unsigned long int getIdentificacion();
    vector<Prestamos> getPrestamos();
    vector<CDP> getCdps();
    void setCuentas(Cuenta cuenta);
    void setPrestamo(Prestamos prestamo);
    void setCdp(CDP cdp);
    bool verificarDinero(double dinero);
};



#endif