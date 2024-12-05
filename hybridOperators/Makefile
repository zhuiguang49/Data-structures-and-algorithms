# 编译器和选项
CXX = g++
CXXFLAGS = -std=c++11 -Wall
LATEX = pdflatex
TARGET = evaluator
SRC = main.cpp
REPORT_SRC = report.tex
REPORT_PDF = report.pdf

# 默认目标
all: $(TARGET)

# 编译程序
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Generate the report
report: $(REPORT_SRC)
	xelatex $(REPORT_SRC)

# Clean up the build files, excluding .pdf
clean:
	rm -f $(TARGET) $(OBJECTS) report.aux report.log

# Phony targets
.PHONY: all clean report
