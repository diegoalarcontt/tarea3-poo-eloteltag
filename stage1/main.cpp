#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>

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

    TerritoryView window(territory);
    window.setWindowTitle("EloTelTag Simulation - Stage 1");
    window.show();

    int resultado = app.exec();

    delete territory;

    return resultado;
}