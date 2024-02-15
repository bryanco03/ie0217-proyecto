/**
 * \copyright Copyright 2024 Diego Alfaro, Bryan Cortes, Heiner Obando. All right reserved. This project is released under the MIT License
 * @file metodosBancoPrestamo.cpp
 * @date 15/02/2024
 * @author Diego Alfaro, Bryan Cortes, Heiner Obando
*/

#include "Banco.hpp"


void Banco::crearPrestamo(){
    std::cout << "\nEscoja el tipo de prestamo a realizar: " << std::endl
              << "1. Personal" << std::endl
              << "2. Hipotecario" << std::endl
              << "3. Prendario" << std::endl;
    std::cout << "Ingrese la opcion: ";
    int opcion; std::cin >> opcion;

    std::cout << "\nIngrese el monto del prestamo: ";
    double monto; std::cin >> monto;

    switch (opcion) {
    case 1:{
        Prestamos prestamo = personal(monto);
        this->usuarioActual->setPrestamo(prestamo);
        break;
        }

    case 2:{
        Prestamos prestamo = hipotecario(monto);
        this->usuarioActual->setPrestamo(prestamo);
        break;
        }
    case 3:{
        Prestamos prestamo = prendario(monto);
        this->usuarioActual->setPrestamo(prestamo);
        break;
        }
    default:{
        break;
        }
    }
}


Prestamos personal(const double monto){
    std::cout << "Escoja una de las siguientes opciones:" << std::endl
              << "1. 5 meses a 15% de interes." << std::endl
              << "2. 10 meses a 7% de interes." << std::endl
              << "3. 12 meses a 5% de interes." << std::endl;
    std::cout << "Ingrese la opcion: ";
    int opcion; std::cin >> opcion;

    switch (opcion) {
    case 1:
        return Prestamos(monto, 15, 5, "Personal", "1001");
        break;

    case 2:
        return Prestamos(monto, 7, 10, "Personal", "1001");
        break;

    case 3:
        return Prestamos(monto, 5, 12, "Personal", "1001");
        break;
    default:
        return Prestamos(monto, 15, 5, "Personal", "1001");
        break;
    }
}


Prestamos hipotecario(const double monto){
    std::cout << "Escoja una de las siguientes opciones:" << std::endl
              << "1. 12 meses a 15% de interes." << std::endl
              << "2. 24 meses a 10% de interes." << std::endl
              << "3. 36 meses a 5% de interes." << std::endl;
    std::cout << "Ingrese la opcion: ";
    int opcion; std::cin >> opcion;

    switch (opcion) {
    case 1:
        return Prestamos(monto, 15, 12, "Hipotecario", "1001");
        break;

    case 2:
        return Prestamos(monto, 10, 24, "Hipotecario", "1001");
        break;

    case 3:
        return Prestamos(monto, 5, 36, "Hipotecario", "1001");
        break;
    default:
        return Prestamos(monto, 15, 12, "Hipotecario", "1001");
        break;
    }
}


Prestamos prendario(const double monto){
    std::cout << "Escoja una de las siguientes opciones:" << std::endl
              << "1. 10 meses a 13% de interes." << std::endl
              << "2. 20 meses a 7% de interes." << std::endl
              << "3. 30 meses a 5% de interes." << std::endl;
    std::cout << "Ingrese la opcion: ";
    int opcion; std::cin >> opcion;

    switch (opcion) {
    case 1:
        return Prestamos(monto, 13, 10, "Prendario", "1001");
        break;

    case 2:
        return Prestamos(monto, 7, 20, "Prendario", "1001");
        break;

    case 3:
        return Prestamos(monto, 5, 30, "Prendario", "1001");
        break;
    default:
        return Prestamos(monto, 13, 10, "Prendario", "1001");
        break;
    }
}