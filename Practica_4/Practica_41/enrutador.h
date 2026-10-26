#ifndef ENRUTADOR_H
#define ENRUTADOR_H


#include <string>
#include <map>

class Enrutador {
private:
    std::string nombre;

    // Almacena los vecinos directos: Key = Nombre del vecino, Value = Costo del enlace
    std::map<std::string, int> vecinosDirectos;

    // Tabla de enrutamiento optimizada: Key = Destino, Value = Costo minimo total
    std::map<std::string, int> tablaCostos;

public:
    // Constructor
    Enrutador(const std::string &nombre = "");

    // Getters y Setters basicos
    std::string getNombre() const;
    void setNombre(const std::string &nuevoNombre);

    // Gestion de vecinos directos
    void agregarVecino(const std::string &nombreVecino, int costo);
    void eliminarVecino(const std::string &nombreVecino);
    std::map<std::string, int> getVecinosDirectos() const;

    // Gestion de la tabla de enrutamiento (actualizada por la clase Red)
    void actualizarTablaCostos(const std::map<std::string, int> &nuevaTabla);
    void limpiarTablaCostos();
    std::map<std::string, int> getTablaCostos() const;

    // Funcion auxiliar para imprimir el estado del enrutador en consola
    void mostrarEstado() const;
};

#endif // ENRUTADOR_H
