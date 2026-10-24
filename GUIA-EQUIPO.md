# Guía del Equipo — Proyecto Programado II: Árboles

- **Universidad:** Universidad Nacional (UNA), Sede Chorotega, Campus Nicoya
- **Curso:** Estructura de Datos — II Ciclo 2026
- **Profesor:** MSc. Walter León Chavarría
- **Evaluación:** Proyecto Programado II "Árboles" (Valor: 15 %)
- **Entrega límite:** 11 de noviembre de 2026 antes de las 12:00 medianoche en el Aula Virtual (no se recibe después)
- **Integrantes:**
  - **Parte 1 (Líder e integración):** Angel
  - **Parte 2:** Derek
  - **Parte 3:** Dario
  - **Parte 4:** Manuel

---

## 1. Qué hay que hacer e idea del diseño

### Resumen del enunciado

Debemos construir en C++ un programa de consola que gestione un **Árbol Binario de Búsqueda (ABB)** alimentado desde una **lista doblemente enlazada**:

1. Al iniciar, el programa genera una lista doblemente enlazada con un **tamaño aleatorio entre 7 y 15 nodos**, rellena con **valores enteros aleatorios entre 1 y 100 sin repetir**.
2. **Antes de cargar el árbol**, se muestra en pantalla la lista generada indicando su tamaño y sus elementos en orden.
3. Con los elementos de esa lista se carga el ABB respetando su secuencia original.
4. Luego se ejecuta un menú interactivo con 8 opciones:
   - `1` Mostrar Árbol
   - `2` Cantidad de Nodos
   - `3` Buscar (validar si existe; si existe, indicar si es nodo padre u hoja, además de informar si es la raíz)
   - `4` preOrden
   - `5` InOrden
   - `6` postOrden
   - `7` Eliminar (validar que exista; resolver los casos de dos hijos, un hijo o ningún hijo)
   - `8` Salir

La entrega consiste en un único archivo `.rar` nombrado con los nombres de los integrantes, que incluya todos los `.cpp`/`.h` y el documento escrito (portada académica, comentario de los métodos más importantes, manual de usuario y limitaciones del proyecto). **Advertencia del enunciado:** cualquier copia o plagio se penaliza a todos los involucrados.

### Idea del diseño (`ListaDoble -> ArbolBST -> Menu`)

El flujo separa la generación de datos, la estructura lineal de origen, el árbol de búsqueda y la interfaz de consola:

1. `main.cpp` instancia `ListaDoble` y usa `GeneradorAleatorio` para insertar entre 7 y 15 valores únicos del 1 al 100.
2. `main.cpp` llama a `lista.mostrar()` antes de crear y poblar el árbol. La `ListaDoble` queda como registro original persistente: eliminar nodos en el ABB nunca modifica la lista.
3. `ArbolBST` lee la `ListaDoble` secuencialmente desde `obtenerPrimero()` e inserta cada entero según la regla del ABB (menores a la izquierda, mayores a la derecha, ignorando duplicados).
4. `Menu` lee y valida las opciones del usuario y delega todas las consultas y eliminaciones a `ArbolBST`, sin tocar punteros ni nodos directamente.

### Diagrama de dependencias (`ARQUITECTURA.md`)

```text
main.cpp
  ├── GeneradorAleatorio ──> ListaDoble ──> NodoDoble
  ├── ArbolBST <─────────── ListaDoble (lee el origen para cargar)
  └── Menu ────────────────> ArbolBST

ConstantesProyecto.h ──────> GeneradorAleatorio (rangos 7-15 y 1-100)
ArbolBST.h ────────────────> declaraciones compartidas por ambos .cpp del ABB
```

---

## 2. Cómo está organizado el código

El esqueleto del proyecto **ya compila** de principio a fin usando implementaciones base (*stubs*): en su estado inicial la lista queda vacía y el árbol no tiene nodos. Dentro de los archivos `.cpp`, cada método pendiente está marcado con un comentario `// TODO (Parte N)` que indica a quién le toca implementarlo.

Para que las Partes 3 y 4 trabajen en el ABB al mismo tiempo sin generar conflictos, existe un único encabezado `ArbolBST.h` y dos archivos de implementación separados (`ArbolBST_Consultas.cpp` y `ArbolBST_Modificacion.cpp`) que se compilan juntos.

### Regla de oro del equipo

- **Edita únicamente los archivos asignados a tu parte.**
- **No cambies ninguna firma en los archivos `.h`** (ni nombres, ni parámetros, ni tipos de retorno, ni `const`, ni visibilidad).
- **No declares otra clase `ArbolBST` ni redefinas `NodoArbol`.**
- **`ArbolBST.h` está a cargo de Angel.** Si necesitas agregar o ajustar algo en cualquier `.h`, no lo modifiques por tu cuenta: pídeselo primero a Angel para que coordine el cambio con todo el grupo.

| Archivo(s) | Responsabilidad | Responsable |
|---|---|---|
| `main.cpp`, `Menu.h`, `Menu.cpp`, `ConstantesProyecto.h` | Flujo principal, menú, validación de lectura, rangos, integración y `.rar` | Parte 1: Angel (líder) |
| `ArbolBST.h` | Contrato único compartido del ABB | Angel (nadie más lo edita) |
| `NodoDoble.h/.cpp`, `ListaDoble.h/.cpp`, `GeneradorAleatorio.h/.cpp` | Nodo doble, lista doble y generación de 7-15 enteros únicos (1-100) | Parte 2: Derek |
| `ArbolBST_Consultas.cpp` | Inserción, carga desde lista, conteo, búsqueda y recorridos del ABB | Parte 3: Dario |
| `ArbolBST_Modificacion.cpp` | Eliminación (3 casos), dibujo jerárquico y liberación de memoria del ABB | Parte 4: Manuel |

---

## 3. Distribución de las 4 partes

### Parte 1 — Angel (Líder)

- **Archivos:** `main.cpp`, `Menu.h`, `Menu.cpp`, `ConstantesProyecto.h`, custodia de `ArbolBST.h`, integración general, compilación final y armado del `.rar`.
- **Dificultad estimada:** Baja-Media en codificación individual; Media-Alta por la coordinación, integración de entregas y verificación completa.

**Flujo base y constantes:**
- `ConstantesProyecto.h` — Define `enum RangoProyecto` (`TAMANO_LISTA_MINIMO = 7`, `TAMANO_LISTA_MAXIMO = 15`, `VALOR_ALEATORIO_MINIMO = 1`, `VALOR_ALEATORIO_MAXIMO = 100`).
- `int main()` (`main.cpp`) — Crea y llena la `ListaDoble`, la imprime antes de cargar el árbol, construye y carga `ArbolBST` e inicia `Menu::ejecutar`.

**Métodos públicos (`Menu.h`):**
- `void ejecutar(ArbolBST& arbol) const;` — Ejecuta el ciclo principal del menú validando opciones entre 1 y 8 y delegando cada operación a `arbol` hasta salir o llegar al fin de entrada.

**Auxiliares privados (`Menu.h`):**
- `bool leerEntero(const char* indicacion, int& valor) const;` — *(Incluye completar el `TODO` de `leerEntero`)* Muestra `indicacion`, intenta leer un entero y retorna `true` si fue válido; ante texto inválido limpia la entrada y retorna `false` sin ciclarse, y permite salir ordenadamente ante fin de entrada.
- `void mostrarOpciones() const;` — Imprime en consola las 8 opciones disponibles del menú.

**Pruebas mínimas:**
- Introducir las opciones `1` y `8` y confirmar que se ejecutan en orden.
- Introducir una opción fuera de `1` a `8` y luego una válida.
- Introducir texto no numérico y confirmar que se recupera sin quedarse en un ciclo de lectura.

---

### Parte 2 — Derek

- **Archivos:** `NodoDoble.h`, `NodoDoble.cpp`, `ListaDoble.h`, `ListaDoble.cpp`, `GeneradorAleatorio.h`, `GeneradorAleatorio.cpp` (usa las constantes de `ConstantesProyecto.h` sin editar ese archivo).
- **Dificultad estimada:** Media (manejo de enlaces dobles `anterior`/`siguiente`, liberación completa en destructor y control de unicidad).

**Métodos públicos (`NodoDoble.h`, `ListaDoble.h`, `GeneradorAleatorio.h`):**
- `explicit NodoDoble(int valor);` — Inicializa un nodo con `dato = valor` y punteros `anterior` y `siguiente` nulos (`0`), sin imprimir.
- `ListaDoble();` — Inicializa una lista vacía (`primero = 0`, `ultimo = 0`, `cantidad = 0`) en O(1). Ya viene hecho en el esqueleto.
- `~ListaDoble();` — Recorre todos los nodos de la lista y libera cada uno con `delete` en O(n).
- `void insertarAlFinal(int valor);` — Crea un `NodoDoble` al final actualizando enlaces y `cantidad` en O(1) (la unicidad la controla el generador).
- `bool contiene(int valor) const;` — Recorre la lista y retorna `true` si `valor` está presente o `false` si no, en O(n).
- `int tamano() const;` — Retorna la cantidad actual de nodos (`0` si está vacía) en O(1).
- `void mostrar() const;` — Imprime el tamaño de la lista y sus elementos en orden; si está vacía, imprime tamaño cero y avisa que está vacía, en O(n).
- `const NodoDoble* obtenerPrimero() const;` — Retorna el puntero al primer nodo (`0` si está vacía) para lectura secuencial desde el ABB, en O(1).
- `GeneradorAleatorio();` — Inicializa la semilla del generador aleatorio una sola vez (ver el `TODO` del constructor).
- `void cargarElementos(ListaDoble& lista);` — Elige un tamaño aleatorio inclusivo entre 7 y 15 e inserta en `lista` esa cantidad de enteros únicos entre 1 y 100 usando `contiene` e `insertarAlFinal`, sin imprimir, en O(n²).

**Auxiliares privados:**
- Ninguno por implementar. (`ListaDoble(const ListaDoble& otra);` y `ListaDoble& operator=(const ListaDoble& otra);` están declarados en `private` en `ListaDoble.h` únicamente para impedir copias superficiales; no los implementes).

**Pruebas mínimas:**
- Generar y revisar 20 listas consecutivas con tamaños entre 7 y 15.
- Comprobar que cada lista no contiene repetidos y que todos sus valores están entre 1 y 100.
- Comprobar mostrar y destruir una lista vacía y una lista llena.

---

### Parte 3 — Dario

- **Archivos:** `ArbolBST_Consultas.cpp` (implementa las consultas e inserción declaradas en `ArbolBST.h`; **no edites** `ArbolBST.h`).
- **Dificultad estimada:** Media (recursividad en árboles binarios para insertar, contar y recorrer, más clasificación de nodos al buscar).

**Constructores base (ya vienen hechos en `ArbolBST_Consultas.cpp`):**
- `explicit NodoArbol(int valor);` — Crea un nodo del árbol con `dato = valor` e hijos `izquierdo` y `derecho` en `0`.
- `ArbolBST();` — Inicializa un árbol vacío (`raiz = 0`) en O(1).

**Métodos públicos (`ArbolBST.h`):**
- `void insertar(int valor);` — Inserta `valor` manteniendo el orden del ABB e ignorando duplicados, sin imprimir, en O(h).
- `void cargarDesdeLista(const ListaDoble& lista);` — Recorre `lista` desde `obtenerPrimero()` e inserta cada elemento en ese mismo orden mediante `insertar`, en O(nh).
- `int cantidadNodos() const;` — Retorna el número total de nodos del ABB (`0` en árbol vacío), sin imprimir, en O(n).
- `bool buscar(int valor) const;` — Imprime si `valor` existe o no; si existe, informa si es la raíz y si es nodo padre (1 o 2 hijos) u hoja (0 hijos), retornando `true` o `false` en O(h).
- `void preOrden() const;` — Imprime el recorrido raíz-izquierdo-derecho, o un mensaje claro si el árbol está vacío, en O(n).
- `void inOrden() const;` — Imprime el recorrido izquierdo-raíz-derecho (valores ordenados), o un mensaje claro si está vacío, en O(n).
- `void postOrden() const;` — Imprime el recorrido izquierdo-derecho-raíz, o un mensaje claro si está vacío, en O(n).

**Auxiliares privados (`ArbolBST.h`):**
- `void insertarRecursivo(NodoArbol*& nodo, int valor);` — Busca recursivamente la posición en el ABB y enlaza un nuevo `NodoArbol` por referencia al puntero si el dato no está repetido.
- `int contarNodos(const NodoArbol* nodo) const;` — Retorna `0` si `nodo` es nulo o `1` más el conteo recursivo de sus subárboles izquierdo y derecho.
- `const NodoArbol* buscarNodo(int valor, const NodoArbol*& padre) const;` — Retorna el puntero al nodo con `valor` (o `0` si no existe) y actualiza `padre` (`padre` queda en `0` cuando el nodo hallado es la raíz).
- `void preOrdenRecursivo(const NodoArbol* nodo) const;` — Visita e imprime recursivamente raíz, subárbol izquierdo y subárbol derecho.
- `void inOrdenRecursivo(const NodoArbol* nodo) const;` — Visita e imprime recursivamente subárbol izquierdo, raíz y subárbol derecho.
- `void postOrdenRecursivo(const NodoArbol* nodo) const;` — Visita e imprime recursivamente subárbol izquierdo, subárbol derecho y raíz.

**Pruebas mínimas:**
- Cargar la lista vacía y comprobar cantidad cero, búsqueda ausente y recorridos vacíos.
- Insertar un valor, uno menor y uno mayor y comprobar preorden/inorden/postorden.
- Insertar un duplicado y verificar que cantidad no cambia.
- Buscar raíz, hoja, nodo padre y valor inexistente.

---

### Parte 4 — Manuel

- **Archivos:** `ArbolBST_Modificacion.cpp` (implementa destructor, eliminación y dibujo declarados en `ArbolBST.h`; **no edites** `ArbolBST.h`).
- **Dificultad estimada:** Alta (es la parte más delicada del proyecto: manejo exacto de punteros y `delete` en los 3 casos de eliminación —incluyendo el sucesor inorden con dos hijos y el borrado de la raíz— más el dibujo jerárquico en consola).

**Métodos públicos (`ArbolBST.h`):**
- `~ArbolBST();` — Libera todos los nodos reservados del ABB llamando a `liberar(raiz)` en O(n).
- `bool eliminar(int valor);` — Elimina `valor` del ABB manejando 0, 1 o 2 hijos (con sucesor inorden), actualiza `raiz` si cambia, muestra en pantalla si se eliminó o no existía y retorna `true` o `false` sin tocar `ListaDoble`, en O(h).
- `void mostrarArbol() const;` — Muestra el encabezado `Árbol binario de búsqueda:` y dibuja la jerarquía del árbol en consola, o imprime un mensaje claro si está vacío, en O(n).

**Auxiliares privados (`ArbolBST.h`):**
- `void liberar(NodoArbol* nodo);` — Libera recursivamente en postorden los subárboles izquierdo y derecho y luego hace `delete nodo`.
- `NodoArbol* eliminarRecursivo(NodoArbol* nodo, int valor, bool& eliminado);` — Localiza `valor`, aplica el caso correspondiente (sin hijos, un hijo o dos hijos reemplazando el dato por el de `minimo(nodo->derecho)` y eliminando ese nodo sucesor), marca `eliminado = true` y retorna la nueva raíz del subárbol.
- `NodoArbol* minimo(NodoArbol* nodo) const;` — Desciende por los punteros `izquierdo` hasta retornar el nodo con el valor mínimo del subárbol.
- `void dibujar(const NodoArbol* nodo, int nivel) const;` — Imprime el ABB rotado 90 grados (primero subárbol derecho en `nivel + 1`, luego el nodo actual indentado según `nivel` y finalmente subárbol izquierdo en `nivel + 1`; puedes pulir el formato visual sin cambiar la firma).

*(Nota: `ArbolBST(const ArbolBST& otro);` y `ArbolBST& operator=(const ArbolBST& otro);` en `ArbolBST.h` solo deshabilitan la copia superficial; no se implementan).*

**Pruebas mínimas:**
- Eliminar una hoja, un nodo con un hijo, un nodo con dos hijos, la raíz y un valor inexistente.
- Después de cada eliminación exitosa comprobar que inorden sigue ordenado y que `cantidadNodos` baja en uno.
- Comprobar destruir árbol vacío y árbol no vacío.

---

## 4. Cómo compilar y probar solo tu parte

Antes de enviar tu avance, verifica que el proyecto completo **compile sin errores y sin una sola advertencia (`warning`)**.

### Cómo compilar en cada entorno

- **MSYS2 / MinGW (línea de comandos):** abre la terminal en la carpeta donde están todos los `.h` y `.cpp` y ejecuta:
  ```sh
  g++ -std=c++11 -Wall -Wextra -pedantic *.cpp -o ProyectoArboles
  ```
  *(En MSYS2 también puedes usar `C:\msys64\ucrt64\bin\g++.exe` directamente).*
- **Dev-C++:** crea un proyecto de consola agregando todos los `.h` y `.cpp` de la carpeta y activa `-std=c++11` en **Herramientas > Opciones del compilador** (añade también `-Wall -Wextra -pedantic` para ver todas las advertencias).
- **Visual Studio:** crea un **proyecto de consola vacío** en C++, agrega todos los archivos `.h` y `.cpp` existentes al proyecto y compila toda la solución.

### Cómo probar tu parte sin depender de entregas ajenas

- **Parte 3 sin Parte 2:** aunque la Parte 2 todavía no esté lista, puedes probar todas tus funciones de `ArbolBST_Consultas.cpp` llamando a `arbol.insertar(...)` con valores fijos a mano (por ejemplo: `4, 2, 8, 1, 3, 9`) en una copia local de `main.cpp`. Ese cambio temporal es solo para tus pruebas y **NO se entrega**.
- **Parte 4 y su dependencia de `insertar` (Parte 3):** para probar `eliminar`, `mostrarArbol` y `~ArbolBST` necesitas poder poblar el árbol con nodos. Coordínate con Dario para que te pase un adelanto de `insertar` / `insertarRecursivo`, o escribe en tu copia local una versión temporal mínima de inserción únicamente para armar árboles de prueba. **Esa versión temporal NO se entrega**: tú solo entregas `ArbolBST_Modificacion.cpp`.

---

## 5. Reglas de código obligatorias

1. **Estándar C++11:** evita extensiones fuera del estándar; todo debe compilar con `-std=c++11 -Wall -Wextra -pedantic`.
2. **Prohibido usar contenedores de la STL:** no se permite incluir ni usar `vector`, `list`, `set`, `map`, `stack`, `queue` ni contenedores equivalentes. Toda estructura debe construirse con nodos enlazados, punteros, `new` y `delete`.
3. **Cada `new` con su `delete`:** todo nodo creado con `new` debe liberarse con `delete` cuando se elimina individualmente en el ABB o cuando se destruyen `ListaDoble` y `ArbolBST`.
4. **Nombres y estilo en español (UTF-8):**
   - Clases, estructuras y enumeraciones en `PascalCase` (`ListaDoble`, `ArbolBST`, `NodoArbol`).
   - Métodos y variables en `camelCase` (`insertarAlFinal`, `cargarDesdeLista`, `cantidadNodos`).
   - Constantes de rangos en mayúsculas (`TAMANO_LISTA_MINIMO`).
5. **Comentario de encabezado en cada método:** todo método que implementes debe llevar justo encima un comentario breve indicando:
   - Propósito.
   - Parámetros.
   - Retorno.
   - Complejidad temporal (`O(1)`, `O(h)`, `O(n)`, `O(nh)` u `O(n²)`).
6. **Sin emojis:** no pongas emojis ni en los mensajes de `std::cout` ni en comentarios ni en documentos.
7. **Código propio (cero plagio):** cada quien programa su parte desde cero entendiendo cada línea. No copies código de internet ni de otros grupos: el profesor penaliza por igual a todos los involucrados.

---

## 6. Documento escrito y presentación

### Documento escrito (4 secciones obligatorias)

| Sección del documento | Responsable | Qué debe contener |
|---|---|---|
| 1. Portada académica | Angel | Datos oficiales de la UNA Sede Chorotega Campus Nicoya, curso, ciclo, profesor MSc. Walter León Chavarría, título del proyecto, nombres completos y fecha. |
| 2. Comentar los métodos más importantes | **Los 4 integrantes** (cada uno redacta los de su parte) | Para cada método clave de tu parte: **qué hace**, **cómo funciona** internamente, **complejidad temporal** y **un ejemplo paso a paso usando el árbol `4, 2, 8, 1, 3, 9`**. |
| 3. Manual de usuario | Angel | Explicación clara de ejecución, salida inicial de la lista y uso de las 8 opciones del menú con entradas válidas e inválidas. |
| 4. Limitaciones del proyecto | Angel (y armado final) | Decisiones y límites de diseño (lista original inmutable al eliminar en el ABB, un intento por lectura de entero antes de volver al menú, dibujo en texto según secuencia aleatoria inicial). |

Para unificar los ejemplos de la sección **"Comentar los métodos más importantes"**, todos usaremos este mismo árbol de referencia cargado con la secuencia `4, 2, 8, 1, 3, 9`:

```text
        4
       / \
      2   8
     / \   \
    1   3   9
```

Con este árbol:
- `cantidadNodos()` da `6`.
- `buscar`: `4` es raíz y padre; `8` es padre (no raíz); `3` es hoja; `7` no existe.
- Recorridos: `preOrden` = `4 2 1 3 8 9`, `inOrden` = `1 2 3 4 8 9`, `postOrden` = `1 3 2 9 8 4`.
- `eliminar(4)`: caso de dos hijos; se reemplaza `4` por su sucesor inorden (`8`, el mínimo de su subárbol derecho) y se elimina el nodo original del `8`.

### Presentación y dominio (Rúbrica: 15 puntos = 15 %)

- **Presentación de la temática:** 5 puntos.
- **Implementación:** 4 puntos.
- **Demuestra dominio explicando en detalle la solución:** **6 puntos**.

En la exposición cada integrante presentará su parte, **pero los 4 debemos poder explicar el flujo completo del programa y la eliminación de un nodo con dos hijos (sucesor inorden)**. El dominio individual y grupal vale 6 de los 15 puntos totales, así que nadie puede quedarse solo con conocer su archivo.

---

## 7. Calendario de trabajo

Hoy es **viernes 23 de octubre de 2026**. Trabajaremos con este cronograma para subir el proyecto un día antes del cierre oficial:

| Fecha | Hito | Responsable(s) y detalle |
|---|---|---|
| Sábado 24 oct | Arranque del equipo | Angel comparte el esqueleto compilable y esta guía con los 4 integrantes. |
| Miércoles 28 oct | Entrega de Parte 2 | Derek entrega `NodoDoble`, `ListaDoble` y `GeneradorAleatorio` probados; las demás partes pasan a probar con datos aleatorios reales. |
| Domingo 1 nov | Entrega de Partes 3 y 4 | Dario y Manuel entregan `ArbolBST_Consultas.cpp` y `ArbolBST_Modificacion.cpp` compilando sin advertencias. |
| Lunes 2 al miércoles 4 nov | Integración y pruebas | Angel integra todas las partes, ejecuta pruebas completas del sistema y coordina ajustes si aparece algún fallo. |
| Viernes 6 nov | Secciones del documento | Cada integrante envía a Angel la redacción de sus métodos más importantes (con complejidad y ejemplo en `4, 2, 8, 1, 3, 9`). |
| Domingo 8 nov | Documento armado | Angel completa portada, manual de usuario y limitaciones, y comparte el documento unificado para revisión. |
| Lunes 9 nov | Ensayo general | Reunión de los 4 para ensayar la explicación de cada parte, el flujo completo y el borrado con dos hijos. |
| Martes 10 nov | Entrega en Aula Virtual | Angel sube el `.rar` definitivo (1 día de margen antes del cierre). |
| Miércoles 11 nov (antes de las 12:00 medianoche) | Cierre oficial | Fecha y hora límite en el Aula Virtual; no se reciben entregas posteriores. |
