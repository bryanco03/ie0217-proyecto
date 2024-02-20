#include "Prestamos.hpp"

Prestamos::Prestamos(std::string ID, std::string tipo, double monto, std::string moneda, float tasaInteres, int duracionMeses, int cuotasPagadas /*= 0*/)
    : ID(ID), tipo(tipo), monto(monto), moneda(moneda), tasaInteres(tasaInteres), duracionMeses(duracionMeses), cuotasPagadas(cuotasPagadas) {

    /* Se define el estado del prestamo. */
    if(this->cuotasPagadas >= duracionMeses){
        this->estado = "Pagado";
    } else {
        this->estado = "En proceso de pago.";
    }

    /* Se definen variables por medio de fórmulas. */
    double tasaMensual = this->tasaInteres/(12*100);
    this->cuotaMensual = (this->monto * tasaMensual)/(1 - std::pow(1 + tasaMensual,-this->duracionMeses));

    if(ID != "ERROR"){
        guardarCSV();
    }
}

void Prestamos::generarCSV(){
    /* Se definen variables por medio de fórmulas. */
    double tasaMensual = this->tasaInteres/(12*100);
    double montoRestante = this->monto;

    /* Se abre el archivo .csv */
    std::ofstream archivo ("datos\\" + this->ID + ".csv");
    archivo << "Mes,Cuota Mensual,Intereses,Amortizacion,Monto Restante";
    if(this->ID != "TABLA"){
        archivo << ",Estado" << std::endl;
    } else {
        archivo << std::endl;
    }

    /* Se escribe linea por linea lo necesario. */
    for(int i = 0; i < this->duracionMeses; i++){
        float intereses = montoRestante * tasaMensual;
        float amortizacion = this->cuotaMensual - intereses;
        montoRestante -= amortizacion;
        archivo << i + 1 << "," << this->cuotaMensual << ","
        << intereses << "," << amortizacion << ","
        << montoRestante;

        if(this->ID != "TABLA"){
            archivo << ",NO PAGADO" << std::endl;
        } else {
            archivo << std::endl;
        }
    }
    archivo.close();
}

void Prestamos::guardarCSV(){
    /* Se abre el archivo de registro. */
    std::string nombreArchivo = "datos\\Prestamos.csv";
    std::ifstream viejo(nombreArchivo);
    std::ofstream nuevo("temp1.csv");

    std::string linea, ID_CSV;
    bool encontrado = false;

    while(std::getline(viejo, linea)){
        ID_CSV = linea.substr(0, linea.find(','));
        if(ID_CSV == this->ID){
            nuevo << this->ID << "," << this->tipo << ","
                  << this->monto << "," << this->moneda << ","
                  << this->tasaInteres << "," << this->duracionMeses << ","
                  << this->cuotasPagadas << std::endl;
            encontrado = true;
        } else {
        nuevo << linea << std::endl;
        }
    }

    if(!encontrado){
        nuevo << this->ID << "," << this->tipo << ","
                << this->monto << "," << this->moneda << ","
                << this->tasaInteres << "," << this->duracionMeses << ","
                << this->cuotasPagadas << std::endl;
    }

    /* Se guardan ambos archivos. */
    viejo.close();
    nuevo.close();

    /* Se remueve el archivo viejo y se renombra al nuevo como el csv original. */
    remove(nombreArchivo.c_str());
    rename("temp1.csv", nombreArchivo.c_str());
}

void Prestamos::pagarCuota(){
    /* Por compatibilidad se guarda el nombre como const char*. */
    std::string nombreArchivo = "datos\\" + this->ID + ".csv";
    std::ifstream viejo(nombreArchivo);
    std::ofstream nuevo("temp2.csv");
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
    remove(nombreArchivo.c_str());
    rename("temp2.csv", nombreArchivo.c_str());

    guardarCSV();
}

void Prestamos::mostrarInfo(bool generico){
    /* Se imprime la información del prestamo. */
    if(!generico){
        std::cout << "ID del prestamo: " << this->ID << ",  ";
    }

    std::cout << "Tipo: " << this->tipo
    << ",  Monto: " << this->monto
    << ",  Moneda: " << this->moneda
    << ",  Tasa de interes anual: " << this->tasaInteres
    << ",  Cantidad de meses: " << this->duracionMeses
    << ",  Cuota mensual: " << this->cuotaMensual;

    if(!generico){
        std::cout << ",  Estado: " << this->estado << std::endl;
    } else {
        std::cout << std::endl;
    }
}

std::string Prestamos::getID(){
    return this->ID;
}

double Prestamos::getCuota(){
    if(this->estado == "Pagado"){
        return -1;
    } else {
        return this->cuotaMensual;
    }
}

std::string Prestamos::getMoneda(){
    return this->moneda;
}