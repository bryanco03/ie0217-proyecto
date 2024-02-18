#include "funciones.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
void menuEntrada(Banco* banco){
    int opcion;
    std::cout << "\nBienvenido al sistema " << std::endl;
    std::cout << "1. Atencion al cliente " << std::endl;
    std::cout << "2. Informacion General " << std::endl;
    std::cout << "3. Salir " << std::endl;
    std::cout << "Elige una opcion: ";
    std::cin >> opcion;

    switch (opcion){
    case 1:
        banco->loggearUsuario();
        banco->menuAtencionCliente();
        break;
    case 2:
        banco->menuInformacionGeneral();
        break;
    case 3:
        exit(0);
        break;
    default:
        std::cout << "Opcion desconocida" << std::endl;
        break;
    }
}
