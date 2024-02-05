#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <vector>
#include "prestamo.hpp"
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
    vector<Prestamo> prestamos;
    vector<Cdp> cdps;

    vector<Cuenta> getCuentas();
    unsigned long int getIdentificacion();
    vector<Prestamo> getPrestamos();
    vector<Cdp> getCdps();
    void setCuentas(Cuenta cuenta);
    void setPrestamo(Prestamo prestamo);
    void setCdp(Cdp cdp);
    void verificarDinero(double dinero);
};



#endif