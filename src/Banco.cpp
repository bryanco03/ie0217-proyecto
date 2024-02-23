#include "Banco.hpp"

std::string HoraActual();

void Banco::menuAtencionCliente(){
    try{
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

                if (std::cin.fail()){
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw  std::invalid_argument("Se ingreso un tipo de dato invalido.");
                }

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

                    /* Se eliminan los archivos privados del usuario. */
                    #if _WIN32
                        std::system("del datos\\P-*");
                        std::system("del datos\\C-*");
                    #elif __linux__
                        std::system("rm -f datos/P-*");
                        std::system("rm -f datos/C-*");
                    #endif

                    return;
                    break;
                default:
                    break;
                }
            }
            else{
            std::cout<<"Error, no se pudo loggear ningun usuario"<<std::endl;
            return;
            break;
            }
        }
        delete usuarioActual;
    }
    catch (const std::exception& e) {
        delete usuarioActual;
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Banco::menuInformacionGeneral(){
    /* Se vuelve a mostrar la tabla hecha anteriormente si existe. */
    Prestamos prestamo = this->leerPrestamo("TABLA");
    if(prestamo.getID() != "ERROR"){
        prestamo.generarCSV();
    }
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
            /* Se eliminan el archivo TABLA.csv . */
            #if _WIN32
                std::system("del datos\\TABLA.csv");
            #elif __linux__
                std::system("rm -f datos/TABLA.csv");
            #endif
            return;
            break;
        default:
            std::cout << "Opcion no valida, intente de nuevo." << std::endl;
            break;
        }
    }
}

void Banco::iniciarContadores(){
    /*
    Este método se basó en:
    https://stackoverflow.com/questions/3072795/how-to-count-lines-of-a-file-in-c
    */

    /* Se obtiene el contador de prestamo. */
    std::ifstream inFile("datos//Prestamos.csv"); 
    this->contadorPrestamos = std::count(std::istreambuf_iterator<char>(inFile), 
                                         std::istreambuf_iterator<char>(), '\n') - 1;
    inFile.close();

    /* Se obtiene el contador de CDP. */
    std::ifstream inFileCDP("datos//CDP.csv"); 
    this->contadorCDP = std::count(std::istreambuf_iterator<char>(inFileCDP), 
                                         std::istreambuf_iterator<char>(), '\n') - 1;
    inFileCDP.close();
}

void Banco::iniciarArchivos(){

    if(!std::ifstream("datos//usuarios.csv")){
        std::ofstream usuariosCrear("datos//usuarios.csv");
        usuariosCrear << "Nombre,Identificacion,TipoCuenta1,DineroCuenta1,TipoCuenta2,DineroCuenta2,IdPrestamos,IdCdps" << std::endl;
        usuariosCrear.close();
    }

    if(!std::ifstream("datos//Prestamos.csv")){
        std::ofstream prestamosCrear("datos//Prestamos.csv");
        prestamosCrear << "ID,Tipo,Monto,Moneda,Tasa Interes,Duracion Meses,Cuotas Pagadas" << std::endl;
        prestamosCrear.close(); 
    }

    if(!std::ifstream("datos//CDP.csv")){
        std::ofstream cdpCrear("datos//CDP.csv");
        cdpCrear << "ID,Monto ingresado,Intereses Ganados,Duracion del CDP,Monto Ganado,Moneda" << std::endl;
        cdpCrear.close(); 
    }

    if(!std::ifstream("datos//registro.log")){
        std::ofstream registroCrear("datos//registro.log");
        registroCrear << "Registro de transacciones:" << std::endl;
        registroCrear.close();
    }
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
    std::ofstream registro("datos/registro.log", std::ios::app);

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

/* Determina si un input es numérico por medio de regex. */
bool isNum(const std::string input){
    const std::regex numerico("^([0-9]+)$");
    return (std::regex_match(input, numerico));
}


bool Banco::pagarCuotasCuentas(double monto, std::string moneda ){
    try{

        
        if (usuarioActual->getCuentas().size() == 0){
            std::cout<<"No posees ninguna cuenta para realizar el pago" << std::endl;
            return false;
        }
        else if(usuarioActual->getCuentas().size() == 1){
            Cuenta cuenta = usuarioActual->getCuentas()[0];
            if (cuenta.esDolar){
                if (moneda == "dolar"){
                    if( monto > cuenta.dinero){
                        std::cout << "No posees con el sufiente dinero para pagar la cuota del prestamo"<< std::endl;
                        return false;
                    }
                    cuenta.dinero -= monto;
                    registrarDeposito(cuenta.dinero, "dolar", usuarioActual->getIdentificacion());
                    actualizarCuentas();
                    return true;
                }
                else if (moneda == "colon"){
                    double montoDolar =  convertirMoneda(monto, true);
                    if (montoDolar > cuenta.dinero){
                        std::cout << "No posees con el sufiente dinero para pagar la cuota del prestamo"<< std::endl;
                        return false;
                    }
                    cuenta.dinero -= montoDolar;
                    registrarDeposito(cuenta.dinero, "dolar", usuarioActual->getIdentificacion());
                    actualizarCuentas();
                    return true;
                }
            }
            else{
                if (moneda == "dolar"){
                    double montoColon = convertirMoneda(monto, false);
                    if( montoColon > cuenta.dinero){
                        std::cout << "No posees con el sufiente dinero para pagar la cuota del prestamo"<< std::endl;
                        return false;
                    }
                    cuenta.dinero -= montoColon;
                    registrarDeposito(cuenta.dinero, "colon", usuarioActual->getIdentificacion());
                    actualizarCuentas();
                    return true;
                }
                else if (moneda == "colon"){
                    if (monto > cuenta.dinero){
                        std::cout << "No posees con el sufiente dinero para pagar la cuota del prestamo"<< std::endl;
                        return false;
                    }
                    cuenta.dinero -= monto;
                    registrarDeposito(cuenta.dinero, "colon", usuarioActual->getIdentificacion());
                    actualizarCuentas();
                    return true;
                }
            }
        }
        else if (usuarioActual->getCuentas().size() == 2){
            int opcionCuenta;
            mostrarInfoCuentas(usuarioActual->getCuentas());
            std::cout << "Con Cual Cuenta deseas realizar el pago: ";
            std::cin >> opcionCuenta;
             if (std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw  std::invalid_argument("Se ingreso un tipo de dato invalido.");

            }
            Cuenta cuenta;
            if (opcionCuenta == 1){
                cuenta = usuarioActual->getCuentas()[0];
            }
            else if (opcionCuenta == 2){
                cuenta = usuarioActual->getCuentas()[1];
            }
            else{
                std::cout << "Opcion desconocida" << std::endl;
                return false;
            }
            if (cuenta.esDolar){
                if (moneda == "dolar"){
                    if( monto > cuenta.dinero){
                        std::cout << "No posees con el sufiente dinero para pagar la cuota del prestamo"<< std::endl;
                        return false;
                    }
                    cuenta.dinero -= monto;
                    registrarDeposito(cuenta.dinero, "dolar", usuarioActual->getIdentificacion());
                    actualizarCuentas();
                    return true;
                }
                else if (moneda == "colon"){
                    double montoDolar =  convertirMoneda(monto, true);
                    if (montoDolar > cuenta.dinero){
                        std::cout << "No posees con el sufiente dinero para pagar la cuota del prestamo"<< std::endl;
                        return false;
                    }
                    cuenta.dinero -= montoDolar;
                    registrarDeposito(cuenta.dinero, "dolar", usuarioActual->getIdentificacion());
                    actualizarCuentas();
                    return true;
                }
            }
            else{
                if (moneda == "dolar"){
                    double montoColon = convertirMoneda(monto, false);
                    if( montoColon > cuenta.dinero){
                        std::cout << "No posees con el sufiente dinero para pagar la cuota del prestamo"<< std::endl;
                        return false;
                    }
                    cuenta.dinero -= montoColon;
                    registrarDeposito(cuenta.dinero, "colon", usuarioActual->getIdentificacion());
                    actualizarCuentas();
                    return true;
                }
                else if (moneda == "colon"){
                    if (monto > cuenta.dinero){
                        std::cout << "No posees con el sufiente dinero para pagar la cuota del prestamo"<< std::endl;
                        return false;
                    }
                    cuenta.dinero -= monto;
                    registrarDeposito(cuenta.dinero, "colon", usuarioActual->getIdentificacion());
                    actualizarCuentas();
                    return true;
                }
            }
        }
        return false;
    }
     catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }
}
