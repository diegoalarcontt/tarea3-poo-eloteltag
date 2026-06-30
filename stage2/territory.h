#ifndef TERRITORY_H
#define TERRITORY_H

#include <QString>
#include <QVector>

#include "cellular.h"
#include "eloteltag.h"
#include "tablet.h"

class Territory {
private:
    QString backgroundImage;
    double deltaTiempo;

    QVector<Cellular*> celulares;
    QVector<EloTelTag*> tags;
    QVector<Tablet*> tablets;

public:
    Territory();
    ~Territory();

    bool loadConfig(const QString& filePath);

    QString getBackgroundImage() const;
    double getDeltaTiempo() const;

    QVector<Cellular*> getCelulares() const;
    QVector<EloTelTag*> getTags() const;
    QVector<Tablet*> getTablets() const;

    void moverEquipos(int ancho, int alto);
};

#endif