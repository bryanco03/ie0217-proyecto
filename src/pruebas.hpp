/**
 * \copyright Copyright 2024 Diego Alfaro, Bryan Cortes, Heiner Obando. All right reserved. This project is released under the MIT License
 * @file pruebasClaseCDP.hpp
 * @date 07/02/2024
 * @author Diego Alfaro, Bryan Cortes, Heiner Obando
*/

#ifndef PRUEBAS_HPP
#define PRUEBAS_HPP
#include "cdp.hpp"
#include "Usuario.hpp"
#include "Prestamos.hpp"


/**
 * @brief CDP: Funciones que realiza pruebas sobre las clases  
*/

void PruebasClaseCDP(Usuario* usuario);
void menupruebas(Usuario* usuario);
void crearCuenta(Usuario* usuario);
void mostrarDatosUsuario(Usuario* Usuario);
Prestamos personal(const double);
Prestamos hipotecario(const double);
Prestamos prendario(const double);
void PruebasPrestamos(Usuario* usuario);


#endif