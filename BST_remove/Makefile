# 指定编译器
CXX = g++

# 编译器标志
CXXFLAGS = -Wall -g

# 可执行文件名称
TARGET = bst_test

# 源文件和头文件
SOURCES = main.cpp
HEADERS = BinarySearchTree.h

# 报告文件
REPORT_SRC = report.tex
REPORT_PDF = report.pdf

# 默认目标：无操作提示
all:
	@echo "请使用 'make run' 编译和运行程序，或 'make report' 编译报告。"

# 目标：编译并运行测试程序
run: $(TARGET)
	@echo "编译程序并运行测试："
	./$(TARGET)

# 目标：编译测试程序
$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# 目标：生成报告 PDF 使用 xelatex 编译
report: $(REPORT_SRC)
	@echo "生成实验报告 PDF："
	xelatex $(REPORT_SRC) >/dev/null
	xelatex $(REPORT_SRC) >/dev/null  # 编译两次确保目录引用正确

# 清理编译文件和临时文件
clean:
	rm -f $(TARGET) *.aux *.log *.out *.toc

# 清理所有生成的文件，包括报告
distclean: clean
	rm -f $(REPORT_PDF)
