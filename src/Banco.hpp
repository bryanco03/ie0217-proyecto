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
    public:
    void loggearUsuario();
    void menuAtencionCliente();

    /**
    * @brief Generar el menú del modo de información general.
    * 
    */
    void menuInformacionGeneral();

    /**
     * @brief Crear archivos de registro (usuarios.csv, Prestamos.csv, etc) si no existen.
     * 
     */
    void iniciarArchivos();


    private:
    Usuario* usuarioActual;     /**< Puntero a usuario que esta iniciado en la sesión. */
    int contadorCDP;            /**Contador para ID de los CDP*/
    int contadorPrestamos;      /**< Contador para ID de prestamos. */
    bool usuarioLogeado;        /**< */

    /*************************************************

                    Métodos globales
    
    **************************************************/

    /**
     * @brief Iniciar los contadores contadorCDP y contadorPrestamos.
     * 
     */
    void iniciarContadores();

    void cargarDatosUsuario();
    std::vector<std::string> obtenerDatos();

    /**
     * @brief Actualizar datos de un usuario en datos/usuarios.csv
     * 
     */
    void actualizarUsuarios();

    /**
     * @brief Registrar una transacción hecha en datos/registro.log
     * 
     * @param informacion Linea a escribir en el registro.
     */
    void registrarTrasaccion(const std::string& informacion);


    /*************************************************

            Métodos relacionados a usuarios
    
    **************************************************/
    bool verificarIdentificacionNombreEnCSV(unsigned long int identificacionBuscada, std::string nombreBuscar);
    bool verificarIdentificacioEnCSV(unsigned long int identificacionBuscada);


    /*************************************************

            Métodos relacionados a las cuentas
    
    **************************************************/
    void crearCuenta();
    void registrarCuenta(bool esDolar);
    std::vector<std::string> obtenerDatos(unsigned long int identificacion);
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
    void depositoEntreCuentas(Cuenta cuentaDepositar, Cuenta cuenaRetirar);
    void realizarTransaccion();
    bool pagarCuotasCuentas(double montoCuota, std::string moneda);


    /*************************************************

            Métodos relacionados a los prestamos
    
    **************************************************/

   /**
    * @brief Muestra menú para crear un prestamo.
    * 
    * @param generico bool Indica si es un prestamo en el modo información general, default = false.
    */
    void crearPrestamo(bool generico = false);

    /**
     * @brief Muestra la información de prestamos de un usuario.
     * 
     */
    void mostrarInfoPrestamos();

    /**
     * @brief Muestra menú para pagar una cuota de un prestamo.
     * 
     */
    void pagarPrestamos();

    /**
     * @brief Crear un objeto prestamo de información guardada en datos/Prestamos.csv
     * 
     * @param idPrestamo std::string Id de un prestamo
     * @return Prestamos Objeto prestamo correspondiente al id.
     */
    Prestamos leerPrestamo(std::string idPrestamo);

    /**
     * @brief Cargar los prestamos de un usuario al iniciar sesión.
     * 
     * @param idPrestamos std::string String de ids de prestamos del usuario.
     */
    void cargarPrestamos(std::string idPrestamos);


    /*************************************************

            Métodos relacionados a los CDPs
    
    **************************************************/

    /**
     * @brief Mostrar un menú para crear un CDP.
     * 
     */
    void crearCDP();

    /**
     * @brief Mostrar menú para crear un CDP en modo información general.
     * 
     */
    void InfoGeneralCDP();

    /**
     * @brief Mostrar información de los CDP del usuario loggeado.
     * 
     */
    void mostrarInfoCDP();

    /**
     * @brief Cargar los CDP de un usuario al iniciar sesión.
     * 
     * @param idCDPs std::string String de ids de cdp del usuario.
     */
    void cargarCDPs(std::string idCDPs);

    /**
     * @brief Crear un objeto CDP de información guardada en el csv perteneciente al CDP.
     * 
     * @param idCDP std::string Id de un CDP.
     * @return CDP Objeto CDP correspondiente al id.
     */
    CDP leerCDP(std::string idCDP);
};


#endif