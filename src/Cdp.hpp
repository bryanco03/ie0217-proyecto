/**
 * @file Cdp.hpp
 * @author Diego Alfaro, Bryan Cortes, Heiner Obando
 * @brief Declaración de clase CDP.
 * @version 0.1
 * @date 2024-02-7
 * 
 * @copyright MIT License Copyright (c) 2024
 * 
 */

#ifndef CDP_HPP
#define CDP_HPP

#include <iostream>
#include <cmath>
#include <fstream>

/**
 * @brief Clase que recibe los atributos para calcular las ganacias por un CDP
*/
class CDP {
    private:
        double monto;           /**< Se almacenara el monto a invertir en el CDP. */
        float tasaIntereses;    /**< Se almacenara la tasa de intereses que se ganara. */
        double duracionAnnos;   /**< Se almacenara la cantidad de meses que durara el CDP */
        double montoGanado;     /**< Se almacenara el monto que ganara el cliente. */
        std::string ID;         /**< Número ID del CDP. */
        std::string moneda;     /**< Tipo de moneda usada para el CDP. */

    public:
        /**
        * @brief CDP: Constructor de la clase CDP, el mismo constructor calcula el monto final
        * @param monto monto que se ingresara en el CDP
        * @param tasaIntereses tasa de interes que se pagara
        * @param duracionAnnos tiempo que durara el dinero en el CDP
        * @param montoGanado monto que ganara una vez terminado el contrato
        * @param ID ID del usuario
        * @param moneda Tipo de moneda usada para el CDP.
        */
        CDP(double monto, float tasaIntereses, double duracionAnnos, std::string ID, std::string moneda);
        
        /**
         * @brief Metodo para generar el CSV de un CDP.
         * 
         */
        void generarCSV();

        /**
         * @brief Metodo para guardar información del CSV en un archivo de registro de los CDPs.
         * 
         */
        void guardarCSV();

        /**
         * @brief Metodo para obtener el monto ingresado en el CDP
         * 
         * @return Monto pedido del CDP
        */
        double getMonto();

        /**
         * @brief Metodo para obtener el interes ingresado en el CDP
         * 
         * @return Tasa de interes del CDP.
        */
        float getInteres();

        /**
         * @brief Metodo para obtener la duracion ingresada en el CDP
         * 
         * @return Cantidad de años del CDP
        */
        double getDuracion();

        /**
         * @brief Metodo para obtener el monto ganado para el CDP
         * 
         * @return Monto a ganar del CDP
        */
        double getMontoGanado();

        /**
         * @brief Metodo para obtener el monto ingresado en el CDP
         * 
         * @return Id del prestamo
        */
        std::string getID();

        /**
         * @brief Metodo para obtener el tipo de moneda del CDP.
         * 
         * @return std::string "dolar" o "colon"
         */
        std::string getMoneda();
};

#endif