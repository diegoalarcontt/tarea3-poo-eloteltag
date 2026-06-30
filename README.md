# Tarea 3 - Simulador EloTelTags y Find My

## Descripción

Este proyecto corresponde a la Tarea 3 de Diseño y Programación Orientados a Objetos.

El programa fue desarrollado en C++ utilizando Qt. La aplicación simula un sistema parecido a Find My, donde existen celulares, EloTelTags y tablets que se mueven dentro de un territorio representado por una imagen de fondo.

Los equipos se cargan desde un archivo de configuración llamado `config.txt`. Durante la simulación, los dispositivos se mueven, rebotan en los bordes, detectan celulares cercanos y guardan información en una nube simulada llamada `ETNube`.

---

## Tecnologías utilizadas

* C++
* Qt Creator
* Qt Widgets
* CMake
* Git / GitHub

---

## Estructura del proyecto

```text
stage1/
stage2/
stage3/
stage4/
config.txt
Placeres.jpg
README.md
DOCUMENTACION.md
DIAGRAMA_UML.md
```

Cada carpeta representa una etapa incremental del desarrollo.

---

## Etapas desarrolladas

## Stage 1

En esta etapa se implementó la lectura del archivo de configuración y se mostraron solamente los celulares en el territorio.

Funcionalidades:

* Lectura de `config.txt`.
* Carga de la imagen de fondo.
* Creación de celulares.
* Visualización de celulares en pantalla.

---

## Stage 2

En esta etapa se agregaron los EloTelTags y las tablets.

Funcionalidades:

* Lectura completa del archivo de configuración.
* Creación de celulares, tags y tablets.
* Movimiento automático de los equipos.
* Rebote en los bordes del territorio.
* Visualización de todos los equipos.

Colores utilizados:

* Celulares: azul.
* EloTelTags: rojo.
* Tablets: verde.

---

## Stage 3

En esta etapa se agregó la nube simulada y la función Find My básica.

Funcionalidades:

* Clase `ETNube`.
* Detección de celulares cercanos.
* Reportes hacia la nube.
* Radar visual en tags y tablets.
* Menú emergente con opción `Find My`.
* Visualización de reportes guardados en la nube.

---

## Stage 4

Esta es la versión final del proyecto.

Funcionalidades:

* Menú `Simulation`.
* Opción `Play`.
* Opción `Pause`.
* Ventana `Find My` actualizada cada 1 segundo.
* Radar visual.
* Trayectorias o trazas de los equipos.
* Botones para mostrar u ocultar la traza.
* Movimiento y rebote de todos los equipos.
* Simulación completa con celulares, EloTelTags y tablets.

---

## Clases principales

## Equipo

Clase base del proyecto. Contiene los datos comunes de todos los dispositivos, como posición, rapidez, ángulo, movimiento, rebote y traza.

## Cellular

Representa el celular de una persona.

## EloTelTag

Representa un dispositivo de rastreo asociado a una persona.

## Tablet

Representa una tablet asociada a una persona.

## Territory

Se encarga de leer el archivo de configuración y guardar los celulares, tags y tablets.

## TerritoryView

Se encarga de dibujar el mapa, los equipos, el radar, las trayectorias y el menú Find My.

## ETNube

Simula una nube donde se guardan los reportes cuando un tag o una tablet detecta un celular cercano.

---

## Archivo de configuración

El programa utiliza un archivo llamado `config.txt`.

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

La primera línea corresponde a la imagen de fondo. La imagen debe estar en la misma carpeta que el archivo `config.txt`.

---

## Cómo ejecutar el proyecto

1. Abrir Qt Creator.
2. Seleccionar `Open File or Project`.
3. Abrir el archivo:

```text
stage4/CMakeLists.txt
```

4. Seleccionar el kit de compilación:

```text
Desktop Qt MinGW 64-bit
```

5. Presionar `Run`.
6. Cuando se abra el selector de archivos, elegir:

```text
config.txt
```

---

## Controles

## Menú Simulation

* `Play`: inicia o continúa la simulación.
* `Pause`: pausa la simulación.

## Find My

Para usar Find My:

1. Hacer clic sobre un celular o una tablet.
2. Seleccionar la opción `Find My`.
3. Se abre una ventana con los reportes disponibles.
4. La ventana se actualiza automáticamente cada 1 segundo.

## Trazas

Dentro de la ventana Find My aparecen botones para activar o desactivar la traza de los equipos.

La traza muestra el recorrido que sigue el equipo desde el momento en que se activa.

---

## Consideraciones

* Para que se vea el mapa, la imagen `Placeres.jpg` debe estar en la misma carpeta que `config.txt`.
* Si no aparece un reporte para una persona, puede ser porque sus dispositivos no han pasado cerca de ningún celular.
* El radio de detección usado es de 50 píxeles.
* La simulación se ejecuta hasta que se cierre la ventana principal.

---

## Autores

Diego Alarcón / Ivan Carlsson / Joaquin Cordero

---

## Estado final

El proyecto cumple con las funcionalidades principales solicitadas:

* Lectura de configuración.
* Visualización gráfica.
* Movimiento de equipos.
* Rebote en bordes.
* Detección de celulares cercanos.
* Nube simulada.
* Find My.
* Play/Pause.
* Trazas de equipos.
