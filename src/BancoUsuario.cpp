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





