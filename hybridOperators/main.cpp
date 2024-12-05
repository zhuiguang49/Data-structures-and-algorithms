#include "expression_evaluator.h"
#include <iostream>
#include <vector>
#include <string>

// 运行测试用例
void runTestCases() {
    std::vector<std::string> testCases = {
        // 基本运算
        "1+2",              // 3
        "1-2",              // -1
        "2*3",              // 6
        "6/2",              // 3

        // 运算符优先级和括号
        "1+2*3",            // 7
        "(1+2)*3",          // 9
        "1+(2*3)",          // 7
        "(1+(2*3))*4",      // 28

        // 小数
        "1.5+2.25",         // 3.75
        "0.1*0.2",          // 0.02
        "2.5/0.5",          // 5

        // 负数
        "-1+2",             // 1
        "1+(-2)",           // -1
        "-1*(-2)",          // 2
        "1-(-2)",           // 3

        // 科学计数法
        "1e3+2",            // 1002
        "1.2e3-1e2",        // 1100
        "1e-3*1e3",         // 1
        "2.5e2/5",          // 50

        // 负数与连续运算符检测
        "1+-2.1",           // -1.1
        "1++2.1",           // ILLEGAL
        "(1+-2)*3",         // -3
        "-1+(-2.1)",        // -3.1

        // 边界情况
        "0+0",              // 0
        "1/3",              // 0.333333...
        "1/(1+1)",          // 0.5

        // 错误情况
        "1++2",             // ILLEGAL
        "1+2*",             // ILLEGAL
        "(1+2",             // ILLEGAL
        "1+2)",             // ILLEGAL
        "1/0",              // ILLEGAL (division by zero)
        "1..2+3",           // ILLEGAL
        "abc+1",            // ILLEGAL
    };

    std::cout << "Running predefined test cases:\n" << std::endl;
    for (const auto& testCase : testCases) {
        Calculator calc;
        calc.setExpression(testCase);
        calc.calculate();
        std::cout << "Expression: " << testCase 
                  << " -> Result: " << calc.getResult() << std::endl;
    }
}

int main() {
    // 运行预定义的测试用例
    runTestCases();

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
