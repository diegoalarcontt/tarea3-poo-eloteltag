# Documentación Técnica - Tarea 3 EloTelTags y Find My

## 1. Introducción

Este proyecto corresponde a la Tarea 3 de Diseño y Programación Orientados a Objetos.

El objetivo principal fue desarrollar una aplicación gráfica en C++ y Qt que simula un sistema similar a Find My. En la simulación existen celulares, EloTelTags y tablets que se mueven dentro de un territorio representado por una imagen de fondo.

La configuración inicial de los dispositivos se carga desde un archivo `config.txt`, el cual contiene la imagen de fondo, el tiempo de simulación, las personas, sus celulares, tags y tablets.

---

## 2. Objetivo del proyecto

El objetivo del proyecto es aplicar programación orientada a objetos usando C++ y Qt, modelando distintos dispositivos como objetos de software.

También se busca desarrollar el proyecto en etapas incrementales, donde cada etapa agrega nuevas funcionalidades hasta llegar a una simulación completa.

---

## 3. Tecnologías utilizadas

* C++
* Qt Creator
* Qt Widgets
* CMake
* Git
* GitHub

---

## 4. Organización del proyecto

El proyecto está dividido en cuatro etapas:

```text
stage1/
stage2/
stage3/
stage4/
```

Cada carpeta contiene una versión incremental del sistema.

Además, en la carpeta principal se incluyen:

```text
README.md
DOCUMENTACION.md
DIAGRAMA_UML.md
config.txt
Placeres.jpg
```

---

## 5. Descripción de etapas

## Stage 1

En la primera etapa se implementó la lectura del archivo de configuración y la visualización inicial de celulares.

Funcionalidades implementadas:

* Lectura de archivo `config.txt`.
* Carga de imagen de fondo.
* Creación de objetos `Cellular`.
* Visualización gráfica de celulares.

En esta etapa todavía no se muestran tags ni tablets.

---

## Stage 2

En la segunda etapa se agregaron los EloTelTags y las tablets.

Funcionalidades implementadas:

* Lectura completa del archivo de configuración.
* Creación de celulares, EloTelTags y tablets.
* Movimiento automático de equipos.
* Rebote en los bordes del territorio.
* Visualización gráfica de todos los dispositivos.

Los colores usados fueron:

* Celulares: azul.
* EloTelTags: rojo.
* Tablets: verde.

---

## Stage 3

En la tercera etapa se agregó la nube simulada `ETNube` y la función Find My básica.

Funcionalidades implementadas:

* Clase `ETNube`.
* Detección de celulares cercanos.
* Reportes hacia la nube.
* Radar visual en tags y tablets.
* Menú emergente con opción `Find My`.
* Visualización de reportes almacenados.

En esta etapa la ventana Find My muestra la información disponible, pero todavía no se actualiza continuamente.

---

## Stage 4

En la cuarta etapa se completaron las funcionalidades principales del sistema.

Funcionalidades implementadas:

* Menú `Simulation`.
* Opción `Play`.
* Opción `Pause`.
* Ventana `Find My` actualizada cada 1 segundo.
* Radar visual.
* Trayectorias o trazas de equipos.
* Botones para mostrar u ocultar trazas.
* Movimiento y rebote de todos los equipos.
* Uso de la nube simulada `ETNube`.

Esta etapa corresponde a la versión final del proyecto.

---

## 6. Clases principales

## Equipo

Es la clase base del sistema.

Contiene los atributos comunes de todos los dispositivos:

* Dueño.
* Posición X.
* Posición Y.
* Rapidez.
* Ángulo.
* Delta de ángulo.
* Estado de traza.
* Trayectoria.

También contiene el método `mover()`, que permite actualizar la posición del equipo y hacerlo rebotar en los bordes del territorio.

---

## Cellular

Representa un celular asociado a una persona.

Hereda de la clase `Equipo`, por lo que comparte sus atributos de posición, movimiento y traza.

---

## EloTelTag

Representa un dispositivo de rastreo asociado a una persona.

Hereda de `Equipo` y además posee un nombre propio, por ejemplo:

```text
llaves
mochila
maleta
```

Los EloTelTags pueden detectar celulares cercanos y generar reportes hacia la nube.

---

## Tablet

Representa una tablet asociada a una persona.

Hereda de `Equipo` y también puede detectar celulares cercanos para reportar información a `ETNube`.

---

## Territory

La clase `Territory` se encarga de almacenar la información del territorio y los dispositivos.

Responsabilidades:

* Guardar la imagen de fondo.
* Guardar el delta de tiempo.
* Leer el archivo `config.txt`.
* Crear celulares, tags y tablets.
* Almacenar listas de dispositivos.
* Mover todos los equipos.

---

## TerritoryView

La clase `TerritoryView` se encarga de la parte gráfica de la simulación.

Responsabilidades:

* Dibujar el mapa.
* Dibujar celulares.
* Dibujar tags.
* Dibujar tablets.
* Dibujar el radar visual.
* Dibujar las trazas.
* Detectar clics sobre celulares o tablets.
* Mostrar el menú Find My.
* Controlar el temporizador de la simulación.
* Implementar las opciones Play y Pause.

---

## ETNube

La clase `ETNube` simula una nube donde se guardan los reportes de detección.

Responsabilidades:

* Guardar reportes.
* Actualizar reportes existentes.
* Entregar texto para mostrar en la ventana Find My.
* Contabilizar reportes.

---

## ReporteNube

Es una estructura usada por `ETNube`.

Guarda información como:

* Dueño del dispositivo.
* Nombre del dispositivo.
* Celular que reportó.
* Posición X.
* Posición Y.

---

## 7. Diagrama de clases

El diagrama de clases se encuentra en el archivo:

```text
DIAGRAMA_UML.md
```

Resumen de relaciones principales:

```text
Equipo
├── Cellular
├── EloTelTag
└── Tablet

Territory contiene celulares, tags y tablets.

TerritoryView utiliza Territory y ETNube.

ETNube contiene reportes de tipo ReporteNube.
```

---

## 8. Funcionamiento general

Al iniciar el programa, se abre un selector de archivos para escoger `config.txt`.

El archivo indica qué imagen se usará como fondo y qué dispositivos deben crearse.

Luego se abre la ventana principal de simulación. En ella se muestran los celulares, tags y tablets sobre el mapa.

Los equipos se mueven automáticamente según su rapidez y ángulo. Si llegan al borde del territorio, rebotan.

Los tags y tablets revisan si existen celulares cercanos dentro de un radio de detección. Si encuentran uno, generan un reporte en `ETNube`.

---

## 9. Find My

La función Find My se activa haciendo clic sobre un celular o una tablet.

Al seleccionar la opción `Find My`, se abre una ventana que muestra la información disponible en la nube para esa persona.

En Stage 4, esta ventana se actualiza automáticamente cada 1 segundo.

---

## 10. Trazas

En la ventana Find My se agregaron botones para activar o desactivar la traza de los equipos.

Cuando la traza está activa, el programa guarda las posiciones por las que pasa el dispositivo y dibuja una línea en el mapa.

Al volver a presionar el botón, la traza se oculta.

---

## 11. Play y Pause

En Stage 4 se agregó un menú llamado `Simulation`.

Este menú contiene dos opciones:

* `Play`: continúa la simulación.
* `Pause`: detiene temporalmente la simulación.

---

## 12. Archivo de configuración

El archivo de configuración utilizado es `config.txt`.

Ejemplo:

```text
Placeres.jpg
0.1
3
Pedro 2 1
100 100 20 30 8
maleta 50 170 15 -20 10 mochila 220 130 10 -130 30
305 99 15 150 20
Juan 1 0
200 150 15 -120 20
llaves 250 180 10 -90 10
Diego 2 1
300 200 10 -20 20
llaves 310 205 40 90 30 mochila 330 210 15 -10 20
320 220 15 180 20
```

La imagen `Placeres.jpg` debe estar en la misma carpeta que `config.txt`.

---

## 13. Conclusión

El proyecto permitió aplicar programación orientada a objetos en C++ utilizando Qt.

Se implementó una simulación gráfica con movimiento, rebote, dispositivos rastreables, nube simulada, función Find My, radar visual, trazas y control Play/Pause.

El desarrollo por etapas permitió avanzar de forma incremental hasta obtener una versión final funcional en `stage4`.
