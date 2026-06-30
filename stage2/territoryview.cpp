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

    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, [this]() {
        this->territory->moverEquipos(width(), height());
        update();
    });

    int intervalo = territory->getDeltaTiempo() * 1000;

    if (intervalo < 10) {
        intervalo = 100;
    }

    timer->start(intervalo);
}

void TerritoryView::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);

    QPainter painter(this);

    if (!background.isNull()) {
        painter.drawPixmap(0, 0, background);
    } else {
        painter.fillRect(rect(), Qt::white);
    }

    for (Cellular* celular : territory->getCelulares()) {
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

    for (EloTelTag* tag : territory->getTags()) {
        int size = 10;

        painter.setBrush(Qt::red);
        painter.setPen(Qt::black);

        painter.drawEllipse(
            tag->getX() - size / 2,
            tag->getY() - size / 2,
            size,
            size
            );

        painter.drawText(
            tag->getX() + 8,
            tag->getY(),
            tag->getOwner() + "/" + tag->getNombre()
            );
    }

    for (Tablet* tablet : territory->getTablets()) {
        int widthTablet = 18;
        int heightTablet = 12;

        painter.setBrush(Qt::green);
        painter.setPen(Qt::black);

        painter.drawRect(
            tablet->getX() - widthTablet / 2,
            tablet->getY() - heightTablet / 2,
            widthTablet,
            heightTablet
            );

        painter.drawText(
            tablet->getX() + 10,
            tablet->getY(),
            tablet->getOwner() + " tablet"
            );
    }
}