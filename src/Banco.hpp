/**
 * @file Banco.hpp
 * @author Diego Alfaro, Bryan Cortes, Heiner Obando
 * @brief Declaración de clase Banco.
 * @version 0.1
 * @date 2024-02-15
 * 
 * @copyright MIT License Copyright (c) 2024
 * 
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


/**
 * @brief Clase que realiza las acciones del banco.
 * 
 */
class Banco{
    public:
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
    * @brief Generar el menú del modo de información general.
    * 
    */
    void menuInformacionGeneral();

    /**
     * @brief Crear archivos de registro (usuarios.csv, Prestamos.csv, etc) si no existen.
     * 
     */
    void iniciarArchivos();
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

    /**
     * @brief Registrar una transacción hecha en datos/registro.log
     * 
     * @param informacion Linea a escribir en el registro.
     */
    void registrarTrasaccion(const std::string& informacion);

    /* Métodos relacionados a usuarios. */


    /*
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


    bool verificarIdentificacioEnCSV(unsigned long int identificacionBuscada);

    /*************************************************

            Métodos relacionados a las Cuentas
    
    **************************************************/


    /**
     * @brief Permite al usuario crear una cuenta en la moneda deseada (dólares o colones).
     * Si el usuario no tiene cuentas, se le permite crear una cuenta en la moneda que elija.
     * Si el usuario ya tiene una cuenta, se le permite crear una segunda cuenta en la moneda que no tenga.
     * Si el usuario ya tiene dos cuentas, se muestra un mensaje indicando que ya tiene el máximo permitido.
     * 
     */
    void crearCuenta();
    
    /**
     * @brief Registra una cuenta en el archivo de usuarios.
     * 
     * @param esDolar  Indica si la nueva cuenta es en dólares (true) o colones (false).
     */

    void registrarCuenta(bool esDolar);

    /**
     * @brief Carga las cuentas de un usuario con la informacion del archivo usuarios.csv
     * 
     * 
     * @param tipoCuenta1 Tipo de la primera cuenta ("dolar" o "colon").
     * @param dineroCuenta1 Monto de dinero de la primera cuenta.
     * @param tipoCuenta2 Tipo de la segunda cuenta ("dolar" o "colon").
     * @param dineroCuenta2 Monto de dinero de la segunda cuenta.
     */

    void cargarCuentas(std::string tipoCuenta1, double dineroCuenta1, std::string tipoCuenta2, double dineroCuenta2);

    /**
     * @brief Convierte un monto en colones a dolares o viceversa.
     * 
     * @param monto dinero a convertir
     * @param enDolar Indica si la conversion es de colones a dolares o dolares a colones
     * @return double dinero convertido a la moneda deseada.
     */
    double convertirMoneda(double monto, bool enDolar);


    /**
     * @brief Registra un depósito en la cuenta del usuario especificado por su identificacion.
     * 
     * @param monto Monto a depositar.
     * @param tipoCuenta Tipo de cuenta en la que se realizará el depósito ("dolar" o "colon").
     * @param identificacionBuscar Identificación del usuario en cuya cuenta se realizará el depósito.
     */
    

    void registrarDeposito(double monto, std::string tipoCuenta, unsigned long int identificacion);

    /**
    * @brief Muestra la información de las cuentas del usuario.incluyendo el tipo de moneda y, opcionalmente, el dinero disponible en cada cuenta.
    * 
    * @param cuentas Vector de cuentas del usuario.
    * @param mostrarDinero Indica si se debe mostrar el dinero disponible en cada cuenta.
    */

    void mostrarInfoCuentas(std::vector<Cuenta> cuentas, bool mostrarDinero = true);

    /**
     * @brief Realiza un depósito en una cuenta del usuario actual.
     * El usuario debe tener al menos una cuenta para poder realizar un depósito.
    * Se pueden realizar depósitos en efectivo o entre cuentas del mismo usuario.
     * @throws std::runtime_error si el usuario no tiene ninguna cuenta.
     * 
     */
    void realizarDeposito();
    /**
     * @brief  Realiza un depósito en la cuenta en colones del usuario actual.
     * Se solicita al usuario el monto a depositar y se registra la transacción.
     * 
     * @param dinero El saldo actual de la cuenta en colones.
     */
    void depositarCuentaColon(double dinero);
        /**
     * @brief  Realiza un depósito en la cuenta en Dolares del usuario actual.
     * Se solicita al usuario el monto a depositar y se registra la transacción.
     * 
     * @param dinero El saldo actual de la cuenta en Dolares.
     */

    void depositarCuentaDolar(double dinero);

    /**
     * @brief  Realiza un retiro de dinero de una o dos cuentas del usuario actual.
     * Se solicita al usuario seleccionar la cuenta y el monto a retirar.
     * Si el monto a retirar es mayor al saldo disponible en la cuenta, se muestra un mensaje de error.
     * Se registra la transacción y se actualiza el saldo de la cuenta.
     * 
     */
    void realizarRetiro();

    /**
     * @brief Obtiene las cuentas transferibles asociadas a un usuario identificado por su identificación.
     * Se obtienen los datos de las cuentas del usuario y se crea un vector de cuentas transferibles.
     * Cada cuenta transferible se representa como un objeto de la clase Cuenta con su tipo (dólar o colón)
     * y el saldo disponible en esa cuenta.
     * 
     * @param identificacion  La identificación del usuario del cual se obtendrán las cuentas transferibles.
     * @return std::vector<Cuenta> Un vector de cuentas transferibles asociadas al usuario.
     */
    std::vector<Cuenta> cuentasTransferibles(unsigned long int identificacion);

    /**
     * @brief  Realiza una transferencia de dinero en efectivo entre cuentas del banco.
     * 
     * @param cuenta cuenta La cuenta de destino de la transferencia.
     * @param identificacion  La identificación del usuario a quien se le realiza la transferencia.
     *  
     */

    void transferenciaEfectivo(Cuenta cuenta , unsigned long int identificacion);

    /**
     * @brief  Realiza una transferencia de dinero entre cuentas del banco.
     * 
     * @param cuenta cuentaDepositar La cuenta de destino de la transferencia.
     * @param cuenta cuentaRetirar La cuenta origen de la transferencia
     * @param identificacion  La identificación del usuario a quien se le realiza la transferencia.
     *  
     */

    void transferenciaEntreCuentas(Cuenta cuentaDepositar, Cuenta cuentaRetirar, unsigned long int identificacion);

    /**
     * @brief  Actualiza la información de los usuarios en el archivo CSV de usuarios.
     * Abre el archivo de usuarios y crea un nuevo archivo temporal para escribir los cambios.
     * Recorre cada línea del archivo, si encuentra la línea correspondiente al usuario actualiza sus datos con los nuevos valores.
     * Guarda los cambios en el nuevo archivo temporal y luego reemplaza el archivo original por el nuevo.
     * 
     */
    void actualizarCuentas();

    /**
     * @brief  Realiza un depósito entre dos cuentas del mismo usuario. Permite transferir dinero entre una cuenta en dólares y una cuenta en colones, o viceversa.
     * 
     * @param cuentaDepositar La cuenta a la que se realizará el depósito.
     * @param cuenaRetirar La cuenta de la que se retirará el dinero para el depósito.
     */


    void depositoEntreCuentas(Cuenta cuentaDepositar, Cuenta cuenaRetirar);

    /**
     * @brief Realiza una transacción entre cuentas del banco.
     * Se solicita la identificación de la persona a la cual se desea realizar la transacción. 
     * Se verifican las cuentas transferibles asociadas a esa persona.
     * Se ofrece la opción de realizar la transacción en efectivo o entre cuentas.
     * 
     */

    void realizarTransaccion();

    /**
     * @brief Realiza el pago de una cuota de un préstamo o cdp utilizando una de las cuentas del usuario actual.
     * 
     * @param montoCuota El monto a pagar.
     * @param moneda La moneda en la que se realiza el pago ("dolar" o "colon").
     * @return true Si el pago fue exitoso.
     * @return false si no es exitoso.
     */

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
     * @brief Ingresa el monto del prestamo a las cuentas del usuario.
     * 
     * @param monto Monto del prestamo.
     * @param moneda Tipo de moneda del prestamo.
     * @return true Si se recibió el dinero.
     * @return false Si no se recibió el dinero.
     */
    bool recibirPrestamo(double monto, std::string moneda);

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