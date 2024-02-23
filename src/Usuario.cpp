/**
 * @file Usuario.cpp
 * @author Diego Alfaro, Bryan Cortes, Heiner Obando
 * @brief Implementacion de los metodos de Usuario
 * @version 0.1
 * @date 2024-02-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "Usuario.hpp"

Usuario::Usuario(unsigned long int identificacion, std::string nombre): identificacion(identificacion), nombre(nombre){
    // registrarUsuario();
}

unsigned long int Usuario::getIdentificacion(){
    return identificacion;
}

std::vector<Prestamos>  Usuario::getPrestamos(){
    return prestamos;
}
std::vector<CDP> Usuario::getCdps(){
    return cdps;
}

std::vector<Cuenta> Usuario::getCuentas(){
    return cuentas;
}


void Usuario::setCuentas(Cuenta cuenta){
    cuentas.push_back(cuenta);

}

void Usuario::setPrestamo(Prestamos prestamo){
    prestamos.push_back(prestamo);
}

void Usuario::setCdp(CDP cdp){
    cdps.push_back(cdp);
}

void Usuario::registrarUsuario(){
        std::ofstream archivo("datos/usuarios.csv", std::ios_base::app); // Modo de apertura para añadir al final del archivo
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo "<< std::endl;
        return;
    }

    if (cuentas.size() == 0 ){
        archivo << nombre << "," << identificacion << "," << " "<< "," << 0 << "," << " "<< "," << 0 << "," << " "<< "," << " " << "\n";
    }
    archivo.close();
}

std::string Usuario::getNombre(){
    return nombre;
}

void Usuario::limpiarCuentas(){
    cuentas.clear();
}