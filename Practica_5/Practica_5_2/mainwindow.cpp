#include "mainwindow.h"
#include <QPainter>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {

    configurarInterfaz();

    // Configurar el temporizador para actualizar la fisica cada 16 ms (~60 FPS)
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::actualizarSimulacion);
    timer->start(16);
}

MainWindow::~MainWindow() {}

void MainWindow::configurarInterfaz() {
    setWindowTitle("Juego de Estrategia Militar - Fisica 2D");
    // Tamano fijo: 800 de ancho x (500 de escenario + 60 de barra superior)
    setFixedSize(800, 500 + offsetSuperior);

    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    // Barra superior de controles
    QHBoxLayout *barraControles = new QHBoxLayout();
    barraControles->setContentsMargins(15, 10, 15, 10);

    lblTurno = new QLabel("Turno: Jugador 1 (Azul)", this);
    lblTurno->setStyleSheet("font-weight: bold; font-size: 14px; color: #1E88E5;");

    QLabel *lblAng = new QLabel("Ángulo (°):", this);
    spinAngulo = new QDoubleSpinBox(this);
    spinAngulo->setRange(-45.0, 85.0); // Permite apuntar ligeramente hacia abajo o arriba
    spinAngulo->setValue(35.0);
    spinAngulo->setSingleStep(5.0);

    QLabel *lblVel = new QLabel("Velocidad:", this);
    spinVelocidad = new QDoubleSpinBox(this);
    spinVelocidad->setRange(50.0, 800.0);
    spinVelocidad->setValue(350.0);
    spinVelocidad->setSingleStep(10.0);

    btnDisparar = new QPushButton("¡Disparar!", this);
    btnDisparar->setStyleSheet("background-color: #43A047; color: white; font-weight: bold; padding: 5px 15px;");

    btnReiniciar = new QPushButton("Reiniciar", this);

    barraControles->addWidget(lblTurno);
    barraControles->addStretch();
    barraControles->addWidget(lblAng);
    barraControles->addWidget(spinAngulo);
    barraControles->addWidget(lblVel);
    barraControles->addWidget(spinVelocidad);
    barraControles->addWidget(btnDisparar);
    barraControles->addWidget(btnReiniciar);

    QVBoxLayout *layoutPrincipal = new QVBoxLayout(central);
    layoutPrincipal->setContentsMargins(0, 0, 0, 0);
    layoutPrincipal->addLayout(barraControles);
    layoutPrincipal->addStretch(); // El resto del espacio queda libre para dibujar con QPainter

    // Conectar botones y cambio de angulo (para rotar el canon en vivo)
    connect(btnDisparar, &QPushButton::clicked, this, &MainWindow::onDispararClicked);
    connect(btnReiniciar, &QPushButton::clicked, this, &MainWindow::onReiniciarClicked);
    connect(spinAngulo, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [this]() {
        update(); // Redibuja el canon cuando cambia el angulo
    });
}

void MainWindow::onDispararClicked() {
    if (!simulacion.getProyectil().activo && !simulacion.isJuegoTerminado()) {
        simulacion.dispararProyectil(spinAngulo->value(), spinVelocidad->value());
        btnDisparar->setEnabled(false); // Desactiva boton mientras vuela el proyectil
    }
}

void MainWindow::onReiniciarClicked() {
    simulacion.reiniciarJuego();
    btnDisparar->setEnabled(true);
    lblTurno->setText("Turno: Jugador 1 (Azul)");
    lblTurno->setStyleSheet("font-weight: bold; font-size: 14px; color: #1E88E5;");
    update();
}

void MainWindow::actualizarSimulacion() {
    bool estabaActivo = simulacion.getProyectil().activo;

    // Avanzar un paso en la fisica
    simulacion.actualizacion();

    // Si el proyectil acaba de detenerse en este frame, actualizar interfaz
    if (estabaActivo && !simulacion.getProyectil().activo) {
        if (simulacion.isJuegoTerminado()) {
            QString msg = QString("¡El Jugador %1 ha ganado la partida!").arg(simulacion.getGanador());
            lblTurno->setText(msg);
            QMessageBox::information(this, "Fin del Juego", msg);
        } else {
            btnDisparar->setEnabled(true);
            if (simulacion.getTurnoActual() == 1) {
                lblTurno->setText("Turno: Jugador 1 (Azul)");
                lblTurno->setStyleSheet("font-weight: bold; font-size: 14px; color: #1E88E5;");
            } else {
                lblTurno->setText("Turno: Jugador 2 (Rojo)");
                lblTurno->setStyleSheet("font-weight: bold; font-size: 14px; color: #E53935;");
            }
        }
    }

    // Solicitar redibujado de la pantalla
    update();
}

void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Desplazar el origen de dibujo hacia abajo para no tapar la barra de botones
    painter.translate(0, offsetSuperior);

    // 1. Fondo del escenario (800 x 500)
    painter.fillRect(0, 0, simulacion.getAncho(), simulacion.getAlto(), QColor("#F5F7FA"));
    painter.setPen(QPen(Qt::black, 2));
    painter.drawRect(0, 0, simulacion.getAncho(), simulacion.getAlto());

    // 2. Dibujar a los dos personajes (Rival 1 y Rival 2)
    const Rival& r1 = simulacion.getRival1();
    painter.setBrush(QColor("#1E88E5")); // Azul
    painter.drawRect(r1.x, r1.y, r1.ancho, r1.alto);
    painter.setPen(Qt::white);
    painter.drawText(r1.x, r1.y, r1.ancho, r1.alto, Qt::AlignCenter, "J1");

    const Rival& r2 = simulacion.getRival2();
    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(QColor("#E53935")); // Rojo
    painter.drawRect(r2.x, r2.y, r2.ancho, r2.alto);
    painter.setPen(Qt::white);
    painter.drawText(r2.x, r2.y, r2.ancho, r2.alto, Qt::AlignCenter, "J2");

    // 3. Dibujar los obstaculos y su resistencia actual
    painter.setFont(QFont("Arial", 10, QFont::Bold));
    for (const Obstaculo& obs : simulacion.getObstaculos()) {
        painter.setPen(QPen(Qt::black, 2));
        // Color segun el jugador al que pertenece el muro
        if (obs.jugadorId == 1)
            painter.setBrush(QColor("#90CAF9"));
        else
            painter.setBrush(QColor("#EF9A9A"));

        painter.drawRect(obs.x, obs.y, obs.ancho, obs.alto);

        // Escribir la resistencia en el centro del bloque
        painter.setPen(Qt::black);
        painter.drawText(obs.x, obs.y, obs.ancho, obs.alto, Qt::AlignCenter,
                         QString::number((int)std::ceil(obs.resistencia)));
    }

    // 4. Dibujar los canones a media altura (y = 250)
    Vector2D c1(70.0, 250.0);
    Vector2D c2(730.0, 250.0);

    // Base de los canones
    painter.setBrush(Qt::darkGray);
    painter.drawEllipse(QPointF(c1.x, c1.y), 14, 14);
    painter.drawEllipse(QPointF(c2.x, c2.y), 14, 14);

    // Tubo del canon activo rotando segun el angulo elegido
    const double PI = 3.14159265358979323846;
    double angRad = spinAngulo->value() * PI / 180.0;
    double largoCanon = 32.0;

    painter.setPen(QPen(Qt::black, 6, Qt::SolidLine, Qt::RoundCap));
    if (simulacion.getTurnoActual() == 1) {
        double finX = c1.x + largoCanon * std::cos(angRad);
        double finY = c1.y - largoCanon * std::sin(angRad);
        painter.drawLine(QPointF(c1.x, c1.y), QPointF(finX, finY));
    } else {
        double angJ2 = (180.0 - spinAngulo->value()) * PI / 180.0;
        double finX = c2.x + largoCanon * std::cos(angJ2);
        double finY = c2.y - largoCanon * std::sin(angJ2);
        painter.drawLine(QPointF(c2.x, c2.y), QPointF(finX, finY));
    }

    // 5. Dibujar el proyectil
    const Particula& p = simulacion.getProyectil();
    painter.setPen(QPen(Qt::black, 1));
    painter.setBrush(QColor("#FFB300")); // Amarillo/Naranja
    painter.drawEllipse(QPointF(p.posicion.x, p.posicion.y), p.radio, p.radio);
}
