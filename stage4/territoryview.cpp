#include "territoryview.h"

#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QMenu>
#include <QMessageBox>
#include <QtMath>
#include <QDialog>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QPen>

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

void TerritoryView::play() {
    if (timer != nullptr) {
        timer->start();
    }
}

void TerritoryView::pause() {
    if (timer != nullptr) {
        timer->stop();
    }
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
            double d = distancia(
                tag->getX(),
                tag->getY(),
                celular->getX(),
                celular->getY()
                );

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
            double d = distancia(
                tablet->getX(),
                tablet->getY(),
                celular->getX(),
                celular->getY()
                );

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
        if (qAbs(mouseX - celular->getX()) <= 12 &&
            qAbs(mouseY - celular->getY()) <= 12) {
            return celular->getOwner();
        }
    }

    for (Tablet* tablet : territory->getTablets()) {
        if (qAbs(mouseX - tablet->getX()) <= 18 &&
            qAbs(mouseY - tablet->getY()) <= 18) {
            return tablet->getOwner();
        }
    }

    return "";
}

void TerritoryView::mousePressEvent(QMouseEvent* event) {
    QString owner = obtenerOwnerDesdeClick(
        event->position().x(),
        event->position().y()
        );

    if (owner.isEmpty()) {
        return;
    }

    QMenu menu(this);
    QAction* findMyAction = menu.addAction("Find My");

    QAction* selectedAction = menu.exec(event->globalPosition().toPoint());

    if (selectedAction == findMyAction) {
        QDialog* ventanaFindMy = new QDialog(this);
        ventanaFindMy->setWindowTitle("Find My - " + owner);
        ventanaFindMy->resize(400, 450);

        QVBoxLayout* layout = new QVBoxLayout(ventanaFindMy);

        QTextEdit* textoReportes = new QTextEdit(ventanaFindMy);
        textoReportes->setReadOnly(true);
        textoReportes->setText(nube.obtenerTextoReportes(owner));

        layout->addWidget(textoReportes);

        QLabel* tituloTrazas = new QLabel("Trazas de equipos:", ventanaFindMy);
        layout->addWidget(tituloTrazas);

        for (Cellular* celular : territory->getCelulares()) {
            if (celular->getOwner() == owner) {
                QPushButton* botonCelular = new QPushButton("Mostrar/Ocultar traza celular", ventanaFindMy);

                connect(botonCelular, &QPushButton::clicked, this, [this, celular]() {
                    celular->toggleTraza();
                    update();
                });

                layout->addWidget(botonCelular);
            }
        }

        for (EloTelTag* tag : territory->getTags()) {
            if (tag->getOwner() == owner) {
                QPushButton* botonTag = new QPushButton("Mostrar/Ocultar traza " + tag->getNombre(), ventanaFindMy);

                connect(botonTag, &QPushButton::clicked, this, [this, tag]() {
                    tag->toggleTraza();
                    update();
                });

                layout->addWidget(botonTag);
            }
        }

        for (Tablet* tablet : territory->getTablets()) {
            if (tablet->getOwner() == owner) {
                QPushButton* botonTablet = new QPushButton("Mostrar/Ocultar traza tablet", ventanaFindMy);

                connect(botonTablet, &QPushButton::clicked, this, [this, tablet]() {
                    tablet->toggleTraza();
                    update();
                });

                layout->addWidget(botonTablet);
            }
        }

        QTimer* timerFindMy = new QTimer(ventanaFindMy);

        connect(timerFindMy, &QTimer::timeout, this, [this, textoReportes, owner]() {
            textoReportes->setText(nube.obtenerTextoReportes(owner));
        });

        timerFindMy->start(1000);

        ventanaFindMy->exec();
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
    painter.setPen(QPen(Qt::black, 2));

    for (Cellular* celular : territory->getCelulares()) {
        if (celular->isTrazaActiva() && celular->getTrayectoria().size() > 1) {
            QVector<QPointF> puntos = celular->getTrayectoria();
            painter.drawPolyline(puntos.data(), puntos.size());
        }
    }

    for (EloTelTag* tag : territory->getTags()) {
        if (tag->isTrazaActiva() && tag->getTrayectoria().size() > 1) {
            QVector<QPointF> puntos = tag->getTrayectoria();
            painter.drawPolyline(puntos.data(), puntos.size());
        }
    }

    for (Tablet* tablet : territory->getTablets()) {
        if (tablet->isTrazaActiva() && tablet->getTrayectoria().size() > 1) {
            QVector<QPointF> puntos = tablet->getTrayectoria();
            painter.drawPolyline(puntos.data(), puntos.size());
        }
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