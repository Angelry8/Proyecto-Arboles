#include "Menu.h"
#include <iostream>
#include <limits>

// Propósito: imprimir en consola las ocho opciones disponibles del menú principal.
// Parámetros: ninguno.
// Retorno: ninguno.
// Complejidad: O(1).
void Menu::mostrarOpciones() const {
    std::cout << "\nMenu principal\n"
              << "1. Mostrar arbol\n"
              << "2. Cantidad de nodos\n"
              << "3. Buscar un elemento\n"
              << "4. Mostrar recorrido preOrden\n"
              << "5. Mostrar recorrido InOrden\n"
              << "6. Mostrar recorrido postOrden\n"
              << "7. Eliminar un elemento\n"
              << "8. Salir\n";
}

// Propósito: solicitar y leer un número entero desde el teclado, validando formato y descartando basura.
// Parámetros: indicacion (mensaje orientativo para el usuario), valor (referencia donde se guarda el entero leído).
// Retorno: true si se leyó un entero válido sin caracteres adicionales, false en caso de error o fin de entrada.
// Complejidad: O(k), donde k es la cantidad de caracteres en la línea introducida.
bool Menu::leerEntero(const char* indicacion, int& valor) const {
    std::cout << indicacion;
    if (std::cin >> valor) {
        // Validar que tras el entero solo haya espacios o tabulaciones hasta el final de la linea
        bool entradaValida = true;
        int c = std::cin.get();
        while (c != '\n' && c != EOF) {
            if (c != ' ' && c != '\t' && c != '\r') {
                entradaValida = false;
            }
            c = std::cin.get();
        }
        if (!entradaValida) {
            std::cout << "Entrada invalida. Debe escribir unicamente un numero entero.\n";
            return false;
        }
        return true;
    }
    if (std::cin.eof()) {
        return false;
    }
    std::cout << "Entrada invalida. Debe escribir un numero entero.\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return false;
}

// Propósito: ejecutar el ciclo de interacción por menú, procesando las selecciones del usuario y delegando al ABB.
// Parámetros: arbol (referencia al árbol binario de búsqueda a gestionar).
// Retorno: ninguno.
// Complejidad: O(m * c), donde m es el número de operaciones y c la complejidad de cada opción seleccionada.
void Menu::ejecutar(ArbolBST& arbol) const {
    bool continuar = true;
    while (continuar) {
        int opcion = 0;
        mostrarOpciones();
        if (!leerEntero("Seleccione una opcion: ", opcion)) {
            if (std::cin.eof()) {
                break;
            }
            continue;
        }
        switch (opcion) {
        case 1:
            arbol.mostrarArbol();
            break;
        case 2:
            std::cout << "Cantidad de nodos: " << arbol.cantidadNodos() << "\n";
            break;
        case 3: {
            int valor = 0;
            if (leerEntero("Digite el elemento a buscar: ", valor)) {
                arbol.buscar(valor);
            }
            break;
        }
        case 4:
            std::cout << "Recorrido preOrden: ";
            arbol.preOrden();
            break;
        case 5:
            std::cout << "Recorrido InOrden: ";
            arbol.inOrden();
            break;
        case 6:
            std::cout << "Recorrido postOrden: ";
            arbol.postOrden();
            break;
        case 7: {
            int valor = 0;
            if (leerEntero("Digite el elemento a eliminar: ", valor)) {
                arbol.eliminar(valor);
            }
            break;
        }
        case 8:
            continuar = false;
            std::cout << "Programa finalizado.\n";
            break;
        default:
            std::cout << "Opcion fuera de rango. Seleccione de 1 a 8.\n";
            break;
        }
    }
}
