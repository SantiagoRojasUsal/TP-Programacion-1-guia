# Paso a paso: cómo subir el TP al repo de entrega

No hace falta instalar nada ni usar comandos: **todo se hace desde la página de GitHub**. Cada uno hace su paso **con su propia cuenta**, así queda registrada la participación de cada integrante.

Los archivos que cada uno tiene que subir están en la carpeta `guia/subir_por_partes/` de este repo:

```
guia/subir_por_partes/
├── paso1_santiago_base/   main.c (base con el menú) y reservas.txt
├── paso2_ornella/         parte_ornella.c   (opciones 1 y 2)
├── paso3_denise/          parte_denise.c    (opciones 3 y 4)
└── paso4_santiago/        parte_santiago.c  (opciones 5 y 6)
```

> **Cómo descargar un archivo de GitHub:** abrirlo y tocar el botón de descarga (⤓, "Download raw file") arriba a la derecha.
> **Cómo copiar el contenido:** abrirlo y tocar el botón de copiar (⧉, "Copy raw file").
> **Para bajar todo junto:** en la página principal del repo, botón verde **Code → Download ZIP**.

Tienen que hacerse **en orden**: el paso 1 primero. Los pasos 2, 3 y 4 se pueden hacer en cualquier orden después del 1.

---

## Paso 0 — Santiago: crear el repo e invitar a las chicas
1. En GitHub: **+** (arriba a la derecha) → **New repository**.
2. Nombre: por ejemplo `TP-Programacion-1-Hotel`. Elegir **Public** o **Private** según lo que pida la profe. Si es privado, después hay que invitarla a ella también.
3. **No** marcar "Add a README" (lo sube Ornella en el paso 2). Tocar **Create repository**.
4. Ir a **Settings → Collaborators → Add people** y agregar a Ornella y a Denise por su usuario de GitHub. Ellas tienen que **aceptar la invitación**, que les llega por mail o aparece en github.com/notifications.

## Paso 1 — Santiago: subir la base
1. En el repo nuevo, en la pantalla de inicio tocar **uploading an existing file** (o **Add file → Upload files**).
2. Arrastrar los dos archivos de `paso1_santiago_base/`: `main.c` y `reservas.txt`.
3. Abajo, en el mensaje, escribir: `Base del programa: estructura, menu y funciones generales`.
4. Tocar **Commit changes**.

Con esto el programa ya compila y muestra el menú. Las opciones dicen "Opcion en desarrollo" hasta que cada uno suba su parte.

## Paso 2 — Ornella: opciones 1 y 2 + README
**a) Escribir su parte en una rama propia**
1. Abrir `main.c` en el repo y tocar el **lápiz** ✏️ (Edit this file).
2. Buscar estas líneas:
   ```c
   //==================== OPCIONES 1 Y 2 - ORNELLA ====================

   void cargar_reserva(T_RESERVA hotel){
   	printf("\nOpcion en desarrollo (Ornella).\n");
   }

   void listar_reservas(T_RESERVA hotel){
   	printf("\nOpcion en desarrollo (Ornella).\n");
   }
   ```
3. **Dejar** la línea del comentario `//=== OPCIONES 1 Y 2 - ORNELLA ===`. **Borrar** las dos funciones de abajo (las 7 líneas) y **pegar** en su lugar todo el contenido de `paso2_ornella/parte_ornella.c`.
4. Tocar **Commit changes...** y en la ventana:
   - Mensaje: `Opciones 1 y 2: cargar reserva y listar reservas`
   - Elegir **Create a new branch for this commit and start a pull request**
   - Nombre de la rama: `ornella`
   - Tocar **Propose changes**.
5. Se abre la pantalla del Pull Request. **Todavía no tocar "Create pull request"**: primero hay que subir el README (punto b).

**b) Subir el README a la misma rama**
1. Arriba a la izquierda, en el selector de ramas, elegir **`ornella`**.
2. **Add file → Upload files** → arrastrar `README.md` (está en la carpeta principal de este repo guía).
3. Mensaje: `README con la explicacion del programa`. Dejar marcado **Commit directly to the `ornella` branch** → **Commit changes**.

**c) Unir la rama a main**
1. Ir a la pestaña **Pull requests** → **New pull request** (o tocar el aviso amarillo "ornella had recent pushes" → **Compare & pull request**).
2. base: `main` ← compare: `ornella`. Tocar **Create pull request** y después otra vez **Create pull request**.
3. Tocar **Merge pull request** → **Confirm merge**.

## Paso 3 — Denise: opciones 3 y 4 + DOCUMENTACION
Igual que el paso 2, pero:
- En `main.c` buscar `//==================== OPCIONES 3 Y 4 - DENISE ====================`. Borrar las dos funciones que dicen "Opcion en desarrollo (Denise)" y pegar el contenido de `paso3_denise/parte_denise.c`.
- Mensaje: `Opciones 3 y 4: listado con descuento y busqueda`. Rama: `denise`.
- En la rama `denise` subir `DOCUMENTACION.md` (está en la carpeta principal de este repo guía) con el mensaje `Documentacion del programa`.
- Crear el Pull Request `denise` → `main` y hacer **Merge**.

## Paso 4 — Santiago: opciones 5 y 6
Igual que el paso 2, pero:
- En `main.c` buscar `//==================== OPCIONES 5 Y 6 - SANTIAGO ====================`. Borrar las dos funciones que dicen "Opcion en desarrollo (Santiago)" y pegar el contenido de `paso4_santiago/parte_santiago.c`.
- Mensaje: `Opciones 5 y 6: dividir archivo segun tarjeta y salir`. Rama: `santiago`.
- Crear el Pull Request `santiago` → `main` y hacer **Merge**.

## Paso 5 — Todos: comprobar que quedó bien
1. En `main` del repo de entrega tienen que estar: `main.c`, `reservas.txt`, `README.md` y `DOCUMENTACION.md`.
2. Bajar el ZIP (**Code → Download ZIP**), compilar `main.c` y probar las 6 opciones. Ninguna debe decir "Opcion en desarrollo".
3. Comparar el `main.c` final con el `main.c` de este repo guía: tiene que ser igual.
4. Mandar el link del repo por Blackboard antes del **viernes 23 de octubre**.

---

### Si algo sale mal
- **"This branch has conflicts" en un Pull Request:** pasa si dos personas tocaron la misma parte del archivo. Tocar **Resolve conflicts** y dejar el código de las dos partes, borrando las líneas `<<<<<<<`, `=======` y `>>>>>>>`. Si cada uno solo cambia su sección, no debería pasar.
- **Una opción no compila después de pegar:** revisar que se hayan borrado las dos funciones "Opcion en desarrollo" (si quedan, la función aparece repetida) y que se haya pegado el archivo **completo**.
- **No aparece el lápiz para editar:** falta aceptar la invitación del paso 0.
