/**
 * \copyright Copyright 2024 Diego Alfaro, Bryan Cortes, Heiner Obando. All right reserved. This project is released under the MIT License
 * @file Banco.hpp
 * @date 15/02/2024
 * @author Diego Alfaro, Bryan Cortes, Heiner Obando
*/

#ifndef BANCO_HPP
#define BANCO_HPP
#include <algorithm>
#include <sstream>
#include "Prestamos.hpp"
#include "Usuario.hpp"
#include "Cdp.hpp"


class Banco{
    private:

    public:
    int contadorCDP; /**Contador para ID de los CDP*/
    int contadorPrestamos;  /**< Contador para ID de prestamos. */
    Usuario* usuarioActual;      /**< Puntero a usuario que esta iniciado en la sesión. */
    bool usuarioLogeado;

    public:
    void loggearUsuario();
    void crearPrestamo();
    void mostrarInfoPrestamos();
    bool verificarIdentificacionNombreEnCSV(unsigned long int identificacionBuscada, std::string nombreBuscar);
    void menuAtencionCliente();
    bool verificarIdentificacioEnCSV(unsigned long int identificacionBuscada);
    void iniciarContadores();
    void crearCuenta();
    void registrarCuenta(bool esDolar);
    void cargarDatosUsuario();
    std::vector<std::string> obtenerDatos();
    void cargarCuentas(std::string tipoCuenta1, double dineroCuenta1, std::string tipoCuenta2, double dineroCuenta2);
    void realizarDeposito();
    double convertirMoneda(double monto, bool enDolar);
    void registrarDeposito();
    void crearCDP();
    void mostrarInfoCDP();
    void pagarPrestamos();
    void loggearUsuario();
    void cargarPrestamos();
};

#endif