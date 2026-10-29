#ifndef RED_H
#define RED_H

#include "Enrutador.h"
#include <vector>
#include <string>
#include <map>

class Red {
private:
    // Contenedor principal: Key = Nombre del enrutador, Valor = Objeto Enrutador
    std::map<std::string, Enrutador> enrutadores;

public:
    // Constructor
    Red() = default;

    // Gestión de topologia
    void agregarEnrutador(const std::string &nombre);
    void eliminarEnrutador(const std::string &nombre);
    void agregarEnlace(const std::string &origen, const std::string &destino, int costo);
    void eliminarEnlace(const std::string &origen, const std::string &destino);

    // Algoritmo central y actualizacion
    void recalcularTopologia();

    // Encuentra el camino optimo y devuelve el vector con la ruta y el costo por referencia
    int obtenerCamino(const std::string &origen, const std::string &destino, std::vector<std::string> &caminoMit);

    // Cargar desde archivo
    bool cargarDesdeArchivo(const std::string &nombreArchivo);
    // Guardar en archivo
    bool guardarEnArchivo(const std::string &nombreArchivo) const;

    // Mostrar el estado de toda la red
    void mostrarRed() const;
};

#endif // RED_H