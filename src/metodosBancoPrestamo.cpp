/**
 * \copyright Copyright 2024 Diego Alfaro, Bryan Cortes, Heiner Obando. All right reserved. This project is released under the MIT License
 * @file metodosBancoPrestamo.cpp
 * @date 15/02/2024
 * @author Diego Alfaro, Bryan Cortes, Heiner Obando
*/

#include "Banco.hpp"

/* Funciones usadas por los métodos, que no son miembros de banco. */
Prestamos opcionesPrestamo(const double monto, std::string moneda, const int tipo, const std::string ID){
    /* Se definen los meses e intereses dependiendo del tipo de prestamo. */
    std::vector<std::string> tipos = {"Personal", "Hipotecario", "Prendario"};
    std::vector<int> meses;
    std::vector<int> intereses;

    if(tipo == 1){
        meses.insert(meses.end(), {5, 10, 12});
        intereses.insert(intereses.end(), {15, 7, 5});
    } else if (tipo == 2) {
        meses.insert(meses.end(), {12, 24, 36});
        intereses.insert(intereses.end(), {15, 10, 5});
    } else if (tipo == 3){
        meses.insert(meses.end(), {10, 20, 30});
        intereses.insert(intereses.end(), {13, 7, 5});
    }

    /* Se imprime menu de opciones según el tipo. */
    std::cout << "Escoja una de las siguientes opciones:" << std::endl
              << "1. " << meses[0] << " meses a " << intereses[0] << "% de interes." << std::endl
              << "2. " << meses[1] << " meses a " << intereses[1] << "% de interes." << std::endl
              << "3. " << meses[2] << " meses a " << intereses[2] << "% de interes." << std::endl;
    std::cout << "Ingrese la opcion: ";
    int opcion = -1; 
    std::string input;
    std::cin >> input;

    if(isNum(input)){
        opcion = std::stoi(input);
    }

    switch (opcion) {
    case -1:
        return Prestamos("ERROR", "", 0, "", 0, 0);
    case 1:
        return Prestamos(ID, tipos[tipo - 1], monto, moneda, intereses[0], meses[0]);
        break;

    case 2:
        return Prestamos(ID, tipos[tipo - 1], monto, moneda, intereses[1], meses[1]);
        break;

    case 3:
        return Prestamos(ID, tipos[tipo - 1], monto, moneda, intereses[2], meses[2]);
        break;
    default:
        return Prestamos("ERROR", "", 0, "", 0, 0);
        break;
    }
}

Prestamos Banco::leerPrestamo(std::string idPrestamo){
    /* Se crean variables a usar. */
    std::string ID_CSV, linea;                      /*String de IDs y linea a leer del csv. */
    std::ifstream database("datos\\Prestamos.csv"); /* Se lee el archivo csv. */
    std::vector<std::string> infoP;                 /* Vector con la informacion del prestamo. */

    /* Se busca el prestamo. */
    while(std::getline(database, linea)){
        ID_CSV = linea.substr(0, linea.find(','));

        /* Si se encuentra se lee la linea y se guarda en infoP. */
        if(idPrestamo == ID_CSV){
            std::stringstream datos(linea);
            while(datos.good()){
                std::string columna;
                std::getline(datos, columna, ',');
                infoP.push_back(columna);
            }
        }
    }

    /* Se cierra el archivo.*/
    database.close();

    /* Si no se encontró el prestamo se imprime el error. */
    if(infoP.size() == 0){
        return Prestamos("ERROR", "", 1, "", 1, 1);
    }

    /* Si se encontró se crea el objeto y se paga el prestamo. */
    Prestamos prestamo(infoP[0], infoP[1], std::stod(infoP[2]), infoP[3], std::stof(infoP[4]),
                       std::stoi(infoP[5]), std::stoi(infoP[6]));
    
    return prestamo;
}

/* Métodos de Banco. */

void Banco::cargarPrestamos(std::string idPrestamos){
    if(idPrestamos == " "){
        return;
    }
    std::stringstream streamID(idPrestamos);
    std::string id;

    while(std::getline(streamID, id, ' ')){
        Prestamos prestamo = this->leerPrestamo(id);
        if(prestamo.getID() != "ERROR"){
            this->usuarioActual->setPrestamo(prestamo);
        }
    }
}

void Banco::crearPrestamo(bool generico){
    /* Se imprime el menú. */
    std::cout << "\nEscoja el tipo de prestamo a realizar: " << std::endl
              << "1. Personal" << std::endl
              << "2. Hipotecario" << std::endl
              << "3. Prendario" << std::endl;
    std::cout << "Ingrese la opcion: ";

    /* Se obtiene la opción de prestamo a crear. */
    std::string tipoInput; std::cin >> tipoInput;
    int tipo;
    if(!isNum(tipoInput) || std::stoi(tipoInput) > 3 || std::stoi(tipoInput) < 0){
        std::cout << "ERROR: Opcion dada debe ser entero entre 1 y 3." << std::endl;
        return;
    }
    tipo = std::stoi(tipoInput);

    /* Se obtiene el tipo de moneda. */
    std::cout << "\nIngrese el tipo de moneda \"dolar\" o \"colon\": ";
    std::string moneda; std::cin >> moneda;
    if((moneda != "dolar") && (moneda != "colon")){
        std::cout << "ERROR: Moneda ingresada no es valida." << std::endl;  
        return;
    }

    /* Se obtiene el monto del prestamo. */
    std::cout << "Ingrese el monto del prestamo: ";
    double monto; std::cin >> monto;
    if(monto <= 0){
        std::cin.clear();
        std::cin.ignore(1, '\n');
        std::cout << "ERROR: Monto debe ser un numero mayor a 0." << std::endl;
        return;
    }

    /* Se genera el ID del prestamo. */
    std::string ID;
    if(!generico){
        std::string primeros3 = std::to_string(this->usuarioActual->identificacion).substr(0, 3);
        ID = "P-" + primeros3 + "-" + std::to_string(this->contadorPrestamos);
    } else {
        ID = "TABLA";
    }

    /* Se aumenta contador de prestamos. */
    this->contadorPrestamos += 1;

    /* Se crea el prestamo. */
    Prestamos prestamo = opcionesPrestamo(monto, moneda, tipo, ID);
    if (prestamo.getID() == "ERROR") {
        std::cout << "ERROR: Opcion debe ser un entero entre 1 y 3." << std::endl;
        return;
    }
    
    prestamo.generarCSV();
    std::cout << "Tabla de prestamo generada en " << ID << ".csv." << std::endl;

    /* Si no es generado por modo información general se guarda en el usuario. */
    if (!generico) {
        this->usuarioActual->setPrestamo(prestamo);
        std::string registro = "Creacion Prestamo, Usuario: " + std::to_string((*this->usuarioActual).identificacion) +
                               ", ID del prestamo: " + ID;
        registrarTrasaccion(registro);
    } else {
        std::string registro = "Creacion tabla de Prestamo en modo información general";
        registrarTrasaccion(registro);
    }
}

void Banco::mostrarInfoPrestamos(){
    /* Se imprimen instrucciones del menu. */
    std::cout << "\n-----Menu de mostrar prestamos-----" << std::endl;
    std::cout << "Ingrese la identificacion del usuario para mostrar sus prestamos\nAlternativamente, ingrese \"Yo\" para ver los suyos: ";
    std::string idUsuario; std::cin >> idUsuario;

    /* Caso donde se ven los prestamos propios. */
    if(idUsuario == "Yo"){

        if(this->usuarioActual->getPrestamos().size() == 0){
            std::cout << "\nUsted no posee prestamos actualmente." << std::endl;
            return;
        }

        std::cout << "\n-----Informacion de sus prestamos-----" << std::endl;
        for(auto& prestamo: this->usuarioActual->getPrestamos()){
            prestamo.mostrarInfo();
        }
        return;
    }

    /* Prestamos del nombre dado. */
    std::string idCSV, linea, sinNombre, columna, idPrestamos, id;
    std::ifstream database("datos\\usuarios.csv");
    bool encontrado = false;

    while(std::getline(database, linea)){
        sinNombre = linea.substr(linea.find(',') + 1);
        idCSV = sinNombre.substr(0, sinNombre.find(','));
        if(idCSV == idUsuario){
            encontrado = true;
            int i = 0;
            std::stringstream datos(linea);
            while(std::getline(datos, columna, ',')){
                if(i == 6){
                    idPrestamos = columna;
                }
                i++;
            }
        }
    }
    database.close();

    if(!encontrado){
        std::cout << "Id de usuario no encontrado." << std::endl;
        return;
    }

    if(idPrestamos == " "){
        std::cout << "\nEste cliente no posee prestamos actualmente." << std::endl;
        return;
    }

    std::stringstream idParseados(idPrestamos);
    while(std::getline(idParseados, id, ' ')){
        Prestamos prestamo = this->leerPrestamo(id);
        if(prestamo.getID() != "ERROR"){
            prestamo.mostrarInfo();
        }
    }
}

void Banco::pagarPrestamos(){
    /* Se crean variables a usar. */
    std::string ID_P;

    /* Se imprime el menu y se recibe el ID del prestamo a pagar. */
    std::cout << "\n-----Menu de pago de prestamos-----" << std::endl;
    std::cout << "Puede pagar cualquier prestamo (suyo o no) con el ID, estos tienen la forma \"P-123-0\". " << std::endl;
    std::cout << "Ingrese el ID del prestamo al que quiere pagar una cuota: ";
    std::cin >> ID_P;

    /* Se busca el prestamo, si no se encuentra se muestra el error. */
    Prestamos prestamo = this->leerPrestamo(ID_P);
    if(prestamo.getID() == "ERROR"){
        std::cout << "No se encontro ningun prestamo con ese Id" << std::endl;
        return;
    }

    /* Se obtiene el monto, si ya ha sido pagado se retorna. */
    double cuotaMensual = prestamo.getCuota();
    if(cuotaMensual == -1){
        std::cout << "Prestamo ya ha sido pagado completamente." << std::endl;
        return;
    }

    /* Se maneja el pago. */
    bool aprovado = false;
    std::cout << "La cuota a pagar es: " << cuotaMensual << prestamo.getMoneda() << std::endl;
    std::cout << "Ingrese el metodo de pago:" << std::endl
                << "1. Efectivo. " << std::endl
                << "2. Fondos en las cuentas. " << std::endl
                << "3. Volver" << std::endl
                << "Ingrese una opcion: ";
    std::string input; std::cin >> input;
    int opcion;

    /* Manejo de errores. */
    if(!isNum(input) || std::stoi(input) > 3 || std::stoi(input) < 0){
        std::cout << "ERROR: Opcion debe ser entero entre 1 y 3. " << std::endl;
        return;
    }
    opcion = std::stoi(input);

    /* Métodos de pago. */
    switch (opcion) {
    case 1:
        aprovado = true;
        break;
    case 2:
        break;
    case 3:
        return;
        break;
    default:
        break;
    }

    if(aprovado){
        prestamo.pagarCuota();
        std::string registro = "Pago de cuota de prestamo, Usuario: " + std::to_string((*this->usuarioActual).identificacion) +
                                ", ID del prestamo: " + ID_P;
        registrarTrasaccion(registro);
    } else {
        std::cout << "ERROR: Pago no fue aprobado." << std::endl;
        return;
    }
}
