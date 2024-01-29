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

    <a><img src="https://github.com/DiegoAlfaroUCR/repoImagenes/blob/803c59cf447e9d7d332710a02954c8c79d73534e/imagenesProyecto/cuotasMensuales1.svg?raw=true"></a>

    Tomada de https://www.billin.net/simulador-prestamos-personales-calculadora/#resultados
    
    <a><img src="https://github.com/DiegoAlfaroUCR/repoImagenes/blob/803c59cf447e9d7d332710a02954c8c79d73534e/imagenesProyecto/cuotasMensuales2.svg?raw=true"></a>

    Tomada de https://excelparatodos.com/tabla-de-amortizacion/

    P: Valor del préstamo

    i: Tasa de interés nominal anual (en porcentaje, osea para 3% usar 0.003)

    m: Número de capitalizaciones en el año

    n: Número de años

* Interés compuesto: Cantidad a pagar restante * Interés mensual = Cuota restante * Tasa interés/12
* Cantidad pagada a deuda = cuota mensual – interés compuestos
* Cantidad a pagar restante = Cantidad a pagar restante – cuota mensual

## 3. Certificados de depósito a plazo (CDP)
## 4. Registro de transacciones
## 5. Reporte de préstamos: las cuotas pagadas, desglosando el aporte al capital y los intereses abonados hasta el momento
## 6. Préstamos asociados: la tasa de interés, el periodo en meses y la cuota mensual

Se podría tener una clase Prestamo que guarde la cantidad del préstamo, la tasa de interés, el periodo, la cuota mensual (esta última es opcional se podría obtener con la fórmula). Además se le agregaría un atributo que indica si es en dólares o en colones que modifica las impresiones (las fórmulas deberían ser iguales). Se podría guardar un contenedor de objetos tipo Prestamo para cada cliente así pueden tener más de uno. Como se guardan los tres datos necesarios para generar la tabla se podría generar la tabla del préstamo en cualquier momento accediendo al objeto Prestamo. La clase Prestamo debería ser accedida por los usuarios y por el sistema bancario en sí. La clase Préstamo podría tener los métodos para generar la cuota mensual y la tabla de sí misma.