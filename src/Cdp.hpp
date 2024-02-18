/**
 * \copyright Copyright 2024 Diego Alfaro, Bryan Cortes, Heiner Obando. All right reserved. This project is released under the MIT License
 * @file CDP.hpp
 * @date 07/02/2024
 * @author Diego Alfaro, Bryan Cortes, Heiner Obando
*/

#ifndef CDP_HPP
#define CDP_HPP

#include <iostream>
#include <cmath>
#include <fstream>

/**
 * @brief CDP: Clase que recibe los atributos para calcular las ganacias por un CDP
*/
class CDP {
    public:
        /**
        * @brief CDP: Constructor de la clase CDP, el mismo constructor calcula el monto final
        * @param monto monto que se ingresara en el CDP
        * @param tasaIntereses tasa de interes que se pagara
        * @param duracionAnnos tiempo que durara el dinero en el CDP
        * @param montoGanado monto que ganara una vez terminado el contrato
        * @param ID ID del usuario
        */
        CDP(double monto, float tasaIntereses, double duracionAnnos, std::string ID);
        
        /**
         * @brief Método para generar el CSV de un CDP.
         * 
         */
        void generarCSV();

        /**
         * @brief Método para guardar información del CSV en un archivo de registro de los CDPs.
         * 
         */
        void guardarCSV();

        /**
         * @brief Metodo para obtener el monto ingresado en el CDP
        */
        std::string getID();

    protected:
        double monto; /**< Se almacenara el monto a invertir en el CDP. */
        float tasaIntereses; /**< Se almacenara la tasa de intereses que se ganara. */
        double duracionAnnos; /**< Se almacenara la cantidad de meses que durara el CDP */
        double montoGanado; /**< Se almacenara el monto que ganara el cliente. */
        std::string ID;         /**< Número ID del CDP. */
};

#endif