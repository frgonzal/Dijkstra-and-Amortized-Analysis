# Dijkstra y análisis amortizado

## Ejecutar Proyecto
### Necesario!
El proyecto se construyo en un sistema operativo con linux y se utilizo
la funcionalidad "make" para la compilación y ejecución del proyecto.    
Por lo anterior, es necesario tener la funcionalidad "make" para ejecutar los test y el main.

Se necesita std=c++17.

### Ejecutar
	Uso: make [target] [options]
	Targets:
	    run            Compila y ejecuta archivo main
	    run-exp        Compila y ejecuta archivo experimentation
	    clean          Limpia los archivos generados
	    help           Mensaje de ayuda
	Options:
	    test=1          Ejecutar test que comprueben resultados de la experimentación
	    save=1	        Guardar resultados de la experimentación
	    test-and-save=1 Ejecutar test y guardar resultados

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

