# Guía por integrante

Este repo es una **guía de referencia**. Cada una/o tiene que hacer su parte en el repo de entrega, subirla con **su propia cuenta** y poder explicarla en el oral (viernes 6 de noviembre).

## Qué hay en cada rama
| Rama | Contenido |
|---|---|
| `main` | Programa **completo** (las 3 partes ya unidas) |
| `ornella` | Base común + opciones 1 y 2 |
| `denise` | Base común + opciones 3 y 4 |
| `santiago` | Base común + opciones 5 y 6 |

La **base común** es lo que comparte todo el grupo: estructura, constantes, menú (`switch`) y funciones generales (`leer_entero`, `mostrar_reserva`, etc.). Las opciones que no le tocan a cada rama solo muestran "Opcion en desarrollo".

En `main.c` cada parte está marcada con un comentario:
```
//==================== OPCIONES 1 Y 2 - ORNELLA ====================
//==================== OPCIONES 3 Y 4 - DENISE ====================
//==================== OPCIONES 5 Y 6 - SANTIAGO ====================
```

## Orden sugerido para el repo de entrega
1. Alguien sube la base común a `main`.
2. Cada una/o crea su rama, escribe sus funciones y las sube con su cuenta.
3. Se abre un Pull Request por rama y se aceptan de a uno en `main`. Como cada uno cambia solo su sección, no deberían aparecer conflictos.
4. Al final se prueba todo junto con `reservas.txt`.

---

## Ornella – opciones 1 y 2
**`cargar_reserva`**
- Pide apellido, habitación, tarjeta (S/N), medio de pago (D/E/C) y monto.
- Valida cada dato con un `while`. Usa `habitacion_ocupada` para no repetir habitaciones.
- Abre el archivo en modo `"a"` (agrega al final sin borrar) y escribe con `fprintf(FORMATO_ESCRITURA)`.

**`listar_reservas`**
- Abre en modo `"r"` y recorre con `while (fscanf(...) == CAMPOS)`.
- Muestra cada reserva y al final la cantidad y el total facturado.

Preguntas posibles en el oral:
- ¿Qué diferencia hay entre `"a"`, `"w"` y `"r"`?
- ¿Por qué la tarjeta se guarda como 1/0 y no como `true`/`false`?
- ¿Qué pasa si `fopen` devuelve `NULL`?

## Denise – opciones 3 y 4
**`listar_debito_efectivo`** (la condición elegida)
- Recorre el archivo y muestra solo las reservas con `medio_de_pago == 'D' || medio_de_pago == 'E'`.
- Calcula el monto con descuento: `monto * (1 - DESCUENTO)`.

**`buscar_reserva`**
- Pregunta si buscar por habitación (1) o por apellido (2) y pide el dato.
- Compara números con `==` y textos con `strcmp(...) == 0`. Los apellidos se pasan a mayúsculas antes de comparar.
- Si se busca por habitación, informa si está OCUPADA o LIBRE.

Preguntas posibles en el oral:
- ¿Por qué no se pueden comparar strings con `==`?
- ¿Para qué sirve `pasar_a_mayusculas` en la búsqueda?
- ¿Por qué `DESCUENTO` es un `#define`?

## Santiago – opciones 5 y 6
**`dividir_por_tarjeta`**
- Abre `reservas.txt` en `"r"` y los dos archivos nuevos en `"w"`, que los crea o los pisa.
- Lee una reserva por vez y la escribe en `reservas_con_tarjeta.txt` o en `reservas_sin_tarjeta.txt` según `hotel.tarjeta`.
- Si falla algún `fopen`, cierra los archivos que sí se abrieron y avisa.
- Al final cierra los tres archivos e informa cuántas reservas fueron a cada uno.

**`salir_del_sistema`**
- Muestra el mensaje de salida. El `do-while` del menú termina porque la condición es `opcion != 6`.

Preguntas posibles en el oral:
- ¿Por qué no se necesita `malloc` para dividir el archivo?
- ¿Por qué hay que cerrar todos los archivos con `fclose`?
- ¿Qué devuelve `fscanf` y por qué se compara con 5 (`CAMPOS`)?

## Preguntas para todo el grupo
- ¿Dónde está el único puntero del programa y por qué no se puede evitar? (`FILE *`)
- ¿Por qué no hay variables globales y cómo pasan los datos entre funciones? (por valor y con variables locales)
- ¿Qué pasa si en el menú se escribe una letra? (`leer_entero` limpia el buffer y la vuelve a pedir)
