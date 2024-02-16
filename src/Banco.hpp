/**
 * \copyright Copyright 2024 Diego Alfaro, Bryan Cortes, Heiner Obando. All right reserved. This project is released under the MIT License
 * @file Banco.hpp
 * @date 15/02/2024
 * @author Diego Alfaro, Bryan Cortes, Heiner Obando
*/

#ifndef BANCO_HPP
#define BANCO_HPP

#include <algorithm>

#include "Prestamos.hpp"
#include "Usuario.hpp"


class Banco{
    public:
    int contadorPrestamos = 0;  /**< Contador para ID de prestamos. */
    Usuario* usuarioActual;      /**< Puntero a usuario que esta iniciado en la sesión. */

    public:
    void crearPrestamo();
    void mostrarInfoPrestamos();
    void iniciarContadores();
};

#endif