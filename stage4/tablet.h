#ifndef TABLET_H
#define TABLET_H

#include "equipo.h"

class Tablet : public Equipo {
public:
    Tablet(QString owner, double x, double y, double rapidez, double angulo, double deltaAngulo)
        : Equipo(owner, x, y, rapidez, angulo, deltaAngulo) {}
};

#endif