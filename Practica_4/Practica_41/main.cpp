#include "Red.h"
#include <iostream>
#include <vector>
#include <string>

void mostrarMenu() {
    std::cout << "\n==========================================\n";
    std::cout << "     SIMULADOR DE RED DE ENRUTADORES      \n";
    std::cout << "==========================================\n";
    std::cout << "1. Cargar topologia desde archivo (.txt)\n";
    std::cout << "2. Mostrar estado de la red (Tablas de costos)\n";
    std::cout << "3. Agregar un Enrutador\n";
    std::cout << "4. Eliminar un Enrutador\n";
    std::cout << "5. Agregar/Modificar un Enlace (Costo)\n";
    std::cout << "6. Eliminar un Enlace\n";
    std::cout << "7. Calcular camino mas corto entre dos nodos\n";
    std::cout << "8. Salir\n";
    std::cout << "Seleccione una opcion: ";
}

int main() {
    Red miRed;
    int opcion = 0;

    while (opcion != 8) {
        mostrarMenu();
        if (!(std::cin >> opcion)) {
            std::cout << "Entrada invalida. Intente de nuevo.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        std::string u, v, archivo;
        int costo;
        std::vector<std::string> camino;

        switch (opcion) {
        case 1:
            std::cout << "Ingrese el nombre del archivo (ej. topologia.txt): ";
            std::cin >> archivo;
            if (miRed.cargarDesdeArchivo(archivo)) {
                std::cout << "¡Topologia cargada exitosamente!\n";
            } else {
                std::cout << "Error: No se pudo abrir o leer el archivo.\n";
            }
            break;

        case 2:
            std::cout << "\n=== ESTADO ACTUAL DE LOS ENRUTADORES ===\n";
            miRed.mostrarRed();
            break;

        case 3:
            std::cout << "Nombre del nuevo enrutador: ";
            std::cin >> u;
            miRed.agregarEnrutador(u);
            std::cout << "Enrutador '" << u << "' agregado. Red actualizada.\n";
            break;

        case 4:
            std::cout << "Nombre del enrutador a eliminar: ";
            std::cin >> u;
            miRed.eliminarEnrutador(u);
            std::cout << "Enrutador '" << u << "' eliminado. Red actualizada.\n";
            break;

        case 5:
            std::cout << "Enrutador de origen: ";
            std::cin >> u;
            std::cout << "Enrutador de destino: ";
            std::cin >> v;
            std::cout << "Costo del enlace (entero positivo): ";
            std::cin >> costo;
            if (costo <= 0) {
                std::cout << "Error: El costo debe ser mayor a 0.\n";
            } else {
                miRed.agregarEnlace(u, v, costo);
                std::cout << "Enlace [" << u << " <-> " << v << "] configurado con costo " << costo << ".\n";
            }
            break;

        case 6:
            std::cout << "Enrutador de origen: ";
            std::cin >> u;
            std::cout << "Enrutador de destino: ";
            std::cin >> v;
            miRed.eliminarEnlace(u, v);
            std::cout << "Enlace [" << u << " <-> " << v << "] eliminado si existia.\n";
            break;

        case 7:
            std::cout << "Ingrese nodo de ORIGEN: ";
            std::cin >> u;
            std::cout << "Ingrese nodo de DESTINO: ";
            std::cin >> v;

            costo = miRed.obtenerCamino(u, v, camino);

            if (costo == -1) {
                std::cout << "\nError: No existe un camino entre '" << u << "' y '" << v << "', o alguno de los nodos no existe.\n";
            } else {
                std::cout << "\n=== RESULTADO DEL CAMINO OPTIMO ===\n";
                std::cout << "Ruta: ";
                for (size_t i = 0; i < camino.size(); ++i) {
                    std::cout << camino[i];
                    if (i < camino.size() - 1) std::cout << " -> ";
                }
                std::cout << "\nCosto Total: " << costo << "\n";
            }
            break;

        case 8:
            std::cout << "Saliendo del simulador...\n";
            break;

        default:
            std::cout << "Opcion no valida. Intente de nuevo.\n";
            break;
        }
    }

    return 0;
}