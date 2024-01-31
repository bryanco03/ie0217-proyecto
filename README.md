# ie0217-proyecto

# Temas a investigar 

## 1. Información sobre préstamos personales, prendarios e hipotecarios

Con este proyecto se busca crear una simulación de una aplicación bancaria, por lo que es necesario conocer algunos de los conceptos que se manejan en este ámbito y se buscan aplicar en la aplicación a crear, uno de los primeros conceptos a revisar son los préstamos, éxisten diferentes tipos de préstamos, se podrían comenzar hablando sobre los préstamos personales, estos se tratan de una operación bancaria, donde el banco presta un determinado capital a un cliente. Luego de cerrado el trato entre el banco y el cliente, este último debe de abonar el capital prestado de vuelta al banco, junto con una serie de interesés que fue definida entre el cliente y el banco al momento de iniciar con el proceso del préstamo. Tomado de: https://economipedia.com/definiciones/prestamo-bancario.html. 

Existen diferentes tipos de préstamos además del préstamo personal anteriormente mencionado, uno de estos es el crédito prendario, en este caso el cliente entrega a la entidad que realiza el préstamo un objeto como garantía, como lo pueden ser obras de arte o joyas, al igual que en el caso anterior, al momento de recibir el dinero, el cliente debe comenzar a realizar abonos del capital con una tasa de interés determinada, en este caso el cliente debe cancelar el monto total del préstamo junto con los interés establecidos para recuperar el bien que dejó en custodia con el banco, en caso de que el cliente se niegue a pagar el préstamo el objeto pasará a ser propiedad del banco. Tomado de: https://economipedia.com/definiciones/credito-prendario.html.

Por otra parte, se tiene uno de los préstamos más cómunes utilizado por las personas para poder conseguir contruir sus viviendas, el préstamo hipotecario, este un préstamo es utilizado para la adquisición de un bien inmueble por parte del cliente. En este caso el crédito dado por el banco no superará el valor de la vivienda que se desea adquirir, esto es así ya que, el inmueble adquirido por el usuario se grava con una hipoteca, esto significa que en caso de que el cliente no pague el crédito al banco, este tendrá la libertad de hacer valer la garantía hipotecaria y vender el inmueble hipotecado, con el fin de saldar la deuda del crédito entrega al cliente, en caso de que el banco logre vender el inmueble por un precio mayor a la deuda del cliente, el excedente será entregado al cliente, pero si, el precio de venta es menor a la deuda, el banco tendrá derecho a apropiarse de los bienes presentes y futuros del deudor, hasta que la deuda quede saldada. Tomado de: https://economipedia.com/definiciones/credito-hipotecario.html

La forma en que los pagdos de interéses son realizados se encuentran en el punto 2. Y la forma en que se pueden manejar los préstamos en este proyecto es mencionada en el punto 6 de este documento.



## 2. Como obtener la tabla mediante valores personalizados demonto, cantidad de cuotas y la tasa de interés

### Variables del préstamo.
1.	Préstamo: Cantidad a pagar
2.	Tasa de interés: Usualmente es interés anual fijo.

    ```
    Simple interest: Solo se agrega interés por la cantidad principal.
    Compound interest: Calcula el porcentaje con la cantidad principal y con cantidad ganada por interés en periodos pasados. [https://www.investopedia.com/terms/i/interest.asp]
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

    Tomada de https://www.billin.net/simulador-prestamos-personales-calculadora/#resultados
    
    <a><img src="https://github.com/DiegoAlfaroUCR/repoImagenes/blob/803c59cf447e9d7d332710a02954c8c79d73534e/imagenesProyecto/cuotasMensuales2.svg?raw=true"></a>

    Tomada de https://excelparatodos.com/tabla-de-amortizacion/

    P: Valor del préstamo

    CM: Cantidad de meses a pagar.

    i: Tasa de interés nominal anual (en porcentaje, osea para 3% usar 0.003)

    m: Número de capitalizaciones en el año

    n: Número de años

* Interés compuesto: Cantidad a pagar restante * Interés mensual = Cuota restante * Tasa interés/12
* Cantidad pagada a deuda = cuota mensual – interés compuestos
* Cantidad a pagar restante = Cantidad a pagar restante – cuota mensual

## 3. Certificados de depósito a plazo (CDP)

Otro tema a tratar dentro del proyecto, son los certificados de depósito a plazo, estos consisten en un depósito que realiza el cliente al banco, donde esté recibirá el dinero y trabajará con él durante un tiempo establecido por un acuerdo entre el banco y el cliente, inicialmente la idea de este proceso es que el cliente no pueda retirar el dinero durante el tiempo establecido y cuando este tiempo termine, el banco devolverá al cliente el dinero depositado, más una cantidad de interés extra generados por el tiempo que estuvo el dinero en el banco. Tomado de: https://www.bbva.pe/blog/mis-finanzas/inversiones/diferencia-entre-certificado-bancario-y-deposito-a-plazo.html

La fórmula para generar los interéses ganados por el cliente es la siguiente:

<a><img src="https://latex.codecogs.com/svg.image?%20A=P%20x(1+r/n)^{nt}"></a>

Tomada de: https://miniwebtool.com/es/certificate-of-deposit-calculator/?p=1000&t=12&r=5&n=1

Donde:

A = Es el saldo que recibirá el cliente, su depósito más los interéses
P = Depósito inicial que realizó el cliente
r = Tasa de interés anual
t = Plazo en años que estará el depósito en el banco
n = número de períodos de capitalización por año (Cuantas veces se capitalizan las ganancias al año)

Para su implementación en C++ se puede crear una clase CDP, que tenga como atributos las variables para calcular el CDP, así como una variable que indique si el depósito del cliente será en dólares o colones. Utilizando un método de la clase que incorporé la fórmula anterior se podría obtener la ganancia que obtendría el cliente dependiendo de la cantidad de dinero y la cantidad de tiempo que deje el dinero en el banco. La instancia de esta clase podría ser almacenada de forma que cada cliente tenga acceso a su respectivo CDP realizado.

## 4. Registro de transacciones
## 5. Reporte de préstamos: las cuotas pagadas, desglosando el aporte al capital y los intereses abonados hasta el momento
## 6. Préstamos asociados: la tasa de interés, el periodo en meses y la cuota mensual

Se podría tener una clase Prestamo que guarde la cantidad del préstamo, la tasa de interés, el periodo, la cuota mensual (esta última es opcional se podría obtener con la fórmula). Además se le agregaría un atributo que indica si es en dólares o en colones que modifica las impresiones (las fórmulas deberían ser iguales). Se podría guardar un contenedor de objetos tipo Prestamo para cada cliente así pueden tener más de uno. Como se guardan los tres datos necesarios para generar la tabla se podría generar la tabla del préstamo en cualquier momento accediendo al objeto Prestamo. La clase Prestamo debería ser accedida por los usuarios y por el sistema bancario en sí. La clase Préstamo podría tener los métodos para generar la cuota mensual y la tabla de sí misma.