#include "Cdp.hpp"

CDP::CDP(double monto, float tasaIntereses, double duracionAnnos, std::string ID, std::string moneda){

    // Se almacenan los valores recibidos por parte del usuario
    this->monto = monto;
    this->tasaIntereses = tasaIntereses;
    this->duracionAnnos = duracionAnnos;
    this->ID = ID;
    this->moneda = moneda;
    
    /* 
    A partir de los datos recibidos se calculara la ganancia que
    recibira el cliente, se utiliza la formula que se encontro
    durante la investigacion para calcular el CDP, el metodo pow()
    se utiliza para realizar potencias en C++
    */
    this->montoGanado = this->monto * pow((1 + (this->tasaIntereses / 1)), 1 * this->duracionAnnos);

    if(this->ID != "MOSTRARINFO" && this->ID != "ERROR"){
        guardarCSV();
    }

}

void CDP::generarCSV(){

    /* Se abre el archivo .csv con el nombre del ID */
    std::ofstream archivo("datos\\" + this->ID + ".csv");
    archivo << "Monto ingresado,Tasa de intereses,Tiempo del CDP (annos),Monto ganado,Moneda\n";

    /* Se almacenan la informacion del CDP en una linea del CDP */
    archivo << this->monto << "," << this->tasaIntereses << ","
            << this->duracionAnnos << "," << this->montoGanado
            << "," << this->moneda << std::endl;
    
    /* Se cierra el archivo, evitando errores de esta manera */
    archivo.close();
}

void CDP::guardarCSV(){

    /* Se abre el archivo de registro. */
    std::string nombreArchivo = "datos\\CDP.csv";
    
    /* Se abre el archivo .csv previamente creado */
    std::ifstream viejo(nombreArchivo);

    /* Se crea un archivo .csv temporal */
    std::ofstream nuevo("temp1.csv");

    /* Se declaran las variables necesarias a utilizar para
    almacenar los archivos */
    std::string linea, ID_CSV;
    bool encontrado = false;

    /* Se lee cada linea del archivo. */
    while(std::getline(viejo, linea)){
        /* Se obtiene el id de la linea. */
        ID_CSV = linea.substr(0, linea.find(','));
        /* Si se encuentra el mismo id del prestamo se actualiza. */
        if(ID_CSV == this->ID){
            nuevo << this->ID << "," << this->monto << ","
                  << this->tasaIntereses << "," << this->duracionAnnos << ","
                  << this->montoGanado << "," << this->moneda << std::endl;
            encontrado = true;
        } else {
            /* Si no se encuentra se mantiene la linea. */
            nuevo << linea << std::endl;
        }
    }

    /* Si no se encontró se agrega al final. */
    if(!encontrado){
        nuevo << this->ID << "," << this->monto << ","
              << this->tasaIntereses << "," << this->duracionAnnos << ","
              << this->montoGanado << "," << this->moneda << std::endl;
    }

    /* Se guardan ambos archivos. */
    viejo.close();
    nuevo.close();

    /* Se remueve el archivo viejo y se renombra al nuevo como el csv original. */
    remove(nombreArchivo.c_str());
    rename("temp1.csv", nombreArchivo.c_str());
}

double CDP::getMonto(){
    return this->monto;
}

float CDP::getInteres(){
    return this->tasaIntereses;
}

double CDP::getDuracion(){
    return this->duracionAnnos;
}

double CDP::getMontoGanado(){
    return this->montoGanado;
}

std::string CDP::getID(){
    return this->ID;
}

std::string CDP::getMoneda(){
    return this->moneda;
}

