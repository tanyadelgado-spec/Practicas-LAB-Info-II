#include "Red.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <vector>
#include <climits>
#include <algorithm>

void Red::agregarEnrutador(const std::string &nombre) {
    if (enrutadores.find(nombre) == enrutadores.end()) {
        enrutadores[nombre] = Enrutador(nombre);
        recalcularTopologia();
    }
}

void Red::eliminarEnrutador(const std::string &nombre) {
    if (enrutadores.find(nombre) != enrutadores.end()) {
        enrutadores.erase(nombre);
        // Eliminar este enrutador de las listas de vecinos de los demás
        for (auto &par : enrutadores) {
            par.second.eliminarVecino(nombre);
        }
        recalcularTopologia();
    }
}

void Red::agregarEnlace(const std::string &origen, const std::string &destino, int costo) {
    if (enrutadores.find(origen) != enrutadores.end() && enrutadores.find(destino) != enrutadores.end()) {
        enrutadores[origen].agregarVecino(destino, costo);
        enrutadores[destino].agregarVecino(origen, costo); // Enlaces bidireccionales
        recalcularTopologia();
    }
}

void Red::eliminarEnlace(const std::string &origen, const std::string &destino) {
    if (enrutadores.find(origen) != enrutadores.end() && enrutadores.find(destino) != enrutadores.end()) {
        enrutadores[origen].eliminarVecino(destino);
        enrutadores[destino].eliminarVecino(origen);
        recalcularTopologia();
    }
}

// Algoritmo de Dijkstra para calcular distancias minimas y actualizar tablas de costos
void Red::recalcularTopologia() {
    // Limpiar las tablas de costos de todos antes de iniciar
    for (auto &par : enrutadores) {
        par.second.limpiarTablaCostos();
    }

    // Ejecutar Dijkstra tomando cada enrutador como origen secuencialmente
    for (auto &parOrigen : enrutadores) {
        std::string nodoInicio = parOrigen.first;

        std::map<std::string, int> distancias;
        // Inicializar todas las distancias en "infinito"
        for (const auto &p : enrutadores) {
            distancias[p.first] = INT_MAX;
        }
        distancias[nodoInicio] = 0;

        // Queue de prioridad: almacena pares <distancia, nombre_nodo>
        std::priority_queue<std::pair<int, std::string>,
                            std::vector<std::pair<int, std::string>>,
                            std::greater<std::pair<int, std::string>>> pq;

        pq.push({0, nodoInicio});

        while (!pq.empty()) {
            int distActual = pq.top().first;
            std::string u = pq.top().second;
            pq.pop();

            if (distActual > distancias[u]) continue;

            // Revisar los vecinos del enrutador actual
            std::map<std::string, int> vecinos = enrutadores[u].getVecinosDirectos();
            for (const auto &vecino : vecinos) {
                std::string v = vecino.first;
                int pesoEnlace = vecino.second;

                if (distancias[u] != INT_MAX && distancias[u] + pesoEnlace < distancias[v]) {
                    distancias[v] = distancias[u] + pesoEnlace;
                    pq.push({distancias[v], v});
                }
            }
        }

        // Guardar la tabla calculada en el enrutador correspondiente
        std::map<std::string, int> tablaFinal;
        for (const auto &d : distancias) {
            if (d.second != INT_MAX) {
                tablaFinal[d.first] = d.second;
            }
        }
        enrutadores[nodoInicio].actualizarTablaCostos(tablaFinal);
    }
}

int Red::obtenerCamino(const std::string &origen, const std::string &destino, std::vector<std::string> &camino) {
    camino.clear();
    if (enrutadores.find(origen) == enrutadores.end() || enrutadores.find(destino) == enrutadores.end()) {
        return -1; // Retorna -1 si alguno de los nodos no existe
    }

    // Re-ejecución de Dijkstra para reconstruir el camino
    std::map<std::string, int> distancias;
    std::map<std::string, std::string> padre;

    for (const auto &p : enrutadores) distancias[p.first] = INT_MAX;
    distancias[origen] = 0;

    std::priority_queue<std::pair<int, std::string>,
                        std::vector<std::pair<int, std::string>>,
                        std::greater<std::pair<int, std::string>>> pq;
    pq.push({0, origen});

    while (!pq.empty()) {
        std::string u = pq.top().second;
        pq.pop();

        if (u == destino) break; // Ya llegamos al objetivo

        for (const auto &vecino : enrutadores[u].getVecinosDirectos()) {
            std::string v = vecino.first;
            int peso = vecino.second;

            if (distancias[u] + peso < distancias[v]) {
                distancias[v] = distancias[u] + peso;
                padre[v] = u;
                pq.push({distancias[v], v});
            }
        }
    }

    if (distancias[destino] == INT_MAX) return -1; // Inalcanzable

    // Reconstruir el camino desde el destino hacia atras
    std::string actual = destino;
    while (actual != origen) {
        camino.push_back(actual);
        actual = padre[actual];
    }
    camino.push_back(origen);
    std::reverse(camino.begin(), camino.end()); // Voltear para que quede de Origen -> Destino

    return distancias[destino];
}

bool Red::cargarDesdeArchivo(const std::string &nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) return false;

    std::string linea;

    while (std::getline(archivo, linea)) {
        if (linea.empty()) continue;
        std::stringstream ss(linea);
        std::string u, v;
        int costo;
        if (ss >> u >> v >> costo) {
            agregarEnrutador(u);
            agregarEnrutador(v);
            agregarEnlace(u, v, costo);
        }
    }
    archivo.close();
    recalcularTopologia();
    return true;
}

void Red::mostrarRed() const {
    for (const auto &par : enrutadores) {
        par.second.mostrarEstado();
    }
}