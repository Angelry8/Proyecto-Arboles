# Arquitectura del Proyecto Programado II

## Objetivo

Construir un programa de consola en C++11 para generar una lista doblemente enlazada con entre 7 y 15 enteros únicos entre 1 y 100, mostrarla antes de cargarla y crear con esos datos un árbol binario de búsqueda (ABB). El menú permite mostrar el árbol, contar nodos, buscar, recorrer en preorden/inorden/postorden y eliminar.

El alcance de este entregable es la arquitectura y el esqueleto compilable. Las operaciones propias de las estructuras quedan como `TODO` para que las implemente el equipo.

## Decisiones de diseño

- **ABB:** cada valor menor que un nodo va a su subárbol izquierdo y cada valor mayor al derecho. La secuencia de inserción es el orden de la lista; por eso el árbol final depende de esa secuencia.
- **Sin contenedores STL:** lista y árbol usan nodos enlazados con punteros y administran su memoria con `new`/`delete` al implementarse. Se evita `vector`, `list`, `set`, `map`, `stack` y `queue` según la decisión del supervisor.
- **Datos únicos:** el generador evita duplicados; la operación `insertar` también debe ignorarlos para mantener la propiedad del ABB si se usa con otros datos.
- **Eliminación con dos hijos:** reemplazar el dato del nodo por su sucesor inorden, el valor mínimo de su subárbol derecho, y luego eliminar el nodo que contenía ese sucesor.
- **Lista como origen persistente:** eliminar un valor del árbol no modifica la lista. La lista representa los datos generados inicialmente y el ABB es la estructura sobre la que opera el menú.
- **Responsabilidad de memoria:** los destructores de ambas estructuras liberan todos los nodos propios. Las clases deshabilitan copia superficial para evitar doble liberación accidental.
- **Interfaz en español:** clases en PascalCase, métodos en camelCase y mensajes/comentarios en español, con UTF-8.
- **Separación por archivos:** un solo `ArbolBST.h` y dos unidades de implementación para que las partes 3 y 4 trabajen por separado. Los archivos `.cpp` se compilan juntos.

## Capas y dependencias

```text
main.cpp
  ├── GeneradorAleatorio ──> ListaDoble ──> NodoDoble
  ├── ArbolBST <─────────── ListaDoble (lee el origen para cargar)
  └── Menu ────────────────> ArbolBST

ConstantesProyecto.h ──────> GeneradorAleatorio (rangos 7-15 y 1-100)
ArbolBST.h ────────────────> declaraciones compartidas por ambos .cpp del ABB
```

`main` crea y llena la lista, la muestra antes de cargar el ABB, carga el árbol e inicia el menú. El menú no accede directamente a los nodos; delega consultas y modificaciones a `ArbolBST`.

## Archivos y responsables

| Archivo(s) | Responsabilidad | Responsable |
|---|---|---|
| `main.cpp`, `Menu.h`, `Menu.cpp` | Flujo principal, menú, lectura validada de enteros y llamadas a operaciones | Parte 1: Angel, líder e integración |
| `ConstantesProyecto.h` | Rangos centrales de tamaño y valor | Integración (usar Parte 2) |
| `NodoDoble.h/.cpp`, `ListaDoble.h/.cpp` | Nodo, lista, inserción al final, búsqueda, tamaño, salida y destructor | Parte 2: Derek |
| `GeneradorAleatorio.h/.cpp` | Crear de 7 a 15 valores únicos del 1 al 100 y agregarlos a la lista | Parte 2: Derek |
| `ArbolBST.h` | Declaración única del ABB y sus contratos compartidos | Angel: integración; nadie más lo edita sin coordinar |
| `ArbolBST_Consultas.cpp` | Insertar, cargar, contar, buscar y recorridos | Parte 3: Dario |
| `ArbolBST_Modificacion.cpp` | Eliminar, dibujar y liberar el ABB | Parte 4: Manuel |
| `ARQUITECTURA.md` | Contratos, decisiones, integración y guía de uso | Angel / equipo |

Angel integra los cambios de las partes en sus archivos asignados y verifica el conjunto al recibir cada entrega. Nadie debe declarar otra clase `ArbolBST` ni redefinir `NodoArbol`.

## Contrato de las clases

### `NodoDoble`

- `explicit NodoDoble(int valor)`: crea un nodo con `dato = valor` y enlaces `anterior` y `siguiente` nulos. No imprime.

### `ListaDoble`

- `ListaDoble()`: crea una lista vacía.
- `~ListaDoble()`: libera cada nodo reservado por la lista.
- `void insertarAlFinal(int valor)`: agrega el valor al final y aumenta el tamaño. No rechaza duplicados por sí sola; el generador garantiza unicidad.
- `bool contiene(int valor) const`: retorna `true` si aparece y `false` si no.
- `int tamano() const`: retorna el número de nodos; para lista vacía retorna `0`.
- `void mostrar() const`: imprime tamaño y todos los elementos en orden. Para lista vacía, imprime tamaño cero y una indicación de lista vacía.
- `const NodoDoble* obtenerPrimero() const`: retorna el primer nodo para lectura secuencial; retorna `0` si la lista está vacía.
- Copia y asignación están deshabilitadas para no duplicar propietarios de los punteros.

### `GeneradorAleatorio`

- `GeneradorAleatorio()`: inicializa el generador si la implementación lo requiere.
- `void cargarElementos(ListaDoble& lista)`: elige un tamaño inclusivo de 7 a 15 y agrega esa cantidad de valores únicos inclusivos de 1 a 100. La lista destino debe estar vacía al llamarlo. No imprime; `main` presenta la lista inmediatamente después.

### `ArbolBST`

- `ArbolBST()`: crea un árbol vacío.
- `~ArbolBST()`: libera cada nodo del ABB.
- `void insertar(int valor)`: inserta según orden ABB; un duplicado se ignora. No imprime.
- `void cargarDesdeLista(const ListaDoble& lista)`: recorre la lista desde el inicio e inserta los datos en el mismo orden. Lista vacía deja el árbol sin nodos; una segunda carga en el mismo árbol intentaría añadir los valores a los ya existentes.
- `int cantidadNodos() const`: cuenta nodos; árbol vacío retorna `0`. No imprime.
- `bool buscar(int valor) const`: imprime si existe. Si existe, informa si es raíz y si es nodo padre (uno o dos hijos) u hoja (ningún hijo). Retorna `true` si existe, `false` si no; árbol vacío se informa como inexistente.
- `void preOrden() const`: imprime raíz, subárbol izquierdo y subárbol derecho. Vacío imprime mensaje claro.
- `void inOrden() const`: imprime subárbol izquierdo, raíz y subárbol derecho; para ABB válido, los datos salen ordenados. Vacío imprime mensaje claro.
- `void postOrden() const`: imprime subárbol izquierdo, subárbol derecho y raíz. Vacío imprime mensaje claro.
- `bool eliminar(int valor)`: retorna `true` si elimina y `false` si el dato no existe; informa el resultado en pantalla. Maneja cero hijos (desconectar/liberar), un hijo (conectar el hijo al padre) y dos hijos (sucesor inorden). Si elimina la raíz, actualiza `raiz`. Nunca modifica la lista original.
- `void mostrarArbol() const`: dibuja una representación jerárquica que permite reconocer raíz e hijos; árbol vacío imprime mensaje claro.
- Auxiliares privados de **Parte 3** (declarados aquí para evitar ediciones concurrentes del encabezado): `insertarRecursivo(NodoArbol*& nodo, int valor)`, `contarNodos(const NodoArbol* nodo) const`, `buscarNodo(int valor, const NodoArbol*& padre) const`, `preOrdenRecursivo(const NodoArbol* nodo) const`, `inOrdenRecursivo(const NodoArbol* nodo) const` y `postOrdenRecursivo(const NodoArbol* nodo) const`. `buscarNodo` retorna el nodo encontrado o `0` y deja el padre en `0` si el nodo encontrado es la raíz.
- Auxiliares privados de **Parte 4**: `liberar(NodoArbol* nodo)`, `eliminarRecursivo(NodoArbol* nodo, int valor, bool& eliminado)`, `minimo(NodoArbol* nodo) const` y `dibujar(const NodoArbol* nodo, int nivel) const`. `eliminarRecursivo` retorna la nueva raíz del subárbol. `dibujar` usa dibujo rotado 90 grados, subárbol derecho arriba e indentación por nivel; Parte 4 puede mejorar el formato sin cambiar la firma pública.
- Copia y asignación están deshabilitadas para evitar doble liberación.

Complejidad: `n` es el número de nodos y `h` la altura. Las operaciones de búsqueda/inserción/eliminación son O(h), por lo que en el peor caso degenerado pueden ser O(n). Recorridos, dibujo, conteo y liberación son O(n). Cargar n elementos es O(nh).

### `Menu`

- `void ejecutar(ArbolBST& arbol) const`: presenta opciones y delega cada acción hasta seleccionar salir o llegar al fin de entrada. Valida que las entradas sean enteros y que las opciones estén entre 1 y 8.
- `bool leerEntero(const char* indicacion, int& valor) const`: método privado para lectura validada. Devuelve `true` si recibió un entero; ante texto inválido limpia la entrada y retorna `false`; ante fin de entrada permite terminar ordenadamente.
- `void mostrarOpciones() const`: método privado que imprime las ocho opciones.

## Salida esperada del menú

Para ejemplificar, se considera el ABB solicitado:

```text
        4
       / \
      2   8
     / \   \
    1   3   9
```

La salida concreta del dibujo puede variar según la representación elegida, pero debe conservar esas relaciones.

1. **Mostrar árbol:** encabezado `Árbol binario de búsqueda:` seguido del dibujo anterior.
2. **Cantidad:** `Cantidad de nodos: 6`.
3. **Buscar:** para buscar `8`, indicar que existe, que es nodo padre y que no es raíz. Para `4`, indicar que existe, que es raíz y padre. Para `3`, indicar que existe, que es hoja. Para `7`, indicar que no existe.
4. **Preorden:** `4 2 1 3 8 9`.
5. **Inorden:** `1 2 3 4 8 9`.
6. **Postorden:** `1 3 2 9 8 4`.
7. **Eliminar:** pedir el entero e informar si se eliminó o no. Al eliminar `4`, se aplica sucesor inorden: el sucesor es `8`; la lista permanece intacta.
8. **Salir:** `Programa finalizado.`

Para árbol vacío, las consultas de cantidad muestran cero, mostrar/recorridos indican que está vacío, buscar informa que el valor no existe y eliminar informa que no se encontró.

## Convenciones y comentarios

- C++11, nombres y mensajes en español, UTF-8, sin emojis.
- Clases y tipos en PascalCase; métodos y variables en camelCase; constantes de rangos en mayúsculas.
- Cada método debe tener comentario breve con propósito, parámetros, retorno y complejidad temporal. Complejidades de los contratos son metas para la implementación, no una afirmación de que los stubs ya realizan la operación.
- Mantener cada responsabilidad dentro de sus archivos asignados. No introducir contenedores STL.
- Cada `new` debe tener una ruta de `delete`, incluyendo destructor y eliminación de nodos.

## Compilación

Desde la carpeta del proyecto:

```sh
g++ -std=c++11 -Wall -Wextra -pedantic *.cpp -o ProyectoArboles.exe
```

En MSYS2 puede usarse `C:\msys64\ucrt64\bin\g++.exe`. En Dev-C++ o Visual Studio deben incluirse todos los `.cpp` del proyecto y mantenerse el estándar C++11.

## Orden de integración

1. Parte 2 entrega `NodoDoble`, `ListaDoble`, constantes y generador, respetando exactamente las firmas de los encabezados.
2. Parte 3 completa consultas en `ArbolBST_Consultas.cpp` usando los auxiliares ya declarados en `ArbolBST.h`; no necesita coordinar sus firmas con Parte 4.
3. Parte 4 completa eliminación, dibujo y liberación en `ArbolBST_Modificacion.cpp`, sin cambiar contratos sin coordinar con Angel.
4. Angel integra cada archivo, conserva el orden cargar lista → mostrar lista → cargar ABB → menú y compila todos los `.cpp` en una sola invocación.
5. El equipo verifica ejemplos y casos borde: lista/árbol vacío, dato ausente, hoja, padre, raíz, eliminación con cero/uno/dos hijos y eliminación de raíz.

## Pruebas mínimas por parte

Antes de entregar, cada parte debe verificar al menos estos casos concretos:

- **Parte 1:** introducir las opciones `1` y `8` y confirmar que se ejecutan en orden; introducir una opción fuera de `1` a `8` y luego una válida; introducir texto no numérico y confirmar que se recupera sin quedarse en un ciclo de lectura.
- **Parte 2:** generar y revisar 20 listas consecutivas con tamaños entre 7 y 15; comprobar que cada lista no contiene repetidos y que todos sus valores están entre 1 y 100; comprobar mostrar y destruir una lista vacía y una lista llena.
- **Parte 3:** cargar la lista vacía y comprobar cantidad cero, búsqueda ausente y recorridos vacíos; insertar un valor, uno menor y uno mayor y comprobar preorden/inorden/postorden; insertar un duplicado y verificar que cantidad no cambia; buscar raíz, hoja, nodo padre y valor inexistente.
- **Parte 4:** eliminar una hoja, un nodo con un hijo, un nodo con dos hijos, la raíz y un valor inexistente; después de cada eliminación exitosa comprobar que inorden sigue ordenado y que `cantidadNodos` baja en uno; comprobar destruir árbol vacío y árbol no vacío.

## Limitaciones conocidas del esqueleto

- Las estructuras y el generador son stubs: la lista inicial queda vacía y el ABB no tiene nodos hasta completar las partes.
- La lectura de un entero consume un solo intento por solicitud: una entrada malformada muestra aviso y vuelve al menú; la persona puede reintentar.
- El dibujo de consola queda a criterio de Parte 4, sujeto a preservar las relaciones del ABB.
- Al eliminar en el ABB, la lista original no se modifica deliberadamente.
