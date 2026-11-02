# UNIVERSIDAD NACIONAL
### Sede Regional Chorotega — Campus Nicoya
### Escuela de Informática
### Carrera: Ingeniería en Sistemas de Información
### Curso: Estructuras de Datos — II Ciclo 2026
### Profesor: MSc. Walter León Chavarría

---

# II Proyecto Programado: Manejo de Árboles Binarios de Búsqueda (ABB)

### Integrantes:
- **Angel** (Líder e integración — Parte 1)
- **Derek** (Estructuras lineales y generación aleatoria — Parte 2)
- **Dario** (Consultas, inserción y recorridos del ABB — Parte 3)
- **Manuel** (Modificación, eliminación, dibujo y memoria — Parte 4)

**Fecha:** Noviembre de 2026

---

## 1. Portada Académica y Datos Generales

- **Institución:** Universidad Nacional de Costa Rica (UNA)
- **Sede:** Regional Chorotega, Campus Nicoya
- **Curso:** Estructuras de Datos (EIF)
- **Periodo:** II Ciclo Lectivo 2026
- **Proyecto:** II Proyecto Programado — Árboles Binarios de Búsqueda alimentados desde Lista Doblemente Enlazada
- **Docente:** MSc. Walter León Chavarría
- **Empresa cliente ficticia:** GPT S.A.

---

## 2. Comentarios de los Métodos Más Importantes

Para el análisis técnico de los métodos, se utiliza el árbol binario de búsqueda oficial de referencia construido con la secuencia `4, 2, 8, 1, 3, 9`:

```text
        [4]
       /   \
     [2]   [8]
    /   \     \
  [1]   [3]   [9]
```

---

### Parte 1 (Angel) — Flujo Principal, Validación y Menú

#### 1. `bool Menu::leerEntero(const char* indicacion, int& valor) const`
- **Qué hace:** Imprime la indicación, solicita por teclado un número entero, valida que no haya caracteres adicionales en la línea (descartando entradas como `"5abc"` o `"3 4"`) y gestiona posibles estados de fin de archivo (`EOF`).
- **Cómo funciona internamente:** Utiliza `std::cin >> valor`. Si la lectura es exitosa, recorre con `std::cin.get()` los caracteres restantes de la línea hasta encontrar `'\n'` o `EOF`, verificando que todos sean espacios en blanco o tabulaciones. Si detecta texto no numérico o basura adicional, limpia el buffer de entrada con `std::cin.clear()` e ignora hasta el final de línea, retornando `false`.
- **Complejidad temporal:** $O(k)$, donde $k$ es la cantidad de caracteres leídos en la línea.
- **Ejemplo paso a paso:**
  - El usuario escribe `"8\n"`. La función lee `8`, verifica que lo siguiente es `'\n'`, almacena `valor = 8` y retorna `true`.
  - El usuario escribe `"4xyz\n"`. Se lee el `4`, pero al iterar sobre el buffer se encuentra la letra `'x'`. Se emite mensaje de entrada inválida y retorna `false`.

#### 2. `void Menu::ejecutar(ArbolBST& arbol) const`
- **Qué hace:** Mantiene el bucle interactivo de opciones del programa (1 a 8) despachando cada acción a los métodos correspondientes del árbol binario.
- **Cómo funciona internamente:** Contiene un bucle `while (continuar)` que invoca `mostrarOpciones()`, solicita la opción mediante `leerEntero` y entra a un `switch-case` que delega las operaciones a `arbol`. La opción 8 cambia la bandera a `false` para terminar ordenadamente.
- **Complejidad temporal:** $O(m \times c)$, donde $m$ es el número de selecciones realizadas y $c$ la complejidad de la operación invocada.

---

### Parte 2 (Derek) — Estructura Lineal y Generador Aleatorio

#### 1. `void GeneradorAleatorio::cargarElementos(ListaDoble& lista)`
- **Qué hace:** Determina aleatoriamente un tamaño $N \in [7, 15]$ y genera $N$ números enteros pseudoaleatorios dentro del rango $[1, 100]$ sin repeticiones, insertándolos secuencialmente en la lista doble.
- **Cómo funciona internamente:** Inicializa la semilla aleatoria una sola vez mediante `std::time(0)`. En un bucle `while`, genera candidatos con `std::rand()`. Con cada número generado invoca `lista.contiene(valor)`. Si retorna `false`, llama a `lista.insertarAlFinal(valor)` y aumenta el contador de insertados.
- **Complejidad temporal:** $O(n^2)$ en el peor caso, pues verificar unicidad en una lista doble de tamaño $i$ requiere $O(i)$ comparaciones, resultando en $\sum_{i=1}^{n} i = O(n^2)$.
- **Ejemplo paso a paso:**
  - Se define aleatoriamente un tamaño de 6 elementos para el conjunto `{4, 2, 8, 1, 3, 9}`.
  - Se genera `4`, no está en la lista $\rightarrow$ se inserta.
  - Se genera `2`, no está en la lista $\rightarrow$ se inserta.
  - Si saliera `4` nuevamente, `lista.contiene(4)` retorna `true` y se descarta sin duplicar.

#### 2. `void ListaDoble::insertarAlFinal(int valor)`
- **Qué hace:** Instancia un nuevo nodo doble y lo enlaza al final de la lista enlazada.
- **Cómo funciona internamente:** Reserva dinámicamente memoria con `new NodoDoble(valor)`. Si `ultimo == 0` (lista vacía), apunta `primero` y `ultimo` al nuevo nodo. En caso contrario, asigna `nuevo->anterior = ultimo`, `ultimo->siguiente = nuevo` y mueve el puntero `ultimo = nuevo`. Incrementa `cantidad`.
- **Complejidad temporal:** $O(1)$, gracias al puntero directo al último nodo.
- **Ejemplo paso a paso:**
  - Con lista `[4] <-> [2]`: Al insertar `8`, se crea el nodo con valor 8, `nuevo->anterior` apunta al nodo 2, `2->siguiente` apunta al nodo 8, y `ultimo` pasa a ser el nodo 8.

---

### Parte 3 (Dario) — Consultas, Recorridos y Carga del ABB

#### 1. `void ArbolBST::insertarRecursivo(NodoArbol*& nodo, int valor)`
- **Qué hace:** Ubica la posición jerárquica correspondiente del valor dentro del árbol e inserta un nuevo nodo, asegurando que los valores menores vayan a la izquierda, los mayores a la derecha y los duplicados sean ignorados.
- **Cómo funciona internamente:** Recibe una referencia a un puntero a nodo (`NodoArbol*&`). Si el puntero es nulo (`nodo == 0`), se asigna directamente `nodo = new NodoArbol(valor)`. Si `valor < nodo->dato`, desciende recursivamente por `nodo->izquierdo`. Si `valor > nodo->dato`, desciende por `nodo->derecho`. Si `valor == nodo->dato`, no realiza acción alguna.
- **Complejidad temporal:** $O(h)$, donde $h$ es la altura del árbol ($O(\log n)$ en árboles balanceados, $O(n)$ en el peor caso degenerado).
- **Ejemplo paso a paso (Inserción de la secuencia 4, 2, 8, 1, 3, 9):**
  - Inserta `4`: `raiz == 0` $\rightarrow$ se convierte en la raíz `[4]`.
  - Inserta `2`: $2 < 4 \rightarrow$ desciende a `4->izquierdo` (nulo) $\rightarrow$ se crea `[2]`.
  - Inserta `8`: $8 > 4 \rightarrow$ desciende a `4->derecho` (nulo) $\rightarrow$ se crea `[8]`.
  - Inserta `1`: $1 < 4 \rightarrow$ va a `[2]`; $1 < 2 \rightarrow$ se crea `[1]` a la izquierda de `[2]`.
  - Inserta `3`: $3 < 4 \rightarrow$ va a `[2]`; $3 > 2 \rightarrow$ se crea `[3]` a la derecha de `[2]`.
  - Inserta `9`: $9 > 4 \rightarrow$ va a `[8]`; $9 > 8 \rightarrow$ se crea `[9]` a la derecha de `[8]`.

#### 2. `void ArbolBST::cargarDesdeLista(const ListaDoble& lista)`
- **Qué hace:** Pobla el ABB insertando uno a uno todos los elementos contenidos en la lista doblemente enlazada, conservando su orden de aparición original.
- **Cómo funciona internamente:** Obtiene el inicio de la lista con `lista.obtenerPrimero()`. Mediante un puntero iterador `actual`, recorre secuencialmente la lista llamando a `insertar(actual->dato)` y avanza con `actual = actual->siguiente`.
- **Complejidad temporal:** $O(n \times h)$, donde $n$ es la cantidad de elementos de la lista y $h$ la altura promedio del árbol.

#### 3. `int ArbolBST::contarNodos(const NodoArbol* nodo) const` y `cantidadNodos()`
- **Qué hace:** Calcula y retorna el número total de nodos que componen el árbol binario.
- **Cómo funciona internamente:** Aplica recursión estructural: si el nodo evaluado es nulo, retorna 0. Si no es nulo, retorna `1 + contarNodos(nodo->izquierdo) + contarNodos(nodo->derecho)`.
- **Complejidad temporal:** $O(n)$, visitando cada nodo exactamente una vez.
- **Ejemplo paso a paso:**
  - En el árbol `{4, 2, 8, 1, 3, 9}`, cuenta: nodo 1 (1) + nodo 3 (1) + nodo 2 (1) = 3 a la izquierda; nodo 9 (1) + nodo 8 (1) = 2 a la derecha; más la raíz (1) = 6 nodos en total.

#### 4. `bool ArbolBST::buscar(int valor) const`
- **Qué hace:** Verifica si un valor existe en el árbol; si existe, clasifica y notifica si el nodo es la raíz del árbol y si se trata de un nodo padre o un nodo hoja.
- **Cómo funciona internamente:** Invoca la función auxiliar `buscarNodo(valor, padre)`. Si el nodo retornado es nulo, notifica que no existe y retorna `false`. Si existe, evalúa si `padre == 0` (es la raíz) y si `nodo->izquierdo != 0 || nodo->derecho != 0` (tiene al menos un hijo, por ende es nodo padre; caso contrario es hoja).
- **Complejidad temporal:** $O(h)$, donde $h$ es la altura del árbol.
- **Ejemplos con el árbol de referencia:**
  - Buscar `4`: Se encuentra en la raíz (`padre == 0`) y tiene hijos 2 y 8 $\rightarrow$ *"El elemento 4 existe en el arbol: es la raiz y es un nodo padre."*
  - Buscar `8`: No es raíz (`padre = 4`) y tiene hijo derecho 9 $\rightarrow$ *"El elemento 8 existe en el arbol: es un nodo padre."*
  - Buscar `3`: No es raíz (`padre = 2`) y no tiene hijos (`izq = 0, der = 0`) $\rightarrow$ *"El elemento 3 existe en el arbol: es un nodo hoja."*
  - Buscar `7`: Se busca por la izquierda de 8 y se llega a un puntero nulo $\rightarrow$ *"El elemento 7 no existe en el arbol."*

#### 5. Recorridos: `preOrden()`, `inOrden()`, `postOrden()`
- **Qué hacen:** Realizan y muestran los tres recorridos en profundidad del árbol binario.
- **Cómo funcionan internamente:**
  - `preOrden`: Visita **Raíz $\rightarrow$ Izquierdo $\rightarrow$ Derecho**.
  - `inOrden`: Visita **Izquierdo $\rightarrow$ Raíz $\rightarrow$ Derecho** (imprime las claves en orden ascendente estricto).
  - `postOrden`: Visita **Izquierdo $\rightarrow$ Derecho $\rightarrow$ Raíz**.
- **Complejidad temporal:** $O(n)$ para cada recorrido.
- **Resultados con el árbol de referencia:**
  - `preOrden`: `4 2 1 3 8 9`
  - `inOrden`: `1 2 3 4 8 9`
  - `postOrden`: `1 3 2 9 8 4`

---

### Parte 4 (Manuel) — Modificación, Eliminación y Memoria

#### 1. `NodoArbol* ArbolBST::eliminarRecursivo(NodoArbol* nodo, int valor, bool& eliminado)`
- **Qué hace:** Elimina un nodo con un valor específico garantizando mantener las propiedades del ABB y contemplando los 3 casos posibles (sin hijos, un solo hijo o dos hijos).
- **Cómo funciona internamente:**
  - Localiza el nodo por comparación con `nodo->dato`.
  - **Caso 1 (Nodo hoja / sin hijos):** Libera el nodo con `delete nodo` y retorna `0`.
  - **Caso 2 (Un solo hijo):** Si solo tiene hijo derecho, guarda `temporal = nodo->derecho`, libera `nodo` con `delete` y retorna `temporal`. De igual forma si solo tiene hijo izquierdo.
  - **Caso 3 (Dos hijos):** Busca el **sucesor inorden** (el valor mínimo del subárbol derecho) mediante `minimo(nodo->derecho)`. Copia el dato del sucesor en el nodo actual (`nodo->dato = sucesor->dato`) y elimina recursivamente el sucesor en el subárbol derecho invocando `nodo->derecho = eliminarRecursivo(nodo->derecho, sucesor->dato, ...)`.
- **Complejidad temporal:** $O(h)$, donde $h$ es la altura del árbol.
- **Ejemplo paso a paso (Eliminar la raíz 4):**
  - El nodo `4` tiene dos hijos (`2` y `8`).
  - Se busca el mínimo de su subárbol derecho (`nodo->derecho` es `8`). Como `8` no tiene hijo izquierdo, el mínimo es `8`.
  - Se copia el dato `8` en la raíz.
  - Se elimina el nodo `8` del subárbol derecho. Como el nodo `8` original solo tenía un hijo (`9`), se aplica el caso de un solo hijo: se enlaza `9` a la derecha de la nueva raíz y se libera la memoria del nodo `8` original.
  - El nuevo recorrido inorden queda: `1 2 3 8 9`.

#### 2. `void ArbolBST::dibujar(const NodoArbol* nodo, int nivel) const`
- **Qué hace:** Imprime gráficamente la estructura jerárquica del árbol en la consola, rotado 90 grados a la izquierda (la raíz a la izquierda y el subárbol derecho arriba).
- **Cómo funciona internamente:** Aplica recorrido inorden inverso recursivo: primero procesa `nodo->derecho` con `nivel + 1`, imprime la sangría correspondiente al nivel con `[nodo->dato]`, y finalmente procesa `nodo->izquierdo` con `nivel + 1`.
- **Complejidad temporal:** $O(n)$.

#### 3. `void ArbolBST::liberar(NodoArbol* nodo)` y `~ArbolBST()`
- **Qué hace:** Destruye y libera la memoria dinámica de todos los nodos del árbol.
- **Cómo funciona internamente:** Aplica recorrido postorden: primero libera recursivamente los subárboles izquierdo y derecho, y por último ejecuta `delete nodo`. El destructor `~ArbolBST` ejecuta `liberar(raiz)` y establece `raiz = 0`.
- **Complejidad temporal:** $O(n)$.

---

## 3. Manual de Usuario

### 3.1. Requisitos y Compilación
Para compilar el proyecto en cualquier entorno compatible con el estándar C++11 (GCC, Clang, MinGW, MSYS2):

```bash
g++ -std=c++11 -Wall -Wextra -pedantic *.cpp -o ProyectoArboles
```

Para ejecutar en Windows:
```bash
ProyectoArboles.exe
```

### 3.2. Flujo de Ejecución Inicial
Al iniciar el programa, automáticamente:
1. Se crea la lista doblemente enlazada con un tamaño aleatorio entre 7 y 15 elementos.
2. Se generan números enteros aleatorios entre 1 y 100 sin repetición y se insertan al final de la lista.
3. Se despliega en pantalla el tamaño de la lista generada y sus elementos.
4. Se instancia el Árbol Binario de Búsqueda (ABB) y se cargan los elementos en el mismo orden de la lista.
5. Se despliega el menú principal interactivo.

### 3.3. Opciones del Menú

| Opción | Nombre | Descripción |
|---|---|---|
| **1** | Mostrar árbol | Imprime en pantalla la representación visual y jerárquica del árbol (rotado 90 grados). |
| **2** | Cantidad de nodos | Muestra el conteo exacto de nodos presentes en el ABB en ese instante. |
| **3** | Buscar un elemento | Solicita un número entero; indica si existe, si es la raíz y si es un nodo padre o nodo hoja. |
| **4** | Recorrido preOrden | Muestra los elementos visitados en orden: Raíz - Izquierda - Derecha. |
| **5** | Recorrido InOrden | Muestra los elementos ordenados ascendentemente: Izquierda - Raíz - Derecha. |
| **6** | Recorrido postOrden | Muestra los elementos visitados en orden: Izquierda - Derecha - Raíz. |
| **7** | Eliminar un elemento | Solicita un número y lo elimina del árbol resolviendo correctamente los casos de 0, 1 o 2 hijos. |
| **8** | Salir | Concluye la ejecución del programa y libera toda la memoria dinámica. |

### 3.4. Manejo de Entradas Válidas e Inválidas
- **Texto o caracteres inválidos:** Si el usuario ingresa letras o símbolos (ej. `"abc"`, `"5x"`), el sistema detecta la anomalía, descarta los caracteres erróneos sin ciclarse y solicita nuevamente la opción.
- **Opciones numéricas fuera de rango:** Si se introduce un número menor a 1 o mayor a 8, se muestra el mensaje de advertencia *"Opción fuera de rango. Seleccione de 1 a 8."* y se retorna al menú.
- **Búsqueda o eliminación de valores inexistentes:** Si se busca o elimina un valor que no está en el árbol, el programa informa con claridad que no existe sin alterar la estructura ni generar errores en tiempo de ejecución.

---

## 4. Limitaciones del Proyecto

1. **Inmutabilidad de la Lista Doble de Origen:**
   Por especificación del diseño, la lista doblemente enlazada actúa como el registro histórico persistente de los datos generados inicialmente. Al eliminar nodos del árbol binario de búsqueda mediante la opción 7, la lista doble no se modifica.
2. **Interfaz en Modo Texto / Consola:**
   La visualización del árbol se realiza en modo texto rotado 90 grados a la izquierda mediante sangrías proporcionales a la profundidad. Para árboles de alturas elevadas o desbalanceados, la visualización requiere una ventana de consola con ancho suficiente.
3. **Restricción Estricta contra Contenedores STL:**
   Cumpliendo con las directrices académicas del curso de Estructuras de Datos, no se utilizó ningún contenedor de la biblioteca estándar (`std::vector`, `std::list`, `std::queue`, `std::stack`, etc.). Toda la memoria dinámica y los enlaces de punteros son gestionados manualmente mediante `new` y `delete`.
4. **Conjunto de Claves Enteras Únicas:**
   El árbol está diseñado exclusivamente para el tipo primitivo `int` y rechaza la inserción de claves duplicadas para mantener la definición clásica de Árbol Binario de Búsqueda estricto.
