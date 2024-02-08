#include "Usuario.hpp"

Usuario::Usuario(unsigned long int identificacion): identificacion(identificacion){}

unsigned long int Usuario::getIdentificacion(){
    return identificacion;
}

vector<Prestamo>  Usuario::getPrestamos(){
    return prestamos;
}
vector<CDP> Usuario::getCdps(){
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
void Usuario::setCdp(CDP cdp){
    cdps.push_back(cdp);
}

bool Usuario::verificarDinero(double dinero){
    for( auto& cuenta : cuentas){
        if (cuenta.dinero >= dinero){
            return true;
        }
    }
    return false;
}