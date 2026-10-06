# Preparación para el oral (viernes 6 de noviembre)

La nota individual depende del oral. Cada uno tiene que poder **explicar su parte línea por línea** y responder preguntas generales del programa. Abajo hay un resumen de cada parte y preguntas probables, con la respuesta corta.

---

## Ornella – opciones 1 y 2

**`cargar_reserva(T_RESERVA hotel)`**
- Pide cada dato y lo valida con un `while` hasta que es correcto.
- Usa `habitacion_ocupada` para no repetir habitaciones.
- Abre el archivo en modo `"a"` y escribe la reserva al final con `fprintf(archivo, FORMATO_ESCRITURA, ...)`.

**`listar_reservas(T_RESERVA hotel)`**
- Abre en `"r"`, recorre con `while (fscanf(...) == CAMPOS)`, muestra cada reserva y acumula `cantidad` y `total`.

| Pregunta | Respuesta corta |
|---|---|
| ¿Diferencia entre `"a"`, `"w"` y `"r"`? | `"r"` lee; `"w"` crea el archivo o lo borra y escribe desde cero; `"a"` agrega al final sin borrar. |
| ¿Por qué la tarjeta se guarda como 1/0? | `fscanf` y `fprintf` no tienen un formato para `bool`; se guarda como entero y al leer se convierte con `tarjeta != 0`. |
| ¿Qué pasa si `fopen` devuelve `NULL`? | No se pudo abrir el archivo: se muestra un mensaje y la función termina con `return`. |
| ¿Por qué `leer_entero` y no `scanf` directo? | Si el usuario escribe letras, `scanf` falla y deja la letra en el buffer; sin limpiarlo, el programa entra en un loop infinito. |

## Denise – opciones 3 y 4

**`listar_debito_efectivo(T_RESERVA hotel)`** (la condición elegida)
- Muestra solo las reservas con `medio_de_pago == 'D' || medio_de_pago == 'E'`.
- Calcula el monto con descuento: `hotel.monto * (1 - DESCUENTO)`.

**`buscar_reserva(T_RESERVA hotel)`**
- Pregunta el criterio (1 = habitación, 2 = apellido) y pide el dato.
- Recorre el archivo y muestra las coincidencias. Si busca por habitación, dice si está OCUPADA o LIBRE.

| Pregunta | Respuesta corta |
|---|---|
| ¿Por qué `strcmp` y no `==` para comparar apellidos? | Un string es un arreglo de `char`; `==` no compara el contenido. `strcmp` devuelve 0 si los textos son iguales. |
| ¿Por qué se pasa el apellido a mayúsculas? | Para que `perez`, `Perez` y `PEREZ` se encuentren igual; en el archivo se guardan en mayúsculas. |
| ¿Por qué `DESCUENTO` es un `#define`? | Si el descuento cambia, se modifica una sola línea. |
| ¿Por qué se recorre todo el archivo al buscar por apellido? | Un cliente puede tener varias reservas y hay que mostrarlas todas. |

## Santiago – opciones 5 y 6

**`dividir_por_tarjeta(T_RESERVA hotel)`**
- Abre `reservas.txt` en `"r"` y los dos archivos nuevos en `"w"`.
- Lee una reserva por vez y la escribe en `reservas_con_tarjeta.txt` o `reservas_sin_tarjeta.txt` según `hotel.tarjeta`.
- Si falla algún `fopen`, cierra los archivos que sí se abrieron y avisa.
- Al final cierra los tres archivos e informa cuántas reservas fueron a cada uno.

**`salir_del_sistema()`**
- Muestra el mensaje de salida. El menú termina porque el `do-while` se repite mientras `opcion != 6`.

| Pregunta | Respuesta corta |
|---|---|
| ¿Por qué no hace falta `malloc` para dividir el archivo? | Se lee una reserva, se escribe y se pasa a la siguiente; nunca se guarda todo el archivo en memoria. |
| ¿Por qué los archivos nuevos se abren en `"w"` y no en `"a"`? | Para que cada vez que se divide queden solo los datos actuales y no se dupliquen. |
| ¿Por qué hay que cerrar los archivos? | `fclose` termina de grabar los datos en el disco y libera el archivo. |
| ¿Qué devuelve `fscanf` y por qué se compara con `CAMPOS`? | La cantidad de datos que pudo leer. Si leyó los 5, la línea está completa; al llegar al final del archivo devuelve otro valor y el `while` termina. |

---

## Preguntas para todo el grupo
| Pregunta | Respuesta corta |
|---|---|
| ¿Dónde hay punteros en el programa? | Solo `FILE *`; C lo exige para usar archivos. No hay punteros propios ni memoria dinámica. |
| ¿Por qué no hay variables globales? ¿Cómo pasan los datos? | Cada función usa variables locales; la reserva `hotel` se crea en `main` y se pasa por valor. |
| ¿Qué es `T_RESERVA`? | Un tipo de dato propio creado con `typedef struct` que agrupa los 5 campos de una reserva. |
| ¿Por qué `%14s` si `STRING` es 15? | Se deja un lugar para el `'\0'` que marca el fin del string. |
| ¿Para qué sirve `limpiar_buffer`? | Descarta lo que quedó escrito en la línea (por ejemplo el Enter) para que no lo lea el siguiente `scanf`. |
| ¿Qué pasa si `reservas.txt` no existe? | Las opciones de lectura avisan que no hay reservas; la opción 1 lo crea al guardar. |
