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
    Usuario* usuarioActual;      /**< Puntero a usuario que esta iniciado en la sesión. */
    public:
    int contadorCDP; /**Contador para ID de los CDP*/
    int contadorPrestamos;  /**< Contador para ID de prestamos. */
    //Usuario* usuarioActual;      /**< Puntero a usuario que esta iniciado en la sesión. */
    bool usuarioLogeado;

    public:
    void loggearUsuario();
    void crearPrestamo(bool generico = false);
    void mostrarInfoPrestamos();
    bool verificarIdentificacionNombreEnCSV(unsigned long int identificacionBuscada, std::string nombreBuscar);
    void menuAtencionCliente();
    bool verificarIdentificacioEnCSV(unsigned long int identificacionBuscada);
    void iniciarContadores();
    void crearCuenta();
    void registrarCuenta(bool esDolar);
    void cargarDatosUsuario();
    std::vector<std::string> obtenerDatos(unsigned long int identificacion);
    void cargarCuentas(std::string tipoCuenta1, double dineroCuenta1, std::string tipoCuenta2, double dineroCuenta2);
    void realizarDeposito();
    double convertirMoneda(double monto, bool enDolar);
    void registrarDeposito(double monto, std::string tipoCuenta, unsigned long int identificacion);
    void crearCDP();
    void mostrarInfoCDP();
    void pagarPrestamos();
    Prestamos leerPrestamo(std::string idPrestamo);
    void cargarPrestamos(std::string idPrestamos);
    void actualizarUsuarios();
    void mostrarInfoCuentas(std::vector<Cuenta> cuentas, bool mostrarDinero = true);
    void actualizarCuentas();
    void depositarCuentaColon(double dinero);
    void depositarCuentaDolar(double dinero);
    void realizarRetiro();
    void menuInformacionGeneral();
    void registrarTrasaccion(const std::string& informacion);
    void InfoGeneralCDP();
    void depositoEntreCuentas(Cuenta cuentaDepositar, Cuenta cuenaRetirar);
    void realizarTransaccion();
    std::vector<Cuenta> cuentasTransferibles(unsigned long int identificacion);
    void transferenciaEfectivo(Cuenta cuenta , unsigned long int identificacion);
    void transfereciaEntreCuentas(Cuenta cuentaDepositar, Cuenta cuentaRetirar, unsigned long int identificacion);
    void cargarCDPs(std::string idCDPs);
    CDP leerCDP(std::string idCDP);
    bool pagarCuotasCuentas(double montoCuota, std::string moneda);
};


    
#endif