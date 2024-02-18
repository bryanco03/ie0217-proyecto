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

void Banco::cargarDatosUsuario(){
    std::vector<std::string> datos = obtenerDatos();
    for (auto dato : datos){
        std::cout << dato << std::endl;
    }
    std::string tipoCuenta1, dineroCuenta1Str, tipoCuenta2, dineroCuenta2Str;
    tipoCuenta1 = datos[0];
    tipoCuenta2 = datos[2];
    dineroCuenta1Str = datos[1];
    dineroCuenta2Str = datos[3];
    double dineroCuenta1 = std::stod(dineroCuenta1Str);
    double dineroCuenta2 = std::stod(dineroCuenta2Str);

    cargarCuentas(tipoCuenta1, dineroCuenta1, tipoCuenta2, dineroCuenta2);

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
            Cuenta cuenta1 = usuarioActual->getCuentas()[0];
            Cuenta* cuenta = &usuarioActual->getCuentas()[0];
            cuenta->dinero = cuenta1.dinero;
            if (cuenta->esDolar){
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
                    std::cout<<montoDolar<< std::endl;
                    std::cout<<cuenta->dinero<< std::endl;
                    cuenta->dinero += montoDolar;
                    std::cout<<cuenta->dinero<< std::endl;
                    registrarDeposito(cuenta->dinero, "dolar");
                }
                else if (opcionEfectivo == 2){
                    double montoDolar, montoColon;
                    std::cout << "Ingrese el monto a depositar: ";
                    std::cin >> montoColon;
                    montoDolar = convertirMoneda(montoColon, true);
                    std::cout << montoDolar << std::endl;
                    std::cout << cuenta->dinero << std::endl;
                    cuenta->dinero += montoDolar;
                    registrarDeposito(cuenta->dinero, "dolar");

                }
            }
            else{
        }
    }
    else if (opcion == 2){

    }
    else if (opcion == 3){

    }
    else{

    }


}
}



