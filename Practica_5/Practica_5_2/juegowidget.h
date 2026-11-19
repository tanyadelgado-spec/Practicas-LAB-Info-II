#ifndef JUEGOWIDGET_H
#define JUEGOWIDGET_H

#include <QWidget>
#include <QPixmap>
#include "interacciones.h"

class JuegoWidget : public QWidget {
    Q_OBJECT
public:
    explicit JuegoWidget(QWidget *parent = nullptr);

    Simulacion simulacion;
    double anguloActual = 35.0; // Para rotar la imagen del canon en vivo

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap imgFondo;
    QPixmap imgCanon;
};

#endif // JUEGOWIDGET_H