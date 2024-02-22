/**
 * @file Prestamos.hpp
 * @author Diego Alfaro, Bryan Cortes, Heiner Obando
 * @brief Declaraciones de la clase Prestamos 
 * @version 0.1
 * @date 2024-02-14
 * 
 * @copyright MIT License Copyright (c) 2024
 * 
 */

#ifndef PRESTAMOS_HPP
#define PRESTAMOS_HPP

#include <string>
#include <iostream>
#include <cmath>
#include <fstream>


class Prestamos{
    private:
        std::string ID;         /**< Número ID del prestamo. */
        std::string tipo;       /**< Tipo de prestamo: Personal, Prendario o Hipotecario. */
        double monto;           /**< Monto a pedir del Prestamo. */
        std::string moneda;     /**< El tipo de moneda del monto. */
        float tasaInteres;      /**< Tasa de interés anual del Prestamo. */
        int duracionMeses;      /**< Cantidad de meses a pagar de cuotas. */
        int cuotasPagadas = 0;  /**< Cantidad de cuotas ya pagadas del Prestamo. */
        double cuotaMensual;    /**< Cuota mensual a pagar. */

    public:

        /**
         * @brief Constructor que inicializa un prestamo.
         * 
         * @param ID Número ID del prestamo.
         * @param tipo Tipo de prestamo: Personal, Prendario o Hipotecario.
         * @param monto Monto a pedir del Prestamo.
         * @param moneda El tipo de moneda del monto.
         * @param tasaInteres Tasa de interés anual del Prestamo.
         * @param duracionMeses Cantidad de meses a pagar de cuotas.
         * @param cuotasPagadas Cantidad de cuotas ya pagadas, default = 0.
         */
        Prestamos(std::string ID, std::string tipo, double monto, std::string moneda,
                  float tasaInteres, int duracionMeses, int cuotasPagadas = 0);

        /**
         * @brief Método para generar el CSV de un prestamo.
         * 
         */
        void generarCSV();

        /**
         * @brief Método para guardar información del CSV en un archivo de registro.
         * 
         */
        void guardarCSV();

        /**
         * @brief Método para pagar una cuota del prestamo.
         * 
         */
        void pagarCuota();

        /**
         * @brief Método para mostrar información del Prestamo.
         * 
         */
        void mostrarInfo(bool generico = false);

        /**
         * @brief Método para retornar el ID del prestamo.
         * 
         * @return std::string ID del prestamo.
         */
        std::string getID();

        /**
         * @brief Método para obtener la cuota a pagar del prestamo.
         * 
         * @return double Cuota mensual del prestamo, si ya fue pagado se retorna -1s.
         */
        double getCuota();

        /**
         * @brief Método para obtener el tipo de moneda del prestamo.
         * 
         * @return std::string dolares o colones.
         */
        std::string getMoneda();

        /**
         * @brief Método para imprimir la cantidad de cuotas que falta de pagar.
         * 
         * @return int Cantidad de cuotas que restantes.
         */
        int getCuotasRestantes();
};

#endif