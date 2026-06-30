#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>

#include "territory.h"
#include "territoryview.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QString filePath = QFileDialog::getOpenFileName(
        nullptr,
        "Seleccionar archivo de configuracion",
        "",
        "Archivos de texto (*.txt);;Todos los archivos (*)"
        );

    if (filePath.isEmpty()) {
        return 0;
    }

    Territory* territory = new Territory();

    if (!territory->loadConfig(filePath)) {
        QMessageBox::critical(
            nullptr,
            "Error",
            "No se pudo cargar el archivo de configuracion"
            );

        delete territory;
        return 1;
    }

    QMainWindow window;

    TerritoryView* territoryView = new TerritoryView(territory);
    window.setCentralWidget(territoryView);

    QMenu* simulationMenu = window.menuBar()->addMenu("Simulation");

    QAction* playAction = simulationMenu->addAction("Play");
    QAction* pauseAction = simulationMenu->addAction("Pause");

    QObject::connect(playAction, &QAction::triggered, territoryView, &TerritoryView::play);
    QObject::connect(pauseAction, &QAction::triggered, territoryView, &TerritoryView::pause);

    window.setWindowTitle("EloTelTag Simulation - Stage 4");
    window.resize(1200, 700);
    window.show();

    int resultado = app.exec();

    delete territory;

    return resultado;
}