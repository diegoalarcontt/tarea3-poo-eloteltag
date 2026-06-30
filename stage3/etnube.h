#ifndef ETNUBE_H
#define ETNUBE_H

#include <QString>
#include <QVector>

struct ReporteNube {
    QString owner;
    QString dispositivo;
    QString celularReporta;
    double x;
    double y;
};

class ETNube {
private:
    QVector<ReporteNube> reportes;

public:
    ETNube() {}

    void agregarReporte(QString owner, QString dispositivo, QString celularReporta, double x, double y) {
        for (ReporteNube& reporte : reportes) {
            if (reporte.owner == owner && reporte.dispositivo == dispositivo) {
                reporte.celularReporta = celularReporta;
                reporte.x = x;
                reporte.y = y;
                return;
            }
        }

        ReporteNube nuevoReporte;
        nuevoReporte.owner = owner;
        nuevoReporte.dispositivo = dispositivo;
        nuevoReporte.celularReporta = celularReporta;
        nuevoReporte.x = x;
        nuevoReporte.y = y;

        reportes.append(nuevoReporte);
    }

    QString obtenerTextoReportes(QString owner) const {
        QString texto;

        for (const ReporteNube& reporte : reportes) {
            if (reporte.owner == owner) {
                texto += "Dispositivo: " + reporte.dispositivo + "\n";
                texto += "Reportado por celular de: " + reporte.celularReporta + "\n";
                texto += "Posicion aproximada X: " + QString::number(reporte.x, 'f', 0) + "\n";
                texto += "Posicion aproximada Y: " + QString::number(reporte.y, 'f', 0) + "\n";
                texto += "----------------------\n";
            }
        }

        if (texto.isEmpty()) {
            texto = "No hay reportes disponibles para esta persona.";
        }

        return texto;
    }

    int getCantidadReportes() const {
        return reportes.size();
    }
};

#endif