#ifndef TERRITORY_H
#define TERRITORY_H

#include <QString>
#include <QVector>
#include "cellular.h"

class Territory {
private:
    QString backgroundImage;
    double deltaTiempo;
    QVector<Cellular*> celulares;

public:
    Territory();
    ~Territory();

    bool loadConfig(const QString& filePath);

    QString getBackgroundImage() const;
    double getDeltaTiempo() const;
    QVector<Cellular*> getCelulares() const;
};

#endif