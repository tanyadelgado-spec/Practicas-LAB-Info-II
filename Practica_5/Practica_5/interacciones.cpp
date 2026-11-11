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

//Clase Particula
Particula::Particula(int id, Vector2D posicion, Vector2D velocidad, double masa, double radio) :
                    id(id),
                    posicion(posicion),
                    velocidad(velocidad),
                    masa(masa),
                    radio(radio) {}

void Particula::movimiento(double dt) {
    posicion = posicion + velocidad * dt;
}

//Clase Obstaculo
Obstaculo::Obstaculo(int id, double x, double y, double ancho, double alto) :
            id(id),
            x(x),
            y(y),
            ancho(ancho),
            alto(alto) {}

//Clase Simulacion
Simulacion::Simulacion() {//Constructor

    // Cuatro particulas iniciales. 'emplace_back' agrega un nuevo objeto al final del vector 'particulas'
    particulas.emplace_back(1, Vector2D(100, 100),
                            Vector2D(100, 65), 2.0, 15);

    particulas.emplace_back(2, Vector2D(700, 100),
                            Vector2D(-85, 90), 3.0, 18);

    particulas.emplace_back(3, Vector2D(100, 400),
                            Vector2D(110, -75), 2.5, 16);

    particulas.emplace_back(4, Vector2D(700, 400),
                            Vector2D(-100, -85), 3.5, 20);
    // Cuatro obstaculos cuadrados
    obstaculos.emplace_back(1, 270, 100, 60, 60);
    obstaculos.emplace_back(2, 470, 100, 60, 60);
    obstaculos.emplace_back(3, 270, 340, 60, 60);
    obstaculos.emplace_back(4, 470, 340, 60, 60);

    //Apertura de archivos
    openFiles();
    // Registrar estado inicial
    guardarPosiciones();
}

//Destructor
Simulacion::~Simulacion() {
    closeFiles();
}

//Gestion de archivos
bool Simulacion::openFiles() {

    archivoPosicion.open("posiciones.csv");
    archivoColision.open("colisiones.csv");

    if (!archivoPosicion.is_open() || !archivoColision.is_open()) {
        std::cerr
            << "Error al crear los archivos CSV.\n";
        return false;
    }

    //Encabezados de los archivos
    archivoPosicion << "tiempo,id,x,y,vx,vy,masa,radio\n";
    archivoColision << "tiempo,tipo,id1,id2,detalle\n";

    //Formato para numeros decimales, se escribirsn con 2 cifras después del punto decimal
    archivoPosicion << std::fixed << std::setprecision(2);
    archivoColision << std::fixed << std::setprecision(2);

    return true;
}

//Cerrar los archivos si fueron abiertos
void Simulacion::closeFiles() {

    if (archivoPosicion.is_open())
        archivoPosicion.close();

    if (archivoColision.is_open())
        archivoColision.close();
}

//Registrar colisiones segun su tipo, particula/obstaculo involucrado y especificacion adicional
void Simulacion::registrarColision(const std::string& tipo, int id1, int id2, const std::string& detalle) {

    //Verificacion de que el archivo este abierto
    if (!archivoColision.is_open())
        return;

    archivoColision << tiempoSimulacion << ","
                    << tipo << ","
                    << id1 << ","
                    << id2 << ","
                    << detalle << "\n";
}

//Registra el estado de todas las particulas en el archivo
void Simulacion::guardarPosiciones() {

    if (!archivoPosicion.is_open())
        return;

    //Se recorre vector 'particulas'
    for (const Particula& p : particulas) {

        archivoPosicion << tiempoSimulacion << ","
                        << p.id << ","
                        << p.posicion.x << ","
                        << p.posicion.y << ","
                        << p.velocidad.x << ","
                        << p.velocidad.y << ","
                        << p.masa << ","
                        << p.radio << "\n";
    }
}

//Colisiones con paredes (elasticas, e=1). Recibe por referencia una partícula y verifica si ha sobrepasado algun limite del escenario
void Simulacion::detectarColisionPared(Particula& p) {

    // Pared izquierda
    if (p.posicion.x - p.radio < 0) {//x-r<0

        //Como se ha sobrepasado el limite, se corrige la posicion
        p.posicion.x = p.radio;

        //Verificar la dirección de la velocidad para ponerla en sentido contrario dada la colision
        if (p.velocidad.x < 0) {

            p.velocidad.x *= -1;
            registrarColision("Pared", p.id, 0, "Izquierda");
        }
    }
    // Pared derecha
    if (p.posicion.x + p.radio > ancho) {//x+r>ancho (800)

        //Se corrige la posicion
        p.posicion.x = ancho - p.radio;

        //Se invierte direccion de la velocidad
        if (p.velocidad.x > 0) {

            p.velocidad.x *= -1;
            registrarColision("Pared", p.id, 0, "Derecha");
        }
    }
    // Pared superior
    if (p.posicion.y - p.radio < 0) {//y-r<0

        p.posicion.y = p.radio;

        if (p.velocidad.y < 0) {

            p.velocidad.y *= -1;
            registrarColision("Pared", p.id, 0, "Superior");
        }
    }
    // Pared inferior
    if (p.posicion.y + p.radio > alto) {//y+r>alto (500)

        p.posicion.y = alto - p.radio;

        if (p.velocidad.y > 0) {

            p.velocidad.y *= -1;
            registrarColision("Pared", p.id, 0, "Inferior");
        }
    }
}

//Colisiones con obstaculos (inelasticas, e=0.65).
void Simulacion::detectarColisionObstaculo(Particula& p, const Obstaculo& o) {

    // Punto mas cercano del obstaculo. 'clamp()' limitar valor a un intervalo, std::clamp(valor, minimo, maximo)
    double cercanoX = std::clamp(p.posicion.x, o.x, o.x + o.ancho);
    double cercanoY = std::clamp(p.posicion.y, o.y, o.y + o.alto);

    //Vector con el punto mas cercano al centro de la particula
    Vector2D cercano(cercanoX, cercanoY);
    //vector conel punto mas cercano del obstaculo
    Vector2D diferencia = p.posicion - cercano;

    //Magnitud del vector que representa la distancia para determinar si laparticula toca o atraviesa el obstaculo
    double distancia = diferencia.longitud();

    Vector2D normal;//Representa la direccion perpendicular a la superficie de contacto
    double atraviesa;//Representa cuanto se ha introducido la particula dentro del obstaculo

    //Verificar si lo atraviesa o no para hacer modificaciones de los vectores
    if (distancia > 1e-10) {

        if (distancia >= p.radio)//No existe colision si se cumple
            return;

        normal = diferencia / distancia;//Vector uniktario para determinar direccion de desplazamiento
        atraviesa = p.radio - distancia;//Unidades que atraviesa para saber el desplazamiento

    }else {//Centro de particula dentro del obstaculo

        //Distancias desde el centro de la partícula hasta los 4 lados
        double izquierda = p.posicion.x - o.x;//Distancia al lado izquierdo
        double derecha = o.x + o.ancho - p.posicion.x;//Distancia al lado derecho
        double superior = p.posicion.y - o.y;//Distancia al lado superior
        double inferior = o.y + o.alto - p.posicion.y;//Distancia al lado inferior

        //Distancia minima entre las 4, cual es el lado mas cercano del obstaculo
        double minima = std::min({izquierda, derecha, superior, inferior});

        //Acorde al lado mas cercano, se determina direccion perpendicular
        if (minima == izquierda)
            normal = Vector2D(-1, 0);

        else if (minima == derecha)
            normal = Vector2D(1, 0);

        else if (minima == superior)
            normal = Vector2D(0, -1);

        else
            normal = Vector2D(0, 1);

        //Con centro de la partícula dentro del obstaculo, calcular cuanto debe desplazarse para salir
        //completamente por el lado mas cercano
        atraviesa = p.radio + minima;
    }

    //Corregir posicion
    p.posicion = p.posicion + normal * atraviesa;

    //Componente de la velocidad en la dirección perpendicular a la superficie
    double normalVelocidad = p.velocidad.pPunto(normal);

    if (normalVelocidad < 0) {//la particula se mueve hacia el obstaculo

        //Calcular rebote con ecuacuion de reflexión de la velocidad
        p.velocidad = p.velocidad - normal * ((1 + restitucion) * normalVelocidad);

        //Identificar lado del obstaculo donde ocurrio la colision
        std::string ladoC;

        if (normal.x < -0.5)
            ladoC = "Izquierda";
        else if (normal.x > 0.5)
            ladoC = "Derecha";
        else if (normal.y < -0.5)
            ladoC = "Superior";
        else
            ladoC = "Inferior";

        registrarColision("Obstaculo", p.id, o.id, ladoC);
    }
}

//Colisiones entre particulas (completamente inelasticas). Combina dos partículas cuando chocan
void Simulacion::fusionParticulas(int i, int j) {

    //Los parametros son los ids de las particulas
    Particula& p1 = particulas[i];
    Particula& p2 = particulas[j];

    //Masa de la particula resultante
    double totalMass = p1.masa + p2.masa;

    //Su nueva posicion es el centro de masa del sistema
    Vector2D nuevaPosicion = (p1.posicion * p1.masa + p2.posicion * p2.masa) / totalMass;

    //Principio de conservacion del momento lineal para su nueva velocidad
    Vector2D nuevaVelocidad =(p1.velocidad * p1.masa + p2.velocidad * p2.masa) / totalMass;

    //Por conservacion del area, la nueva area es la raiz de la suma del cuadrado de sus radios
    double nuevoRadio = std::sqrt(p1.radio * p1.radio + p2.radio * p2.radio);

    //Guardar identificadores antes de eliminar la particula
    int id1 = p1.id;
    int id2 = p2.id;

    //Actualizar particula resultante, en la posisicon de la 1ra particula
    p1.posicion = nuevaPosicion;
    p1.velocidad = nuevaVelocidad;
    p1.masa = totalMass;
    p1.radio = nuevoRadio;

    registrarColision("Particula", id1, id2, "Fusion");

    //Eliminar 2da particula
    particulas.erase(particulas.begin() + j);
}

//Recorrer todas las parejas posibles de particulas y determinar si se encuentran en contacto
void Simulacion::detectarColisionParticula() {

    //Se toma de a una particula y se compara con las demás con el ciclo anidado
    for (int i = 0; i < (int)particulas.size(); i++) {

        for (int j = i + 1; j < (int)particulas.size();) {

            //Diferencia entre posiciones
            Vector2D diferencia = particulas[j].posicion - particulas[i].posicion;
            //Distancia entre los centros
            double distancia = diferencia.longitud();
            //Distancia minima de contacto
            double distanciaMinima = particulas[i].radio + particulas[j].radio;

            //Ambas particulas estan en contacto si la distancia entre sus centros es igual a la suma de sus radios
            if (distancia < distanciaMinima)
                fusionParticulas(i, j);
            else
                j++;
        }
    }
}

//Actualizacion (avanzando 0.01s)
void Simulacion::actualizacion() {

    //Recorrer el vector y actualizar la posición de cada particula utilizando su velocidad
    for (Particula& p : particulas)
        p.movimiento(dt);

    //Detectar colision con paredes
    for (Particula& p : particulas)
        detectarColisionPared(p);

    //Detectar colision con obstaculos. Por cada particula se verifican todos los obstaculos
    for (Particula& p : particulas) {

        for (const Obstaculo& o : obstaculos)
            detectarColisionObstaculo(p, o);
    }

    //Detectar colision entre particulas
    detectarColisionParticula();

    //Actualizacion del tiempo de simulacion
    tiempoSimulacion += dt;

    //Guardar posiciones con las modificaciones generadas anteriormente
    guardarPosiciones();
}

//Permite ejecutar la simulación durante una cantidad determinada de pasos (cant. de actualizaciones)
void Simulacion::ejecucion(int pasos) {

    //Verificar que los archivos esten abiertos
    if (!archivoPosicion.is_open() || !archivoColision.is_open()) {
        std::cerr << "No se puede iniciar la simulacion.\n";
        return;
    }

    //Se llama al metodo 'actualizacion' la cant. de pasos determinada
    for (int i = 0; i < pasos; i++) {

        actualizacion();

        //Mostrar la informacion en consola cada 45pasos para que se evidencie la cant. y momento de fusion de las part.
        if ((i + 1) % 45 == 0) {

            std::cout << "Paso: " << i + 1
                      << " | Tiempo: " << tiempoSimulacion
                      << " s | Particulas: "
                      << particulas.size()
                      << "\n";
        }
    }

    //'flush()' para forzar a que la información pendiente se envie al archivo permanente
    archivoPosicion.flush();
    archivoColision.flush();

    //Resultados finales
    std::cout << "\nSimulacion finalizada.\n";
    std::cout << "Tiempo total: " << tiempoSimulacion << " segundos\n";
    std::cout << "Particulas restantes: " << particulas.size() << "\n";

    std::cout << "Archivos generados:\n";
    std::cout << "- posiciones.csv\n";
    std::cout << "- colisiones.csv\n";
}