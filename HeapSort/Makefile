# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall

# Targets
TARGET = test
SOURCES = test.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Report-related files
REPORT_SRC = report.tex
REPORT_PDF = report.pdf

# Default target: build the test executable
all: $(TARGET)

# Compile the test executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Generate the report
report: $(REPORT_SRC)
	xelatex $(REPORT_SRC)

# Clean up the build files, excluding .pdf
clean:
	rm -f $(TARGET) $(OBJECTS) report.aux report.log

# Phony targets
.PHONY: all clean report
