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
    double x, y;
    Vector2D(double x = 0, double y = 0);

    //Deinicion de operadores
    Vector2D operator+(const Vector2D& v) const;
    Vector2D operator-(const Vector2D& v) const;
    Vector2D operator*(double k) const;
    Vector2D operator/(double k) const;

    //producto punto entre vectores
    double pPunto(const Vector2D& v) const;
    // magnitud del vector
    double longitud() const;
};

// Clase Particula.
class Particula {
public:
    int id;             // Identificador (ej. 1 para Jugador 1, 2 para Jugador 2)
    Vector2D posicion;
    Vector2D velocidad;
    double masa;
    double radio;
    bool activo;        // Indica si el proyectil esta en movimiento durante el turno

    // Constante de gravedad
    static constexpr double gravedad = 150.0;

    // Constructor
    Particula(int id = 1, Vector2D posicion = Vector2D(0, 0), Vector2D velocidad = Vector2D(0, 0), double masa = 2.0, double radio = 10.0);
    void lanzar(Vector2D posInicial, double anguloGrados, double rapidezInicial);
    void movimiento(double dt);
    void detener();
};


// Clase Obstaculo. Representa los obstáculos rectangulares
class Obstaculo {
public:
    int id;

    double x;//coordenada horizontal de la esquina superior izquierda.
    double y;//coordenada vertical de la esquina superior izquierda
    double ancho;
    double alto;
    double resistencia;
    int jugadorId;

    //Constructor
    Obstaculo(int id, int jugadorId, double x, double y, double ancho, double alto, double resistencia);

    bool danio(double danio);
};


// Clase Rival. Representa el objetivo principal de cada jugador
class Rival {
public:
    int jugadorId;      // 1 para el representante del Jugador 1, 2 para el del Jugador 2
    double x;
    double y;
    double ancho;
    double alto;
    bool derrotado;

    Rival(int jugadorId = 1, double x = 0, double y = 0, double ancho = 40, double alto = 40);
};

// Clase Simulacion. Administra la fisica del juego, turnos, danos y victoria
class Simulacion {
private:
    Particula proyectil;
    std::vector<Obstaculo> obstaculos;
    Rival rival1;
    Rival rival2;

    // Dimensiones del escenario
    const double ancho = 800.0;
    const double alto = 500.0;
    //Posicion cañones
    const Vector2D posCanon1 = Vector2D(70.0, 250.0);   // Canon Jugador 1 (izquierda, mitad de altura)
    const Vector2D posCanon2 = Vector2D(730.0, 250.0);  // Canon Jugador 2 (derecha, mitad de altura)

    // Constantes fisicas
    const double dt = 0.016;           // ~60 FPS
    const double restitucion = 0.65;   // Coeficiente de restitucion con obstaculos
    const double factorDanio = 0.25;   // Constante para calcular dano por momento lineal

    // Estado del juego
    int turnoActual;                   // 1 = Jugador 1 (izquierda), 2 = Jugador 2 (derecha)
    bool juegoTerminado;
    int ganador;                       // 0 = nadie aun, 1 = Jugador 1, 2 = Jugador 2
    double tiempoTurno;                // Evita turnos infinitos si el proyectil queda rebotando

public:
    Simulacion();

    // Inicializa o reinicia la partida con las fortalezas de la Figura 2
    void reiniciarJuego();

    // Dispara el proyectil del jugador en turno
    void dispararProyectil(double anguloGrados, double rapidezInicial);

    // Colisiones
    void detectarColisionPared();
    bool detectarColisionObstaculo(Obstaculo& o);
    bool detectarColisionRival(Rival& r);

    // Un paso de simulacion (sera llamado por un QTimer en la interfaz)
    void actualizacion();

    // Cambia al siguiente jugador cuando el proyectil se detiene
    void cambiarTurno();

    // Getters
    const Particula& getProyectil() const { return proyectil; }
    const std::vector<Obstaculo>& getObstaculos() const { return obstaculos; }
    const Rival& getRival1() const { return rival1; }
    const Rival& getRival2() const { return rival2; }
    int getTurnoActual() const { return turnoActual; }
    bool isJuegoTerminado() const { return juegoTerminado; }
    int getGanador() const { return ganador; }
    double getAncho() const { return ancho; }
    double getAlto() const { return alto; }
    Vector2D getPosicionCanonActual() const {
        return (turnoActual == 1) ? posCanon1 : posCanon2;
    }
};

#endif // INTERACCIONES_H
