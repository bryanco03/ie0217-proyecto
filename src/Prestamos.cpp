#include "Prestamos.hpp"

Prestamos::Prestamos(std::string ID, std::string tipo, double monto, float tasaInteres, int duracionMeses, int cuotasPagadas /*= 0*/)
    : ID(ID), tipo(tipo), monto(monto), tasaInteres(tasaInteres), duracionMeses(duracionMeses), cuotasPagadas(cuotasPagadas) {

    /* Se define el estado del prestamo. */
    if(this->cuotasPagadas >= duracionMeses){
        this->estado = "Pagado";
    } else {
        this->estado = "En proceso de pago.";
    }

    /* Se definen variables por medio de fórmulas. */
    double tasaMensual = this->tasaInteres/(12*100);
    this->cuotaMensual = (this->monto * tasaMensual)/(1 - std::pow(1 + tasaMensual,-this->duracionMeses));
}

void Prestamos::generarCSV(){
    /* Se definen variables por medio de fórmulas. */
    double tasaMensual = this->tasaInteres/(12*100);
    double montoRestante = this->monto;

    /* Se abre el archivo .csv */
    std::ofstream archivo ("datos\\" + this->ID + ".csv");
    archivo << "Mes,Cuota Mensual,Intereses,Amortizacion,Monto Restante,Estado\n";

    /* Se escribe linea por linea lo necesario. */
    for(int i = 0; i < this->duracionMeses; i++){
        float intereses = montoRestante * tasaMensual;
        float amortizacion = this->cuotaMensual - intereses;
        montoRestante -= amortizacion;
        archivo << i + 1 << "," << this->cuotaMensual << ","
        << intereses << "," << amortizacion << ","
        << montoRestante << ",NO PAGADO" << std::endl;
    }
    archivo.close();
    this->guardarCSV();
}

void Prestamos::guardarCSV(){
    /* Se abre el archivo de registro. */
    std::ifstream viejo("datos\\Prestamos.csv");
    std::ofstream nuevo("temp.csv");

    std::string linea;

    while(std::getline(viejo, linea)){
        nuevo << linea << std::endl;
    }

    nuevo << this->ID << "," << this->tipo << ","
          << this->monto << "," << this->tasaInteres << ","
          << this->duracionMeses << "," << this->cuotasPagadas << std::endl;

    /* Se guardan ambos archivos. */
    viejo.close();
    nuevo.close();

    /* Se remueve el archivo viejo y se renombra al nuevo como el csv original. */
    remove("datos\\Prestamos.csv");
    rename("temp.csv", "datos\\Prestamos.csv");
}

void Prestamos::pagarCuota(){
    /* Por compatibilidad se guarda el nombre como const char*. */
    const char path[7] = "datos\\";
    const char * nombreArchivo =  path + *(ID + ".csv").c_str();
    std::ifstream viejo(nombreArchivo);
    std::ofstream nuevo("temp.csv");
    std::string temp, linea, palabra;
    int mesActual = 0;
    int cantidadLineas = 0;

    while(std::getline(viejo, linea)){
        if(mesActual == this->cuotasPagadas + 1){
            std::string datos = linea.substr(0, linea.find("NO PAGADO"));
            nuevo << datos << "PAGADO" << std::endl;
        } else {
            nuevo << linea << std::endl;
        }
        cantidadLineas += 1;
        mesActual += 1;
    }

    /* Se imprime mensaje de que se pagó la cuota. */
    std::cout << "Se ha pagado la cuota exitosamente" << std::endl;

    /* Se aumentan la cantidad de cuotas pagadas. */
    this->cuotasPagadas += 1;

    /* Si se han pagado todas las cuotas se registra como pagado. */
    if(cuotasPagadas == cantidadLineas - 1){
        std::cout << "El prestamo se ha pagado completamente, "
        << "se va a registrar como pagado."<< std::endl;
        this->estado = "Pagado";
    }

    /* Se guardan ambos archivos. */
    viejo.close();
    nuevo.close();

    /* Se remueve el archivo viejo y se renombra al nuevo como el csv original. */
    remove(nombreArchivo);
    rename("temp.csv", nombreArchivo);
}

void Prestamos::mostrarInfo(){
    /* Se imprime la información del prestamo. */
    std::cout << "ID del prestamo: " << this->ID
    << ",  Tipo: " << this->tipo
    << ",  Monto: " << this->monto
    << ",  Tasa de interes anual: " << this->tasaInteres
    << ",  Cantidad de meses: " << this->duracionMeses
    << ",  Cuota mensual: " << this->cuotaMensual
    << ",  Estado: " << this->estado << std::endl;
}

std::string Prestamos::getID(){
    return this->ID;
}