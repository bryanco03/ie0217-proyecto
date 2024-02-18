#include "Banco.hpp"


void Banco::menuAtencionCliente(){
    int opcion;
    if (usuarioLogeado){
        cargarDatosUsuario();
        iniciarContadores();
    }
    while (1){
        if (usuarioLogeado){
            std::cout << "Bienvenido, " << usuarioActual->getNombre() << std::endl;
            std::cout << "1. Crear una cuenta"<< std::endl;
            std::cout << "2. Realizar un deposito"<< std::endl;
            std::cout << "3. Realizar un retiro"<< std::endl;
            std::cout << "4. Realizar una transferencia"<< std::endl;
            std::cout << "5. Pagar Cuotas de prestamo"<< std::endl;
            std::cout << "6. Solicitar Prestamo"<< std::endl;
            std::cout << "7. Solicitar certificado de plazo"<< std::endl;
            std::cout << "8. Mostrar información de prestamos" << std::endl;
            std::cout << "9. Atras"<< std::endl; 
            std::cout << "Ingrese una opcion: ";
            std::cin >> opcion;

            switch (opcion)
            {
            case 1:
                crearCuenta();
                break;
            case 5:
                pagarPrestamos();
                break;
            case 6:
                crearPrestamo();
                actualizarUsuarios();
                break;
            case 8:
                mostrarInfoPrestamos();
                break;
            case 9:
                delete usuarioActual;
                return;
                break;
            default:
                break;
            }
        }
    else{
        std::cout<<"Error, no se pudo loggear ningun usuario"<<std::endl;
    }
    }
    delete usuarioActual;

}

void Banco::menuInformacionGeneral(){
    bool generico = true;
    while (1) {
        std::cout << "\nBienvenido al menu de informacion general" << std::endl
              << "1. Generar un prestamo y su tabla. " << std::endl
              << "2. Mostrar informacion del prestamo." << std::endl
              << "3. Atras." << std::endl
              << "Digite una opcion: ";
        char opcion; std::cin >> opcion;

        switch (opcion) {
        case '1':{
            this->crearPrestamo(generico);
            std::cout << "\nSe ha generado su tabla en el archivo \"TABLA.csv\"" << std::endl;
            break;}
        case '2':{
            std::cout << "Información del prestamo generado: ";
            this->leerPrestamo("TABLA").mostrarInfo(generico);
            break;}
        default:
            return;
            break;
        }
    }
}

void Banco::iniciarContadores(){
    /* Se obtiene el contador de prestamo. */
    /* https://stackoverflow.com/questions/3072795/how-to-count-lines-of-a-file-in-c */
    std::ifstream inFile("datos//Prestamos.csv"); 
    this->contadorPrestamos = std::count(std::istreambuf_iterator<char>(inFile), 
                                         std::istreambuf_iterator<char>(), '\n') - 1;
    inFile.close();

    /* Se obtiene el contador de CDP. */
    /* https://stackoverflow.com/questions/3072795/how-to-count-lines-of-a-file-in-c */
    std::ifstream inFileCDP("datos//CDP.csv"); 
    this->contadorCDP = std::count(std::istreambuf_iterator<char>(inFileCDP), 
                                         std::istreambuf_iterator<char>(), '\n') - 1;
    inFileCDP.close();

    /* PARA AGREGAR LOS SUYOS SOLO COPIEN EL CÓDIGO Y CAMBIAN EL PATH DE inFile y el contador al que lo guardan. */
}