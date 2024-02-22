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
    /**
     * @brief Carga los datos del usuario actual desde un archivo CSV.
     *        Los datos incluyen el tipo de cuenta, el saldo de cada cuenta,
     *        los IDs de los préstamos y los CDPs del usuario.
     * 
     */
    void cargarDatosUsuario();
    /**
     * @brief Obtiene los datos de un usuario a partir de su identificación.
     * 
     * @param identificacionBuscar La identificación del usuario a buscar.
     * 
     * @return std::vector<std::string> vector de strings con los datos del usuario, o un vector vacío si no se encontró el usuario.
     */
    std::vector<std::string> obtenerDatos(unsigned long int identificacion);
    void actualizarUsuarios();
    void menuInformacionGeneral();
    void registrarTrasaccion(const std::string& informacion);

    /* Métodos relacionados a usuarios. */

    /**
     * @brief Interfaz para que el usuario se logee o registre en el sistema.
     * Si elige loggearse, se le pedirá su nombre y número de identificación,
     * y se verificará si los datos coinciden con un usuario registrado.
     * Si elige registrarse, se le pedirá su número de identificación y nombre,
     * y se verificará si el número de identificación ya está registrado.
     * Si no se encuentra el usuario o el número de identificación ya está registrado,
     * se mostrará un mensaje de error y no se permitirá el acceso.
     * 
     */
    void loggearUsuario();
    /**
     * @brief Verifica si la identificación y el nombre de un usuario se encuentran en el archivo CSV de usuarios.
     * 
     * @param identificacionBuscada 
     * @param nombreBuscar La identificación del usuario a buscar.
     * @return true Si la identificacion y el nombre coinciden.
     * @return false si no coinciden.
     */

    bool verificarIdentificacionNombreEnCSV(unsigned long int identificacionBuscada, std::string nombreBuscar);

    /**
     * @brief  Menú de atención al cliente que permite realizar diversas operaciones bancarias.
     * Si el usuario está logeado, carga sus datos y muestra las opciones del menú.
     * El usuario puede realizar acciones como crear una cuenta, realizar un depósito, realizar un retiro,
     * realizar una transferencia, pagar cuotas de préstamo, solicitar un préstamo, solicitar un certificado de plazo,
     * mostrar información de préstamos, mostrar información de cuentas, y mostrar información de certificados de plazo.
     * Si el usuario elige la opción "Atrás", se cierra la sesión y se libera la memoria del usuario actual. 
     *
     */

    void menuAtencionCliente();
    /**
     * @brief verifica si la identificación de un usuario se encuentran en el archivo CSV de usuarios.
     *
     * @param identificacionBuscada  Verifica si la identificación y el nombre de un usuario se encuentran en el archivo CSV de usuarios.
     * @return true Si se encontri la identificacion.
     * @return false si no se encontro.
     */
    bool verificarIdentificacioEnCSV(unsigned long int identificacionBuscada);

    /* Métodos relacionados a las cuentas. */

    /**
     * @brief Permite al usuario crear una cuenta en la moneda deseada (dólares o colones).
     * Si el usuario no tiene cuentas, se le permite crear una cuenta en la moneda que elija.
     * Si el usuario ya tiene una cuenta, se le permite crear una segunda cuenta en la moneda que no tenga.
     * Si el usuario ya tiene dos cuentas, se muestra un mensaje indicando que ya tiene el máximo permitido.
     * 
     */
    void crearCuenta();
    
    void registrarCuenta(bool esDolar);
    void cargarCuentas(std::string tipoCuenta1, double dineroCuenta1, std::string tipoCuenta2, double dineroCuenta2);
    double convertirMoneda(double monto, bool enDolar);
    void registrarDeposito(double monto, std::string tipoCuenta, unsigned long int identificacion);
    void mostrarInfoCuentas(std::vector<Cuenta> cuentas, bool mostrarDinero = true);
    void realizarDeposito();
    void depositarCuentaColon(double dinero);
    void depositarCuentaDolar(double dinero);
    void realizarRetiro();
    std::vector<Cuenta> cuentasTransferibles(unsigned long int identificacion);
    void transferenciaEfectivo(Cuenta cuenta , unsigned long int identificacion);
    void transfereciaEntreCuentas(Cuenta cuentaDepositar, Cuenta cuentaRetirar, unsigned long int identificacion);
    void actualizarCuentas();

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
    void depositoEntreCuentas(Cuenta cuentaDepositar, Cuenta cuenaRetirar);
    void realizarTransaccion();
    void cargarCDPs(std::string idCDPs);
    bool pagarCuotasCuentas(double montoCuota, std::string moneda);
    CDP leerCDP(std::string idCDP);
};


    
#endif