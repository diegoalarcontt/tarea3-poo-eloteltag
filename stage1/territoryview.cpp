#include "territoryview.h"

#include <QPainter>
#include <QPaintEvent>

TerritoryView::TerritoryView(Territory* territory, QWidget* parent)
    : QWidget(parent) {
    this->territory = territory;

    background.load(territory->getBackgroundImage());

    if (!background.isNull()) {
        resize(background.size());
        setMinimumSize(800, 500);
    } else {
        resize(1200, 700);
        setMinimumSize(800, 500);
    }
}

void TerritoryView::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);

    QPainter painter(this);

    if (!background.isNull()) {
        painter.drawPixmap(0, 0, background);
    } else {
        painter.fillRect(rect(), Qt::white);
    }

    QVector<Cellular*> celulares = territory->getCelulares();

    for (Cellular* celular : celulares) {
        int size = 12;

        painter.setBrush(Qt::blue);
        painter.setPen(Qt::black);

        painter.drawRect(
            celular->getX() - size / 2,
            celular->getY() - size / 2,
            size,
            size
            );

        painter.drawText(
            celular->getX() + 8,
            celular->getY(),
            celular->getOwner()
            );
    }
}