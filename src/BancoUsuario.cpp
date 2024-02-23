/**
 * @file BancoUsuario.cpp
 * @author Diego Alfaro, Bryan Cortes, Heiner Obando
 * @brief Implementacion de  métodos Sobre Usuarios y cuentas dentro  de la Clase Banco
 * @version 0.1
 * @date 2024-02-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "Banco.hpp"
#include "Usuario.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

void Banco::loggearUsuario() {
    try{
        int opcion;
        std::cout << "\nBienvenido a atencion al cliente " << std::endl;
        std::cout << "1. Loggearse " << std::endl;
        std::cout << "2. Registrarse " << std::endl;
        std::cout << "Elige una opcion: ";
        std::cin >> opcion;

        if (std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw  std::invalid_argument("Se ingreso un tipo de dato invalido.");
        }

    
        if (opcion == 1) {
            unsigned long int identificacion;
            std::string nombre;
            std::cout << "Ingrese su nombre: ";
            std::cin >> nombre;
            std::cout << "Ingrese su identificacion: ";
            std::cin >> identificacion;

            if (std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw  std::invalid_argument("Se ingreso un tipo de dato invalido.");

            }

            if (verificarIdentificacionNombreEnCSV(identificacion, nombre)) {
                usuarioActual = new Usuario(identificacion, nombre);
                usuarioLogeado = true;
            } else {
                throw std::runtime_error("Error, el nombre del usuario o identificación no se encuentra en el registro.");
            }
        } else if (opcion == 2) {
            unsigned long int identificacion;
            std::string nombre;
            std::cout << "Ingrese su numero de cedula: ";
            std::cin >> identificacion;

            if (std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw  std::invalid_argument("Se ingreso un tipo de dato invalido.");
            }

            if (identificacion < 0 || identificacion > 999999999){
                throw  std::invalid_argument("El numero de identificacion debe estar entre 0 y 999999999");
            }

            if (verificarIdentificacioEnCSV(identificacion)) {
                throw std::runtime_error("El numero de cedula ingresado ya habia sido registrado");
            } else {
                std::cout << "Ingrese su nombre: ";
                std::cin >> nombre;
                std::cout << "Creando Usuario ..." << std::endl;
                usuarioActual = new Usuario(identificacion, nombre);
                usuarioActual->registrarUsuario();
                std::string registro = "Creacion de usuario, " + std::to_string(usuarioActual->getIdentificacion());
                registrarTrasaccion(registro);
                usuarioLogeado = true;
            }

        } else {
            throw std::invalid_argument("Opcion invalida");
        }
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        usuarioLogeado = false;
    }
}

void Banco::crearCuenta(){
    std::vector<Cuenta> cuentasUsuario = usuarioActual->getCuentas();
    try{
        if (cuentasUsuario.size() == 0 ){
            int opcion;
            std::cout << "Puedes Crear una cuenta en:"<< std::endl;
            std::cout << "1. Dolares"<< std::endl;
            std::cout << "2. Colones" << std::endl;
            std::cout << "3. Atras" << std::endl;
            std::cout << "Ingrese una opcion: ";
            std::cin >> opcion;
            if (std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw  std::invalid_argument("Se ingreso un tipo de dato invalido.");
            }
            if (opcion < 1 || opcion > 3) {
                throw std::invalid_argument("Opcion invalida");
            }
            if (opcion == 1){
                Cuenta cuenta;
                cuenta.dinero = 0.0;
                cuenta.esDolar = true;
                usuarioActual->setCuentas(cuenta);
                registrarCuenta(cuenta.esDolar);
                std::string registro = "Creacion Cuenta, Usuario: " + std::to_string(usuarioActual->getIdentificacion()) +
                                        ", Moneda: Dolar";
                registrarTrasaccion(registro);
                std::cout << "Cuenta creada con exito"<< std::endl;
            }
            else if (opcion == 2){
                Cuenta cuenta;
                cuenta.dinero = 0.0;
                cuenta.esDolar = false;
                usuarioActual->setCuentas(cuenta);
                registrarCuenta(cuenta.esDolar);
                std::string registro = "Creacion Cuenta, Usuario: " + std::to_string(usuarioActual->getIdentificacion()) +
                                        ", Moneda: Colon";
                registrarTrasaccion(registro);
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
                if (std::cin.fail()){
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw  std::invalid_argument("Se ingreso un tipo de dato invalido.");
                }
                if (opcionCuenta == 1){
                    Cuenta cuentaColon;
                    cuentaColon.dinero = 0;
                    cuentaColon.esDolar = false;
                    usuarioActual->setCuentas(cuentaColon);
                    registrarCuenta(cuentaColon.esDolar);
                    std::string registro = "Creacion Cuenta, Usuario: " + std::to_string(usuarioActual->getIdentificacion()) +
                                            ", Moneda: Colon";
                    registrarTrasaccion(registro);
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
                if (std::cin.fail()){
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw  std::invalid_argument("Se ingreso un tipo de dato invalido.");
                }

                if (opcionCuenta == 1){
                    Cuenta cuenta;
                    cuenta.dinero = 0;
                    cuenta.esDolar = true;
                    usuarioActual->setCuentas(cuenta);
                    registrarCuenta(cuenta.esDolar);
                    std::string registro = "Creacion Cuenta, Usuario: " + std::to_string(usuarioActual->getIdentificacion()) +
                                            ", Moneda: Dolar";
                    registrarTrasaccion(registro);
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
            throw std::runtime_error("Ya tienes el maximo permitido de cuentas");
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Banco::cargarDatosUsuario(){
    /* Obtener los datos del usuario acutal */
    std::vector<std::string> datos = obtenerDatos(usuarioActual->getIdentificacion());
    /* Extraer datos*/
    std::string tipoCuenta1, dineroCuenta1Str, tipoCuenta2, dineroCuenta2Str, idPrestamos, idCDPs;
    tipoCuenta1 = datos[0];
    tipoCuenta2 = datos[2];
    dineroCuenta1Str = datos[1];
    dineroCuenta2Str = datos[3];
    idPrestamos = datos[4];
    idCDPs = datos[5];
    /*Convertir los saldos de las cuentas a double */
    double dineroCuenta1 = std::stod(dineroCuenta1Str);
    double dineroCuenta2 = std::stod(dineroCuenta2Str);
    // Cargar las cuentas, préstamos y CDPs del usuario actual
    cargarCuentas(tipoCuenta1, dineroCuenta1, tipoCuenta2, dineroCuenta2);
    cargarPrestamos(idPrestamos);
    cargarCDPs(idCDPs);
}

std::vector<std::string> Banco::obtenerDatos(unsigned long int identificacionBuscar) {
     // Abrir el archivo CSV que contiene los datos de los usuarios
    std::ifstream archivoEntrada("datos/usuarios.csv");
    if (!archivoEntrada.is_open()) {
        std::cerr << "Error al abrir el archivo " << std::endl;
        return {};
    }
    // Variables para almacenar los datos del usuario encontrado
    std::string linea;
    std::string resultado;
    // Ignorar la primera línea
    std::getline(archivoEntrada, resultado);
     // Se itera cada línea del archivo hasta encontrar al usuario buscado
    while (std::getline(archivoEntrada, linea)) {
        std::istringstream iss(linea);
        std::string nombre, identificacionStr, tipoCuenta1, dineroCuenta, tipoCuenta2, dineroCuenta2, idPrestamos, idCdps;
        if (std::getline(iss, nombre, ',') && std::getline(iss, identificacionStr, ',') &&
            std::getline(iss, tipoCuenta1, ',') && std::getline(iss, dineroCuenta, ',') &&
            std::getline(iss, tipoCuenta2, ',') && std::getline(iss, dineroCuenta2, ',') &&
            std::getline(iss, idPrestamos, ',') && std::getline(iss, idCdps)) {
            unsigned long int identificacion = std::stoul(identificacionStr);
            if (identificacion == identificacionBuscar) {
                resultado = linea;
                break;
            }
        }
    }
    // Cerrar el archivo
    archivoEntrada.close();
     // Extraer los datos relevantes encontrados
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
    try{
        if (usuarioActual->getCuentas().size() == 0){
            throw std::runtime_error("No tienes ninguna cuenta, necesitas hacer una cuenta para realizar un deposito");
            return ;
        }
        int opcion;
        std::cout<< "Como deseas realizar el deposito:"<< std::endl;
        std::cout<< "1. Efectivo"<< std::endl;
        std::cout<< "2. Entre cuentas"<< std::endl;
        std::cout<< "3. Atras"<< std::endl;
        std::cout<< "Elige una opcion: ";
        std::cin >> opcion;
        if (std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw  std::invalid_argument("Se ingreso un tipo de dato invalido.");
        }

        if (opcion == 1){
            if (usuarioActual->getCuentas().size()== 1){
                Cuenta cuenta = usuarioActual->getCuentas()[0];
                std::cout << cuenta.esDolar << std::endl;
                if (cuenta.esDolar){
                    depositarCuentaDolar(cuenta.dinero);
                    }
                else {
                    depositarCuentaColon(cuenta.dinero);
                }   
            }
            else if (usuarioActual->getCuentas().size()== 2){
                int opcionCuentas;
                std::cout << "En cual cuenta deseas realizar el deposito" << std::endl;
                mostrarInfoCuentas(usuarioActual->getCuentas());
                std::cout << "Ingrese una cuenta: ";
                std::cin >> opcionCuentas;
                if (std::cin.fail()){
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw  std::invalid_argument("Se ingreso un tipo de dato invalido.");
                }   
                if (opcionCuentas == 1){
                    Cuenta cuenta = usuarioActual->getCuentas()[0];
                    if (cuenta.esDolar){
                        depositarCuentaDolar(cuenta.dinero);
                    }
                    else {
                        depositarCuentaColon(cuenta.dinero);
                    }  
                }
                else if (opcionCuentas == 2){
                    Cuenta cuenta = usuarioActual->getCuentas()[1];
                    if (cuenta.esDolar){
                        depositarCuentaDolar(cuenta.dinero);
                    }
                    else {
                        depositarCuentaColon(cuenta.dinero);
                    }  
                }
            }
        }
        else if (opcion == 2){
            if (usuarioActual->getCuentas().size() == 2){
                int opcionCuentas;
                std::cout << "En cual cuenta deseas depositar" << std::endl;
                mostrarInfoCuentas(usuarioActual->getCuentas());
                std::cout << "Ingrese una cuenta: ";
                std::cin >> opcionCuentas;
                if (std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw  std::invalid_argument("Se ingreso un tipo de dato invalido.");
                }  


                if (opcionCuentas == 1){
                    Cuenta cuentaDepositar = usuarioActual->getCuentas()[0];
                    Cuenta cuentaRetirar = usuarioActual->getCuentas()[1];
                    depositoEntreCuentas(cuentaDepositar, cuentaRetirar);
                }
                else if (opcionCuentas == 2){
                    Cuenta cuentaDepositar = usuarioActual->getCuentas()[1];
                    Cuenta cuentaRetirar = usuarioActual->getCuentas()[0];
                    depositoEntreCuentas(cuentaDepositar, cuentaRetirar);
                }
                else{
                    throw std::invalid_argument("Opción inválida");
                }
            }
            else {
                throw std::invalid_argument("Debes tener dos cuentas");
            }

        }
        else if (opcion == 3){
            return;
        }
        else{
            throw std::invalid_argument("Opcion invalida");
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
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

void Banco::mostrarInfoCuentas(std::vector<Cuenta> cuentas, bool mostrarDinero){
    if (cuentas.empty()){
        std::cout<< "No Tienes Ninguna Cuenta" << std::endl;
        return;
    }
    for (size_t i = 0; i < cuentas.size(); ++i){
        std::cout << "---------------------"<< std::endl;
        std::cout << "Cuenta "<< i + 1 << ":" << std::endl;
        if (cuentas[i].esDolar){
            std::cout<< "Moneda: Dolar"<< std::endl; 
        }
        else{
            std::cout<< "Moneda: Colon"<< std::endl;
        }
        if (mostrarDinero){
        std::cout <<"Dinero: "<<cuentas[i].dinero << std::endl;
        }
    }   std::cout << "---------------------"<< std::endl;
}

void Banco::actualizarCuentas(){
    usuarioActual->limpiarCuentas();
    std::vector<std::string> datos = obtenerDatos(usuarioActual->getIdentificacion());
    std::string tipoCuenta1, dineroCuenta1Str, tipoCuenta2, dineroCuenta2Str;
    tipoCuenta1 = datos[0];
    tipoCuenta2 = datos[2];
    dineroCuenta1Str = datos[1];
    dineroCuenta2Str = datos[3];
    double dineroCuenta1 = std::stod(dineroCuenta1Str);
    double dineroCuenta2 = std::stod(dineroCuenta2Str);
    cargarCuentas(tipoCuenta1, dineroCuenta1, tipoCuenta2, dineroCuenta2);

}


void Banco::depositarCuentaColon(double dinero){
    try{
        int opcionEfectivo;
        std::cout << "Vas a realizar un deposito a tu cuenta en Colones"<< std::endl;
        std::cout << "Con que monedas vas a realizar el deposito: " << std::endl;
        std::cout << "1. Dolares"<< std::endl;
        std::cout << "2. Colones"<< std::endl;
        std::cout << "Ingrese una opcion: " ;
        std:: cin >> opcionEfectivo;
        if (std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw  std::invalid_argument("Se ingreso un tipo de dato invalido.");
        }
        if (opcionEfectivo < 1 || opcionEfectivo > 2) {
            throw std::invalid_argument("Opcion invalida");
        }

        if (opcionEfectivo == 1){
            double montoDolar, montoColon;
            std::cout << "Ingrese el monto a depositar: ";
            std::cin >> montoDolar;
            if (std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw  std::invalid_argument("Se ingreso un tipo de dato invalido.");
            }
            if (montoDolar < 0) {
                throw std::invalid_argument(" El monto a depositar debe ser mayor que cero");
            }
            montoColon = convertirMoneda(montoDolar, false);
            dinero += montoColon;
            registrarDeposito(dinero, "colon", usuarioActual->getIdentificacion());
            actualizarCuentas();
            std::string registro = "Deposito , Usuario: " + std::to_string(usuarioActual->getIdentificacion()) +
                                    ", Cuenta: Colon, tipo: Efectivo, monto: " + std::to_string(montoColon);
            registrarTrasaccion(registro);
        }
        else if (opcionEfectivo == 2){
            double montoColon;
            std::cout << "Ingrese el monto a depositar: ";
            std::cin >> montoColon;
            if (std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw  std::invalid_argument("Se ingreso un tipo de dato invalido.");
            }
            if (montoColon < 0) {
                throw std::invalid_argument(" El monto a depositar debe ser mayor que cero");
            }
            dinero += montoColon;
            registrarDeposito(dinero, "colon", usuarioActual->getIdentificacion());
            actualizarCuentas();
            std::string registro = "Deposito , Usuario: " + std::to_string(usuarioActual->getIdentificacion()) +
                                    ", Cuenta: Colon, tipo: Efectivo, monto: " + std::to_string(montoColon);
            registrarTrasaccion(registro);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
void Banco::depositarCuentaDolar(double dinero){
    try{
        int opcionEfectivo;
        std::cout << "Vas a realizar un deposito a tu cuenta en Dolares"<< std::endl;
        std::cout << "Con que monedas vas a realizar el deposito: " << std::endl;
        std::cout << "1. Dolares"<< std::endl;
        std::cout << "2. Colones"<< std::endl;
        std::cout << "Ingrese una opcion: " ;
        std:: cin >> opcionEfectivo;
        if (std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw  std::invalid_argument("Se ingreso un tipo de dato invalido.");
        }
        if (opcionEfectivo < 1 || opcionEfectivo > 2) {
            throw std::invalid_argument("Opcion inválida");
        }

        if (opcionEfectivo == 1){
            double montoDolar;
            std::cout << "Ingrese el monto a depositar: ";
            std::cin >> montoDolar;
            if (std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw  std::invalid_argument("Se ingreso un tipo de dato invalido.");
            }
            if (montoDolar < 0) {
                throw std::invalid_argument(" El monto a depositar debe ser mayor que cero");
            }
            dinero += montoDolar;
            registrarDeposito(dinero, "dolar", usuarioActual->getIdentificacion());
            actualizarCuentas();
            std::string registro = "Deposito, Usuario: " + std::to_string(usuarioActual->getIdentificacion()) +
                                    ", Cuenta: Dolar, tipo: Efectivo, monto: " + std::to_string(montoDolar);
            registrarTrasaccion(registro);

        }
        else if (opcionEfectivo == 2){
            double montoDolar, montoColon;
            std::cout << "Ingrese el monto a depositar: ";
            std::cin >> montoColon;
            if (std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw  std::invalid_argument("Se ingreso un tipo de dato invalido.");
            }
            if (montoColon < 0) {
                throw std::invalid_argument(" El monto a depositar debe ser mayor que cero");
            }
            montoDolar = convertirMoneda(montoColon, true);
            dinero += montoDolar;
            registrarDeposito(dinero, "dolar", usuarioActual->getIdentificacion());
            actualizarCuentas();
            std::string registro = "Deposito, Usuario: " + std::to_string(usuarioActual->getIdentificacion()) +
                                    ", Cuenta: Dolar, tipo: Efectivo, monto: " + std::to_string(montoDolar);
            registrarTrasaccion(registro);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Banco::realizarRetiro(){
    try{
        if (usuarioActual->getCuentas().size() == 0){
            throw std::runtime_error("Debes tener al menos una cuenta para realizar un retiro");
        }
        if (usuarioActual->getCuentas().size() == 1){
            double monto;
            mostrarInfoCuentas(usuarioActual->getCuentas());
            Cuenta cuenta = usuarioActual->getCuentas()[0];
            std::cout << "Cuanto dinero deseas sacar: ";
            std::cin >> monto;
            if (std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw  std::invalid_argument("Se ingreso un tipo de dato invalido.");
            }
            if (monto < 0) {
                throw std::invalid_argument(" El monto a depositar debe ser mayor que cero");
            }

            if (monto > cuenta.dinero){
                throw std::invalid_argument(" No cuentas con ese monto en la cuenta para retirar");
            }
            cuenta.dinero -= monto;
            if (cuenta.esDolar){
                registrarDeposito(cuenta.dinero, "dolar", usuarioActual->getIdentificacion());
                std::string registro = "Retiro, Usuario: " + std::to_string(usuarioActual->getIdentificacion()) +
                                    ", Cuenta: Dolar, tipo: Efectivo, monto: " + std::to_string(monto);
                registrarTrasaccion(registro);
            }
            else{
                registrarDeposito(cuenta.dinero, "colon", usuarioActual->getIdentificacion());
                std::string registro = "Retiro, Usuario: " + std::to_string(usuarioActual->getIdentificacion()) +
                                    ", Cuenta: Colon, tipo: Efectivo, monto: " + std::to_string(monto);
                registrarTrasaccion(registro);
            }
            actualizarCuentas();
        }
        if (usuarioActual->getCuentas().size() == 2){
            int opcionCuentas;
            std::cout << "En cual cuenta deseas realizar el retiro" << std::endl;
            mostrarInfoCuentas(usuarioActual->getCuentas());
            std::cout << "Ingrese una cuenta: ";
            std::cin >> opcionCuentas;
            if (std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw  std::invalid_argument("Se ingreso un tipo de dato invalido.");
            }
            if (opcionCuentas == 1){
                Cuenta cuenta = usuarioActual->getCuentas()[0];
                double monto;
                std::cout << "Cuanto dinero deseas sacar: ";
                std::cin >> monto;
                if (std::cin.fail()){
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw  std::invalid_argument("Se ingreso un tipo de dato invalido.");
                }
                if (monto < 0) {
                    throw std::invalid_argument(" El monto a depositar debe ser mayor que cero");
                }

                if (monto > cuenta.dinero){
                    throw std::invalid_argument(" No cuentas con ese monto en la cuenta para retirar");
                }
                cuenta.dinero -= monto;
                if (cuenta.esDolar){
                    registrarDeposito(cuenta.dinero, "dolar", usuarioActual->getIdentificacion());
                    std::string registro = "Retiro, Usuario: " + std::to_string(usuarioActual->getIdentificacion()) +
                                    ", Cuenta: Dolar, tipo: Efectivo, monto: " + std::to_string(monto);
                    registrarTrasaccion(registro);
                }
                else{
                    registrarDeposito(cuenta.dinero, "colon", usuarioActual->getIdentificacion());
                    std::string registro = "Retiro, Usuario: " + std::to_string(usuarioActual->getIdentificacion()) +
                                    ", Cuenta: Colon, tipo: Efectivo, monto: " + std::to_string(monto);
                    registrarTrasaccion(registro);
                }
                actualizarCuentas();
            }
            else if (opcionCuentas == 2){
                Cuenta cuenta = usuarioActual->getCuentas()[1];
                double monto;
                std::cout << "Cuanto dinero deseas sacar: ";
                std::cin >> monto;
                if (std::cin.fail()){
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw  std::invalid_argument("Se ingreso un tipo de dato invalido.");
                }
                if (monto < 0) {
                    throw std::invalid_argument(" El monto a depositar debe ser mayor que cero");
                }

                if (monto > cuenta.dinero){
                    throw std::invalid_argument(" No cuentas con ese monto en la cuenta para retirar");
                }
                cuenta.dinero -= monto;
                if (cuenta.esDolar){
                    registrarDeposito(cuenta.dinero, "dolar", usuarioActual->getIdentificacion());
                    std::string registro = "Retiro, Usuario: " + std::to_string(usuarioActual->getIdentificacion()) +
                                    ", Cuenta: Dolar, tipo: Efectivo, monto: " + std::to_string(monto);
                    registrarTrasaccion(registro);
                }
                else{
                    registrarDeposito(cuenta.dinero, "colon", usuarioActual->getIdentificacion());
                    std::string registro = "Retiro, Usuario: " + std::to_string(usuarioActual->getIdentificacion()) +
                                    ", Cuenta: Colon, tipo: Efectivo, monto: " + std::to_string(monto);
                    registrarTrasaccion(registro);
                }
                actualizarCuentas();
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Banco::depositoEntreCuentas(Cuenta cuentaDepositar, Cuenta cuentaRetirar){
    try{
        if (cuentaDepositar.esDolar){
            double montoDolar, montoColon;
            std::cout << "Vas a depositar a tu cuenta en dolares usando la cuenta en colones" << std::endl;
            std::cout << "Ingrese la cantidad en dolares que deseas ingresar: ";
            std::cin >> montoDolar;
            if (std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw  std::invalid_argument("Se ingreso un tipo de dato invalido.");
            }
            if (montoDolar < 0) {
                throw std::invalid_argument(" El monto a depositar debe ser mayor que cero");
            }

            montoColon = convertirMoneda(montoDolar, false);
            if (montoColon > cuentaRetirar.dinero){
                throw std::invalid_argument(" No cuentas con ese monto en la cuenta para retirar");
            }
    
            cuentaDepositar.dinero += montoDolar;
            cuentaRetirar.dinero -= montoColon;
            std::cout << cuentaRetirar.dinero << std::endl;
            registrarDeposito(cuentaDepositar.dinero, "dolar", usuarioActual->getIdentificacion());
            registrarDeposito(cuentaRetirar.dinero, "colon", usuarioActual->getIdentificacion());
            actualizarCuentas();
            std::string registro = "Deposito, Usuario: " + std::to_string(usuarioActual->getIdentificacion()) +
                                    ", Cuenta: Dolar, tipo: Entre Cuentas, monto: " + std::to_string(montoDolar) +
                                    ", retirado de: Cuenta Colon, monto: " + std::to_string(montoColon);
            registrarTrasaccion(registro);
            }
            else{
                double montoDolar, montoColon;
                std::cout << "Vas a depositar a tu cuenta en colones usando la cuenta en dolares" << std::endl;
                std::cout << "Ingrese la cantidad en colones que deseas ingresar: ";
                std::cin >> montoColon;
                if (std::cin.fail()){
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw  std::invalid_argument("Se ingreso un tipo de dato invalido.");
                }
                if (montoColon < 0) {
                    throw std::invalid_argument(" El monto a depositar debe ser mayor que cero");
                }
                montoDolar = convertirMoneda(montoColon, true);
                if (montoDolar > cuentaRetirar.dinero){
                    throw std::invalid_argument(" No cuentas con ese monto en la cuenta para retirar");
                }

                cuentaDepositar.dinero += montoColon;
                cuentaRetirar.dinero -= montoDolar;
                registrarDeposito(cuentaDepositar.dinero, "colon", usuarioActual->getIdentificacion());
                registrarDeposito(cuentaRetirar.dinero, "dolar", usuarioActual->getIdentificacion());
                actualizarCuentas();
                std::string registro = "Deposito, Usuario: " + std::to_string(usuarioActual->getIdentificacion()) +
                                    ", Cuenta: Colon, tipo: Entre Cuentas, monto: " + std::to_string(montoColon) +
                                    ", retirado de: Cuenta Dolar, monto: " + std::to_string(montoDolar);
                registrarTrasaccion(registro);
        }   
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Banco::realizarTransaccion(){
    try{
        unsigned long int identificacionUsuarioTransferir;
        std::cout << "Ingrese la identificacion de la persona que deseas realizar la transaccion: ";
        std::cin >> identificacionUsuarioTransferir;
        if(identificacionUsuarioTransferir == usuarioActual->getIdentificacion()){
            throw  std::invalid_argument("No Puedes hacer una transferencia a usted mismo.");
        }
        if (std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw  std::invalid_argument("Se ingreso un tipo de dato invalido.");
        }
        if (verificarIdentificacioEnCSV(identificacionUsuarioTransferir)){
            std::vector<Cuenta> cuentas = cuentasTransferibles(identificacionUsuarioTransferir);
            if (cuentas.size() == 0){
                throw  std::invalid_argument("El usuario que deseas transferir no cuenta con ninguna cuenta");
            }
            if (cuentas.size() == 1){
                int opcionTransferencia;
                Cuenta cuenta = cuentas[0];
                std::cout << "Como deseas realizar la transferencia: " << std::endl;
                std::cout << "1. Efectivo " << std::endl;
                std::cout << "2. Cuentas" << std::endl;
                std::cout << "Ingrese una opcion: ";
                std::cin >> opcionTransferencia;
                if (std::cin.fail()){
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw  std::invalid_argument("Se ingreso un tipo de dato invalido.");
                }

                if (opcionTransferencia == 1){
                    transferenciaEfectivo(cuenta, identificacionUsuarioTransferir);
                }
                else if (opcionTransferencia == 2){
                    if (usuarioActual->getCuentas().size() == 0){
                        std::cout << "No tienes ninguna cuenta para realizar la transferencia" << std::endl;
                        return;
                    }
                    if (usuarioActual->getCuentas().size() == 1){
                        Cuenta cuentaRetirar = usuarioActual->getCuentas()[0];
                        transferenciaEntreCuentas(cuenta, cuentaRetirar, identificacionUsuarioTransferir);
                    }
                    else if (usuarioActual->getCuentas().size() == 2){
                        int opcionCuentas;
                        mostrarInfoCuentas(usuarioActual->getCuentas());
                        std::cout << "Cual Cuenta deseas realizar la transferencia: ";
                        std::cin >> opcionCuentas;
                        if (std::cin.fail()){
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            throw  std::invalid_argument("Se ingreso un tipo de dato invalido.");
                        }

                        if (opcionCuentas == 1){
                            Cuenta cuentaRetirar = usuarioActual->getCuentas()[0];
                            transferenciaEntreCuentas(cuenta, cuentaRetirar, identificacionUsuarioTransferir);
                        }
                        else if (opcionCuentas == 2){
                            Cuenta cuentaRetirar = usuarioActual->getCuentas()[1];
                            transferenciaEntreCuentas(cuenta, cuentaRetirar, identificacionUsuarioTransferir);
                        }
                        else{
                            std::cout << "Opcion desconocida" << std::endl;
                            return;
                        }
                    }
                }
                else{
                    std::cout << "Opcion desconocida" << std::endl;
                }
            }
            else if (cuentas.size() == 2){
                int opcionCuenta;
                mostrarInfoCuentas(cuentas, false);
                std::cout << "A cual cuenta deseas realizar la transferecia: ";
                std::cin >> opcionCuenta;
                if (std::cin.fail()){
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw  std::invalid_argument("Se ingreso un tipo de dato invalido.");
                }

                if (opcionCuenta == 1){
                    int opcionTransferencia;
                    Cuenta cuenta = cuentas[0];
                    std::cout << "Como deseas realizar la transferencia: " << std::endl;
                    std::cout << "1. Efectivo " << std::endl;
                    std::cout << "2. Cuentas" << std::endl;
                    std::cout << "Ingrese una opcion: ";
                    std::cin >> opcionTransferencia;
                    if (std::cin.fail()){
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        throw  std::invalid_argument("Se ingreso un tipo de dato invalido.");
                    }
                    if (opcionTransferencia == 1){
                        transferenciaEfectivo(cuenta, identificacionUsuarioTransferir);
                    }
                    else if (opcionTransferencia == 2){ 
                        if (usuarioActual->getCuentas().size() == 0){
                            std::cout << "No tienes ninguna cuenta para realizar la transferencia" << std::endl;
                            return;
                        }
                        if (usuarioActual->getCuentas().size() == 1){
                            Cuenta cuentaRetirar = usuarioActual->getCuentas()[0];
                            transferenciaEntreCuentas(cuenta, cuentaRetirar, identificacionUsuarioTransferir);
                        }
                        else if (usuarioActual->getCuentas().size() == 2){
                            int opcionCuentas;
                            mostrarInfoCuentas(usuarioActual->getCuentas());
                            std::cout << "Cual Cuenta deseas realizar la transferencia: ";
                            std::cin >> opcionCuentas;
                            if (std::cin.fail()){
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                throw  std::invalid_argument("Se ingreso un tipo de dato invalido.");
                            }

                            if (opcionCuentas == 1){
                                Cuenta cuentaRetirar = usuarioActual->getCuentas()[0];
                                transferenciaEntreCuentas(cuenta, cuentaRetirar, identificacionUsuarioTransferir);
                            }
                            else if (opcionCuentas == 2){
                                Cuenta cuentaRetirar = usuarioActual->getCuentas()[1];
                                transferenciaEntreCuentas(cuenta, cuentaRetirar, identificacionUsuarioTransferir);
                            }
                            else{
                                std::cout << "Opcion desconocida" << std::endl;
                                return;
                            }
                            }

                    }
                    else{
                    std::cout << "Opcion desconocida" << std::endl;
                    }            
                }
                else if (opcionCuenta == 2){
                    int opcionTransferencia;
                    Cuenta cuenta = cuentas[1];
                    std::cout << "Como deseas realizar la transferencia: " << std::endl;
                    std::cout << "1. Efectivo " << std::endl;
                    std::cout << "2. Cuentas" << std::endl;
                    std::cout << "Ingrese una opcion: ";
                    std::cin >> opcionTransferencia;
                    if (std::cin.fail()){
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        throw  std::invalid_argument("Se ingreso un tipo de dato invalido.");
                    }

                    if (opcionTransferencia == 1){
                        transferenciaEfectivo(cuenta, identificacionUsuarioTransferir);
                    }
                    else if (opcionTransferencia == 2){
                        if (usuarioActual->getCuentas().size() == 0){
                            throw  std::invalid_argument(" No tienes ninguna cuenta para realizar la transferencia");
                        }
                        if (usuarioActual->getCuentas().size() == 1){
                            Cuenta cuentaRetirar = usuarioActual->getCuentas()[0];
                            transferenciaEntreCuentas(cuenta, cuentaRetirar, identificacionUsuarioTransferir);
                        }
                        else if (usuarioActual->getCuentas().size() == 2){
                            int opcionCuentas;
                            mostrarInfoCuentas(usuarioActual->getCuentas());
                            std::cout << "Cual Cuenta deseas realizar la transferencia: ";
                            std::cin >> opcionCuentas;
                            if (std::cin.fail()){
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            throw  std::invalid_argument("Se ingreso un tipo de dato invalido.");
                            }
                            if (opcionCuentas == 1){
                                Cuenta cuentaRetirar = usuarioActual->getCuentas()[0];
                                transferenciaEntreCuentas(cuenta, cuentaRetirar, identificacionUsuarioTransferir);
                            }
                            else if (opcionCuentas == 2){
                                Cuenta cuentaRetirar = usuarioActual->getCuentas()[1];
                                transferenciaEntreCuentas(cuenta, cuentaRetirar, identificacionUsuarioTransferir);
                            }
                            else{
                                std::cout << "Opcion desconocida" << std::endl;
                                return;
                            }
                        }
                    }
                    else{
                        std::cout << "Opcion desconocida" << std::endl;
                    }       
                }
            }
        }
        else{
            throw  std::invalid_argument("La indentificacion ingresada no se encuentra registrada en el sistema ");
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Banco::transferenciaEfectivo(Cuenta cuenta, unsigned long int identificacionUsuarioTransferir){
    try {
        int opcionEfectivo;
        std::cout << "Con que tipo de moneda vas a realizar la transferencia: " << std::endl;
        std::cout << "1. Dolares"<< std::endl;
        std::cout << "2. Colones"<< std::endl;
        std::cout << "Ingrese una opcion: " ;
        std:: cin >> opcionEfectivo;

        if (opcionEfectivo != 1 && opcionEfectivo != 2) {
            throw std::invalid_argument("Opcion invalida. Debes seleccionar 1 para Dolares o 2 para Colones.");
        }

        double monto;
        std::cout << "Ingrese el monto a depositar: ";
        std::cin >> monto;

        if (std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw  std::invalid_argument("Se ingreso un tipo de dato invalido.");
        }

        if (monto <= 0) {
            throw std::invalid_argument("El monto debe ser mayor que cero.");
        }

        double montoConvertido;
        if (opcionEfectivo == 1) {
            if (cuenta.esDolar){
                cuenta.dinero += monto;
                registrarDeposito(cuenta.dinero, "dolar", identificacionUsuarioTransferir);
                std::string registro = "Transferencia, Origen: Usuario " + std::to_string(usuarioActual->getIdentificacion()) +
                                    ", Efectivo, Destino: Usuario " +  std::to_string(identificacionUsuarioTransferir) + "Cuenta: Dolar, Monto: " +
                                    std::to_string(monto) + ", moneda: dolar" ;
                registrarTrasaccion(registro);
                return;
            }
            else{
                montoConvertido = convertirMoneda(monto, false);
                cuenta.dinero += montoConvertido;
                registrarDeposito(cuenta.dinero, "colon", identificacionUsuarioTransferir);
                std::string registro = "Transferencia, Origen: Usuario " + std::to_string(usuarioActual->getIdentificacion()) +
                                    ", Efectivo, Destino: Usuario " +  std::to_string(identificacionUsuarioTransferir) + "Cuenta: Colon, Monto: " +
                                    std::to_string(montoConvertido) + ", moneda: dolar" ;
                registrarTrasaccion(registro);
                return;
            }
        } else if (opcionEfectivo == 2) {
            if (cuenta.esDolar){
                montoConvertido = convertirMoneda(monto, true);
                cuenta.dinero += montoConvertido;
                registrarDeposito(cuenta.dinero, "dolar", identificacionUsuarioTransferir);
                std::string registro = "Transferencia, Origen: Usuario " + std::to_string(usuarioActual->getIdentificacion()) +
                                    ", Efectivo, Destino: Usuario " +  std::to_string(identificacionUsuarioTransferir) + "Cuenta: Dolar, Monto: " +
                                    std::to_string(montoConvertido) + ", moneda: Colon" ;
                registrarTrasaccion(registro);
                return;
            }
            else{
                cuenta.dinero += monto;
                registrarDeposito(cuenta.dinero, "colon", identificacionUsuarioTransferir);
                std::string registro = "Transferencia, Origen: Usuario " + std::to_string(usuarioActual->getIdentificacion()) +
                                    ", Efectivo, Destino: Usuario " +  std::to_string(identificacionUsuarioTransferir) + "Cuenta: Colon, Monto: " +
                                    std::to_string(monto) + ", moneda: dolar" ;
                registrarTrasaccion(registro);
                return;
            }
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Error inesperado." << std::endl;
    }
}


void Banco::transferenciaEntreCuentas(Cuenta cuentaDepositar, Cuenta cuentaRetirar, unsigned long int identificacionUsuarioTransferir){
    try {
        if (cuentaRetirar.esDolar){
            double montoDolar;
            std::cout << "Vas a transferir el dinero de la cuenta en dolares" << std::endl;
            std::cout << "Ingrese el monto en dolares que deseas transferir: " ;
            std::cin >> montoDolar;

            if (std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw  std::invalid_argument("Se ingreso un tipo de dato invalido.");
            }

            if (montoDolar <= 0) {
                throw std::invalid_argument("El monto debe ser mayor que cero.");
            }
            if (montoDolar > cuentaRetirar.dinero){
                std::cout << "No cuentas con el suficiente dinero para realizar la transferencia" <<std::endl;
                return; 
            }
            if (cuentaDepositar.esDolar){
                cuentaDepositar.dinero += montoDolar;
                cuentaRetirar.dinero -= montoDolar;
                registrarDeposito(cuentaDepositar.dinero, "dolar", identificacionUsuarioTransferir);
                registrarDeposito(cuentaRetirar.dinero, "dolar", usuarioActual->getIdentificacion());
                actualizarCuentas();
                std::string registro = "Transferencia, Origen: Usuario " + std::to_string(usuarioActual->getIdentificacion()) +
                                        ", Cuenta: Dolar, Destino: Usuario " +  std::to_string(identificacionUsuarioTransferir) + ", Cuenta: Dolar, Monto: " +
                                        std::to_string(montoDolar) + ", moneda: dolar" ;
                registrarTrasaccion(registro);
            }
            else{
                double montoColon = convertirMoneda(montoDolar, false);
                cuentaDepositar.dinero +=montoColon;
                cuentaRetirar.dinero -= montoDolar;
                registrarDeposito(cuentaDepositar.dinero, "colon", identificacionUsuarioTransferir);
                registrarDeposito(cuentaRetirar.dinero, "dolar", usuarioActual->getIdentificacion());
                actualizarCuentas();
                std::string registro = "Transferencia, Origen: Usuario " + std::to_string(usuarioActual->getIdentificacion()) +
                                        ", Cuenta: Dolar, Monto: " + std::to_string(montoDolar) + ", Destino: Usuario " +  std::to_string(identificacionUsuarioTransferir) + 
                                        ", Cuenta: Colon, Monto: " +std::to_string(montoColon) + ", moneda: Colon" ;
                registrarTrasaccion(registro);
            }
        }
        else{
            double montoColon;
            std::cout << "Vas a transferir el dinero de la cuenta en Colones" << std::endl;
            std::cout << "Ingrese el monto en colones que deseas transferir: " ;
            std::cin >> montoColon;
            if (std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw  std::invalid_argument("Se ingreso un tipo de dato invalido.");
            }
            if (montoColon <= 0) {
                throw std::invalid_argument("El monto debe ser mayor que cero.");
            }
            if (montoColon > cuentaRetirar.dinero){
                std::cout << "No cuentas con el suficiente dinero para realizar la transferencia" <<std::endl;
                return; 
            }
            if (cuentaDepositar.esDolar){
                double  montoDolar = convertirMoneda(montoColon, true);
                cuentaDepositar.dinero += montoDolar;
                cuentaRetirar.dinero -= montoColon;
                registrarDeposito(cuentaDepositar.dinero, "dolar", identificacionUsuarioTransferir);
                registrarDeposito(cuentaRetirar.dinero, "colon", usuarioActual->getIdentificacion());
                actualizarCuentas();
                std::string registro = "Transferencia, Origen: Usuario " + std::to_string(usuarioActual->getIdentificacion()) +
                                        ", Cuenta: Colon, Monto: " + std::to_string(montoColon) + ", Destino: Usuario " +  std::to_string(identificacionUsuarioTransferir) + 
                                        ", Cuenta: Dolar, Monto: " +std::to_string(montoDolar) + ", moneda: Dolar" ;
                registrarTrasaccion(registro);
            }
            else{
                cuentaDepositar.dinero +=montoColon;
                cuentaRetirar.dinero -= montoColon;
                registrarDeposito(cuentaDepositar.dinero, "colon", identificacionUsuarioTransferir);
                registrarDeposito(cuentaRetirar.dinero, "colon", usuarioActual->getIdentificacion());
                actualizarCuentas();
                std::string registro = "Transferencia, Origen: Usuario " + std::to_string(usuarioActual->getIdentificacion()) +
                                        ", Cuenta: Colon, Destino: Usuario " +  std::to_string(identificacionUsuarioTransferir) + 
                                        ", Cuenta: Colon, Monto: " +std::to_string(montoColon) + ", moneda: Colon" ;
                registrarTrasaccion(registro);
            }
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Error inesperado." << std::endl;
    }
}
