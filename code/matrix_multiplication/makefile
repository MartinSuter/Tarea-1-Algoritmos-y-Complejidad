CXX = g++
CXXFLAGS = -O3 -Wall -std=c++17

SRCS = matrix_multiplication.cpp algorithms/naive.cpp algorithms/strassen.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = matrix_multiplication

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)