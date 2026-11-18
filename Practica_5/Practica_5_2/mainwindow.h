#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QPaintEvent>
#include "interacciones.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    // Evento de Qt que se ejecuta cada vez que hay que redibujar la pantalla
    void paintEvent(QPaintEvent *event) override;

private slots:
    // Slots (acciones) conectados a los botones y al temporizador
    void actualizarSimulacion();
    void onDispararClicked();
    void onReiniciarClicked();

private:
    Simulacion simulacion;
    QTimer *timer;

    // Controles de la interfaz
    QLabel *lblTurno;
    QDoubleSpinBox *spinAngulo;
    QDoubleSpinBox *spinVelocidad;
    QPushButton *btnDisparar;
    QPushButton *btnReiniciar;

    // Altura reservada arriba para la barra de controles
    const int offsetSuperior = 60;

    void configurarInterfaz();
};

#endif // MAINWINDOW_H
