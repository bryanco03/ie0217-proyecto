/**
 * \copyright Copyright 2024 Diego Alfaro, Bryan Cortes, Heiner Obando. All right reserved. This project is released under the MIT License
 * @file metodosBancoPrestamo.cpp
 * @date 15/02/2024
 * @author Diego Alfaro, Bryan Cortes, Heiner Obando
*/

#include "Banco.hpp"

CDP opcionesCDP(const double monto, const int opcion, const std::string ID);

void Banco::crearCDP(){

    int opcion; // Almacena la opcion de la prueba que se desea realizar
    std::cout << "\nSe dispone de 3 diferentes tipos de certificados a plazo" << std::endl;
    std::cout << "1. Si desea un certificado a plazo de 1 anno con 4.5% de intereses" << std::endl;
    std::cout << "2. Si desea un certificado a plazo de 2 annos con 7% de intereses" << std::endl;
    std::cout << "3. Si desea un certificado a plazo de 3 annos con 9% de intereses" << std::endl;
    
    // Se recibe la opcion elegida
    std:: cout << "Ingrese una opcion: " << std::endl;
    std::cin >> opcion; 

    /* Se obtiene el monto para el CDP. */
    std::cout << "\nIngrese el monto que desea depositar en el CDP: ";
    double monto; std::cin >> monto;

    /* Se genera el ID del prestamo. */
    std::string primeros3 = std::to_string((*this->usuarioActual).identificacion).substr(0, 3);
    std::string ID = "C-" + primeros3 + "-" + std::to_string(this->contadorCDP);

    /* Se aumenta contador de prestamos. */
    this->contadorCDP += 1;

    CDP cdp = opcionesCDP(monto, opcion, ID);
    cdp.generarCSV();

    this->usuarioActual->setCdp(cdp);

}


CDP opcionesCDP(const double monto, const int opcion, const std::string ID){

    double tasaIntereses;
    double duracionAnnos;
    // A partir de la opción del usuario se definen los intereses y el tiempo del CDP
    if(opcion == 1){
        tasaIntereses = 0.045;
        duracionAnnos = 1;
        return CDP(monto, tasaIntereses, duracionAnnos, ID);
    } else if (opcion == 2){
        tasaIntereses = 0.07;
        duracionAnnos = 2;
        return CDP(monto, tasaIntereses, duracionAnnos, ID);
    } else if (opcion == 3){
        tasaIntereses = 0.09;
        duracionAnnos = 3;
        return CDP(monto, tasaIntereses, duracionAnnos, ID);
    }
}

int main(){
    Banco inst;
    inst.iniciarContadores();
    Usuario instUsuario(2769427);
    inst.usuarioActual = &(instUsuario);
    inst.crearCDP();
    inst.crearCDP();
    return 0;
}