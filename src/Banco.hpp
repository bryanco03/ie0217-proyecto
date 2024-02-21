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
#include <stdexcept>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <regex>

#include "Prestamos.hpp"
#include "Usuario.hpp"
#include "Cdp.hpp"

bool isNum(std::string input);

class Banco{
    private:
    Usuario* usuarioActual;     /**< Puntero a usuario que esta iniciado en la sesión. */
    public:
    int contadorCDP;            /**Contador para ID de los CDP*/
    int contadorPrestamos;      /**< Contador para ID de prestamos. */
    bool usuarioLogeado;

    public:
    /* Métodos globales. */
    void iniciarContadores();
    void iniciarArchivos();
    void cargarDatosUsuario();
    std::vector<std::string> obtenerDatos();
    double convertirMoneda(double monto, bool enDolar);
    void actualizarUsuarios();
    void menuInformacionGeneral();
    void registrarTrasaccion(const std::string& informacion);

    /* Métodos relacionados a usuarios. */
    void loggearUsuario();
    bool verificarIdentificacionNombreEnCSV(unsigned long int identificacionBuscada, std::string nombreBuscar);
    void menuAtencionCliente();
    bool verificarIdentificacioEnCSV(unsigned long int identificacionBuscada);
    void registrarDeposito(double monto, std::string tipoCuenta);

    /* Métodos relacionados a las cuentas. */
    void crearCuenta();
    void registrarCuenta(bool esDolar);
    void cargarCuentas(std::string tipoCuenta1, double dineroCuenta1, std::string tipoCuenta2, double dineroCuenta2);
    void realizarDeposito();
    void mostrarInfoCuentas();
    void actualizarCuentas();
    void depositarCuentaColon(double dinero);
    void depositarCuentaDolar(double dinero);
    void realizarRetiro();

    /* Métodos relacionados a los prestamos. */
    void crearPrestamo(bool generico = false);
    void mostrarInfoPrestamos();
    void pagarPrestamos();
    Prestamos leerPrestamo(std::string idPrestamo);
    void cargarPrestamos(std::string idPrestamos);

    /* Métodos relacionados a los CDPs. */
    void crearCDP();
    void mostrarInfoCDP();
    void InfoGeneralCDP();
    CDP leerCDP(std::string idCDP);
    void cargarCDPs(std::string idCDPs);
};

#endif