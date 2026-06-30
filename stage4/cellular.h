#ifndef CELLULAR_H
#define CELLULAR_H

#include "equipo.h"

class Cellular : public Equipo {
public:
    Cellular(QString owner, double x, double y, double rapidez, double angulo, double deltaAngulo)
        : Equipo(owner, x, y, rapidez, angulo, deltaAngulo) {}
};

#endif