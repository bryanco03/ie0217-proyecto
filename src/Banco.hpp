/**
 * \copyright Copyright 2024 Diego Alfaro, Bryan Cortes, Heiner Obando. All right reserved. This project is released under the MIT License
 * @file Banco.hpp
 * @date 15/02/2024
 * @author Diego Alfaro, Bryan Cortes, Heiner Obando
*/

#ifndef BANCO_HPP
#define BANCO_HPP

#include "Prestamos.hpp"
#include "Usuario.hpp"


class Banco{
    private:

    int contadorPrestamos = 0;  /**< Contador par ID de prestamos. */
    Usuario* usuarioActual;      /**< Puntero a usuario que esta iniciado en la sesión. */

    public:
    void loggearUsuario();
    void crearPrestamo();
    void mostrarInfoPrestamos();
};

#endif