#include "territoryview.h"

#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QMenu>
#include <QMessageBox>
#include <QtMath>

TerritoryView::TerritoryView(Territory* territory, QWidget* parent)
    : QWidget(parent) {
    this->territory = territory;

    tiempoSimulacion = 0;
    acumuladorReportes = 0;

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
        double dt = this->territory->getDeltaTiempo();

        this->territory->moverEquipos(width(), height());

        tiempoSimulacion += dt;
        acumuladorReportes += dt;

        if (acumuladorReportes >= 4.0) {
            detectarCercanos();
            acumuladorReportes = 0;
        }

        update();
    });

    int intervalo = territory->getDeltaTiempo() * 1000;

    if (intervalo < 10) {
        intervalo = 100;
    }

    timer->start(intervalo);
}

double TerritoryView::distancia(double x1, double y1, double x2, double y2) {
    double dx = x1 - x2;
    double dy = y1 - y2;

    return qSqrt(dx * dx + dy * dy);
}

void TerritoryView::detectarCercanos() {
    double radioDeteccion = 50.0;

    for (EloTelTag* tag : territory->getTags()) {
        for (Cellular* celular : territory->getCelulares()) {
            double d = distancia(tag->getX(), tag->getY(), celular->getX(), celular->getY());

            if (d <= radioDeteccion) {
                nube.agregarReporte(
                    tag->getOwner(),
                    tag->getNombre(),
                    celular->getOwner(),
                    celular->getX(),
                    celular->getY()
                    );
            }
        }
    }

    for (Tablet* tablet : territory->getTablets()) {
        for (Cellular* celular : territory->getCelulares()) {
            double d = distancia(tablet->getX(), tablet->getY(), celular->getX(), celular->getY());

            if (d <= radioDeteccion) {
                nube.agregarReporte(
                    tablet->getOwner(),
                    "tablet",
                    celular->getOwner(),
                    celular->getX(),
                    celular->getY()
                    );
            }
        }
    }
}

QString TerritoryView::obtenerOwnerDesdeClick(int mouseX, int mouseY) {
    for (Cellular* celular : territory->getCelulares()) {
        if (qAbs(mouseX - celular->getX()) <= 12 && qAbs(mouseY - celular->getY()) <= 12) {
            return celular->getOwner();
        }
    }

    for (Tablet* tablet : territory->getTablets()) {
        if (qAbs(mouseX - tablet->getX()) <= 18 && qAbs(mouseY - tablet->getY()) <= 18) {
            return tablet->getOwner();
        }
    }

    return "";
}

void TerritoryView::mousePressEvent(QMouseEvent* event) {
    QString owner = obtenerOwnerDesdeClick(event->position().x(), event->position().y());

    if (owner.isEmpty()) {
        return;
    }

    QMenu menu(this);
    QAction* findMyAction = menu.addAction("Find My");

    QAction* selectedAction = menu.exec(event->globalPosition().toPoint());

    if (selectedAction == findMyAction) {
        QMessageBox::information(
            this,
            "Find My - " + owner,
            nube.obtenerTextoReportes(owner)
            );
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

    int radioRadar = static_cast<int>((tiempoSimulacion * 50.0)) % 50;

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

        painter.setBrush(Qt::NoBrush);
        painter.setPen(Qt::gray);
        painter.drawEllipse(
            QPointF(tag->getX(), tag->getY()),
            radioRadar,
            radioRadar
            );

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

        painter.setBrush(Qt::NoBrush);
        painter.setPen(Qt::gray);
        painter.drawEllipse(
            QPointF(tablet->getX(), tablet->getY()),
            radioRadar,
            radioRadar
            );

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