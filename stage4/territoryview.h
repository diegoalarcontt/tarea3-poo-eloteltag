#ifndef TERRITORYVIEW_H
#define TERRITORYVIEW_H

#include <QWidget>
#include <QPixmap>
#include <QTimer>
#include <QString>

#include "territory.h"
#include "etnube.h"

class TerritoryView : public QWidget {
private:
    Territory* territory;
    QPixmap background;
    QTimer* timer;
    ETNube nube;

    double tiempoSimulacion;
    double acumuladorReportes;

    void detectarCercanos();
    double distancia(double x1, double y1, double x2, double y2);
    QString obtenerOwnerDesdeClick(int mouseX, int mouseY);

public:
    TerritoryView(Territory* territory, QWidget* parent = nullptr);

    void play();
    void pause();

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
};

#endif