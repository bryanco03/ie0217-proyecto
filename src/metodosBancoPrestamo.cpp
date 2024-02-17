/**
 * \copyright Copyright 2024 Diego Alfaro, Bryan Cortes, Heiner Obando. All right reserved. This project is released under the MIT License
 * @file metodosBancoPrestamo.cpp
 * @date 15/02/2024
 * @author Diego Alfaro, Bryan Cortes, Heiner Obando
*/

#include "Banco.hpp"

/* Funciones usadas por los métodos, que no son miembros de banco. */
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

Prestamos leerPrestamo(std::string idPrestamo){
    /* Se crean variables a usar. */
    std::string ID_CSV, linea;                      /*String de IDs y linea a leer del csv. */
    std::ifstream database("datos\\Prestamos.csv"); /* Se lee el archivo csv. */
    std::vector<std::string> infoP;                 /* Vector con la informacion del prestamo. */

    /* Se busca el prestamo. */
    while(std::getline(database, linea)){
        ID_CSV = linea.substr(0, linea.find(','));

        /* Si se encuentra se lee la linea y se guarda en infoP. */
        if(idPrestamo == ID_CSV){
            std::stringstream datos(linea);
            while(datos.good()){
                std::string columna;
                std::getline(datos, columna, ',');
                infoP.push_back(columna);
            }
        }
    }

    /* Se cierra el archivo.*/
    database.close();

    /* Si no se encontró el prestamo se imprime el error. */
    if(infoP.size() == 0){
        std::cout << "No se encontró ningún prestamo con ese Id" << std::endl;
        return Prestamos("ERROR", "", 1, 1, 1);
    }

    /* Si se encontró se crea el objeto y se paga el prestamo. */
    Prestamos prestamo(infoP[0], infoP[1], std::stod(infoP[2]), std::stof(infoP[3]),
                       std::stoi(infoP[4]), std::stoi(infoP[5]));
    
    return prestamo;
}

/* Métodos de Banco. */

void Banco::cargarPrestamos(){
    std::vector<std::string> idPrestamos;
    /* Continuar. */
}

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
    std::string primeros3 = std::to_string(this->usuarioActual->identificacion).substr(0, 3);
    std::string ID = "P-" + primeros3 + "-" + std::to_string(this->contadorPrestamos);

    /* Se aumenta contador de prestamos. */
    this->contadorPrestamos += 1;

    /* Se crea el prestamo. */
    Prestamos prestamo = opcionesPrestamo(monto, tipo, ID);
    prestamo.generarCSV();
    this->usuarioActual->setPrestamo(prestamo);
}

void Banco::mostrarInfoPrestamos(){
    /*
    std::cout << "\n-----Menu de mostrar prestamos-----" << std::endl;
    std::cout << "Ingrese identificacion de usuario para mostrar sus prestamos: ";
    unsigned long int id; std::cin >> id;
    */

    std::cout << "\n-----Información de prestamos-----" << std::endl;
    for(auto& prestamo: this->usuarioActual->prestamos){
        prestamo.mostrarInfo();
    }
}

void Banco::pagarPrestamos(){
    /* Se crean variables a usar. */
    std::string ID_P, ID_CSV, linea;                /*String de IDs y linea a leer del csv. */
    std::ifstream database("datos\\Prestamos.csv"); /* Se lee el archivo csv. */
    std::vector<std::string> infoP;                 /* Vector con la informacion del prestamo. */

    /* Se imprime el menu y se recibe el ID del prestamo a pagar. */
    std::cout << "\n-----Menu de pago de prestamos-----" << std::endl;
    std::cout << "Puede pagar cualquier prestamo (suyo o no) con el ID, estos tienen la forma \"P-123-0\". " << std::endl;
    std::cout << "Ingrese el ID del prestamo al que quiere pagar una cuota: ";
    std::cin >> ID_P;

    /* Se busca el prestamo. */
    while(std::getline(database, linea)){
        ID_CSV = linea.substr(0, linea.find(','));

        /* Si se encuentra se lee la linea y se guarda en infoP. */
        if(ID_P == ID_CSV){
            std::stringstream datos(linea);
            while(datos.good()){
                std::string columna;
                std::getline(datos, columna, ',');
                infoP.push_back(columna);
            }
        }
    }

    /* Se cierra el archivo, IMPORTANTE.*/
    database.close();

    /* Si no se encontró el prestamo se imprime el error. */
    if(infoP.size() == 0){
        std::cout << "No se encontró ningún prestamo con ese Id" << std::endl;
        return;
    }

    /* Si se encontró se crea el objeto y se paga el prestamo. */
    Prestamos prestamo(ID_P, infoP[1], std::stod(infoP[2]), std::stof(infoP[3]),
                       std::stoi(infoP[4]), std::stoi(infoP[5]));
    prestamo.pagarCuota();
}

int main(){
    Banco inst;
    inst.iniciarContadores();
    Usuario instUsuario(555555555);
    inst.usuarioActual = &(instUsuario);
    inst.crearPrestamo();
    inst.crearPrestamo();
    inst.pagarPrestamos();
    return 0;
}
