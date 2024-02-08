#include "pruebas.hpp"
#include <stdexcept>
#include <iostream>
#include <iomanip>

void PruebasClaseCDP(Usuario* usuario){

    int opcion; // Almacena la opcion de la prueba que se desea realizar
    double monto; // Almacena monto que el usuario desea ingresar en el CDP
    double ganancia; // Almacena ganacia que recibe el cliente con el CDP

    // Se colocan 3 diferentes pruebas sobre el funcionamiento de la clase CDP
    // 6 meses, 1 anno y 2 annos
    std::cout << "\nSe dispone de 3 diferentes tipos de certificados a plazo" << std::endl;
    std::cout << "1. Si desea un certificado a plazo de 6 meses" << std::endl;
    std::cout << "2. Si desea un certificado a plazo de 1 anno" << std::endl;
    std::cout << "3. Si desea un certificado a plazo de 2 annos" << std::endl;
    std::cout << "4. Salir de la prueba" << std::endl;

    // Se recibe la opcion elegida
    std:: cout << "Ingrese una opcion: " << std::endl;
    std::cin >> opcion; 

    std::cout << std::fixed << std::setprecision(3);

    // Prueba de CDP a 6 meses, 4.5% de intereses
    if (opcion == 1){
        // Se recibe el monto que ingresa el usuario
        std::cout << "Ingrese el monto que desea colocar en su certificado: " << std::endl;
        std::cin >> monto;     
        // Se crea una excepcion que revisa si se ingresa un dato negativo o se ingresa 0  
        try {         
            if (monto <= 0) {
                throw std::runtime_error("Error: El valor recibido es invalido.");
            }
            /* 
            Se instancia la clase, se envia el monto, los intereses que gana el cliente
            y el tiempo, 6 meses se envian como 0.5, dada la formula utilizada para hacer
            el calculo
            */
            CDP opcionUno(monto, 0.045, 0.5);
            // Se llama al metodo que calcula la ganancia
            opcionUno.calcularGanancia();
            // Se obtiene la ganancia obtenida y se imprimen los resultados
            ganancia = opcionUno.getCdp();
            std::cout << "A 6 meses el CDP se trabaja a 4.5\% de intereses" << std::endl;
            std::cout << "Su ganacia con un monto de " << monto << " seria: " << ganancia - monto << std::endl;
            std::cout << "Recibiendo al final del plazo: " << ganancia << std::endl; 
            usuario->setCdp(opcionUno);
        } catch (const std::exception& e) {
		    std::cerr << e.what() << std::endl;
        }
    
    // Prueba de CDP a 1 anno, 7% de intereses
    } else if(opcion == 2){
        // Se recibe el monto que ingresa el usuario
        std::cout << "Ingrese el monto que desea colocar en su certificado: " << std::endl;
        std::cin >> monto; 
        // Se crea una excepcion que revisa si se ingresa un dato negativo o se ingresa 0  
        try {         
            if (monto <= 0) {
                throw std::runtime_error("Error: El valor recibido es invalido.");
            }
            /* 
            Se instancia la clase, se envia el monto, los intereses que gana el cliente
            y el tiempo, 1 anno se envian como 1, dada la formula utilizada para hacer
            el calculo
            */
            CDP opcionUno(monto, 0.07, 1);
            // Se llama al metodo que calcula la ganancia
            opcionUno.calcularGanancia();
            // Se obtiene la ganancia obtenida y se imprimen los resultados
            ganancia = opcionUno.getCdp();
            std::cout << "A 1 anno el CDP se trabaja a 7\% de intereses" << std::endl;
            std::cout << "Su ganacia con un monto de " << monto << " seria: " << ganancia - monto << std::endl;
            std::cout << "Recibiendo al final del plazo: " << ganancia << std::endl; 
            usuario->setCdp(opcionUno);

        } catch (const std::exception& e) {
		    std::cerr << e.what() << std::endl;
        }

    // Prueba de CDP a 2 annos, 9% de intereses
    } else if(opcion == 3){
        // Se recibe el monto que ingresa el usuario
        std::cout << "Ingrese el monto que desea colocar en su certificado: " << std::endl;
        std::cin >> monto;
        // Se crea una excepcion que revisa si se ingresa un dato negativo o se ingresa 0  
        try {         
            if (monto <= 0) {
                throw std::runtime_error("Error: El valor recibido es invalido.");
            }
            /* 
            Se instancia la clase, se envia el monto, los intereses que gana el cliente
            y el tiempo, 2 anno se envian como 2, dada la formula utilizada para hacer
            el calculo
            */
            CDP opcionUno(monto, 0.09, 2);
            // Se llama al metodo que calcula la ganancia
            opcionUno.calcularGanancia();
            // Se obtiene la ganancia obtenida y se imprimen los resultados
            ganancia = opcionUno.getCdp();
            std::cout << "A 2 annos el CDP se trabaja a 9\% de intereses" << std::endl;
            std::cout << "Su ganacia con un monto de " << monto << " seria: " << ganancia - monto << std::endl;
            std::cout << "Recibiendo al final del plazo: " << ganancia << std::endl;  
            usuario->setCdp(opcionUno);

        } catch (const std::exception& e) {
		    std::cerr << e.what() << std::endl;
        }

    } else if(opcion == 4){
        std::cout << "Saliendo de la prueba..." << std::endl;
        exit(0);
    }

}


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
        break;
    case 3:
        PruebasClaseCDP(usuario);
        break;
    case 4:

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
        if (cuenta.esDolar){
            std::cout << "La cuenta es en dolares"<< std::endl;
        }
        else{
            std::cout << "La cuenta es Colones"<< std::endl;
        }
        std::cout << "Dinero: "<< cuenta.dinero<< std::endl;
    }
    std::cout << "---CDP---"<< std::endl;
    for (const auto& cdp : usuario->getCdps()){
        std::cout << "Informacion del CDP" << std::endl;
        //std::cout << "Monto ganado: " << cdp.calcularGanancia() << std::endl;
    }
}
