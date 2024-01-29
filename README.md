# ie0217-proyecto

# Temas a investigar 

## 1. Información sobre préstamos personales, prendarios e hipotecarios
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
    Esta es una de las ingresadas según instrucciones, asumiendo que son mensuales, se toma como cantidad de meses. Por ende, es mejor usar la formula 2 de cuota mensual si el input es número de cuotas y es mensual el pago. Así se ignoran las variables de plazo y frecuencia.
    ```

### Variables a calcular:
* Cuota mensual: El pago que se debe hacer cada mes, incluye el pago de intereses y pago de deuda. Fórmulas de cuota mensual para tasa fija:

    Tomada de https://www.billin.net/simulador-prestamos-personales-calculadora/#resultados
    $$ \frac{P \cdot i/12 }{1 - (1+i/12)^{-12} } $$

    Tomada de https://excelparatodos.com/tabla-de-amortizacion/
    $$ \frac{P \cdot i/m \cdot (1+i/m)^{nm}}{(1+i/m)^{nm} - 1} $$

    P: Valor del préstamo

    i: Tasa de interés nominal anual (en porcentaje, osea para 3% usar 0.003)

    m: Número de capitalizaciones en el año

    n: Número de años

* Interés compuesto: Cantidad a pagar restante * Interés mensual = Cuota restante * Tasa interés/12
* Cantidad pagada a deuda = cuota mensual – interés compuestos
* Cantidad a pagar restante = Cantidad a pagar restante – cuota mensual

## 3. Certificados de depósito a plazo (CDP)
## 4. Registro de transacciones

El registro de transacciones en los bancos es esencial para mantener un historial exacto de todas las operaciones financieras realizadas en las cuentas de los clientes. Estos registros abarcan una amplia gama de transacciones, como depósitos, retiros, transferencias, pagos de facturas y cualquier otra actividad relacionada con el dinero.

El proceso de registro de transacciones contables implica varias etapas. En primer lugar, se identifican las transacciones relevantes y se clasifican según su naturaleza (ventas, compras, gastos, ingresos, etc.). Luego, la información de la transacción se registra en los libros contables utilizando el método de partida doble.

El método de partida doble requiere que cada transacción afecte al menos a dos cuentas contables: una cuenta se debita (incrementa), y otra se acredita (disminuye). Esta doble entrada asegura que el balance contable siempre esté equilibrado.
Hay varios elementos clave que componen una transacción contable:

- Cuenta: Es la categoría utilizada para clasificar y agrupar las transacciones contables. Las cuentas pueden ser de diferentes tipos, como activos, pasivos, capital, ingresos y gastos.

- Débito: Es el lado izquierdo de una transacción contable, donde se registra lo que se recibe o se obtiene. Representa los activos y los gastos.

- Crédito: Es el lado derecho de una transacción contable, donde se registra lo que se da o se entrega. Representa los pasivos, el capital y los ingresos.

Es crucial que estos elementos estén presentes en una transacción contable para asegurar la precisión y consistencia de los registros financieros. Además, comprender estos elementos es fundamental para realizar análisis financieros y tomar decisiones estratégicas basadas en la información contable[1].

Para efectos de la implementacion de un Registro de transacciones en el programa, se buscara realizar una tabla con lo siguientes elementos:

-   Hora y fecha de la transaccion.
- Descripcion: una referencia sobre la naturaleza de la transaccion.
- Cuentas asociadas : Cuentas contables que fueron afectadas por la transacción
- Monto: Cantidad de dinero de la transaccion.

Dicha tabla es actualizada en los mismo instante en el que se ejecuta una transaccion en el programa para asi asegurarse la seguridad y el seguimento preciso de cualquier operacion realizada.




## 5. Reporte de préstamos: las cuotas pagadas, desglosando el aporte al capital y los intereses abonados hasta el momento
## 6. Préstamos asociados: la tasa de interés, el periodo en meses y la cuota mensual

Se podría tener una clase Prestamo que guarde la cantidad del préstamo, la tasa de interés, el periodo, la cuota mensual (esta última es opcional se podría obtener con la fórmula). Además se le agregaría un atributo que indica si es en dólares o en colones que modifica las impresiones (las fórmulas deberían ser iguales). Se podría guardar un contenedor de objetos tipo Prestamo para cada cliente así pueden tener más de uno. Como se guardan los tres datos necesarios para generar la tabla se podría generar la tabla del préstamo en cualquier momento accediendo al objeto Prestamo. La clase Prestamo debería ser accedida por los usuarios y por el sistema bancario en sí. La clase Préstamo podría tener los métodos para generar la cuota mensual y la tabla de sí misma.


## Referencias

[1] [Profinomics](https://profinomics.com/que-es-una-transaccion-en-contabilidad/?expand_article=1)
