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

/**
 * @brief CDP: Clase que recibe los atributos para calcular las ganacias por un CDP
*/
class CDP {
    public:
        /**
        * @brief CDP: Constructor de la clase CDP
        * @param monto monto que se ingresara en el CDP
        * @param tasaIntereses tasa de interes que se pagara
        * @param duracionAnnos tiempo que durara el dinero en el CDP
        * @param montoGanado monto que ganara una vez terminado el contrato
        */
        CDP( double monto, float tasaIntereses, double duracionAnnos);
        
        /**
        * @brief calcularGanancia: Metodo que calculara la ganancia lograda con el CDP
        */
        void calcularGanancia();
        
        /**
        * @brief Metodo provisional para mostrar en el avance del proyecto
        */
        double getCdp();

    protected:
        double monto; /**< Se almacenara el monto a invertir en el CDP. */
        float tasaIntereses; /**< Se almacenara la tasa de intereses que se ganara. */
        double duracionAnnos; /**< Se almacenara la cantidad de meses que durara el CDP */
        double montoGanado; /**< Se almacenara el monto que ganara el cliente. */
};

#endif