CXX = g++
# Usamos -O3 para máxima optimización, fundamental en Análisis de Algoritmos
CXXFLAGS = -O3 -Wall -std=c++17

SRCS = sorting.cpp algorithms/sort.cpp algorithms/mergesort.cpp algorithms/quicksort.cpp algorithms/patiencesort.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = sorting

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)