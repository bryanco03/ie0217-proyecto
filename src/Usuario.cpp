#include "Usuario.hpp"

Usuario::Usuario(unsigned long int identificacion): identificacion(identificacion){}

unsigned long int Usuario::getIdentificacion(){
    return identificacion;
}

vector<Prestamo>  Usuario::getPrestamos(){
    return prestamos;
}
vector<Cdp> Usuario::getCdps(){
    return cdps;
}

vector<Cuenta> Usuario::getCuentas(){
    return cuentas;
}


void Usuario::setCuentas(Cuenta cuenta){
    cuentas.push_back(cuenta);
}

void Usuario::setPrestamo(Prestamo prestamo){
    prestamos.push_back(prestamo);
}
void Usuario::setCdp(Cdp cdp){
    cdps.push_back(cdp);
}
