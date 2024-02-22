/**
 * @file Usuario.hpp
 * @author Diego Alfaro, Bryan Cortes, Heiner Obando
 * @brief Declaraciones de la clase usuario, y del struct Cuentas
 * @version 0.1
 * @date 2024-02-14
 * 
 * @copyright MIT License Copyright (c) 2024
 * 
 */


#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <vector>
#include <fstream>
#include <string>
#include "Prestamos.hpp"
#include "cdp.hpp"

/**
 * @brief struct Cuenta, almacena la informacion de una cuenta del usuario
 */
struct Cuenta
{
    double dinero;  /**< Se almacenara el dinero de la cuenta. */
    bool esDolar;  /**< Se almacenara si la cuenta es en dolar o colones*/
};

class Usuario{

        private:
        std::vector<Cuenta> cuentas;  /**< Vector que almacena las cuentas del usuario*/

        std::string nombre; /**< String que representa el nombre del usuario*/

        unsigned long int identificacion; /**< Numero que indenfitica al usuario*/

        std::vector<Prestamos> prestamos; /**< Vector que almacena los Prestamos solicitados por el usuario*/

        std::vector<CDP> cdps; /**< Vector que almacena los cpds solicitados por el usuario*/

        public:
            /**
            * @brief Costructor de Usuario asigna 
            * @param identificacion Numero que indentifica al usuario dentro del sistena
            */
            Usuario(unsigned long int identificacion, std::string nombre);  
            /**
             * @brief Método para obtener las cuentas del usuario
             * @return vector<Cuenta>  Vector que almacena las cuentas del usuario
             */
            std::vector<Cuenta> getCuentas();
            /**
             * @brief Método para obtener la indentificacion del usuario
             * @return unsigned long int  Numero que indenfitica al usuario
             */
            unsigned long int getIdentificacion();
            /**
             * @brief Método para obtener los prestamos  del usuario
             * @return vector<Prestamos>  Vector que almacena los prestamos solicitados por el usuario usuario
             */
            std::vector<Prestamos> getPrestamos();
            /**
             * @brief Método para obtener los cdp del usuario
             * @return vector<CDP> Vector que almacena los cdps solicitados por el usuario usuario
             */
            std::vector<CDP> getCdps();
            /**
             * @brief Agrega una cuenta al vector de cuentas del usuario
             * @param cuenta 
             */
            void setCuentas(Cuenta cuenta);
            /**
             * @brief Agrega una cuenta al vector de Prestamos del usuario
             * @param prestamo 
             */
            void setPrestamo(Prestamos prestamo);
            /**
             * @brief  Agrega un cdp al vector de cdps del usuario
             * @param cdp 
             */
            void setCdp(CDP cdp);
            /**
             * @brief Registra los datos del usuario en el archivo csv que contiene los datos de cada usuario registrado en el sistema
             * 
             */
            void registrarUsuario();
            /**
             * @brief Retorna el string almacenado que contiene el nombre del usuario
             * 
             * @return std::string nombre del usuario
             */
            std::string getNombre();

            /**
             * @brief Elimina las cuentas almacenadas en el vector cuentas
             * 
             */
            void limpiarCuentas();

};
#endif