# ie0217-proyecto

# Temas a investigar 

## 1. Información sobre préstamos personales, prendarios e hipotecarios

Con este proyecto se busca crear una simulación de una aplicación bancaria, por lo que es necesario conocer algunos de los conceptos que se manejan en este ámbito y se buscan aplicar en la aplicación a crear, uno de los primeros conceptos a revisar son los préstamos, éxisten diferentes tipos de préstamos, se podrían comenzar hablando sobre los préstamos personales, estos se tratan de una operación bancaria, donde el banco presta un determinado capital a un cliente. Luego de cerrado el trato entre el banco y el cliente, este último debe de abonar el capital prestado de vuelta al banco, junto con una serie de interesés que fue definida entre el cliente y el banco al momento de iniciar con el proceso del préstamo.[5]

Existen diferentes tipos de préstamos además del préstamo personal anteriormente mencionado, uno de estos es el crédito prendario, en este caso el cliente entrega a la entidad que realiza el préstamo un objeto como garantía, como lo pueden ser obras de arte o joyas, al igual que en el caso anterior, al momento de recibir el dinero, el cliente debe comenzar a realizar abonos del capital con una tasa de interés determinada, en este caso el cliente debe cancelar el monto total del préstamo junto con los interés establecidos para recuperar el bien que dejó en custodia con el banco, en caso de que el cliente se niegue a pagar el préstamo el objeto pasará a ser propiedad del banco.[6]

Por otra parte, se tiene uno de los préstamos más cómunes utilizado por las personas para poder conseguir contruir sus viviendas, el préstamo hipotecario, este un préstamo es utilizado para la adquisición de un bien inmueble por parte del cliente. En este caso el crédito dado por el banco no superará el valor de la vivienda que se desea adquirir, esto es así ya que, el inmueble adquirido por el usuario se grava con una hipoteca, esto significa que en caso de que el cliente no pague el crédito al banco, este tendrá la libertad de hacer valer la garantía hipotecaria y vender el inmueble hipotecado, con el fin de saldar la deuda del crédito entrega al cliente, en caso de que el banco logre vender el inmueble por un precio mayor a la deuda del cliente, el excedente será entregado al cliente, pero si, el precio de venta es menor a la deuda, el banco tendrá derecho a apropiarse de los bienes presentes y futuros del deudor, hasta que la deuda quede saldada.[7]


La forma en que los pagos de interéses son realizados se encuentran en el punto 2. Y la forma en que se pueden manejar los préstamos en este proyecto es mencionada en el punto 6 de este documento.

## 2. Como obtener la tabla mediante valores personalizados demonto, cantidad de cuotas y la tasa de interés

### Variables del préstamo.
1.	Préstamo: Cantidad a pagar
2.	Tasa de interés: Usualmente es interés anual fijo.

    ```
    Simple interest: Solo se agrega interés por la cantidad principal.
    Compound interest: Calcula el porcentaje con la cantidad principal y con cantidad ganada por interés en periodos pasados. [9]
    ```

3.	Plazo del préstamo: En cuanto tiempo se debe pagar el préstamo.
4.	Frecuencia de pago: Cada cuanto se paga la cuota.
5.	Número de cuotas: Plazo * frecuencia.

    ```
    Esta es una de las ingresadas según instrucciones, asumiendo que son mensuales, se toma como cantidad de meses. Por ende, es mejor usar la primera fórmula de cuota mensual si el input es número de cuotas y es mensual el pago. Así se ignoran las variables de plazo, frecuencia, m y n.
    ```

### Variables a calcular:
* Cuota mensual: El pago que se debe hacer cada mes, incluye el pago de intereses y pago de deuda. Fórmulas de cuota mensual para tasa fija:

    <a><img src="https://github.com/DiegoAlfaroUCR/repoImagenes/blob/9c2612ae3a7fb4ac7dd806ae3d0d651074d41ff3/imagenesProyecto/cuotasMensuales1.svg?raw=true"></a>

    Tomada de [3]

    <a><img src="https://github.com/DiegoAlfaroUCR/repoImagenes/blob/803c59cf447e9d7d332710a02954c8c79d73534e/imagenesProyecto/cuotasMensuales2.svg?raw=true"></a>

    Tomada de [8]

    P: Valor del préstamo

    CM: Cantidad de meses a pagar.

    i: Tasa de interés nominal anual (en porcentaje, osea para 3% usar 0.003)

    m: Número de capitalizaciones en el año

    n: Número de años

* Interés compuesto: Cantidad a pagar restante * Interés mensual = Cuota restante * Tasa interés/12
* Cantidad pagada a deuda = cuota mensual – interés compuestos
* Cantidad a pagar restante = Cantidad a pagar restante – cuota mensual

## 3. Certificados de depósito a plazo (CDP)

Otro tema a tratar dentro del proyecto, son los certificados de depósito a plazo, estos consisten en un depósito que realiza el cliente al banco, donde esté recibirá el dinero y trabajará con él durante un tiempo establecido por un acuerdo entre el banco y el cliente, inicialmente la idea de este proceso es que el cliente no pueda retirar el dinero durante el tiempo establecido y cuando este tiempo termine, el banco devolverá al cliente el dinero depositado, más una cantidad de interés extra generados por el tiempo que estuvo el dinero en el banco.[2]

La fórmula para generar los interéses ganados por el cliente es la siguiente:

<a><img src="https://latex.codecogs.com/svg.image?\color{White}A=P\cdot(1+r/n)^{nt}"></a>

Tomada de [10]

Donde:

A = Es el saldo que recibirá el cliente, su depósito más los interéses.

P = Depósito inicial que realizó el cliente.

r = Tasa de interés anual.

t = Plazo en años que estará el depósito en el banco.

n = número de períodos de capitalización por año (Cuantas veces se capitalizan las ganancias al año).

Para su implementación en C++ se puede crear una clase CDP, que tenga como atributos las variables para calcular el CDP, así como una variable que indique si el depósito del cliente será en dólares o colones. Utilizando un método de la clase que incorporé la fórmula anterior se podría obtener la ganancia que obtendría el cliente dependiendo de la cantidad de dinero y la cantidad de tiempo que deje el dinero en el banco. La instancia de esta clase podría ser almacenada de forma que cada cliente tenga acceso a su respectivo CDP realizado.

## 4. Registro de transacciones

El registro de transacciones en los bancos es esencial para mantener un historial exacto de todas las operaciones financieras realizadas en las cuentas de los clientes. Estos registros abarcan una amplia gama de transacciones, como depósitos, retiros, transferencias, pagos de facturas y cualquier otra actividad relacionada con el dinero.

El proceso de registro de transacciones contables implica varias etapas. En primer lugar, se identifican las transacciones relevantes y se clasifican según su naturaleza (ventas, compras, gastos, ingresos, etc.). Luego, la información de la transacción se registra en los libros contables utilizando el método de partida doble.

El método de partida doble requiere que cada transacción afecte al menos a dos cuentas contables: una cuenta se debita (incrementa), y otra se acredita (disminuye). Esta doble entrada asegura que el balance contable siempre esté equilibrado.
Hay varios elementos clave que componen una transacción contable:

- Cuenta: Es la categoría utilizada para clasificar y agrupar las transacciones contables. Las cuentas pueden ser de diferentes tipos, como activos, pasivos, capital, ingresos y gastos.

- Débito: Es el lado izquierdo de una transacción contable, donde se registra lo que se recibe o se obtiene. Representa los activos y los gastos.

- Crédito: Es el lado derecho de una transacción contable, donde se registra lo que se da o se entrega. Representa los pasivos, el capital y los ingresos.

Es crucial que estos elementos estén presentes en una transacción contable para asegurar la precisión y consistencia de los registros financieros. Además, comprender estos elementos es fundamental para realizar análisis financieros y tomar decisiones estratégicas basadas en la información contable[11].

Para efectos de la implementacion de un Registro de transacciones en el programa, se buscara realizar una tabla con lo siguientes elementos:

-   Hora y fecha de la transaccion.
- Descripcion: una referencia sobre la naturaleza de la transaccion.
- Cuentas asociadas : Cuentas contables que fueron afectadas por la transacción
- Monto: Cantidad de dinero de la transaccion.

Dicha tabla se encontrará en un archivo log y el cual es actualizado en el mismo instante en el que se ejecuta una transaccion en el programa para asi asegurarse la seguridad y el seguimento preciso de cualquier operacion realizada.

## 5. Reporte de préstamos: las cuotas pagadas, desglosando el aporte al capital y los intereses abonados hasta el momento

El informe de préstamos es un documento que proporciona un análisis detallado de los préstamos concedidos por una entidad financiera. Contiene información como el importe del préstamo, la tasa de interés, el periodo de amortización, las fechas de pago, el saldo pendiente, entre otros datos relevantes. Este informe es fundamental para que los bancos y otras instituciones financieras evalúen la calidad de su cartera de préstamos y tomen decisiones relacionadas con el crédito.

En dicho reporte de préstamos se tiene contemplado mostrar la informacion del préstamo del usuario en forma tabular, en donde se muestre la cantidad de cuotas pagadas, asi como el aporte que se ha realizado en total al capital e intereses abonados, dichos valores son caculados de la siguiente manera:

- **Interes por cuota**: si bien hay diferentes tipos de amortizacion, suponiendo uno de couta constate (Francés), el interes de la cuota se calcula como Deuda*Interes/12

- **aporte al capital por cuota**: lo que se aporta con este sistema de amortizacion es Cuota - Interes Por Cuota [1][4]

## 6. Préstamos asociados: la tasa de interés, el periodo en meses y la cuota mensual

Se podría tener una clase Prestamo que guarde la cantidad del préstamo, la tasa de interés, el periodo, la cuota mensual (esta última es opcional se podría obtener con la fórmula). Además se le agregaría un atributo que indica si es en dólares o en colones que modifica las impresiones (las fórmulas deberían ser iguales). Se podría guardar un contenedor de objetos tipo Prestamo para cada cliente así pueden tener más de uno. Como se guardan los tres datos necesarios para generar la tabla se podría generar la tabla del préstamo en cualquier momento accediendo al objeto Prestamo. La clase Prestamo debería ser accedida por los usuarios y por el sistema bancario en sí. La clase Préstamo podría tener los métodos para generar la cuota mensual y la tabla de sí misma.

## 7. Manejo de archivos

Para el manejo de archivos se utilizará una clase de la biblioteca estándar de C++, siendo esta fstream, esta clase ofrece la posibilidad de leer y escribir en archivos, tales como archivos csv o log que serán utilizados en este proyecto. Para trabajar con este clase se trabaja con objetos tipo fstream, donde este será utilizado tanto para escribir como leer en el archivo. Algunos de los comandos básicos para el manejo de fstream son los siguientes:

open(): Método para abrir el archivo.

close(): Método para cerrar el archivo.

<<: Operador para escribir en el archivo.

\>\>: Operador para leer del archivo.

En caso de que el archivo buscado para trabajar con fstream no se encuentre, este será creado automáticamente con el nombre del archivo que se busca. Un ejemplo básico del uso de fstream es el siguiente:

```C++
#include <iostream>
#include <fstream>
using namespace std;

int main () {
  fstream myfile;
  myfile.open ("example.txt");
  myfile << "Writing this to a file.\n";
  myfile.close();
  return 0;
}
```
Tomado de: [12]

## 8. Cronograma

A continuación se coloca el cronograma tentativo con el cual se va a llevar acabo el proyecto.

<a><img src="https://github.com/DiegoAlfaroUCR/repoImagenes/blob/0774487b0c27f52b39e2f32a6f4963718beffac7/imagenesProyecto/Cronograma%20-%20Sheet1-1.svg?raw=true"></a>

## Referencias

[1] [Bankrate](https://www.bankrate.com/loans/loan-calculator/)

[2] [BBVA](https://www.bbva.pe/blog/mis-finanzas/inversiones/diferencia-entre-certificado-bancario-y-deposito-a-plazo.html)

[3] [Billin](https://www.billin.net/simulador-prestamos-personales-calculadora/#resultados)

[4] [Declarando.es](https://declarando.es/blog/amortizacion-prestamo)

[5] [Economipedia pretámos](https://economipedia.com/definiciones/prestamo-bancario.html. )

[6] [Economipedia credito prendario](https://economipedia.com/definiciones/credito-prendario.html.)

[7] [Economipedia credito hipotecario](https://economipedia.com/definiciones/credito-hipotecario.html)

[8] [excelparatodos](https://excelparatodos.com/tabla-de-amortizacion/)

[9] [Investopedia](https://www.investopedia.com/terms/i/interest.asp)

[10] [miniwebtool](https://miniwebtool.com/es/certificate-of-deposit-calculator/?p=1000&t=12&r=5&n=1)

[11] [Profinomics](https://profinomics.com/que-es-una-transaccion-en-contabilidad/?expand_article=1)

[12] [cplusplus](https://cplusplus.com/doc/tutorial/files/)


