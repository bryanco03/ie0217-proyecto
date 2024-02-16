/**
 * \copyright Copyright 2024 Diego Alfaro, Bryan Cortes, Heiner Obando. All right reserved. This project is released under the MIT License
 * @file Prestamos.hpp
 * @date 14/02/2024
 * @author Diego Alfaro, Bryan Cortes, Heiner Obando
*/

#ifndef PRESTAMOS_HPP
#define PRESTAMOS_HPP

#include <string>
#include <iostream>
#include <cmath>
#include <fstream>


class Prestamos{
    private:
        double monto;           /**< Monto a pedir del Prestamo. */
        double cuotaMensual;    /**< Cuota mensual a pagar. */
        float tasaInteres;      /**< Tasa de interés anual del Prestamo. */
        int duracionMeses;      /**< Cantidad de meses a pagar de cuotas. */
        std::string tipo;       /**< Tipo de prestamo: Personal, Prendario o Hipotecario. */
        int cuotasPagadas = 0;  /**< Cantidad de cuotas ya pagadas del Prestamo. */
        std::string ID;         /**< Número ID del prestamo. */

    public:
        std::string estado;     /**< Estado del Prestamo: En proceso de pago o Pagado. */

        /**
         * @brief Constructor que inicializa un prestamo.
         * 
         * @param monto Monto a pedir del Prestamo.
         * @param tasaInteres Tasa de interés anual del Prestamo.
         * @param duracionMeses Cantidad de meses a pagar de cuotas.
         * @param tipo Tipo de prestamo: Personal, Prendario o Hipotecario.
         * @param ID Número ID del prestamo.
         * @param cuotasPagadas Cantidad de cuotas ya pagadas, default = 0.
         */
        Prestamos(double monto, float tasaInteres, int duracionMeses,
                  std::string tipo, std::string ID, int cuotasPagadas = 0);

        /**
         * @brief Método para generar el CSV de un prestamo.
         * 
         */
        void generarCSV();

        /**
         * @brief Método para pagar una cuota del prestamo.
         * 
         */
        void pagarCuota();

        /**
         * @brief Método para calcular/retornar información del Prestamo.
         * 
         */
        void calcular();

        std::string getID();


};

#endif