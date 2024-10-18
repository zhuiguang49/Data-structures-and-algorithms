all: List report

List: List.cpp
	g++ List.cpp -o List -std=c++20 -O2

report: report.tex
	xelatex report.tex

clean:
	rm -f List report.pdf *.aux *.log
