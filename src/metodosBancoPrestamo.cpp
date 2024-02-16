/**
 * \copyright Copyright 2024 Diego Alfaro, Bryan Cortes, Heiner Obando. All right reserved. This project is released under the MIT License
 * @file metodosBancoPrestamo.cpp
 * @date 15/02/2024
 * @author Diego Alfaro, Bryan Cortes, Heiner Obando
*/

#include "Banco.hpp"

Prestamos opcionesPrestamo(const double monto, const std::string tipo, const std::string ID);

void Banco::crearPrestamo(){
    /* Se obtiene la opción de prestamo a crear. */
    std::cout << "\nEscoja el tipo de prestamo a realizar: " << std::endl
              << "1. Personal" << std::endl
              << "2. Hipotecario" << std::endl
              << "3. Prendario" << std::endl;
    std::cout << "Ingrese la opcion: ";
    int opcion; std::cin >> opcion;

    /* Se obtiene el monto del prestamo. */
    std::cout << "\nIngrese el monto del prestamo: ";
    double monto; std::cin >> monto;

    /* Se genera el ID del prestamo. */
    std::string primeros3 = std::to_string((*this->usuarioActual).identificacion).substr(0, 3);
    std::string ID = "P-" + primeros3 + "-" + std::to_string(this->contadorPrestamos);
    
    /* Se aumenta contador de prestamos. */
    this->contadorPrestamos += 1;

    Prestamos* prestamo;
    switch (opcion) {
    case 1:{
        Prestamos inst =  opcionesPrestamo(monto, "Personal", ID);
        prestamo = &inst;
        break;
        }
    case 2:{
        Prestamos inst = opcionesPrestamo(monto, "Hipotecario", ID);
        prestamo = &inst;
        break;
        }
    case 3:{
        Prestamos inst = opcionesPrestamo(monto, "Prendario", ID);
        prestamo = &inst;
        break;
        }
    default:{
        break;
        }
    }

    (*prestamo).generarCSV();
    this->usuarioActual->setPrestamo(*prestamo);
}


void Banco::mostrarInfoPrestamos(){
    
}


Prestamos opcionesPrestamo(const double monto, const std::string tipo, const std::string ID){
    /* Se definen los meses e intereses dependiendo del tipo de prestamo. */
    std::vector<int> meses;
    std::vector<int> intereses;

    if(tipo == "Personal"){
        meses.insert(meses.end(), {5, 10, 12});
        intereses.insert(intereses.end(), {15, 7, 5});
    } else if (tipo == "Hipotecario") {
        meses.insert(meses.end(), {12, 24, 36});
        intereses.insert(intereses.end(), {15, 10, 5});
    } else if (tipo == "Prendario"){
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
        return Prestamos(monto, intereses[0], meses[0], tipo, ID);
        break;

    case 2:
        return Prestamos(monto, intereses[1], meses[1], tipo, ID);
        break;

    case 3:
        return Prestamos(monto, intereses[2], meses[2], tipo, ID);
        break;
    default:
        break;
    }
}

int main(){
    Banco inst;
    Usuario instUsuario(12345678);
    inst.usuarioActual = &(instUsuario);
    inst.crearPrestamo();
    return 0;
}