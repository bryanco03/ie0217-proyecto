#include "Banco.hpp"
#include "Usuario.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


void Banco::loggearUsuario(){
    int opcion;
    std::cout << "Bienvenido a atencion a cliente " << std::endl;
    std::cout << "1. Loggearse " << std::endl;
    std::cout << "2. Registrarse " << std::endl;
    std::cout << "Elige una opcion: ";
    std::cin >> opcion;

    if (opcion == 1){
        unsigned long int identificacion;
        std::string nombre;
        std::cout << "Ingrese su nombre: ";
        std::cin >> nombre;
        std::cout << "Ingrese su indentificacion: ";
        std::cin >> identificacion;
        if (verificarIdentificacionNombreEnCSV(identificacion, nombre)){
            usuarioActual = new Usuario(identificacion,nombre);
            usuarioLogeado = true;
        }
        else{
            std::cout << "Error, el Nombre del usuario o identificacion no se encuentra en el registro." << std::endl;
            usuarioLogeado = false;
        }
    }
    else if(opcion == 2){
        unsigned long int identificacion;
        std::string nombre;
        std::cout << "Ingrese su numero de cedula: ";
        std::cin >> identificacion;
        if (verificarIdentificacioEnCSV(identificacion)){
            std::cout << "El numero de cedula ingresado ya habia sido registrado" << std::endl;
            usuarioLogeado = false;
        }
        else{
            std::cout << "Ingrese su nombre: ";
            std::cin >> nombre;
            std::cout << "Creando Usuario ..."<< std::endl;
            usuarioActual = new Usuario(identificacion,nombre);
            usuarioActual->registrarUsuario();
            usuarioLogeado = true;
        }
        
    }
}

bool Banco::verificarIdentificacionNombreEnCSV(unsigned long int identificacionBuscada, std::string nombreBuscar) {
    std::ifstream archivo("datos/usuarios.csv");
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo " << std::endl;
        return false;
    }

    // Ignorar la primera línea
    std::string primeraLinea;
    std::getline(archivo, primeraLinea);


    std::string linea;
    while (std::getline(archivo, linea)) {
        std::istringstream iss(linea);
        std::string nombre, identificacionStr, restoLinea;
        if (std::getline(iss, nombre, ',') && std::getline(iss, identificacionStr, ',') && std::getline(iss, restoLinea)) {
            unsigned long int identificacion = std::stoul(identificacionStr);
            if (identificacion == identificacionBuscada && nombre == nombreBuscar) {
                archivo.close();
                return true;
            }
        }
    }

    archivo.close();
    return false;
}

bool Banco:: verificarIdentificacioEnCSV(unsigned long int identificacionBuscada) {
    std::ifstream archivo("datos/usuarios.csv");
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo " << std::endl;
        return false;
    }

    // Ignorar la primera línea
    std::string primeraLinea;
    std::getline(archivo, primeraLinea);


    std::string linea;
    while (std::getline(archivo, linea)) {
        std::istringstream iss(linea);
        std::string nombre, identificacionStr, restoLinea;
        if (std::getline(iss, nombre, ',') && std::getline(iss, identificacionStr, ',') && std::getline(iss, restoLinea)) {
            unsigned long int identificacion = std::stoul(identificacionStr);
            if (identificacion == identificacionBuscada) {
                archivo.close();
                return true;
            }
        }
    }

    archivo.close();
    return false;
}

void Banco::crearCuenta(){
    std::vector<Cuenta> cuentasUsuario = usuarioActual->getCuentas();
    if (cuentasUsuario.size() == 0 ){
        int opcion;
        std::cout << "Puedes Crear una cuenta en:"<< std::endl;
        std::cout << "1. Dolares"<< std::endl;
        std::cout << "2. Colones" << std::endl;
        std::cout << "3. Atras" << std::endl;
        std::cout << "Ingrese una opcion: ";
        std::cin >> opcion;
        if (opcion == 1){
            Cuenta cuenta;
            cuenta.dinero = 0.0;
            cuenta.esDolar = true;
            usuarioActual->setCuentas(cuenta);
            registrarCuenta(cuenta.esDolar);
            std::cout << "Cuenta creada con exito"<< std::endl;
        }
        else if (opcion == 2){
            Cuenta cuenta;
            cuenta.dinero = 0.0;
            cuenta.esDolar = false;
            usuarioActual->setCuentas(cuenta);
            registrarCuenta(cuenta.esDolar);
            std::cout << "Cuenta creada con exito"<< std::endl;
        }
        else if(opcion == 3){
            return;
        }
        else{
            std::cout << "Opcion desconocida"<< std::endl;
        }
    }
    else if (cuentasUsuario.size() == 1){
        Cuenta cuentaCreada = cuentasUsuario[0];
        if (cuentaCreada.esDolar){
            int opcionCuenta;
            std::cout<<"Ya posees una cuenta en dolares " << std::endl;
            std::cout<<"Puedes crear una cuenta en :"<< std::endl;
            std::cout<<"1. Colones" << std::endl;
            std::cout<<"2. Atras"<< std::endl;
            std::cout<<"Ingrese una opcion: ";
            std::cin>>opcionCuenta;
            if (opcionCuenta == 1){
                Cuenta cuentaColon;
                cuentaColon.dinero = 0;
                cuentaColon.esDolar = false;
                usuarioActual->setCuentas(cuentaColon);
                registrarCuenta(cuentaColon.esDolar);
                std::cout << "Cuenta creada con exito"<< std::endl;
            }
            else if (opcionCuenta == 2){
                return;
            }
            else{
                std::cout << "Opcion desconocida"<< std::endl;
            }
            
        }
        else{ 
            int opcionCuenta;
            std::cout<<"Ya posees una cuenta en Colones " << std::endl;
            std::cout<<"Puedes crear una cuenta en :"<< std::endl;
            std::cout<<"1. Dolares" << std::endl;
            std::cout<<"2. Atras"<< std::endl;
            std::cout<<"Ingrese una opcion: ";
            std::cin>>opcionCuenta;
            if (opcionCuenta == 1){
                Cuenta cuenta;
                cuenta.dinero = 0;
                cuenta.esDolar = true;
                usuarioActual->setCuentas(cuenta);
                registrarCuenta(cuenta.esDolar);
                std::cout << "Cuenta creada con exito"<< std::endl;
            }
            else if (opcionCuenta == 2){
                return;
            }
            else{
                std::cout << "Opcion desconocida"<< std::endl;
            }

        }

    }
    else if (cuentasUsuario.size() == 2){
        std::cout << "Ya cuentas con el maximo permitido de cuentas"<< std::endl;
    }
    
}

void Banco::registrarCuenta(bool esDolar) {
    std::ifstream archivoEntrada("datos/usuarios.csv");
    if (!archivoEntrada.is_open()) {
        std::cerr << "Error al abrir el archivo " << std::endl;
        return;
    }

    std::string linea;
    std::ostringstream nuevoContenido;
    // Ignorar la primera línea
    std::string primeraLinea;
    std::getline(archivoEntrada, primeraLinea);
    nuevoContenido << primeraLinea << "\n";

    while (std::getline(archivoEntrada, linea)) {
        std::istringstream iss(linea);
        std::string nombre, identificacionStr, tipoCuenta1, dineroCuenta, tipoCuenta2, dineroCuenta2, idPrestamos, idCdps;
        if (std::getline(iss, nombre, ',') && std::getline(iss, identificacionStr, ',') &&
            std::getline(iss, tipoCuenta1, ',') && std::getline(iss, dineroCuenta, ',') &&
            std::getline(iss, tipoCuenta2, ',') && std::getline(iss, dineroCuenta2, ',') &&
            std::getline(iss, idPrestamos, ',') && std::getline(iss, idCdps)) {
            unsigned long int identificacion = std::stoul(identificacionStr);
            if (identificacion == usuarioActual->getIdentificacion()) {
                if (esDolar && usuarioActual->getCuentas().size() == 1) {
                    // Modificar la moneda de la cuenta
                    nuevoContenido << nombre << "," << identificacionStr << "," << "dolar" << ","
                                   << dineroCuenta << "," << tipoCuenta2 << "," << dineroCuenta2 << ","
                                   << idPrestamos << "," << idCdps << "\n";
                } else if (!esDolar && usuarioActual->getCuentas().size() == 1) {
                    nuevoContenido << nombre << "," << identificacionStr << "," << "colon" << ","
                                   << dineroCuenta << "," << tipoCuenta2 << "," << dineroCuenta2 << ","
                                   << idPrestamos << "," << idCdps << "\n";
                } else if (esDolar && usuarioActual->getCuentas().size() == 2) {
                    nuevoContenido << nombre << "," << identificacionStr << "," << tipoCuenta1 << ","
                                   << dineroCuenta << "," << "dolar" << "," << dineroCuenta2 << ","
                                   << idPrestamos << "," << idCdps << "\n";
                } else if (!esDolar && usuarioActual->getCuentas().size() == 2) {
                    nuevoContenido << nombre << "," << identificacionStr << "," << tipoCuenta1 << ","
                                   << dineroCuenta << "," << "colon" << "," << dineroCuenta2 << ","
                                   << idPrestamos << "," << idCdps << "\n";
                } else {
                    // Conservar la línea original si no se cumplen las condiciones
                    nuevoContenido << linea << "\n";
                }
            } else {
                // Conservar la línea original si la identificación no coincide
                nuevoContenido << linea << "\n";
            }
        }
    }

    archivoEntrada.close();

    std::ofstream archivoSalida("datos/usuarios_temp.csv");
    if (!archivoSalida.is_open()) {
        std::cerr << "Error al abrir el archivo para escritura" << std::endl;
        return;
    }

    archivoSalida << nuevoContenido.str();
    archivoSalida.close();

    // Eliminar el archivo original y renombrar el temporal
    std::remove("datos/usuarios.csv");
    std::rename("datos/usuarios_temp.csv", "datos/usuarios.csv");
}

void Banco::cargarDatosUsuario(){
    std::vector<std::string> datos = obtenerDatos();
    //for (auto dato : datos){
    //    std::cout << dato << std::endl;
    //}
    std::string tipoCuenta1, dineroCuenta1Str, tipoCuenta2, dineroCuenta2Str, idPrestamos;
    tipoCuenta1 = datos[0];
    tipoCuenta2 = datos[2];
    dineroCuenta1Str = datos[1];
    dineroCuenta2Str = datos[3];
    idPrestamos = datos[4];
    double dineroCuenta1 = std::stod(dineroCuenta1Str);
    double dineroCuenta2 = std::stod(dineroCuenta2Str);


    cargarCuentas(tipoCuenta1, dineroCuenta1, tipoCuenta2, dineroCuenta2);
    cargarPrestamos(idPrestamos);

}

std::vector<std::string> Banco::obtenerDatos() {
    std::ifstream archivoEntrada("datos/usuarios.csv");
    if (!archivoEntrada.is_open()) {
        std::cerr << "Error al abrir el archivo " << std::endl;
        return {};
    }

    std::string linea;
    std::string resultado;
    // Ignorar la primera línea
    std::getline(archivoEntrada, resultado);

    while (std::getline(archivoEntrada, linea)) {
        std::istringstream iss(linea);
        std::string nombre, identificacionStr, tipoCuenta1, dineroCuenta, tipoCuenta2, dineroCuenta2, idPrestamos, idCdps;
        if (std::getline(iss, nombre, ',') && std::getline(iss, identificacionStr, ',') &&
            std::getline(iss, tipoCuenta1, ',') && std::getline(iss, dineroCuenta, ',') &&
            std::getline(iss, tipoCuenta2, ',') && std::getline(iss, dineroCuenta2, ',') &&
            std::getline(iss, idPrestamos, ',') && std::getline(iss, idCdps)) {
            unsigned long int identificacion = std::stoul(identificacionStr);
            if (identificacion == usuarioActual->getIdentificacion()) {
                resultado = linea;
                break;
            }
        }
    }

    archivoEntrada.close();

    std::vector<std::string> datos;
    std::istringstream tokenStream(resultado);
    std::string token;
    int contador = 0;
    while (std::getline(tokenStream, token, ',')) {
        if (contador == 2 || contador == 3 || contador == 4 || contador == 5 || contador == 6 || contador == 7) {
            datos.push_back(token);
        }
        contador++;
}

    return datos;
}

void Banco::cargarCuentas(std::string tipoCuenta1, double dineroCuenta1, std::string tipoCuenta2, double dineroCuenta2){

    if (tipoCuenta1 == "dolar"){
        Cuenta cuentaDolar;
        cuentaDolar.esDolar = true;
        cuentaDolar.dinero = dineroCuenta1;
        usuarioActual->setCuentas(cuentaDolar);
    }
    else if (tipoCuenta1 == "colon"){
        Cuenta cuentaColon;
        cuentaColon.esDolar = false;
        cuentaColon.dinero = dineroCuenta1;
        usuarioActual->setCuentas(cuentaColon);
    }
    if (tipoCuenta2 == "dolar"){
        Cuenta cuentaDolar2;
        cuentaDolar2.esDolar = true;
        cuentaDolar2.dinero = dineroCuenta2;
        usuarioActual->setCuentas(cuentaDolar2);
    }
    else if (tipoCuenta2 == "colon"){
        Cuenta cuentaColon2;
        cuentaColon2.esDolar = false;
        cuentaColon2.dinero = dineroCuenta2;
        usuarioActual->setCuentas(cuentaColon2);
    }
}

void Banco::realizarDeposito(){
    if (usuarioActual->getCuentas().size() == 0){
        std::cout<< "No Tienes ninguna Cuenta, necesitas hacer una cuenta para realizar un deposito"<< std::endl;
        return ;
    }
    int opcion;
    std::cout<< "Como deseas realizar el deposito:"<< std::endl;
    std::cout<< "1. Efectivo"<< std::endl;
    std::cout<< "2. Entre cuentas"<< std::endl;
    std::cout<< "3. Atras"<< std::endl;
    std::cout<< "Elige una opcion: "<< std::endl;
    std::cin >> opcion;
    
    if (opcion == 1){
        if (usuarioActual->getCuentas().size()== 1){
            Cuenta cuenta = usuarioActual->getCuentas()[0];
            if (cuenta.esDolar){
                int opcionEfectivo;
                std::cout << "Vas a realizar un deposito a tu cuenta en Dolares"<< std::endl;
                std::cout << "Con que monedas vas a realizar el deposito: " << std::endl;
                std::cout << "1. Dolares"<< std::endl;
                std::cout << "2. Colones"<< std::endl;
                std::cout << "Ingrese una opcion: " ;
                std:: cin >> opcionEfectivo;
                if (opcionEfectivo == 1){
                    double montoDolar;
                    std::cout << "Ingrese el monto a depositar: ";
                    std::cin >> montoDolar;
                    cuenta.dinero += montoDolar;

                }
            }
        }
    }
    else if (opcion == 2){

    }
    else if (opcion == 3){

    }
    else{

    }


}

void Banco::actualizarUsuarios(){
    /* Se abre el archivo de registro. */
    std::string nombreArchivo = "datos\\usuarios.csv";
    std::ifstream viejo(nombreArchivo);
    std::ofstream nuevo("temp1.csv");
    Usuario user = *this->usuarioActual;

    std::string linea, sinNombre, idCSV, idPrestamos = " ", idCDPs = " ";
    std::vector<std::string> cuentas = {" ", "0", " ", "0"};

    for(auto& prestamo: user.getPrestamos()){
        idPrestamos += prestamo.getID() + " ";
    }

    for(auto& cdp: user.getCdps()){
        idCDPs += cdp.getID() + " ";
    }

    int i = 0;
    for(auto& cuenta : user.getCuentas()){
        /* Se establece el tipo de la cuenta. */
        if(cuenta.esDolar){
            cuentas[i] = "dolar";
        } else {
            cuentas[i] = "colon";
        }
            i++;

        /* Se establece el monto. */
        cuentas[i] = std::to_string(cuenta.dinero);
        i++;
    }

    while(std::getline(viejo, linea)){
        sinNombre = linea.substr(linea.find(',') + 1);
        idCSV = sinNombre.substr(0, sinNombre.find(','));
        if(idCSV == std::to_string(user.getIdentificacion())){
            nuevo << user.getNombre() << "," << user.getIdentificacion() << ","
                  << cuentas[0] << "," << cuentas[1] << ","
                  << cuentas[2] << "," << cuentas[3] << ","
                  << idPrestamos << "," << idCDPs << std::endl;
        } else {
        nuevo << linea << std::endl;
        }
    }

    /* Se guardan ambos archivos. */
    viejo.close();
    nuevo.close();

    /* Se remueve el archivo viejo y se renombra al nuevo como el csv original. */
    remove(nombreArchivo.c_str());
    rename("temp1.csv", nombreArchivo.c_str());
}