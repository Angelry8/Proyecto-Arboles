#include "Menu.h"
#include <iostream>
#include <limits>

void Menu::mostrarOpciones() const {
    std::cout << "\nMenú principal\n"
              << "1. Mostrar árbol\n"
              << "2. Cantidad de nodos\n"
              << "3. Buscar un elemento\n"
              << "4. Mostrar recorrido preOrden\n"
              << "5. Mostrar recorrido InOrden\n"
              << "6. Mostrar recorrido postOrden\n"
              << "7. Eliminar un elemento\n"
              << "8. Salir\n";
}

bool Menu::leerEntero(const char* indicacion, int& valor) const {
    std::cout << indicacion;
    if (std::cin >> valor) {
        // TODO (Parte 1, Angel): validar que tras el entero solo haya espacios hasta '\n';
        // descartar el resto de la línea y rechazar basura como "5abc" o "3 4".
        return true;
    }
    if (std::cin.eof()) {
        return false;
    }
    std::cout << "Entrada inválida. Debe escribir un número entero.\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return false;
}

void Menu::ejecutar(ArbolBST& arbol) const {
    bool continuar = true;
    while (continuar) {
        int opcion = 0;
        mostrarOpciones();
        if (!leerEntero("Seleccione una opción: ", opcion)) {
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
            std::cout << "Opción fuera de rango. Seleccione de 1 a 8.\n";
            break;
        }
    }
}
