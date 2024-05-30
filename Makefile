CC = g++

## agregar flags? como -g o -Wall
CFLAGS =

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
run: $(OBJS) $(TARGET).o
	@ $(CC) $(CFLAGS) $^ -o $(TARGET) $(LDLIBS) && $(TARGET)

## Compila el ejecutable de los test y ejecuta
run-exp: $(OBJS) $(TEST).o
	@ $(CC) $(CFLAGS) $^ -o $(TEST) $(LDLIBS) && $(TEST)

## borra todo lo que se compilo
clean: $(wildcard build/*.o)
	@ rm -f $(TARGET)
	@ rm -f $(TEST)
	@ rm -f $^


help:
	@echo "	make run:	compiles and runs the main file"
	@echo "	make run-exp:	compiles and runs the experimentation file"
	@echo "	make clean:	deletes all the compiled files"