# Makefile for Warcraft Simulation

CXX = g++
CXXFLAGS = -std=c++11 -Wall -g

# 列出所有的源文件和目标文件
SOURCES = main.cpp time.cpp city.cpp warrior.cpp headquarter.cpp
OBJECTS = main.o time.o city.o warrior.o headquarter.o

# 可执行文件的名称
TARGET = warcraft_simulation

# 规定如何生成可执行文件
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# 规定如何编译 main.cpp
main.o: main.cpp time.h city.h warrior.h headquarter.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# 规定如何编译 time.cpp
time.o: time.cpp time.h
	$(CXX) $(CXXFLAGS) -c time.cpp

# 规定如何编译 city.cpp
city.o: city.cpp city.h warrior.h headquarter.h time.h
	$(CXX) $(CXXFLAGS) -c city.cpp

# 规定如何编译 warrior.cpp
warrior.o: warrior.cpp warrior.h city.h headquarter.h time.h
	$(CXX) $(CXXFLAGS) -c warrior.cpp

# 规定如何编译 headquarter.cpp
headquarter.o: headquarter.cpp headquarter.h city.h warrior.h time.h
	$(CXX) $(CXXFLAGS) -c headquarter.cpp

# 清理生成的文件
clean:
	rm -f $(OBJECTS) $(TARGET)