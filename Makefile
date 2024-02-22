# Se determina el OS y se asignan las variables acordemente.
ifeq ($(OS), Windows_NT)
	terminacion = exe
	cleanCommand = del
	empty = 
	SRCDIR = src\$(empty)
else
	terminacion = out
	cleanCommand = rm -f
	SRCDIR = src/
endif

# Regla para compilar e iniciar el programa.
all: build run

# Nombre del programa de salida
TARGET = programa.$(terminacion)

# Compilador de C++
CXX = g++

# Opciones de compilación
CXXFLAGS = -Wall -std=c++11

# Se obtienen todos los archivos fuente.
ARCHIVOS_SRC = $(wildcard src/*.cpp)


# Se hace cambio al directorio de cada archivo (Solo cambia en caso de ser Windows).
SOURCES = $(addprefix $(SRCDIR),$(notdir $(ARCHIVOS_SRC)))

# Lista de archivos objeto generados a partir de los archivos fuente
OBJECTS_SRC = $(SOURCES:.cpp=.$(terminacion))

# Regla para compilar los archivos fuente en archivos objeto.
%.$(terminacion): %.cpp 
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para compilar el programa a partir de los archivos objeto.
$(TARGET): $(OBJECTS_SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS_SRC)

# Compila el ejecutable.
build: $(TARGET)

# Regla para iniciar el programa
run:
	./$(TARGET)

# Regla para limpiar los archivos generados.
.PHONY: clean
clean:
	$(cleanCommand) $(TARGET) $(OBJECTS_SRC)