#ifndef ELOTELTAG_H
#define ELOTELTAG_H

#include "equipo.h"

class EloTelTag : public Equipo {
private:
    QString nombre;

public:
    EloTelTag(QString owner, QString nombre, double x, double y, double rapidez, double angulo, double deltaAngulo)
        : Equipo(owner, x, y, rapidez, angulo, deltaAngulo),
        nombre(nombre) {}

    QString getNombre() const {
        return nombre;
    }
};

#endif