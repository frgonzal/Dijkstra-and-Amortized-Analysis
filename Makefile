CC = g++

## agregar flags? como -g o -Wall
CFLAGS = -std=c++17 -Wall

## agregar librerias extra
LDLIBS=

TARGET=./build/main
TEST=./build/experimentation

## AQUI INCLUIR LOS ARCHIVOS .C 
## excepto main y test
## agregar un "\" al final de cada nombre
SRC = \
	src/dijkstra.cpp \
	src/graph.cpp \
	src/queue/fibonacci.cpp \
	src/queue/heap.cpp


## nombre de los headers (automatico)
HDRS = $(wildcard headers/*.hpp)
## nombre de los .o (automatico)
OBJS = $(SRC:./src/%.cpp=./build/%.o)



all:
	@echo " MTree implementation proyect"
	@echo ""
	@echo " use \"make help\" to get more info"

## Compila un .o a partir del src
./build/%.o: ./src/*/%.cpp $(HDRS)
	@ $(CC) $(CFLAGS)  -c $< -o $@

## Compila un .o a partir del src
./build/%.o: ./src/%.cpp $(HDRS)
	@ $(CC) $(CFLAGS)  -c $< -o $@

## Compila el ejecutable del main y ejecuta
.PHONY: run
run: $(OBJS) $(TARGET).o
	@ $(CC) $(CFLAGS) $^ -o $(TARGET) $(LDLIBS) && $(TARGET)

## Compila el ejecutable de los test y ejecuta
.PHONY: run-exp
run-exp: $(OBJS) $(TEST).o
	@ $(CC) $(CFLAGS) $^ -o $(TEST) $(LDLIBS)
ifeq ($(test-and-save), 1) 
	@ $(TEST) --test --save
else ifeq ($(save), 1) 
	@ $(TEST) --save
else ifeq ($(test), 1) 
	@ $(TEST) --test
else
	@ $(TEST)
endif

make zip:
	zip -r Tarea2.zip 									\
		./build/ ./headers/ ./src/	 					\
		./results/img/ ./results/requirements.txt 		\
		./results/results.csv ./results/results.ipynb 	\
		./Makefile ./README.md 							\
		./Informe.pdf

## borra todo lo que se compilo
.PHONY: clean
clean: $(wildcard build/*.o)
	@ rm -f $(TARGET)
	@ rm -f $(TEST)
	@ rm -f $^

.PHONY: help
help:
	@echo "Usage: make [target] [options]"
	@echo "Targets:"
	@echo "  run            Build and run the main program"
	@echo "  run-exp        Build and run the experimentation program"
	@echo "  clean          Clean the build files"
	@echo "  help           Display this help message"
	@echo "Options:"
	@echo "  test=1   		Test the experimentation results"
	@echo "  save=1	  	Save the time results"
	@echo "  test-and-save=1	Test the experimentation results and save the time results"