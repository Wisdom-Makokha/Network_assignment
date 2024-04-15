#Makefile for compiling main.c, functions.c and definitions.h

#Compiler
CC = g++

#Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17

#Source files
SRCS = functions.cpp main.cpp

# Header file
HEADERS = definitions.h

#Object files
OBJS = $(SRCS:.cpp=.o)

#Target executable
TARGET = standalone

#Default target
all: $(TARGET)

#Compile object files
%.o: %.cpp $(HEADERS)
		$(CXX) $(CXXFLAGS) -c $< -o $@

#Link object files to create the executable
$(TARGET): $(OBJS)
		$(CXX) $(CXXFLAGS) $(OBJS) -o $@

clean:
		rm -f $(OBJS) $(TARGET)