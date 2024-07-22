# Dijkstra and Amortized Analysis

## Running the Project
### Required!
The project was built on a Linux operating system and used the "make" functionality for compiling and running the project.  
Therefore, it is necessary to have the "make" functionality to run the tests and the main program.

#### Compiler Version
    g++ (GCC) 14.1.1

#### Standard Version Used for Compilation
    std=c++17

### Running
    Usage: make [target] [options]
    Targets:
        run            Compiles and runs the main file
        run-exp        Compiles and runs the experimentation file
        clean          Cleans up generated files
        help           Help message
    Options:
        test=1          Run tests to check the results of the experimentation
        save=1          Save the results of the experimentation
        test-and-save=1 Run tests and save results

### Running Task Experimentation
To execute all the experiments for the task, simply run:

    make run-exp

This will execute the requested experimentation for the task.  
Graphs with $2^i$ vertices and $2^j$ edges are created, with $i\in\{10,12,14\}$ and $j\in\{16,...,25\}$.  
For each combination of $i$ and $j$, 100 distinct graphs are created, and the performance of Dijkstra's algorithm is compared when using a Fibonacci queue against the same algorithm when using a heap.

If you run "make run-exp save=1", the results will be saved in a "results.csv" file, from which information will later be retrieved to generate comparative graphs.

## Project Structure

     .
    ├──  build                 ==> executable files
    │   ├──  experimentation
    │   ├──  experimentation.o
    │   ├──  main
    │   └──  main.o
    ├──  headers               ==> headers for the entire project
    │   ├──  dijkstra.hpp
    │   ├──  graph.hpp
    │   └──  queue
    │       ├──  fibonacci.hpp
    │       ├──  heap.hpp
    │       └──  priqueue.hpp
    ├──  Makefile              
    ├──  README.md
    ├──  results/              ==> folder where results are saved and analyzed
    └── 󱧼 src                   ==> cpp files with the project code
        ├──  dijkstra.cpp
        ├──  experimentation.cpp
        ├──  graph.cpp
        ├──  main.cpp
        └──  queue
            ├──  fibonacci.cpp
            └──  heap.cpp