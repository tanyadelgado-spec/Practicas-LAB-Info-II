#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTransform>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Lista ordenada con los 6 QLabel de obstaculos arrastrados en el .ui
    listaObstaculosUI = {
        ui->obs1, ui->obs2, ui->obs3,
        ui->obs4, ui->obs5, ui->obs6
    };

    // Cargar  imagenes

    pixmapCanon1.load(":/canon.png");
    pixmapCanon2.load(":/canon2.png");

    // Respaldo: si no se cargo por ruta
    if (pixmapCanon1.isNull())
        pixmapCanon1 = ui->lblCanon1->pixmap(Qt::ReturnByValue);
    if (pixmapCanon2.isNull())
        pixmapCanon2 = ui->lblCanon2->pixmap(Qt::ReturnByValue);

    sincronizarInterfaz();
    rotarCanonUI();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::actualizarSimulacion);
    timer->start(16);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::sincronizarInterfaz() {
    // Posicionar Rivales
    const Rival& r1 = simulacion.getRival1();
    ui->lblRival1->setGeometry(r1.x, r1.y, r1.ancho, r1.alto);

    const Rival& r2 = simulacion.getRival2();
    ui->lblRival2->setGeometry(r2.x, r2.y, r2.ancho, r2.alto);

     //Actualizar obstaculos
    for (QLabel* lbl : listaObstaculosUI) {
        lbl->hide();
    }

    const auto& obstaculosActivos = simulacion.getObstaculos();
    for (const Obstaculo& obs : obstaculosActivos) {
        int idx = obs.id - 1;
        if (idx >= 0 && idx < listaObstaculosUI.size()) {
            QLabel* lbl = listaObstaculosUI[idx];
            lbl->setGeometry(obs.x, obs.y, obs.ancho, obs.alto);
            lbl->setText(QString::number((int)std::ceil(obs.resistencia)));
            lbl->show();
        }
    }

    // Mover el proyectil
    const Particula& p = simulacion.getProyectil();
    if (p.activo) {
        int diametro = (int)(p.radio * 2);
        ui->lblProyectil->setGeometry((int)(p.posicion.x - p.radio),
                                      (int)(p.posicion.y - p.radio),
                                      diametro, diametro);
        ui->lblProyectil->show();
    } else {
        ui->lblProyectil->hide();
    }
}

void MainWindow::rotarCanonUI() {
    double angulo = ui->spinAngulo->value();

    // --- Canon 1 (Izquierda, mira a la derecha) ---
    if (!pixmapCanon1.isNull()) {
        QTransform trans1;
        // Sube en sentido antihorario (-angulo)
        trans1.rotate(simulacion.getTurnoActual() == 1 ? -angulo : 0.0);
        ui->lblCanon1->setPixmap(pixmapCanon1.transformed(trans1, Qt::SmoothTransformation));
    }

    // --- Canon 2 (Derecha, mira a la izquierda) ---
    if (!pixmapCanon2.isNull()) {
        QTransform trans2;
        // Sube en sentido horario (+angulo) porque ya apunta hacia la izquierda
        trans2.rotate(simulacion.getTurnoActual() == 2 ? angulo : 0.0);
        ui->lblCanon2->setPixmap(pixmapCanon2.transformed(trans2, Qt::SmoothTransformation));
    }
}

void MainWindow::on_btnDisparar_clicked() {
    if (!simulacion.getProyectil().activo && !simulacion.isJuegoTerminado()) {
        simulacion.dispararProyectil(ui->spinAngulo->value(), ui->spinVelocidad->value());
        ui->btnDisparar->setEnabled(false);
    }
}

void MainWindow::on_btnReiniciar_clicked() {
    simulacion.reiniciarJuego();
    ui->btnDisparar->setEnabled(true);
    ui->lblTurno->setText("Turno: Jugador 1");
    sincronizarInterfaz();
    rotarCanonUI();
}

void MainWindow::on_spinAngulo_valueChanged(double arg1) {
    Q_UNUSED(arg1);
    rotarCanonUI();
}

void MainWindow::actualizarSimulacion() {
    bool estabaActivo = simulacion.getProyectil().activo;

    simulacion.actualizacion();
    sincronizarInterfaz();

    if (estabaActivo && !simulacion.getProyectil().activo) {
        if (simulacion.isJuegoTerminado()) {
            QString msg = QString("¡El Jugador %1 ha ganado!").arg(simulacion.getGanador());
            ui->lblTurno->setText(msg);
            QMessageBox::information(this, "Fin del Juego", msg);
        } else {
            ui->btnDisparar->setEnabled(true);
            ui->lblTurno->setText(simulacion.getTurnoActual() == 1
                                      ? "Turno: Jugador 1"
                                      : "Turno: Jugador 2");
            rotarCanonUI();
        }
    }
}