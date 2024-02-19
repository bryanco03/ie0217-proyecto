/**
 * \copyright Copyright 2024 Diego Alfaro, Bryan Cortes, Heiner Obando. All right reserved. This project is released under the MIT License
 * @file metodosBancoCDP.cpp
 * @date 17/02/2024
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

    /* Se obtiene el objeto a partir de la funcion creada para este fin */
    CDP cdp = opcionesCDP(monto, opcion, ID);

    /* Se crea el CSV que almacena la informacion del CDP */
    cdp.generarCSV();

    /* Se definen los decimales de salida de los elementos en el .log */
    std::ostringstream montoReducido;
    montoReducido << std::fixed << std::setprecision(3) << cdp.getMonto();
    std::string montoReducidoStr = montoReducido.str();
    
    std::ostringstream interesReducido;
    interesReducido << std::fixed << std::setprecision(1) << cdp.getInteres()*100;
    std::string interesReducidoStr = interesReducido.str();

    std::ostringstream tiempoReducido;
    tiempoReducido << std::fixed << std::setprecision(0) << cdp.getDuracion();
    std::string tiempoReducidoStr = tiempoReducido.str();

    /* Se crea el string que sera enviado para almacenar en el .log para el registro de transacciones */
    std::string registro = "Creacion CDP, Usuario: " + std::to_string((*this->usuarioActual).identificacion) + ", ID: " +
    ID + ", Monto Ingresado: " + montoReducidoStr + ',' + " Tasa de interes: " + interesReducidoStr + ", Duracion del CDP: " +
    tiempoReducidoStr + " annos.";
    
    /* Se llama a la funcion que maneja el registro de transacciones */
    registrarTrasaccion(registro);

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

void Banco::InfoGeneralCDP(){
    int opcion; // Almacena la opcion de la prueba que se desea realizar
    
    std::cout << "\nSe dispone de 3 diferentes tipos de certificados a plazo" << std::endl;
    std::cout << "1. Si desea un certificado a plazo de 1 anno con 4.5% de intereses" << std::endl;
    std::cout << "2. Si desea un certificado a plazo de 2 annos con 7% de intereses" << std::endl;
    std::cout << "3. Si desea un certificado a plazo de 3 annos con 9% de intereses" << std::endl;
    
    // Se recibe la opcion elegida
    std::cout << "Ingrese una opcion: " << std::endl;
    std::cin >> opcion; 

    /* Se obtiene el monto para el CDP. */
    std::cout << "\nIngrese el monto que desea depositar en el CDP: ";
    double monto; std::cin >> monto;

    /* Se envia un ID predefinido para que no se cree un .csv del cdp */
    std::string ID = "MOSTRARINFO";

    /* Se crea el objeto */
    CDP cdp = opcionesCDP(monto, opcion, ID);

    /* Se imprime la informacion del CDP */
    std::cout << "Para un certificado de " << cdp.getMonto() <<
    " a un plazo de " << cdp.getDuracion() << " annos, la tasa utilizada es " <<
    cdp.getInteres()*100 << "%, recibiendo al final del plazo " << cdp.getMontoGanado() <<std::endl;

}

void Banco::mostrarInfoCDP(){

    /* Se imprimen los CDPs propios. */
    
    std::cout << "\n-----Información de sus certificados a plazo-----" << std::endl;
    /* Se imprimen los certificados a plazo del usuario que este loggeado en el sistema */
    for(auto& cdp: this->usuarioActual->cdps){
        /* Se imprime la informacion del CDP */
        std::cout << "ID del CDP: " << cdp.getID() <<
        ", Monto ingresado: " << cdp.getMonto() << ", Tasa de intereses: " <<
        cdp.getInteres()*100 << "%, Duracion: " << cdp.getDuracion() << 
        " annos, monto recibido al final del plazo: " << cdp.getMontoGanado() <<std::endl;
    }
    return;
}    


