# Documentación del programa – Sistema de reservas de hotel

**USAL – Programación 1 – Trabajo Práctico (Turno Mañana)**
Integrantes: Denise Muzica, Santiago Rojas, Ornella Sansalone Rodriguez

## 1. Descripción general
Programa en C estándar que administra las reservas de un hotel mediante un **menú de opciones**.
Cada reserva se guarda en una **estructura** (`T_RESERVA`) y se almacena en un **archivo de texto** (`reservas.txt`).

## 2. Archivos entregados
| Archivo | Contenido |
|---|---|
| `main.c` | Código fuente del programa |
| `reservas.txt` | Datos de prueba (8 reservas) |
| `DOCUMENTACION.md` | Este documento |

Al usar la opción 5 el programa genera además `reservas_con_tarjeta.txt` y `reservas_sin_tarjeta.txt`.

## 3. Estructura de datos
```c
typedef struct{
	char cliente[STRING];   // STRING  -> apellido del cliente
	bool tarjeta;           // booleano -> tiene tarjeta de cliente regular
	int habitacion;         // entero  -> número de habitación
	char medio_de_pago;     // char    -> 'D' débito, 'E' efectivo, 'C' crédito
	float monto;            // float   -> monto de la reserva
}T_RESERVA;
```
Cumple con los campos mínimos que pide la consigna: un string, un char, un entero, un float y un booleano.

## 4. Formato del archivo de texto
Una reserva por línea, con los campos separados por espacios:
```
cliente tarjeta habitacion medio_de_pago monto
PEREZ 1 101 D 15000.00
```
- `cliente`: una sola palabra, hasta 14 letras, guardada en mayúsculas.
- `tarjeta`: `1` si tiene tarjeta de cliente regular, `0` si no. En el archivo se guarda como número porque `fscanf` no lee el tipo `bool` directamente; al leerlo se convierte con `hotel.tarjeta = (tarjeta != 0);`.
- `habitacion`: número entero mayor a 0, no puede repetirse.
- `medio_de_pago`: `D`, `E` o `C`.
- `monto`: número mayor a 0, con dos decimales.

El formato está definido una sola vez con las constantes `FORMATO_LECTURA` y `FORMATO_ESCRITURA`, y todas las opciones lo usan.

## 5. Menú de opciones
| Opción | Función | Qué hace | Responsable |
|---|---|---|---|
| 1 | `cargar_reserva` | Pide los datos, los valida y agrega la reserva al final del archivo (modo `"a"`). | Ornella |
| 2 | `listar_reservas` | Muestra todas las reservas, la cantidad y el total facturado. | Ornella |
| 3 | `listar_debito_efectivo` | **Condición elegida:** muestra solo las reservas pagadas con débito o efectivo y el monto con 10 % de descuento. | Denise |
| 4 | `buscar_reserva` | Pregunta si buscar por número de habitación o por apellido, pide el dato y muestra los resultados. Si se busca por habitación, informa si está ocupada o libre. | Denise |
| 5 | `dividir_por_tarjeta` | Divide el archivo en dos archivos nuevos según el campo booleano `tarjeta`. | Santiago |
| 6 | `salir_del_sistema` | Muestra el mensaje de salida y termina el programa. | Santiago |

## 6. Funciones generales
| Función | Uso |
|---|---|
| `menu` | Muestra el menú en un `do-while` hasta elegir la opción 6 y llama a cada opción con un `switch`. |
| `leer_entero` / `leer_float` | Leen un número y lo vuelven a pedir si el usuario escribe letras. Así se evita el loop infinito de `scanf`. |
| `leer_letra` | Lee una letra y la devuelve en mayúscula (sirve para S/N y D/E/C). |
| `limpiar_buffer` | Descarta lo que sobró en la línea de entrada. |
| `pasar_a_mayusculas` | Pasa el apellido a mayúsculas para que la búsqueda no dependa de cómo se escribió. |
| `habitacion_ocupada` | Recorre el archivo y devuelve `true` si la habitación ya tiene una reserva. La usa la opción 1 para no repetir habitaciones. |
| `mostrar_encabezado` / `mostrar_reserva` | Muestran las reservas en forma de tabla. Se usan en varias opciones para no repetir código. |

## 7. Decisiones de diseño
- **Sin memoria dinámica:** no se usa `malloc`, `calloc` ni `realloc`. Cada opción lee el archivo **una reserva por vez** con `fscanf` dentro de un `while`, así nunca se carga el archivo completo en memoria.
- **Sin variables globales:** cada función declara sus propias variables locales. Las reservas se pasan **por valor** (`mostrar_reserva(T_RESERVA hotel)`).
- **Punteros:** no se usan punteros propios. El único es `FILE *`, que el lenguaje C exige para abrir archivos con `fopen`.
- **Control de errores:** se verifica que `fopen` no devuelva `NULL`; si el archivo no existe se avisa que no hay reservas. Cada archivo abierto se cierra con `fclose`.
- **Validación de datos:** no se aceptan habitaciones repetidas ni menores o iguales a 0, montos menores o iguales a 0, ni letras fuera de S/N o D/E/C.

## 8. Cómo compilar y ejecutar
```
gcc -std=c99 -Wall main.c -o hotel
./hotel            (en Windows: hotel.exe)
```
También se puede abrir `main.c` con Dev-C++ o Code::Blocks y ejecutarlo. El archivo `reservas.txt` tiene que estar en la misma carpeta que el programa.

## 9. Pruebas realizadas (con `reservas.txt`)
| Prueba | Resultado esperado |
|---|---|
| Opción 2 | 8 reservas, total facturado $151251.25 |
| Opción 3 | 5 reservas (PEREZ 101, GOMEZ, FERNANDEZ, MARTINEZ, RODRIGUEZ) con el monto con descuento |
| Opción 4 → habitación 203 | LOPEZ, la habitación está OCUPADA |
| Opción 4 → habitación 999 | La habitación está LIBRE |
| Opción 4 → cliente `perez` | 2 reservas (habitaciones 101 y 401); no importan mayúsculas/minúsculas |
| Opción 1 con habitación 101 | La pide de nuevo porque está ocupada |
| Opción 1 con monto `-5` o `abc` | Lo pide de nuevo |
| Opción 5 | 4 reservas con tarjeta y 4 sin tarjeta en los dos archivos nuevos |
| Menú con `7` o con letras | Mensaje de error y vuelve a pedir la opción |
| Opción 6 | "Fuera del sistema" y termina |

## 10. Herramientas utilizadas
Durante el desarrollo se utilizó un asistente de IA (Claude) como apoyo para revisar el código y armar una versión de referencia.
