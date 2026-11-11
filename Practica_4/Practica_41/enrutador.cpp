#include "Enrutador.h"
#include <iostream>

Enrutador::Enrutador(const std::string &nombre) {
    this->nombre = nombre;
    // Un enrutador siempre tiene costo 0 para llegar a sí mismo
    this->tablaCostos[nombre] = 0;
}

std::string Enrutador::getNombre() const {
    return nombre;
}

void Enrutador::setNombre(const std::string &nuevoNombre) {
    nombre = nuevoNombre;
}

void Enrutador::agregarVecino(const std::string &nombreVecino, int costo) {
    vecinosDirectos[nombreVecino] = costo;
}

void Enrutador::eliminarVecino(const std::string &nombreVecino) {
    vecinosDirectos.erase(nombreVecino);
}

std::map<std::string, int> Enrutador::getVecinosDirectos() const {
    return vecinosDirectos;
}

void Enrutador::actualizarTablaCostos(const std::map<std::string, int> &nuevaTabla) {
    this->tablaCostos = nuevaTabla;
    // Asegurar que el costo a sí mismo siga siendo 0
    this->tablaCostos[this->nombre] = 0;
}

void Enrutador::limpiarTablaCostos() {
    tablaCostos.clear();
    tablaCostos[nombre] = 0;
}

std::map<std::string, int> Enrutador::getTablaCostos() const {
    return tablaCostos;
}

void Enrutador::mostrarEstado() const {
    std::cout << "------------------------------------------\n";
    std::cout << "Enrutador: " << nombre << "\n";

    // Mostrar vecinos directos
    std::cout << "Vecinos directos -> ";
    for (const auto &par : vecinosDirectos) {
        std::cout << "[" << par.first << ": " << par.second << "] ";
    }
    std::cout << "\n";

    // Mostrar tabla de costos optimos
    std::cout << "Tabla de costos  -> ";
    for (const auto &par : tablaCostos) {
        std::cout << "(" << par.first << ": " << par.second << ") ";
    }
    std::cout << "\n";
}