#ifndef EQUIPO_H
#define EQUIPO_H

#include <QString>

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
};

#endif