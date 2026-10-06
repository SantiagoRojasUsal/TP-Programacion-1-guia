# Sistema de Reservas de Hotel

**USAL · Programación 1 · Trabajo Práctico – Turno Mañana**

| Integrante | Parte del programa |
|---|---|
| Ornella Sansalone Rodriguez | Opciones 1 y 2 – cargar y listar reservas |
| Denise Muzica | Opciones 3 y 4 – listado con condición y búsqueda |
| Santiago Rojas | Opciones 5 y 6 – dividir el archivo y salir del sistema |

---

## ¿Qué es?
Un programa de consola escrito en **C estándar** para administrar las reservas de un hotel.
Funciona con un **menú de opciones**. Cada reserva se representa con una **estructura** (`T_RESERVA`) y todas se guardan en un **archivo de texto** (`reservas.txt`), así los datos no se pierden al cerrar el programa.

Con el programa se puede:
- cargar reservas nuevas,
- ver todas las reservas,
- ver solo las pagadas con débito o efectivo, con un 10 % de descuento,
- buscar si una habitación está ocupada o qué reservas tiene un cliente,
- separar las reservas en dos archivos nuevos según el cliente tenga o no tarjeta de cliente regular.

---

## Archivos del repositorio
| Archivo | Para qué sirve |
|---|---|
| `main.c` | Código fuente completo del programa |
| `reservas.txt` | Archivo de datos con 8 reservas de prueba |
| `DOCUMENTACION.md` | Explicación técnica: funciones, decisiones de diseño y pruebas |
| `README.md` | Este archivo: qué hace el programa y cómo usarlo |

---

## Cómo compilar y ejecutar

**Con gcc (Linux, Mac o Windows con MinGW):**
```
gcc -std=c99 -Wall main.c -o hotel
./hotel          (en Windows: hotel.exe)
```

**Con Dev-C++ o Code::Blocks:** abrir `main.c`, compilar y ejecutar (F11 en Dev-C++, F9 en Code::Blocks).

> `reservas.txt` tiene que estar **en la misma carpeta** desde la que se ejecuta el programa. Si no está, el programa lo crea solo al cargar la primera reserva.

---

## La estructura de datos
```c
typedef struct{
	char cliente[STRING];   // apellido del cliente          -> campo STRING
	bool tarjeta;           // tiene tarjeta de cliente regular -> campo booleano
	int habitacion;         // número de habitación            -> campo entero
	char medio_de_pago;     // 'D' débito, 'E' efectivo, 'C' crédito -> campo char
	float monto;            // monto de la reserva             -> campo float
}T_RESERVA;
```
Tiene los cinco tipos de campo que pide la consigna: string, char, entero, float y booleano.

## El archivo de texto
Cada línea de `reservas.txt` es una reserva, con los campos separados por espacios:

```
cliente  tarjeta  habitacion  medio_de_pago  monto
PEREZ    1        101         D              15000.00
```

- `tarjeta` se guarda como `1` (sí) o `0` (no), porque `fscanf` no puede leer un `bool` directamente.
- El apellido se guarda en mayúsculas, para que todos los registros queden escritos igual.

---

## Cómo funciona: el menú
Al ejecutar el programa aparece el menú. Se elige una opción escribiendo el número y presionando Enter. Después de cada opción el menú vuelve a aparecer, hasta elegir la 6.

```
================ MENU ================
1) cargar una reserva nueva
2) mostrar lista de todas las reservas
3) mostrar solo los que pagaron con debito o efectivo (10% de descuento)
4) buscar si una habitacion esta ocupada
5) dividir en dos archivos segun tarjeta de cliente regular
6) salir del sistema
opcion=
```

Si se escribe un número fuera de rango (por ejemplo `7`) aparece `ERROR... opcion invalida`. Si se escriben letras, el programa vuelve a pedir el número. En ningún caso se cuelga.

### 1) Cargar una reserva nueva
Pide los datos uno por uno y **valida cada uno** antes de guardarlo:

| Dato | Qué se controla |
|---|---|
| Apellido | Una palabra de hasta 14 letras (se guarda en mayúsculas) |
| Habitación | Mayor a 0 y **que no esté ocupada** (se revisa en el archivo) |
| Tarjeta de cliente regular | Solo `S` o `N` |
| Medio de pago | Solo `D`, `E` o `C` |
| Monto | Un número mayor a 0 |

```
--- CARGAR RESERVA NUEVA ---
Apellido del cliente (una palabra, max 14 letras): Ruiz
Numero de habitacion: 101
La habitacion 101 ya esta ocupada. Elija otra: 501
Tiene tarjeta de cliente regular? (S/N): s
Medio de pago (D=debito, E=efectivo, C=credito): e
Monto: 8000.50

Reserva guardada correctamente.
```
La reserva se agrega **al final** de `reservas.txt` (el archivo se abre en modo `"a"`), sin borrar las que ya estaban.

### 2) Mostrar todas las reservas
Recorre el archivo completo y muestra una tabla con cada reserva. Al final informa la cantidad de reservas y el total facturado.

```
--- TODAS LAS RESERVAS ---
CLIENTE         HABITACION TARJETA  PAGO              MONTO
---------------------------------------------------------
PEREZ           101        SI       Debito         15000.00
GOMEZ           102        NO       Efectivo       12000.50
LOPEZ           203        SI       Credito        30000.00
...

Cantidad de reservas: 8
Total facturado: $151251.24
```

### 3) Reservas pagadas con débito o efectivo (condición)
Muestra **solo** las reservas cuyo medio de pago es débito (`D`) o efectivo (`E`). Para cada una muestra el monto, el **descuento del 10 %** y el total a pagar. Las pagadas con crédito no aparecen.

```
--- RESERVAS PAGADAS CON DEBITO O EFECTIVO (10% DE DESCUENTO) ---
CLIENTE         HAB.   PAGO              MONTO    DESC. 10%      A PAGAR
----------------------------------------------------------------------
PEREZ           101    Debito         15000.00      1500.00     13500.00
GOMEZ           102    Efectivo       12000.50      1200.05     10800.45
FERNANDEZ       204    Debito         18500.75      1850.07     16650.68
MARTINEZ        305    Efectivo       22000.00      2200.00     19800.00
RODRIGUEZ       402    Debito         16250.00      1625.00     14625.00

Cantidad de reservas con descuento: 5
```

### 4) Buscar si una habitación está ocupada
Es la **búsqueda por un campo**: le pregunta al usuario **qué número de habitación buscar** y recorre el archivo hasta encontrarla.

- Si la encuentra, dice que está **OCUPADA** y muestra los datos de la reserva.
- Si no está en el archivo, dice que está **LIBRE**.

```
Ingrese el numero de habitacion a buscar: 203

La habitacion 203 esta OCUPADA:
CLIENTE         HABITACION TARJETA  PAGO              MONTO
---------------------------------------------------------
LOPEZ           203        SI       Credito        30000.00
```
```
Ingrese el numero de habitacion a buscar: 999

La habitacion 999 esta LIBRE (no figura en el archivo).
```
Como no se pueden cargar dos reservas en la misma habitación (la opción 1 lo controla), la búsqueda termina apenas la encuentra.

### 5) Dividir el archivo según la tarjeta de cliente regular
Lee `reservas.txt` y reparte cada reserva en **dos archivos de texto nuevos** según el campo booleano `tarjeta`:

| Archivo generado | Contiene |
|---|---|
| `reservas_con_tarjeta.txt` | Reservas de clientes **con** tarjeta de cliente regular |
| `reservas_sin_tarjeta.txt` | Reservas de clientes **sin** tarjeta |

```
--- ARCHIVO DIVIDIDO ---
4 reserva(s) CON tarjeta de cliente regular -> reservas_con_tarjeta.txt
4 reserva(s) SIN tarjeta de cliente regular -> reservas_sin_tarjeta.txt
```
Los archivos nuevos tienen el mismo formato que `reservas.txt`. El archivo original no se modifica. Si la opción se usa otra vez, los dos archivos se vuelven a generar con los datos actualizados.

### 6) Salir del sistema
Muestra `Fuera del sistema. Hasta luego!` y termina el programa.

---

## Cómo está organizado el código
```
main()                      declara la reserva "hotel" y llama al menu
└── mostrar(hotel)          menu: do-while + switch con las 6 opciones
    ├── 1  cargar_reserva(hotel)          ┐ Ornella
    ├── 2  listar_reservas(hotel)         ┘
    ├── 3  mostrarPagos(hotel)            ┐ Denise
    ├── 4  buscarHabitacion(hotel)        ┘
    ├── 5  dividir_por_tarjeta(hotel)     ┐ Santiago
    └── 6  salir_del_sistema()            ┘

Funciones generales (las usan varias opciones):
leer_entero, leer_float, leer_letra, leer_apellido   -> leer datos del teclado de forma segura
habitacion_ocupada                                   -> revisar si una habitación ya está reservada
mostrar_encabezado, mostrar_reserva                  -> mostrar las reservas en forma de tabla
limpiar_buffer, fin_de_entrada                       -> manejo del teclado
```

## Requisitos de la consigna que cumple
- ✅ Estructura con campo string, char, entero, float y booleano.
- ✅ Archivo de texto para guardar y leer los datos.
- ✅ Menú con las 6 opciones pedidas: agregar, listar todo, listar con condición, búsqueda por un campo elegido por el usuario, dividir según el campo booleano y salir.
- ✅ Lenguaje C estándar (compila con `gcc -std=c99 -Wall -Wextra -pedantic` sin advertencias).
- ✅ Funciones para no repetir código.
- ✅ Uso de memoria eficiente: **sin variables globales**, **sin `malloc`, `calloc` ni `realloc`**. El archivo se procesa de a una reserva por vez y nunca se carga entero en memoria.
- ✅ Sin punteros propios. El único es `FILE *`, que C exige para trabajar con archivos.

Para el detalle de cada función, las decisiones de diseño y las pruebas realizadas, ver **[DOCUMENTACION.md](DOCUMENTACION.md)**.
