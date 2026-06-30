#include "territory.h"

#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QDebug>

Territory::Territory() {
    deltaTiempo = 0;
}

Territory::~Territory() {
    qDeleteAll(celulares);
    qDeleteAll(tags);
    qDeleteAll(tablets);

    celulares.clear();
    tags.clear();
    tablets.clear();
}

bool Territory::loadConfig(const QString& filePath) {
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "No se pudo abrir el archivo de configuracion";
        return false;
    }

    QTextStream in(&file);

    QString imageName;
    in >> imageName;

    QFileInfo info(filePath);
    backgroundImage = info.absolutePath() + "/" + imageName;

    int cantidadPersonas;
    in >> deltaTiempo;
    in >> cantidadPersonas;

    for (int i = 0; i < cantidadPersonas; i++) {
        QString nombrePersona;
        int cantidadTags;
        int tieneTablet;

        in >> nombrePersona >> cantidadTags >> tieneTablet;

        double celularX;
        double celularY;
        double rapidez;
        double angulo;
        double deltaAngulo;

        in >> celularX >> celularY >> rapidez >> angulo >> deltaAngulo;

        Cellular* celular = new Cellular(
            nombrePersona,
            celularX,
            celularY,
            rapidez,
            angulo,
            deltaAngulo
            );

        celulares.append(celular);

        qDebug() << "Celular de" << nombrePersona
                 << "X:" << celularX
                 << "Y:" << celularY;

        for (int j = 0; j < cantidadTags; j++) {
            QString nombreTag;
            double tagX;
            double tagY;
            double tagRapidez;
            double tagAngulo;
            double tagDeltaAngulo;

            in >> nombreTag
                >> tagX
                >> tagY
                >> tagRapidez
                >> tagAngulo
                >> tagDeltaAngulo;

            EloTelTag* tag = new EloTelTag(
                nombrePersona,
                nombreTag,
                tagX,
                tagY,
                tagRapidez,
                tagAngulo,
                tagDeltaAngulo
                );

            tags.append(tag);

            qDebug() << "Tag" << nombreTag
                     << "de" << nombrePersona
                     << "X:" << tagX
                     << "Y:" << tagY;
        }

        if (tieneTablet == 1) {
            double tabletX;
            double tabletY;
            double tabletRapidez;
            double tabletAngulo;
            double tabletDeltaAngulo;

            in >> tabletX
                >> tabletY
                >> tabletRapidez
                >> tabletAngulo
                >> tabletDeltaAngulo;

            Tablet* tablet = new Tablet(
                nombrePersona,
                tabletX,
                tabletY,
                tabletRapidez,
                tabletAngulo,
                tabletDeltaAngulo
                );

            tablets.append(tablet);

            qDebug() << "Tablet de" << nombrePersona
                     << "X:" << tabletX
                     << "Y:" << tabletY;
        }
    }

    file.close();
    return true;
}

QString Territory::getBackgroundImage() const {
    return backgroundImage;
}

double Territory::getDeltaTiempo() const {
    return deltaTiempo;
}

QVector<Cellular*> Territory::getCelulares() const {
    return celulares;
}

QVector<EloTelTag*> Territory::getTags() const {
    return tags;
}

QVector<Tablet*> Territory::getTablets() const {
    return tablets;
}

void Territory::moverEquipos(int ancho, int alto) {
    for (Cellular* celular : celulares) {
        celular->mover(deltaTiempo, ancho, alto);
    }

    for (EloTelTag* tag : tags) {
        tag->mover(deltaTiempo, ancho, alto);
    }

    for (Tablet* tablet : tablets) {
        tablet->mover(deltaTiempo, ancho, alto);
    }
}