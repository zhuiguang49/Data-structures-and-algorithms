CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

# LaTeX compiler and flags
LATEX = xelatex
LATEXFLAGS = -interaction=nonstopmode -shell-escape

# Target executable name
TARGET = test

# Source files
SOURCES = test.cpp
HEADERS = BST.h

# LaTeX files
TEXSOURCE = report.tex
PDFOUTPUT = report.pdf

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(TARGET)

# Link the target executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Compile source files to object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# LaTeX compilation rule
report: $(TEXSOURCE)
	$(LATEX) $(LATEXFLAGS) $(TEXSOURCE)
	$(LATEX) $(LATEXFLAGS) $(TEXSOURCE)  # Run twice for references

# Clean target (不删除 PDF)
clean:
	rm -f $(OBJECTS) $(TARGET)
	rm -f *.aux *.log *.out *.toc *.synctex.gz

# Clean all files including PDFs
cleanall:
	rm -f $(OBJECTS) $(TARGET)
	rm -f *.aux *.log *.out *.toc *.synctex.gz
	rm -f *.pdf *.fls *.fdb_latexmk

# Run target
run: $(TARGET)
	./$(TARGET)

# Run target with time measurement
time: $(TARGET)
	time ./$(TARGET)	

.PHONY: all clean cleanall run report time