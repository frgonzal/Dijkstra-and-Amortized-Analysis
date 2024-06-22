# Dijkstra y análisis amortizado

## Ejecutar Proyecto
### Necesario!
El proyecto se construyo en un sistema operativo con linux y se utilizo
la funcionalidad "make" para la compilación y ejecución del proyecto.    
Por lo anterior, es necesario tener la funcionalidad "make" para ejecutar los test y el main.

#### Versión del compilador
    g++ (GCC) 14.1.1

#### Versión estándar con la que se compilo
    std=c++17


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


### Ejecutar experimentación de la Tarea
Para ejectuar todos los experimentos de la tarea basta con ejecutar:

    make run-exp

Esto ejectuará la experimentación pedida en la tarea.    
Se crean grafos de $2^i$ vertices y $2^j$ aristas, con $i\in\{10,12,14\}$ y $j\in\{16,...,25\}$.    
Por cada combinación de de $i$ y $j$ se crean 100 grafos distintos y se compara el rendimiento del algoritmo de Dijkstra cuando se utiliza una cola de fibonacci contra el mismo algoritmo cuando se utiliza un heap. 


Si se ejecuta "make run-exp save=1" entonces se guardaran los resultados de lo anterior en un archivo "results.csv", del cual luego se recupera la información para generar graficos comparativos.



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

