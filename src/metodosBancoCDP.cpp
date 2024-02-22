/**
 * \copyright Copyright 2024 Diego Alfaro, Bryan Cortes, Heiner Obando. All right reserved. This project is released under the MIT License
 * @file metodosBancoCDP.cpp
 * @date 17/02/2024
 * @author Diego Alfaro, Bryan Cortes, Heiner Obando
*/

#include "Banco.hpp"

/* Métodos usados por CDP. */
CDP opcionesCDP(const double monto, const int opcion, const std::string ID, const std::string moneda){

    double tasaIntereses;
    double duracionAnnos;
    // A partir de la opción del usuario se definen los intereses y el tiempo del CDP
    if(opcion == 1){
        tasaIntereses = 0.045;
        duracionAnnos = 1;
        return CDP(monto, tasaIntereses, duracionAnnos, ID, moneda);
    } else if (opcion == 2){
        tasaIntereses = 0.07;
        duracionAnnos = 2;
        return CDP(monto, tasaIntereses, duracionAnnos, ID, moneda);
    } else if (opcion == 3){
        tasaIntereses = 0.09;
        duracionAnnos = 3;
        return CDP(monto, tasaIntereses, duracionAnnos, ID, moneda);
    } else {
        return CDP(1,1,1,"", "");
    }
}

/* Métodos de banco. */
void Banco::crearCDP(){

    std::string input; // Almacena la opcion de la prueba que se desea realizar
    std::cout << "\nSe dispone de 3 diferentes tipos de certificados a plazo" << std::endl;
    std::cout << "1. Si desea un certificado a plazo de 1 anno con 4.5% de intereses" << std::endl;
    std::cout << "2. Si desea un certificado a plazo de 2 annos con 7% de intereses" << std::endl;
    std::cout << "3. Si desea un certificado a plazo de 3 annos con 9% de intereses" << std::endl;
    
    // Se recibe la opcion elegida
    std::cout << "Ingrese una opcion: ";
    std::cin >> input;

    if(!isNum(input) || std::stoi(input) > 3 || std::stoi(input) < 0){
        std::cout << "ERROR: Opcion debe ser numero entero entre 1 y 3" << std::endl;
        return;
    }
    int opcion = std::stoi(input);

    /* Se obtiene el monto para el CDP. */
    std::cout << "\nIngrese el monto que desea depositar en el CDP: ";
    double monto; std::cin >> monto;
    if(monto <= 0){
        std::cin.clear();
        std::cin.ignore(1, '\n');
        std::cout << "ERROR: Monto debe ser un numero mayor a 0." << std::endl;
        return;
    }

    /* Se obtiene el tipo de moneda. */
    std::cout << "\nIngrese el tipo de moneda \"dolar\" o \"colon\": ";
    std::string moneda; std::cin >> moneda;
    if((moneda != "dolar") && (moneda != "colon")){
        std::cout << "ERROR: Moneda ingresada no es valida." << std::endl;  
        return;
    }

    /* EN ESTE CASO EL MONTO A PAGAR SE GUARDA EN monto Y EL TIPO DE MONEDA EN moneda. */
    /* Se maneja el pago. */
    bool aprovado = false;
    std::cout << "Ingrese el metodo de pago:" << std::endl
                << "1. Efectivo. " << std::endl
                << "2. Fondos en las cuentas. " << std::endl
                << "3. Volver" << std::endl
                << "Ingrese una opcion: ";
    std::string inputPago; std::cin >> inputPago;
    int opcionPago;

    /* Manejo de errores. */
    if(!isNum(inputPago) || std::stoi(inputPago) > 3 || std::stoi(inputPago) < 0){
        std::cout << "ERROR: Opcion debe ser entero entre 1 y 3. " << std::endl;
        return;
    }
    opcionPago = std::stoi(inputPago);

    /* Métodos de pago. */
    switch (opcionPago) {
    case 1:
        aprovado = true;
        break;
    case 2:
        aprovado = pagarCuotasCuentas(monto, moneda);
        break;
    case 3:
        return;
        break;
    default:
        break;
    }

    if(!aprovado){
        std::cout << "El pago no fue aprovado" << std::endl;
        return;
    }

    /* Se genera el ID del CDP. */
    std::string primeros3 = std::to_string((*this->usuarioActual).getIdentificacion()).substr(0, 3);
    std::string ID = "C-" + primeros3 + "-" + std::to_string(this->contadorCDP);

    /* Se aumenta contador de CDPs. */
    this->contadorCDP += 1;

    /* Se obtiene el objeto a partir de la funcion creada para este fin */
    CDP cdp = opcionesCDP(monto, opcion, ID, moneda);

    /* Se crea el CSV que almacena la informacion del CDP */
    cdp.generarCSV();

    /* Se hace feedback del cdp. */
    std::cout << std::endl << "Se registro su CDP exitosamente." << std::endl;

    /* Se definen los decimales de salida de los elementos en el .log */
    std::ostringstream montoReducido;
    montoReducido << std::fixed << std::setprecision(3) << cdp.getMonto();
    std::string montoReducidoStr = montoReducido.str();
    
    std::ostringstream interesReducido;
    interesReducido << std::fixed << std::setprecision(1) << cdp.getInteres()*100;
    std::string interesReducidoStr = interesReducido.str();

    std::ostringstream tiempoReducido;
    tiempoReducido << std::fixed << std::setprecision(0) << cdp.getDuracion();
    std::string tiempoReducidoStr = tiempoReducido.str();

    /* Se crea el string que sera enviado para almacenar en el .log para el registro de transacciones */
    std::string registro = "Creacion CDP, Usuario: " + std::to_string(this->usuarioActual->getIdentificacion()) + ", ID: " +
    ID;

    /*", Monto Ingresado: " + montoReducidoStr + ',' + " Tasa de interes: " + interesReducidoStr + ", Duracion del CDP: " +
    tiempoReducidoStr + " annos.";*/
    
    /* Se llama a la funcion que maneja el registro de transacciones */
    registrarTrasaccion(registro);
    this->usuarioActual->setCdp(cdp);
}

void Banco::InfoGeneralCDP(){
    std::string input; // Almacena la opcion de la prueba que se desea realizar
    
    std::cout << "\nSe dispone de 3 diferentes tipos de certificados a plazo" << std::endl;
    std::cout << "1. Si desea un certificado a plazo de 1 anno con 4.5% de intereses" << std::endl;
    std::cout << "2. Si desea un certificado a plazo de 2 annos con 7% de intereses" << std::endl;
    std::cout << "3. Si desea un certificado a plazo de 3 annos con 9% de intereses" << std::endl;
    
    // Se recibe la opcion elegida
    std::cout << "Ingrese una opcion: ";
    std::cin >> input;

    if(!isNum(input) || std::stoi(input) > 3 || std::stoi(input) < 0){
        std::cout << "ERROR: Opcion debe ser numero entero entre 1 y 3" << std::endl;
        return;
    }
    int opcion = std::stoi(input);

    /* Se obtiene el monto para el CDP. */
    std::cout << "\nIngrese el monto que desea depositar en el CDP: ";
    double monto; std::cin >> monto;
    if(monto <= 0){
        std::cin.clear();
        std::cin.ignore(1, '\n');
        std::cout << "ERROR: Monto debe ser un numero mayor a 0." << std::endl;
        return;
    }

    /* Se obtiene el tipo de moneda. */
    std::cout << "\nIngrese el tipo de moneda \"dolar\" o \"colon\": ";
    std::string moneda; std::cin >> moneda;
    if((moneda != "dolar") && (moneda != "colon")){
        std::cout << "ERROR: Moneda ingresada no es valida." << std::endl;  
        return;
    }

    /* Se envia un ID predefinido para que no se cree un .csv del cdp */
    std::string ID = "MOSTRARINFO";

    /* Se crea el objeto */
    CDP cdp = opcionesCDP(monto, opcion, ID, moneda);

    /* Se imprime la informacion del CDP */
    std::cout << "Para un certificado de " << cdp.getMonto() << " " << cdp.getMoneda() << "es" <<
    " a un plazo de " << cdp.getDuracion() << " annos, la tasa utilizada es " <<
    cdp.getInteres()*100 << "%, recibiendo al final del plazo " << cdp.getMontoGanado() <<std::endl;

}

void Banco::mostrarInfoCDP(){

    /* Se imprimen los CDPs propios. */
    
    std::cout << "\n-----Informacion de sus certificados a plazo-----" << std::endl;
    /* Se imprimen los certificados a plazo del usuario que este loggeado en el sistema */
    for(auto& cdp: this->usuarioActual->getCdps()){
        /* Se imprime la informacion del CDP */
        std::cout << "ID del CDP: " << cdp.getID() <<
        ", Monto ingresado: " << cdp.getMonto() << ", Tasa de intereses: " <<
        cdp.getInteres()*100 << "%, Duracion: " << cdp.getDuracion() << 
        " annos, monto recibido al final del plazo: " << cdp.getMontoGanado() <<std::endl;
    }
    return;
}    

CDP Banco::leerCDP(std::string idCDP){
    /* Se crean variables a usar. */
    std::string linea, primeraLinea;                        /*String de IDs y linea a leer del csv. */
    std::ifstream database("datos\\" + idCDP + ".csv");     /* Se lee el archivo csv. */
    std::vector<std::string> infoC;                         /* Vector con la informacion del CDP. */

    /* Se busca el CDP. */
    if(!database.good()){
        return CDP(1, 1, 1, "ERROR", "");
    }

    /* Se ignora la primera linea. */
    std::getline(database, primeraLinea);

    /* Se cargan los datos. */
    while(std::getline(database, linea)){
        /* Se lee la linea y se guarda en infoC. */
        std::stringstream datos(linea);
        while(datos.good()){
            std::string columna;
            std::getline(datos, columna, ',');
            infoC.push_back(columna);
        }
    }

    /* Se cierra el archivo.*/
    database.close();

    CDP cdp(std::stod(infoC[0]), std::stof(infoC[1]), std::stoi(infoC[2]), idCDP, infoC[4]);
    
    return cdp;
}

void Banco::cargarCDPs(std::string idCDPs){
    if(idCDPs == " "){
        return;
    }
    std::stringstream streamID(idCDPs);
    std::string id;

    while(std::getline(streamID, id, ' ')){
        CDP cdp = this->leerCDP(id);
        if(cdp.getID() != "ERROR"){
            this->usuarioActual->setCdp(cdp);
        }
    }
}