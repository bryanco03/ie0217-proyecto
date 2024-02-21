#include "Usuario.hpp"
#include "Banco.hpp"
#include "funciones.hpp"

int main(){
    Banco banco;
    banco.iniciarArchivos();
    while (1){
    menuEntrada(&banco);
    }
}

