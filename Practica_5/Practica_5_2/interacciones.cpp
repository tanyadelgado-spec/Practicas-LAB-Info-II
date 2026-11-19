#include "interacciones.h"
#include <iostream>
#include <cmath>
#include <iomanip>//permite controlar la presentacion de numeros decimales mediante std::fixed y std::setprecision
#include <algorithm>

Interacciones::Interacciones() {}

//Clase Vector2D
Vector2D::Vector2D(double x, double y) : x(x), y(y) {}

//Sobrecarga del operador '+'
Vector2D Vector2D::operator+(const Vector2D& v) const {
    return Vector2D(x + v.x, y + v.y);
}

//Sobrecarga del operador '-'
Vector2D Vector2D::operator-(const Vector2D& v) const {
    return Vector2D(x - v.x, y - v.y);
}

//Sobrecarga del operador '*'. Multiplicar la velocidad por el intervalo de tiempo y calcular el desplazamiento
Vector2D Vector2D::operator*(double k) const {
    return Vector2D(x * k, y * k);
}

//Sobrecarga del operador '/'. Calcular velocidades promedio por la masa durante la fusion de particulas
Vector2D Vector2D::operator/(double k) const {
    return Vector2D(x / k, y / k);
}

//Producto punto. Determinar si una particula se esta acercando o alejando de una superficie
double Vector2D::pPunto(const Vector2D& v) const {
    return x * v.x + y * v.y;
}

//Magnitud del vector
double Vector2D::longitud() const {
    return std::sqrt(x * x + y * y);
}

// Constructor
Particula::Particula(int id, Vector2D posicion, Vector2D velocidad, double masa, double radio)
    : id(id), posicion(posicion), velocidad(velocidad), masa(masa), radio(radio), activo(false) {}

// Configura el disparo con angulo (en grados) y velocidad inicial
void Particula::lanzar(Vector2D posInicial, double anguloGrados, double rapidezInicial) {
    posicion = posInicial;

    const double PI = 3.14159265;
    double rad = anguloGrados * PI / 180.0;

    velocidad.x = rapidezInicial * std::cos(rad);
    velocidad.y = -rapidezInicial * std::sin(rad);

    activo = true;
}

// Actualiza posicion y velocidad usando la constante gravedad
void Particula::movimiento(double dt) {
    if (!activo)
        return;

    // Aceleracion gravitacional hacia abajo (+Y en coordenadas de Qt)
    velocidad.y += gravedad * dt;

    // Actualizar posicion: r = r0 + v * dt
    posicion = posicion + velocidad * dt;
}

// Detiene el proyectil
void Particula::detener() {
    velocidad = Vector2D(0, 0);
    activo = false;
}


//Clase Obstaculo
Obstaculo::Obstaculo(int id, int jugadorId, double x, double y, double ancho, double alto, double resistencia) :
    id(id),
    x(x),
    y(y),
    ancho(ancho),
    alto(alto),
    resistencia(resistencia),
    jugadorId(jugadorId) {}

bool Obstaculo::danio(double danio) {
    resistencia -= danio;

    if (resistencia <= 0.0) {
        resistencia = 0.0; // Evita mostrar numeros negativos en la interfaz
        return true;       // Indica que el obstáculo ha sido destruido
    }
    return false;          // El obstáculo sigue en pie
}
// --- Implementacion de Rival ---
Rival::Rival(int jugadorId, double x, double y, double ancho, double alto)
    : jugadorId(jugadorId), x(x), y(y), ancho(ancho), alto(alto), derrotado(false) {}

// --- Implementacion de Simulacion ---
Simulacion::Simulacion() {
    reiniciarJuego();
}

void Simulacion::reiniciarJuego() {
    obstaculos.clear();

    // --- JUGADOR 1 (Izquierda, parte inferior) ---
    // Personaje protegido en la esquina inferior izquierda
    rival1 = Rival(1, 50, 440, 40, 60);
    // Obstaculos abajo protegiendo al personaje (200, 200, 100)
    obstaculos.emplace_back(1, 1, 0,  350, 151, 31, 200.0); // Techo sobre el personaje
    obstaculos.emplace_back(2, 1, 110, 380, 41, 61, 200.0); // Muro frontal
    obstaculos.emplace_back(3, 1, 110, 440, 41, 61, 300.0); // Muro frontal

    // --- JUGADOR 2 (Derecha, parte inferior) ---
    // Personaje protegido en la esquina inferior derecha
    rival2 = Rival(2, 710, 440, 40, 60);
    // Obstaculos abajo protegiendo al personaje (200, 200, 100)
    obstaculos.emplace_back(4, 2, 650, 350, 151, 31, 200.0); // Techo sobre el personaje
    obstaculos.emplace_back(5, 2, 650, 380, 41, 61, 200.0); // Muro frontal
    obstaculos.emplace_back(6, 2, 650, 440, 41, 61, 300.0); // Muro frontal

    // Ubicar el proyectil listo en el canon del Jugador 1 (mitad de altura)
    turnoActual = 1;
    proyectil = Particula(1, posCanon1, Vector2D(0, 0), 2.0, 10.0);

    juegoTerminado = false;
    ganador = 0;
    tiempoTurno = 0.0;
}


void Simulacion::dispararProyectil(double anguloGrados, double rapidezInicial) {
    if (proyectil.activo || juegoTerminado)
        return;

    tiempoTurno = 0.0;

    if (turnoActual == 1) {
        // Dispara desde el canon 1 hacia la derecha
        proyectil.lanzar(posCanon1, anguloGrados, rapidezInicial);
    } else {
        // Dispara desde el canon 2 hacia la izquierda
        proyectil.lanzar(posCanon2, 180.0 - anguloGrados, rapidezInicial);
    }
}

void Simulacion::detectarColisionPared() {
    // Pared izquierda
    if (proyectil.posicion.x - proyectil.radio < 0) {
        proyectil.posicion.x = proyectil.radio;
        if (proyectil.velocidad.x < 0)
            proyectil.velocidad.x *= -1;
    }
    // Pared derecha
    if (proyectil.posicion.x + proyectil.radio > ancho) {
        proyectil.posicion.x = ancho - proyectil.radio;
        if (proyectil.velocidad.x > 0)
            proyectil.velocidad.x *= -1;
    }
    // Pared superior (techo)
    if (proyectil.posicion.y - proyectil.radio < 0) {
        proyectil.posicion.y = proyectil.radio;
        if (proyectil.velocidad.y < 0)
            proyectil.velocidad.y *= -1;
    }
    // Pared inferior (suelo) - Rebote elastico
    if (proyectil.posicion.y + proyectil.radio > alto) {
        proyectil.posicion.y = alto - proyectil.radio;
        if (proyectil.velocidad.y > 0) {
            proyectil.velocidad.y *= -1;
        }
    }
}

bool Simulacion::detectarColisionObstaculo(Obstaculo& o) {
    double cercanoX = std::clamp(proyectil.posicion.x, o.x, o.x + o.ancho);
    double cercanoY = std::clamp(proyectil.posicion.y, o.y, o.y + o.alto);

    Vector2D cercano(cercanoX, cercanoY);
    Vector2D diferencia = proyectil.posicion - cercano;
    double distancia = diferencia.longitud();

    Vector2D normal;
    double atraviesa;

    if (distancia > 1e-10) {
        if (distancia >= proyectil.radio)
            return false;

        normal = diferencia / distancia;
        atraviesa = proyectil.radio - distancia;
    } else {
        double izquierda = proyectil.posicion.x - o.x;
        double derecha = o.x + o.ancho - proyectil.posicion.x;
        double superior = proyectil.posicion.y - o.y;
        double inferior = o.y + o.alto - proyectil.posicion.y;

        double minima = std::min({izquierda, derecha, superior, inferior});

        if (minima == izquierda) normal = Vector2D(-1, 0);
        else if (minima == derecha) normal = Vector2D(1, 0);
        else if (minima == superior) normal = Vector2D(0, -1);
        else normal = Vector2D(0, 1);

        atraviesa = proyectil.radio + minima;
    }

    proyectil.posicion = proyectil.posicion + normal * atraviesa;
    double normalVelocidad = proyectil.velocidad.pPunto(normal);

    if (normalVelocidad < 0) {
        bool destruido = false;

        // solo hace daño a los obstaculos del rival
        if (o.jugadorId != turnoActual) {
            double rapidezImpacto = proyectil.velocidad.longitud();
            double momentoLineal = proyectil.masa * rapidezImpacto;
            double danio = factorDanio * momentoLineal;

            destruido = o.danio(danio);
        }

        // El rebote inelastico SIEMPRE
        proyectil.velocidad = proyectil.velocidad - normal * ((1 + restitucion) * normalVelocidad);

        return destruido;
    }

    return false;
}

bool Simulacion::detectarColisionRival(Rival& r) {
    // Evitar que un jugador se derrote a si mismo al disparar
    if (r.jugadorId == turnoActual)
        return false;

    double cercanoX = std::clamp(proyectil.posicion.x, r.x, r.x + r.ancho);
    double cercanoY = std::clamp(proyectil.posicion.y, r.y, r.y + r.alto);

    Vector2D cercano(cercanoX, cercanoY);
    Vector2D diferencia = proyectil.posicion - cercano;

    if (diferencia.longitud() < proyectil.radio) {
        r.derrotado = true;
        return true;
    }
    return false;
}

void Simulacion::actualizacion() {
    // Solo actualizar fisica si el proyectil esta en vuelo y el juego sigue activo
    if (!proyectil.activo || juegoTerminado)
        return;

    tiempoTurno += dt;

    // Mover proyectil (con gravedad)
    proyectil.movimiento(dt);

    //  Colision con bordes del escenario
    detectarColisionPared();

    // Colision con obstaculos y eliminacion si resistencia <= 0
    for (size_t i = 0; i < obstaculos.size(); ) {
        if (detectarColisionObstaculo(obstaculos[i])) {
            obstaculos.erase(obstaculos.begin() + i);
        } else {
            i++;
        }
    }

    // Verificar si impacto al representante enemigo
    Rival& objetivo = (turnoActual == 1) ? rival2 : rival1;
    if (detectarColisionRival(objetivo)) {
        proyectil.detener();
        juegoTerminado = true;
        ganador = turnoActual;
        return;
    }

    // Condicion de fin de turno: si pierde casi toda su energia o pasan 6 segundos
    if (proyectil.velocidad.longitud() < 15.0 || tiempoTurno >= 6.0) {
        proyectil.detener();
        cambiarTurno();
    }
}

void Simulacion::cambiarTurno() {
    turnoActual = (turnoActual == 1) ? 2 : 1;

    // Mover el proyectil en espera al canon del jugador en turno
    proyectil.posicion = getPosicionCanonActual();
}