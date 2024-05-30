# Dijkstra y análisis amortizado

## Ejecutar Proyecto
### Necesario!
El proyecto se construyo en un sistema operativo con linux y se utilizo
la funcionalidad "make" para la compilación y ejecución del proyecto.    
Por lo anterior, es necesario tener la funcionalidad "make" para ejecutar los test y el main.

### Comandos para ejecutar el proyecto

    make run
    make run-exp

### Comandos de ayuda

    make help
    make clean

### make run
Este es el archivo para utilizar las distintas funciones creadas.

### make run-exp
Compila y ejecuta el archivo "experimentation", que contiene el código utilizado para la experimentación.
Además, run-exp escribirá las pruebas realizadas en la carpeta "./results".

### make clean
Permite borrar los ejecutables creados.


## Estructura del proyecto

     .
    ├──  build                 ==> archivos ejecutables
    │   ├──  experimentation
    │   ├──  experimentation.o
    │   ├──  main
    │   └──  main.o
    ├──  headers               ==> headers de todo el proyecto
    │   ├──  dijkstra.hpp
    │   ├──  graph.hpp
    │   └──  queue
    │       ├──  fibonacci.hpp
    │       ├──  heap.hpp
    │       └──  priqueue.hpp
    ├──  Makefile              
    ├──  README.md
    ├──  results               ==> carpeta donde se guardan y analizan los resultados
    │   ├──  results.csv
    │   ├── 󰌠 requirements.txt
    │   └──  results.ipynb
    └── 󱧼 src                   ==> archivos cpp con el código del proyecto
        ├──  dijkstra.cpp
        ├──  experimentation.cpp
        ├──  graph.cpp
        ├──  main.cpp
        └──  queue
            ├──  fibonacci.cpp
            └──  heap.cpp


## Resultados

Los resultados de la experimentación se encuentran disponibles en el archivo results.ipynb,
el cual lee los archivos generados por "experimentation" para generar gráficos y figuras con la información
obtenida.    
Para poder ejecutar el .ipynb, se cuenta con un archivo requirements.txt al interior de la carpeta ./resultados con todos los módulos necesarios.

