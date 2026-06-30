#ifndef TERRITORYVIEW_H
#define TERRITORYVIEW_H

#include <QWidget>
#include <QPixmap>
#include <QTimer>

#include "territory.h"

class TerritoryView : public QWidget {
private:
    Territory* territory;
    QPixmap background;
    QTimer* timer;

public:
    TerritoryView(Territory* territory, QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;
};

#endif