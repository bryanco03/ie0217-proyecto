/**
 * @file BancoRegistroDatos.cpp
 * @author Diego Alfaro, Bryan Cortes, Heiner Obando
 * @brief Implementacion de algunos métodos sobre escritura y lectura de archivos csv de Clase Banco
 * @version 0.1
 * @date 2024-02-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */



#include "Banco.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

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

bool Banco::verificarIdentificacioEnCSV(unsigned long int identificacionBuscada) {
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

void Banco::registrarDeposito(double monto, std::string tipoCuenta, unsigned long int identificacionBuscar){
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
            std::string montoStr = std::to_string(monto);
            if (identificacion == identificacionBuscar) {
                if (tipoCuenta1 == tipoCuenta) {
                    // Modificar la moneda de la cuenta
                    nuevoContenido << nombre << "," << identificacionStr << "," << tipoCuenta1 << ","
                                   << montoStr << "," << tipoCuenta2 << "," << dineroCuenta2 << ","
                                   << idPrestamos << "," << idCdps << "\n";
                } else if (tipoCuenta2 == tipoCuenta) {
                    nuevoContenido << nombre << "," << identificacionStr << "," << tipoCuenta1 << ","
                                   << dineroCuenta << "," << tipoCuenta2 << "," << montoStr << ","
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

std::vector<Cuenta> Banco::cuentasTransferibles(unsigned long int identificacion){
    std::vector<Cuenta> cuentas;
    std::vector<std::string> datos =  obtenerDatos(identificacion);
    std::string tipoCuenta1, tipoCuenta2, dineroCuenta1Str, dineroCuenta2Str;
    tipoCuenta1 = datos[0];
    tipoCuenta2 = datos[2];
    dineroCuenta1Str = datos[1];
    dineroCuenta2Str = datos[3];
    double dineroCuenta1 = std::stod(dineroCuenta1Str);
    double dineroCuenta2 = std::stod(dineroCuenta2Str);
    if (tipoCuenta1 == "dolar"){
        Cuenta cuentaDolar;
        cuentaDolar.esDolar = true;
        cuentaDolar.dinero = dineroCuenta1;
        cuentas.push_back(cuentaDolar);
    }
    else if (tipoCuenta1 == "colon"){
        Cuenta cuentaColon;
        cuentaColon.esDolar = false;
        cuentaColon.dinero = dineroCuenta1;
        cuentas.push_back(cuentaColon);
    }
    if (tipoCuenta2 == "dolar"){
        Cuenta cuentaDolar2;
        cuentaDolar2.esDolar = true;
        cuentaDolar2.dinero = dineroCuenta2;
        cuentas.push_back(cuentaDolar2);
    }
    else if (tipoCuenta2 == "colon"){
        Cuenta cuentaColon2;
        cuentaColon2.esDolar = false;
        cuentaColon2.dinero = dineroCuenta2;
        cuentas.push_back(cuentaColon2);
    }
    return cuentas;
}
