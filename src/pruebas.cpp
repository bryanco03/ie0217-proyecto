#include "pruebas.hpp"
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <typeinfo>



void menupruebas(Usuario* usuario){
    int opcion;
    std::cout << "---Menu---"<< std::endl;
    std::cout << "1. Crear cuenta"<< std::endl;
    std::cout << "2. prestamos"<< std::endl;
    std::cout << "3. Certificado de plazo"<< std::endl;
    std::cout << "4. Mostrar datos de la cuenta"<< std::endl;
    std::cout << "5. Salir "<< std::endl;
    std::cout << "Ingrese una opcion: ";
    std::cin >> opcion;

    switch(opcion){
    case 1:
        crearCuenta(usuario);
        break;
    case 2:
        PruebasPrestamos(usuario);
        break;
    case 3:
        PruebasClaseCDP(usuario);
        break;
    case 4:
        mostrarDatosUsuario(usuario);
        break;
    case 5:
        exit(0);
        break;
    default:
        break;
    }



}

void crearCuenta(Usuario* usuario){
    bool esDolar;
    int opcion;
    std::cout << "La cuenta es en:" << std::endl;
    std::cout << "1. Dolar" << std::endl;
    std::cout << "2. Colon" << std::endl;
    std::cout << "ingrese una opcion: " << std::endl;
    std::cin >> opcion;
    if (opcion == 1){
        Cuenta cuenta;
        cuenta.dinero = 0.0;
        cuenta.esDolar = true;
        usuario->setCuentas(cuenta);
        std::cout << "Cuenta creada con exito"<< std::endl;
    }
    else if (opcion == 2){
        Cuenta cuenta;
        cuenta.dinero = 0.0;
        cuenta.esDolar = true;
        usuario->setCuentas(cuenta);
        std::cout << "Cuenta creada con exito"<< std::endl;
    }
}

void mostrarDatosUsuario(Usuario* usuario){
    
    std::cout << "---Cuentas---"<< std::endl;
    for ( const auto& cuenta : usuario->getCuentas()){
        std::cout << "---------------"<< std::endl;
        if (cuenta.esDolar){
            std::cout << "La cuenta es en dolares"<< std::endl;
        }
        else{
            std::cout << "La cuenta es Colones"<< std::endl;
        }
        std::cout << "Dinero: "<< cuenta.dinero<< std::endl;
        std::cout << "---------------"<< std::endl;
    }
    std::cout << "---CDP---"<< std::endl;
    for ( auto& cdp : usuario->getCdps()){
        std::cout << "---------------"<< std::endl;
        std::cout << "Informacion del CDP" << std::endl;
        double monto = cdp.getCdp();
        std::cout << "Monto Ganado: "<< monto << std::endl;
        std::cout << "---------------"<< std::endl;
    }    
    
    std::cout << "---Prestamos---"<< std::endl;
    for ( auto& prestamo : usuario->getPrestamos()){
        std::cout << "---------------"<< std::endl;
        std::cout << "Informacion del Prestamo" << std::endl;
        prestamo.calcular();
        std::cout << "---------------"<< std::endl;
    }
}
