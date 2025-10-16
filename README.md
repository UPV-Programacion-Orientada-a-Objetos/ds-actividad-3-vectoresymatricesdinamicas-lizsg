[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/eW2MawP6)
[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=21108699)
# Actividad Práctica: Sistema de Planificación de Producción y Costos (Modelo COGS)

## Definición del Problema a Resolver

Una planta manufacturera de componentes electrónicos necesita optimizar su sistema de costeo y planificación de inventario. El sistema actual es rígido y no puede manejar la variación en la cantidad de productos ni la volatilidad de los costos de materia prima. Se requiere un sistema capaz de:

* Modelar el inventario de materia prima (fijo y conocido).
* Modelar el plan de producción para diferentes productos a lo largo de varias semanas.
* Calcular el Costo de Bienes Vendidos (COGS) y el costo de inventario final, aplicando conceptos contables.

El objetivo es construir un programa que utilice matrices y vectores dinámicos para la planificación, un vector estático para constantes de producción, y que permita al usuario modificar y analizar estos datos en tiempo de ejecución.

---

## Temas Relacionados y Necesarios

Para resolver este problema, los alumnos deberán integrar los siguientes conocimientos:

| Tema Principal                     | Concepto a Aplicar                                                                                                                                                                    |
| :--------------------------------- | :------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| Matrices Bidimensionales Dinámicas | Uso de punteros dobles (`float**`) para crear y gestionar la Matriz de Planificación de Producción (Productos vs. Semanas).                                                            |
| Vectores Dinámicos (Punteros)      | Uso de punteros simples (`float*`) para crear y gestionar el Inventario de Materia Prima y el Vector de Costos Unitarios.                                                               |
| Vectores Estáticos                 | Uso de un arreglo de tamaño fijo (`int[]`) para almacenar el Requerimiento Fijo de Unidades/Producto (Constantes de Material).                                                          |
| Contabilidad de Costos             | Aplicación de la fórmula del COGS (\( COGS = Inv.Inicial + Compras - Inv.Final \)) y cálculo de los costos variables de producción.                                                               |
| Gestión de Memoria Manual          | Implementación de funciones para la expansión (duplicación de tamaño) de vectores dinámicos y la redimensión de la matriz dinámica, utilizando `new` y `delete` de manera segura. |

---

## Definición y Detalles del Proceso a Desarrollar

### Estructuras Dinámicas y Estáticas Requeridas

* **Matriz de Planificación (`float**`)**:
  * Filas: Representan **5** tipos de Productos Terminados (Fijos).
  * Columnas: Representan el número de Semanas planificadas (Dinámico, expansible). Almacena la cantidad de unidades a producir por producto y semana.
  * **Vector de Costos (`float*`)**: Vector dinámico que almacena el Costo Variable Unitario por producto (**5** productos). Este vector debe ser susceptible a expansión si se agregan nuevos productos.
  * **Vector de Materia Prima (`float*`)**: Vector dinámico que almacena la cantidad inicial de **4** tipos de Materia Prima (MP) en existencia.
*   **Vector de Requerimientos (`int[]`)**: Vector estático de **5x4** (Productos x MP) que define cuántas unidades de cada MP se requieren para fabricar un producto terminado.

### Proceso de Solución Detallado

1. **Inicialización**: Asignar memoria inicial para **4** semanas en la Matriz de Planificación. Asignar memoria inicial para el Vector de Costos Unitarios y Materia Prima. Cargar datos estáticos del Vector de Requerimientos.
2. **Redimensión de la Matriz**: Implementar una función que permita al usuario agregar una nueva semana a la Matriz de Planificación. La matriz debe expandir sus columnas: crear una matriz temporal más grande, copiar todos los datos existentes y liberar la matriz antigua.
3. **Cálculo de Consumo de MP**: Implementar una función que calcule el consumo total de cada tipo de materia prima basado en el plan de producción de una semana específica (Matriz de Planificación × Vector de Requerimientos).
4. **Cálculo del COGS**: Implementar una función para calcular el Costo de Bienes Vendidos (COGS) y el valor del Inventario Final para una semana dada.
    * COGS: Calcular el costo de producción total de la semana (Producción semanal × Costo Unitario).
    * Inventario Final: El sistema debe calcular el costo de la Materia Prima restante (Inventario Inicial - Consumo de MP) × Costo de Adquisición de la MP (valor constante).
5. **Gestión de Memoria Segura**: El destructor debe liberar de forma segura la memoria de la Matriz de Planificación, el Vector de Costos Unitarios y el Vector de Materia Prima.

---

## Requerimientos Funcionales y No Funcionales

### Requisitos Funcionales

* **Carga Inicial**: Inicializar y cargar los datos de los **5** productos y las **4** semanas iniciales.
* **Planificación y Redimensión**: Permitir al usuario agregar una nueva semana al plan (redimensión de la matriz dinámica).
* **Actualización**: Permitir al usuario modificar la cantidad planificada de producción para cualquier producto en cualquier semana existente.
* **Cálculo COGS**: Función que calcule y muestre el COGS y el Valor del Inventario Final para la semana actual.
* **Reporte de Consumo**: Función que muestre el consumo total de cada materia prima para una semana seleccionada.

### Requisitos No Funcionales

* **Implementación Manual**: Prohibido el uso de `std::vector`, `std::array` o cualquier contenedor de la STL. Todas las estructuras dinámicas deben ser gestionadas con `new` y `delete`.
* **Control de Punteros**: El manejo de la matriz (`float**`) y los vectores (`float*`) debe ser riguroso y libre de fugas de memoria.
* **Robustez**: El sistema debe validar que el usuario ingrese números para las cantidades de producción y que las semanas/productos seleccionados estén dentro de los límites.

---

## Ejemplo de Entradas y Salidas del Problema en Consola

```bash
Simulación de Interacción
--- Sistema de Planificación y Costos (COGS) ---

Inicialización exitosa. Matriz de Planificación: 5 Productos x 4 Semanas.

--- Menú Principal ---
1. Ver Plan de Producción
2. Agregar Nueva Semana (Redimensionar Matriz)
3. Modificar Producción
4. Calcular COGS y Final Inventory
5. Salir

Opción seleccionada: 2
Agregando Semana 5...
Matriz redimensionada a 5x5. ¡Memoria gestionada con éxito!

Opción seleccionada: 3
Ingrese Producto (0-4): 2 (Componente Z)
Ingrese Semana (0-4): 4 (Nueva Semana)
Cantidad a producir: 1500

Opción seleccionada: 4
Ingrese Semana para el cálculo de costos: 1

--- Reporte de Costos (Semana 1) ---
Producción Total (Semana 1): 8000 unidades.
Costo Total de Producción (COGS): $45,000.00
Consumo de Materia Prima: MP-01 (200 kg), MP-04 (150 uni).
Valor del Inventario Final (M.P. restante): $12,500.00

Opción seleccionada: 5
Liberando memoria de Matriz y Vectores Dinámicos...
Sistema cerrado.
```

---

## Temas Adicionales de Investigación Necesarios

Para llevar a cabo esta actividad con éxito, el alumno deberá investigar a fondo:

1. COGS (Costo de Bienes Vendidos): Definición y fórmula contable simplificada para el cálculo de costos variables de producción.
2. Asignación Segura de Memoria: Manejo de la excepción std::bad_alloc en C++ en las funciones de expansión de vectores y matrices.
3. Técnicas de Copia de Datos: Implementación manual de la función de copiado (bucle for) para transferir datos de la matriz antigua a la nueva durante la redimensión, garantizando la integridad de los datos.
4. Estructuras de Datos Estáticas: Cómo inicializar y usar arreglos fijos de manera eficiente dentro de una función.