#include "Banco.hpp"

void Banco::menuAtencionCliente(){
    int opcion;

    if (usuarioLogeado){
        std::cout << "Bienvenido" << usuarioActual->getNombre() << std::endl;
        std::cout << "1. Crear una cuenta"<< std::endl;
        std::cout << "2. Realizar un deposito"<< std::endl;
        std::cout << "3. Realizar un retiro"<< std::endl;
        std::cout << "4. Realizar una transferencia"<< std::endl;
        std::cout << "5. Pagar Cuotas de prestamo"<< std::endl;
        std::cout << "6. Solicitar Prestamo"<< std::endl;
        std::cout << "7. Solicitar certificado de plazo"<< std::endl;
        std::cout << "7. Solicitar certificado de plazo"<< std::endl; 
        std::cout << "Ingrese una opcion: ";
        std::cin >> opcion;
    }
    else{
        std::cout<<"Error, no se pudo loggear ningun usuario"<<std::endl;
    }
    delete usuarioActual;
}