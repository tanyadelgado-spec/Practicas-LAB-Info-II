#include "juegowidget.h"
#include <QPainter>
#include <cmath>

JuegoWidget::JuegoWidget(QWidget *parent) : QWidget(parent) {
    // Cargar imagenes desde el archivo de recursos (.qrc)
    imgFondo.load(":/Fondo.png");
    imgCanon.load(":/Cañon.png");
}

void JuegoWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    // 1. Dibujar el fondo (si no hay imagen, pinta un cielo claro por defecto)
    if (!imgFondo.isNull()) {
        painter.drawPixmap(0, 0, width(), height(), imgFondo);
    } else {
        painter.fillRect(rect(), QColor("#DCEEFB"));
    }

    // 2. Dibujar los personajes (Rival 1 y Rival 2)
    const Rival& r1 = simulacion.getRival1();
    painter.setBrush(QColor("#1E88E5"));
    painter.setPen(QPen(Qt::black, 2));
    painter.drawRect(r1.x, r1.y, r1.ancho, r1.alto);
    painter.setPen(Qt::white);
    painter.drawText(r1.x, r1.y, r1.ancho, r1.alto, Qt::AlignCenter, "J1");

    const Rival& r2 = simulacion.getRival2();
    painter.setBrush(QColor("#E53935"));
    painter.setPen(QPen(Qt::black, 2));
    painter.drawRect(r2.x, r2.y, r2.ancho, r2.alto);
    painter.setPen(Qt::white);
    painter.drawText(r2.x, r2.y, r2.ancho, r2.alto, Qt::AlignCenter, "J2");

    // 3. Dibujar los obstaculos con su resistencia
    painter.setFont(QFont("Arial", 10, QFont::Bold));
    for (const Obstaculo& obs : simulacion.getObstaculos()) {
        painter.setPen(QPen(Qt::black, 2));
        painter.setBrush(obs.jugadorId == 1 ? QColor("#90CAF9") : QColor("#EF9A9A"));
        painter.drawRect(obs.x, obs.y, obs.ancho, obs.alto);

        painter.setPen(Qt::black);
        painter.drawText(obs.x, obs.y, obs.ancho, obs.alto, Qt::AlignCenter,
                         QString::number((int)std::ceil(obs.resistencia)));
    }

    // 4. Dibujar los canones a media altura (y = 250) con imagen rotada
    auto dibujarCanon = [&](double x, double y, double angulo, bool mirarIzquierda) {
        painter.save(); // Guarda el estado actual del pintor
        painter.translate(x, y); // Mueve el origen al centro del canon

        if (mirarIzquierda) {
            painter.scale(-1, 1); // Espejo horizontal para el Jugador 2
        }
        // En Qt los angulos positivos rotan en sentido horario, por eso usamos -angulo
        painter.rotate(-angulo);

        if (!imgCanon.isNull()) {
            // Dibuja la imagen centrada en (0, 0) con tamano 60x40
            painter.drawPixmap(-30, -20, 60, 40, imgCanon);
        } else {
            // Respaldo por si aun no cargas la imagen
            painter.setBrush(Qt::darkGray);
            painter.drawRect(-15, -8, 40, 16);
        }
        painter.restore(); // Restaura el pintor para no rotar lo demas
    };

    double ang1 = (simulacion.getTurnoActual() == 1) ? anguloActual : 0.0;
    double ang2 = (simulacion.getTurnoActual() == 2) ? anguloActual : 0.0;

    dibujarCanon(70.0, 250.0, ang1, false);  // Canon Jugador 1
    dibujarCanon(730.0, 250.0, ang2, true);  // Canon Jugador 2

    // 5. Dibujar el proyectil
    const Particula& p = simulacion.getProyectil();
    painter.setPen(QPen(Qt::black, 1));
    painter.setBrush(QColor("#FFB300"));
    painter.drawEllipse(QPointF(p.posicion.x, p.posicion.y), p.radio, p.radio);
}
