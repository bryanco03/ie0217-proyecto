#include "Banco.hpp"


void Banco::menuAtencionCliente(){
    int opcion;
    if (usuarioLogeado){
        cargarDatosUsuario();
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
            std::cout << "8. Atras"<< std::endl; 
            std::cout << "Ingrese una opcion: ";
            std::cin >> opcion;

            switch (opcion)
            {
            case 1:
                crearCuenta();
                break;
            case 8:
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

/*
    void Banco::loggearUsuario(){
        std::cout << "Ingrese identificación del usuario a loggear: ";
        std::string id; std::cin >> id;

        std::string id_csv, linea, sinNombre;
        std::ifstream database("datos\\usuarios.csv");
        std::vector<std::string> infoP, columnas;

        while(std::getline(database, linea)){
            sinNombre = linea.substr(linea.find(',') + 1);
            id_csv = sinNombre.substr(0, sinNombre.find(','));
            std::cout << id_csv << ',';
            if(id_csv == id){   
                Usuario user(std::stoul(id));
                this->usuarioActual = &user;
            }
        }
        database.close();
}
*/
