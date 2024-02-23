/**
 * @file main.cpp
 * @author Diego Alfaro, Bryan Cortes, Heiner Obando
 * @brief Implementacion del main del programa
 * @version 0.1
 * @date 2024-02-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */


#include "Usuario.hpp"
#include "Banco.hpp"

int main(){
    Banco banco;
    banco.iniciarArchivos();
    while (1){
        /* Se imprime el menu. */
        std::cout << "\nBienvenido al sistema " << std::endl;
        std::cout << "1. Atencion al cliente " << std::endl;
        std::cout << "2. Informacion General " << std::endl;
        std::cout << "3. Salir " << std::endl;
        std::cout << "Elige una opcion: ";

        std::string input;
        int opcion = -1;
        
        std::cin >> input;

        if(isNum(input)){
            opcion = std::stoi(input);
        }

        switch (opcion){
        case -1:
            std::cout << "Debe ingresar un entero entre 1 y 3." << std::endl;
            break;
        case 1:
            banco.loggearUsuario();
            banco.menuAtencionCliente();
            break;
        case 2:
            banco.menuInformacionGeneral();
            break;
        case 3:
            exit(0);
            break;
        default:
            std::cout << "Opcion desconocida" << std::endl;
            break;
        }
    }
}

