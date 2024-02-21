#include "Banco.hpp"

std::string HoraActual();

void Banco::menuAtencionCliente(){
    int opcion;
    if (usuarioLogeado){
        cargarDatosUsuario();
        iniciarContadores();
    }
    while (1){
        if (usuarioLogeado){
            std::cout << "\nBienvenido, " << usuarioActual->getNombre() << std::endl;
            std::cout << "1. Crear una cuenta"<< std::endl;
            std::cout << "2. Realizar un deposito"<< std::endl;
            std::cout << "3. Realizar un retiro"<< std::endl;
            std::cout << "4. Realizar una transferencia"<< std::endl;
            std::cout << "5. Pagar Cuotas de prestamo"<< std::endl;
            std::cout << "6. Solicitar Prestamo"<< std::endl;
            std::cout << "7. Solicitar certificado de plazo"<< std::endl;
            std::cout << "8. Mostrar informacion de prestamos" << std::endl;
            std::cout << "9. Mostrar informacion de Cuentas" << std::endl;
            std::cout << "10. Mostrar informacion de CDP" << std::endl;
            std::cout << "11. Atras"<< std::endl; 
            std::cout << "Ingrese una opcion: ";
            std::cin >> opcion;

            switch (opcion){
            case 1:
                crearCuenta();
                break;
            case 2:
                realizarDeposito();
                break;
            case 3:
                realizarRetiro();
                break;
            case 4:
                realizarTransaccion();
                break;
            case 5:
                pagarPrestamos();
                break;
            case 6:
                crearPrestamo();
                actualizarUsuarios();
                break;
            case 7:
                crearCDP();
                actualizarUsuarios();
                break;
            case 8:
                mostrarInfoPrestamos();
                break;
            case 9:
                mostrarInfoCuentas(usuarioActual->getCuentas());
                break;
            case 10:
                mostrarInfoCDP();
                break;
            case 11:
                delete usuarioActual;
                return;
                break;
            default:
                break;
            }
        }
        else{
        std::cout<<"Error, no se pudo loggear ningun usuario"<<std::endl;
        break;
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
              << "3. Generar un CDP y su informacion." << std::endl
              << "4. Atras." << std::endl
              << "Digite una opcion: ";

        std::string input; std::cin >> input;
        int opcion = -1;

        if(isNum(input)){
            opcion = std::stoi(input);
        }

        switch (opcion) {
        case -1:
            std::cout << "ERROR: Debe ingresar un entero entre 1 y 4." << std::endl;
            break;
        case 1:{
            crearPrestamo(generico);
            break;}
        case 2:{
            Prestamos prestamo = this->leerPrestamo("TABLA");
            if(prestamo.getID() != "ERROR"){
                std::cout << "Informacion del prestamo generado: ";
                prestamo.mostrarInfo(generico);
            } else {
                std::cout << "No se ha generado el prestamo." << std::endl;
            }
            break;}
        case 3:
            InfoGeneralCDP();
            break;
        case 4:
            return;
            break;
        default:
            std::cout << "Opcion no valida, intente de nuevo." << std::endl;
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

double Banco::convertirMoneda(double monto, bool enDolares){
    if (enDolares){
        return monto / 515 ;
    }
    else{
        return monto * 515;
    }
}



void Banco::registrarTrasaccion(const std::string& informacion){
    
    /* Se abre el archivo .log donde se almacenara el registro */
    std::ofstream registro("datos\\registro.log", std::ios::app);

    /* Se comprueba que el .log sea accesible */
    if (!registro.is_open()) {
        std::cerr << "Error intentando abrir el archivo de registro de transacciones." << std::endl;
        return;
    }

    /* Se define la forma en que serán almacenados los registros */
    registro << HoraActual() << " - " << informacion << std::endl;
    
    registro.close();
}

/* Funcion encargada de ajustar y crear un string con la hora y fecha actual */
std::string HoraActual(){
    /* Se obtiene la hora que esta en el sistema actualmente */
    auto horaActual = std::chrono::system_clock::now();

    /* Se cambia el formato de la hora obtenida a un formato compatible */
    auto horaActualFormato = std::chrono::system_clock::to_time_t(horaActual);
    
    /* Se crea el objeto para obtener el string con el tiempo actual */
    std::stringstream tiempoActual;

    /* Se almacena la hora y fecha de salida con el formato elegido */
    tiempoActual << std::put_time(std::localtime(&horaActualFormato), "%d-%m-%Y %H:%M:%S");
    
    return tiempoActual.str();
}

bool isNum(const std::string input){
    const std::regex numerico("^([0-9]+)$");
    return (std::regex_match(input, numerico));
}
