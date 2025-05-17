#include "expression_evaluator.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// 从文件读取表达式
void calculateFromFile(const std::string& fileName) {
    std::ifstream inputFile(fileName);
    if (!inputFile) {
        std::cerr << "Error: Unable to open file " << fileName << std::endl;
        return;
    }

    std::cout << "\nCalculating expressions from file: " << fileName << "\n" << std::endl;

    std::string line;
    while (std::getline(inputFile, line)) {
        // 忽略空行
        if (line.empty()) continue;

        Calculator calc;
        calc.setExpression(line);
        calc.calculate();
        std::cout << "Expression: " << line
                  << " -> Result: " << calc.getResult() << std::endl;
    }

    inputFile.close();
}

int main() {
    // 运行文件输入的计算
    calculateFromFile("scientific.in");
    calculateFromFile("negative.in");

    // 用户交互模式
    std::cout << "\nInteractive mode:\n" << std::endl;

    while (true) {
        std::string input;
        std::cout << "Enter an expression (or type 'exit' to quit): ";
        std::getline(std::cin, input);

        if (input == "exit") break;

        Calculator calc;
        calc.setExpression(input);
        calc.calculate();
        std::cout << "Result: " << calc.getResult() << std::endl;
    }

    return 0;
}
