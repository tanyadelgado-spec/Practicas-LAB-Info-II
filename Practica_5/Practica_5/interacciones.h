#ifndef INTERACCIONES_H
#define INTERACCIONES_H

#include <vector>
#include <fstream>
#include <string>

class Interacciones{
public:
    Interacciones();
};

// Clase Vector2D. Representa vectores bidimensionales y realiza operaciones
class Vector2D {
public:
    //Coordenada horizontal 'x', coordenada vertical 'y'
    double x, y;
    //Constructor
    Vector2D(double x = 0, double y = 0);

    //Deinicion de operadores, operaciones componente a componente entre coordenadas
    Vector2D operator+(const Vector2D& v) const;
    Vector2D operator-(const Vector2D& v) const;
    Vector2D operator*(double k) const;
    Vector2D operator/(double k) const;

    //Metodo para producto punto entre vectores
    double pPunto(const Vector2D& v) const;
    //Metodo para calcular magnitud del vector (Pitagoras)
    double longitud() const;
};

// Clase Particula. Representa las partículas, sus propiedades físicas y movimientos
class Particula {
public:
    int id;//Identificador de cada particula

    //position, velocity
    Vector2D posicion;
    Vector2D velocidad;
    //mass, radius
    double masa;
    double radio;

    //Constructor
    Particula(int id, Vector2D posicion, Vector2D velocidad, double masa, double radio);

    //Actualiza la posición de la partícula con su velocidad e intervalo de tiempo (dt)
    void movimiento(double dt);
};

// Clase Obstaculo. Representa los obstáculos rectangulares
class Obstaculo {
public:
    int id;

    double x;//coordenada horizontal de la esquina superior izquierda.
    double y;//coordenada vertical de la esquina superior izquierda
    double ancho;
    double alto;

    //Constructor
    Obstaculo(int id, double x, double y, double ancho, double alto);
};

/*Clase Simulation. Administra el escenario, actualiza el movimiento, detecta colisiones, fusiona partículas
                   y registra los resultados.
*/
class Simulacion {
private:

    //Vectores con particulas y obstaculos existentes; las particulas varian en tiempo de ejecucuion
    std::vector<Particula> particulas;
    std::vector<Obstaculo> obstaculos;

    //dimensiones del escenario
    const double ancho = 800.0;
    const double alto = 500.0;

    const double dt = 0.01;//Intervalo de tiempo entre actualizaciones
    const double restitucion = 0.65;//Coeficiente de restitución 'e'

    double tiempoSimulacion = 0.0;//Tiempo transcurrido desde el inicio, incrementa en las actualizaciones

    //Archivos de salida
    std::ofstream archivoPosicion;//Almacena posiciones y propiedades de las particulas
    std::ofstream archivoColision;//Almacena los eventos de colision

public:

    Simulacion();
    ~Simulacion();

    //Archivos
    bool openFiles();
    void closeFiles();

    void registrarColision(const std::string& tipo, int id1, int id2, const std::string& detalle);

    //Guardar el estado de todas las partículas en archivo
    void guardarPosiciones();

    //Colisiones con paredes
    void detectarColisionPared(Particula& p);

    //Colisiones con obstaculos
    void detectarColisionObstaculo(Particula& p, const Obstaculo& o);

    //Fusion de particulas por colision
    void fusionParticulas(int i, int j);
    void detectarColisionParticula();

    //Actualizacion de la simulacion
    void actualizacion();

    //Ejecutar la simulación durante cantidad determinada de pasos(actulizaciones)
    void ejecucion(int pasos);
};

#endif // INTERACCIONES_H
