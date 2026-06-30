#ifndef EQUIPO_H
#define EQUIPO_H

#include <QString>
#include <QtMath>
#include <QRandomGenerator>

class Equipo {
protected:
    QString owner;
    double x;
    double y;
    double rapidez;
    double angulo;
    double deltaAngulo;

public:
    Equipo(QString owner, double x, double y, double rapidez, double angulo, double deltaAngulo)
        : owner(owner),
        x(x),
        y(y),
        rapidez(rapidez),
        angulo(angulo),
        deltaAngulo(deltaAngulo) {}

    virtual ~Equipo() {}

    QString getOwner() const {
        return owner;
    }

    double getX() const {
        return x;
    }

    double getY() const {
        return y;
    }

    double getRapidez() const {
        return rapidez;
    }

    double getAngulo() const {
        return angulo;
    }

    double getDeltaAngulo() const {
        return deltaAngulo;
    }

    void mover(double deltaTiempo, int ancho, int alto) {
        double variacion = (QRandomGenerator::global()->generateDouble() * 2.0 * deltaAngulo) - deltaAngulo;

        angulo += variacion;

        double radianes = qDegreesToRadians(angulo);

        x += rapidez * deltaTiempo * qCos(radianes);
        y += rapidez * deltaTiempo * qSin(radianes);

        if (x < 0) {
            x = 0;
            angulo = 180 - angulo;
        }

        if (x > ancho) {
            x = ancho;
            angulo = 180 - angulo;
        }

        if (y < 0) {
            y = 0;
            angulo = -angulo;
        }

        if (y > alto) {
            y = alto;
            angulo = -angulo;
        }
    }
};

#endif