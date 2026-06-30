# Diagrama UML - Tarea 3 EloTelTags

Este diagrama representa la estructura principal de clases utilizadas en la versión final del proyecto, correspondiente a `stage4`.

```mermaid
classDiagram

class Equipo {
    - QString owner
    - double x
    - double y
    - double rapidez
    - double angulo
    - double deltaAngulo
    - bool trazaActiva
    - QVector~QPointF~ trayectoria
    + getOwner()
    + getX()
    + getY()
    + mover()
    + toggleTraza()
    + isTrazaActiva()
    + getTrayectoria()
}

class Cellular {
    + Cellular()
}

class EloTelTag {
    - QString nombre
    + getNombre()
}

class Tablet {
    + Tablet()
}

class Territory {
    - QString backgroundImage
    - double deltaTiempo
    - QVector~Cellular*~ celulares
    - QVector~EloTelTag*~ tags
    - QVector~Tablet*~ tablets
    + loadConfig()
    + getBackgroundImage()
    + getDeltaTiempo()
    + getCelulares()
    + getTags()
    + getTablets()
    + moverEquipos()
}

class TerritoryView {
    - Territory* territory
    - QPixmap background
    - QTimer* timer
    - ETNube nube
    - double tiempoSimulacion
    - double acumuladorReportes
    + play()
    + pause()
    + paintEvent()
    + mousePressEvent()
    - detectarCercanos()
    - distancia()
    - obtenerOwnerDesdeClick()
}

class ETNube {
    - QVector~ReporteNube~ reportes
    + agregarReporte()
    + obtenerTextoReportes()
    + getCantidadReportes()
}

class ReporteNube {
    + QString owner
    + QString dispositivo
    + QString celularReporta
    + double x
    + double y
}

Equipo <|-- Cellular
Equipo <|-- EloTelTag
Equipo <|-- Tablet

Territory o-- Cellular
Territory o-- EloTelTag
Territory o-- Tablet

TerritoryView --> Territory
TerritoryView --> ETNube

ETNube o-- ReporteNube
```

## Explicación breve

La clase `Equipo` es la clase base del sistema. Desde ella heredan `Cellular`, `EloTelTag` y `Tablet`, ya que todos los dispositivos comparten posición, rapidez, ángulo, movimiento y trayectoria.

La clase `Territory` se encarga de leer el archivo de configuración y almacenar las listas de celulares, tags y tablets.

La clase `TerritoryView` se encarga de mostrar gráficamente el mapa, los equipos, el radar, las trazas y el menú Find My.

La clase `ETNube` simula la nube donde se guardan los reportes generados cuando un tag o una tablet detecta un celular cercano.
