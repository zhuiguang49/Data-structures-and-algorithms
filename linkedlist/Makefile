CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGET = linkedlist
SRC = main.cpp
HEADER = LinkedList.h
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

# 链接目标
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)


%.o: %.cpp $(HEADER)
	$(CXX) $(CXXFLAGS) -c $<

# 清理目标
clean:
	rm -f $(OBJ) $(TARGET)

# 重建目标
rebuild: clean all
