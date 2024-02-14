/**
 * \copyright Copyright 2024 Diego Alfaro, Bryan Cortes, Heiner Obando. All right reserved. This project is released under the MIT License
 * @file mainAvance.cpp
 * @date 07/02/2024
 * @author Diego Alfaro, Bryan Cortes, Heiner Obando
*/

#include "pruebas.hpp"
#include "Usuario.hpp"
// Main encargado de llamar a las funcion que realiza las pruebas con la clase
int main() {

    unsigned long int identificacion;
    std::cout << "Ingrese su indentificacion:";
    std::cin >> identificacion;
    Usuario usuario(identificacion);


    std::cout << "\nSe procede a realizar una prueba sobre el funcionamiento de las clases\n";
    while(1){
        menupruebas(&usuario);
    }

    return 0;
}