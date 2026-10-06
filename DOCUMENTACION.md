# Documentación del programa – Sistema de reservas de hotel

**USAL – Programación 1 – Trabajo Práctico (Turno Mañana)**
Integrantes: Denise Muzica, Santiago Rojas, Ornella Sansalone Rodriguez

## 1. Objetivo
Programa en C estándar que resuelve un **menú de opciones** usando una **estructura** (`T_RESERVA`) y un **archivo de texto** (`reservas.txt`). El tema elegido es **hoteles**: cada registro es la reserva de una habitación.

## 2. Especificación de la estructura
| Campo | Tipo | Requisito de la consigna | Valores válidos |
|---|---|---|---|
| `cliente` | `char[STRING]` (15) | campo STRING | una palabra, hasta 14 letras, en mayúsculas |
| `tarjeta` | `bool` | campo booleano | `true` / `false` (en el archivo: `1` / `0`) |
| `habitacion` | `int` | campo entero | mayor a 0, no repetido |
| `medio_de_pago` | `char` | campo char | `'D'` débito, `'E'` efectivo, `'C'` crédito |
| `monto` | `float` | campo float | mayor a 0 |

## 3. Especificación del archivo
- Nombre: `reservas.txt`, en la carpeta desde la que se ejecuta el programa.
- Una reserva por línea: `cliente tarjeta habitacion medio_de_pago monto`.
- Ejemplo: `PEREZ 1 101 D 15000.00`.
- El formato está definido una sola vez en las constantes `FORMATO_LECTURA` (`"%14s %d %d %c %f"`) y `FORMATO_ESCRITURA` (`"%s %d %d %c %.2f\n"`). Todas las funciones las usan, así lectura y escritura siempre coinciden.
- `CAMPOS` (5) es la cantidad de datos por línea. Una lectura es correcta cuando `fscanf` devuelve 5. Cuando devuelve otro valor (fin de archivo), el `while` termina.
- La opción 5 genera `reservas_con_tarjeta.txt` y `reservas_sin_tarjeta.txt`, con el mismo formato.

## 4. Funciones

### 4.1 Programa principal y menú
| Función | Descripción |
|---|---|
| `main` | Declara e inicializa la reserva `hotel` y llama a `mostrar(hotel)`. |
| `mostrar(T_RESERVA hotel)` | Menú principal. Un `do-while` lo repite hasta que la opción sea 6 y un `switch` llama a la función de cada opción, pasándole `hotel` por valor. |

### 4.2 Opciones del menú
| Op. | Función | Responsable | Descripción |
|---|---|---|---|
| 1 | `cargar_reserva(T_RESERVA hotel)` | Ornella | Pide y valida cada dato (apellido, habitación libre y mayor a 0, S/N, D/E/C, monto mayor a 0). Abre el archivo en modo `"a"` y agrega la reserva al final. |
| 2 | `listar_reservas(T_RESERVA hotel)` | Ornella | Abre en modo `"r"`, recorre todo el archivo mostrando cada reserva y al final informa la cantidad y el total facturado. |
| 3 | `listar_debito_efectivo(T_RESERVA hotel)` | Denise | **Listado con condición:** muestra solo las reservas con `medio_de_pago == 'D' \|\| medio_de_pago == 'E'` y el monto con descuento: `monto * (1 - DESCUENTO)`. |
| 4 | `buscar_reserva(T_RESERVA hotel)` | Denise | **Búsqueda específica:** pregunta si buscar por habitación o por apellido, pide el dato y muestra las coincidencias. Los números se comparan con `==` y los apellidos con `strcmp`. Si se busca por habitación, informa si está OCUPADA o LIBRE. |
| 5 | `dividir_por_tarjeta(T_RESERVA hotel)` | Santiago | Abre el original en `"r"` y los dos archivos nuevos en `"w"`. Lee de a una reserva y la escribe en uno u otro archivo según `hotel.tarjeta`. Cierra los tres archivos e informa cuántas reservas fueron a cada uno. |
| 6 | `salir_del_sistema()` | Santiago | Muestra el mensaje de salida; el `do-while` del menú termina. |

### 4.3 Funciones generales
| Función | Descripción |
|---|---|
| `leer_entero()` / `leer_float()` | Leen un número con `scanf`. Si el usuario escribe letras, limpian el buffer y lo vuelven a pedir. Esto evita el loop infinito que se produce cuando `scanf` no puede leer. |
| `leer_letra()` | Lee una letra (ignora espacios y Enter previos) y la devuelve en mayúscula con `toupper`. |
| `leer_apellido(char texto[])` | Lee una palabra de hasta 14 letras (`%14s`, para no pasarse del tamaño del arreglo) y la pasa a mayúsculas. |
| `limpiar_buffer()` | Descarta el resto de la línea escrita (`getchar` hasta `'\n'`). |
| `fin_de_entrada()` | Si se cierra la entrada del teclado (Ctrl+Z / Ctrl+D), termina el programa con un mensaje en vez de quedar trabado. |
| `habitacion_ocupada(int numero)` | Recorre el archivo y devuelve `true` si encuentra la habitación. La usa la opción 1. |
| `mostrar_encabezado()` / `mostrar_reserva(T_RESERVA hotel)` | Muestran el título de la tabla y una reserva en una fila. Las usan las opciones 2, 3 y 4, así no se repite código. |

## 5. Decisiones de diseño
- **Memoria eficiente:** no se usa `malloc`, `calloc` ni `realloc`. Los archivos se procesan con `while (fscanf(...) == CAMPOS)`, **una reserva por vez**, así el uso de memoria es el mismo con 5 reservas que con 5000.
- **Sin variables globales:** todo se declara dentro de cada función. La reserva `hotel` se crea en `main` y se pasa **por valor** a cada opción, que la usa como variable de trabajo.
- **Punteros:** no hay punteros propios. El único es `FILE *`, obligatorio en C para usar `fopen`, `fscanf`, `fprintf` y `fclose`.
- **Constantes con `#define`:** nombres de archivos, descuento, tamaño del string y formato del archivo. Para cambiar cualquiera de estos datos alcanza con modificar una sola línea.
- **Control de errores de archivos:** después de cada `fopen` se verifica que no devuelva `NULL`. Si `reservas.txt` no existe, se informa que todavía no hay reservas. Todo archivo abierto se cierra con `fclose`. En la opción 5, si no se puede crear alguno de los archivos nuevos, se cierran los que sí se abrieron.
- **Validación de datos de entrada:** ningún dato inválido llega al archivo, y escribir letras donde va un número no traba el programa.
- **Mayúsculas:** los apellidos se guardan y se buscan en mayúsculas, así `perez` encuentra a `PEREZ`.
- **Limitación conocida:** el apellido es una sola palabra (sin espacios), porque el archivo separa los campos con espacios.

## 6. Datos de prueba (`reservas.txt`)
```
PEREZ 1 101 D 15000.00
GOMEZ 0 102 E 12000.50
LOPEZ 1 203 C 30000.00
FERNANDEZ 0 204 D 18500.75
MARTINEZ 1 305 E 22000.00
SOSA 0 306 C 9999.99
PEREZ 0 401 C 27500.00
RODRIGUEZ 1 402 D 16250.00
```
Incluye los tres medios de pago, clientes con y sin tarjeta, y un cliente (PEREZ) con dos reservas para probar la búsqueda por apellido.

## 7. Pruebas realizadas
| # | Prueba | Resultado obtenido |
|---|---|---|
| 1 | Opción 2 | 8 reservas, total facturado $151251.25 |
| 2 | Opción 3 | 5 reservas (PEREZ 101, GOMEZ, FERNANDEZ, MARTINEZ, RODRIGUEZ), cada una con el 10 % de descuento |
| 3 | Opción 4 → habitación 203 | Muestra a LOPEZ, la habitación está OCUPADA |
| 4 | Opción 4 → habitación 999 | La habitación está LIBRE |
| 5 | Opción 4 → apellido `perez` | 2 reservas (habitaciones 101 y 401) |
| 6 | Opción 4 → apellido inexistente | "No hay reservas a nombre de ..." |
| 7 | Opción 1 con habitación 101 | La vuelve a pedir porque está ocupada |
| 8 | Opción 1 con habitación 0, tarjeta `x`, medio `q`, monto `-5` y `abc` | Cada dato se vuelve a pedir hasta que es válido |
| 9 | Opción 1 con datos válidos y después opción 4 | La reserva nueva queda guardada y se encuentra |
| 10 | Opción 5 | 4 reservas en `reservas_con_tarjeta.txt` y 4 en `reservas_sin_tarjeta.txt` |
| 11 | Opciones 2 a 5 sin `reservas.txt` | "Todavia no hay reservas cargadas", sin errores |
| 12 | Opción 1 sin `reservas.txt` | Crea el archivo con la reserva nueva |
| 13 | Menú con `7` / con letras | Mensaje de error / vuelve a pedir el número |
| 14 | Opción 6 | "Fuera del sistema. Hasta luego!" y termina |

Compilación: `gcc -std=c99 -Wall -Wextra -pedantic main.c` sin errores ni advertencias.

## 8. Herramientas utilizadas
Durante el desarrollo se utilizó un asistente de IA (Claude) como apoyo para revisar el código y la documentación.
