#include "Banco.hpp"

void Banco::iniciarContadores(){
    /* Se obtiene el contador de prestamo. */
    /* https://stackoverflow.com/questions/3072795/how-to-count-lines-of-a-file-in-c */
    std::ifstream inFile("datos//Prestamos.csv"); 
    this->contadorPrestamos = std::count(std::istreambuf_iterator<char>(inFile), 
                                         std::istreambuf_iterator<char>(), '\n') - 1;
    inFile.close();

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