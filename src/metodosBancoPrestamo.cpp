/**
 * \copyright Copyright 2024 Diego Alfaro, Bryan Cortes, Heiner Obando. All right reserved. This project is released under the MIT License
 * @file metodosBancoPrestamo.cpp
 * @date 15/02/2024
 * @author Diego Alfaro, Bryan Cortes, Heiner Obando
*/

#include "Banco.hpp"

Prestamos opcionesPrestamo(const double monto, const int tipo, const std::string ID);

void Banco::crearPrestamo(){
    /* Se obtiene la opción de prestamo a crear. */
    std::cout << "\nEscoja el tipo de prestamo a realizar: " << std::endl
              << "1. Personal" << std::endl
              << "2. Hipotecario" << std::endl
              << "3. Prendario" << std::endl;
    std::cout << "Ingrese la opcion: ";
    int tipo; std::cin >> tipo;

    /* Se obtiene el monto del prestamo. */
    std::cout << "\nIngrese el monto del prestamo: ";
    double monto; std::cin >> monto;

    /* Se genera el ID del prestamo. */
    std::string primeros3 = std::to_string((*this->usuarioActual).identificacion).substr(0, 3);
    std::string ID = "P-" + primeros3 + "-" + std::to_string(this->contadorPrestamos);

    /* Se aumenta contador de prestamos. */
    this->contadorPrestamos += 1;

    /* Se crea el prestamo. */
    Prestamos prestamo = opcionesPrestamo(monto, tipo, ID);
    prestamo.generarCSV();
    this->usuarioActual->setPrestamo(prestamo);
}


void Banco::mostrarInfoPrestamos(){
    
}


Prestamos opcionesPrestamo(const double monto, const int tipo, const std::string ID){
    /* Se definen los meses e intereses dependiendo del tipo de prestamo. */
    std::vector<std::string> tipos = {"Personal", "Hipotecario", "Prendario"};
    std::vector<int> meses;
    std::vector<int> intereses;

    if(tipo == 1){
        meses.insert(meses.end(), {5, 10, 12});
        intereses.insert(intereses.end(), {15, 7, 5});
    } else if (tipo == 2) {
        meses.insert(meses.end(), {12, 24, 36});
        intereses.insert(intereses.end(), {15, 10, 5});
    } else if (tipo == 3){
        meses.insert(meses.end(), {10, 20, 30});
        intereses.insert(intereses.end(), {13, 7, 5});
    }

    std::cout << "Escoja una de las siguientes opciones:" << std::endl
              << "1. " << meses[0] << " meses a " << intereses[0] << "% de interes." << std::endl
              << "2. " << meses[1] << " meses a " << intereses[1] << "% de interes." << std::endl
              << "3. " << meses[2] << " meses a " << intereses[2] << "% de interes." << std::endl;
    std::cout << "Ingrese la opcion: ";
    int opcion; std::cin >> opcion;

    switch (opcion) {
    case 1:
        return Prestamos(ID, tipos[0], monto, intereses[0], meses[0]);
        break;

    case 2:
        return Prestamos(ID, tipos[1], monto, intereses[1], meses[1]);
        break;

    case 3:
        return Prestamos(ID, tipos[2], monto, intereses[2], meses[2]);
        break;
    default:
        break;
    }
}

