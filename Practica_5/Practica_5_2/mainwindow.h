#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include <QList>
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

    QList<QLabel*> listaObstaculosUI;
    QPixmap pixmapCanon1; // Imagen apuntando a la derecha
    QPixmap pixmapCanon2; // Imagen apuntando a la izquierda (ya volteada en espejo)

    void sincronizarInterfaz();
    void rotarCanonUI();
};

#endif // MAINWINDOW_H
