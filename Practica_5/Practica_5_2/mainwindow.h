#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include <vector>
#include <QPixmap>
#include "interacciones.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void actualizarSimulacion();
    void on_btnDisparar_clicked();
    void on_btnReiniciar_clicked();
    void on_spinAngulo_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;
    Simulacion simulacion;
    QTimer *timer;

    std::vector<QLabel*> listaObstaculosUI;
    QPixmap pixmapCanon1;
    QPixmap pixmapCanon2;

    void sincronizarInterfaz();
    void rotarCanonUI();
};

#endif // MAINWINDOW_H
