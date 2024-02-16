#include "Banco.hpp"

<<<<<<< HEAD
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
=======
void Banco::iniciarContadores(){
    /* Se obtiene el contador de prestamo. */
    /* https://stackoverflow.com/questions/3072795/how-to-count-lines-of-a-file-in-c */
    std::ifstream inFile("datos//Prestamos.csv"); 
    this->contadorPrestamos = std::count(std::istreambuf_iterator<char>(inFile), 
                                         std::istreambuf_iterator<char>(), '\n') - 1;
    inFile.close();

    /* PARA AGREGAR LOS SUYOS SOLO COPIEN EL CÓDIGO Y CAMBIAN EL PATH DE inFile y el contador al que lo guardan. */
>>>>>>> prestamo
}