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