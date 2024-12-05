#ifndef EXPRESSION_EVALUATOR_H
#define EXPRESSION_EVALUATOR_H

#include <stack>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <cstdlib>
#include <cmath>

class Calculator {
public:
    Calculator() : result(0.0), isError(false) {}

    // 核心接口
    void setExpression(const std::string &expr);
    void calculate();
    std::string getResult() const;

private:
    std::string infix;             // 原始表达式
    std::string formattedInfix;    // 格式化后的表达式
    std::vector<std::string> postfix; // 后缀表达式
    double result;                 // 计算结果
    bool isError;                  // 是否发生错误

    // 私有辅助函数
    void formatExpression();
    bool isValidExpression();
    int getPriority(char op);
    void infixToPostfix();
    double applyOperation(double a, double b, char op);
    void evaluatePostfix();
    void setError(); // 设置错误状态

    // 工具函数
    static bool isOperator(char c);
    static bool isDigitOrDot(char c);
};

// 设置表达式
void Calculator::setExpression(const std::string &expr) {
    infix = expr;
    isError = false;
}

// 格式化表达式
void Calculator::formatExpression() {
    formattedInfix = infix;
    formattedInfix.erase(remove(formattedInfix.begin(), formattedInfix.end(), ' '), formattedInfix.end());

    // 如果表达式以 `-` 开头，补充 0
    if (formattedInfix.empty()) {
        setError();
        return;
    }
    if (formattedInfix[0] == '-') {
        formattedInfix.insert(0, "0");
    }

    // 在 `(-` 或 `+(-` 的情况下，补充 0
    for (size_t i = 1; i < formattedInfix.size(); ++i) {
        if ((formattedInfix[i] == '-' && formattedInfix[i - 1] == '(') ||
            (formattedInfix[i] == '-' && isOperator(formattedInfix[i - 1]))) {
            formattedInfix.insert(i, "0");
        }
    }
}

// 检查表达式是否合法
bool Calculator::isValidExpression() {
    int bracketCount = 0;

    for (size_t i = 0; i < formattedInfix.size(); ++i) {
        char c = formattedInfix[i];

        if (isdigit(c) || c == '.' || c == 'e' || c == 'E') {
            continue; // 数字和科学计数法
        } else if (c == '(') {
            ++bracketCount;
        } else if (c == ')') {
            --bracketCount;
            if (bracketCount < 0) return false; // 括号不匹配
        } else if (isOperator(c)) {
            if (i == 0 || i == formattedInfix.size() - 1 || isOperator(formattedInfix[i + 1])) {
                return false; // 运算符不能出现在开头、结尾或连续出现
            }
        } else {
            return false; // 非法字符
        }
    }

    return bracketCount == 0; // 括号匹配
}

// 获取运算符优先级
int Calculator::getPriority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// 中缀转后缀表达式
void Calculator::infixToPostfix() {
    std::stack<char> operators;
    std::string number;

    for (size_t i = 0; i < formattedInfix.size(); ++i) {
        char c = formattedInfix[i];

        if (isdigit(c) || c == '.' || c == 'e' || c == 'E') {
            number += c; // 读取数字或科学计数法
        } else {
            if (!number.empty()) {
                postfix.push_back(number);
                number.clear();
            }

            if (c == '(') {
                operators.push(c);
            } else if (c == ')') {
                while (!operators.empty() && operators.top() != '(') {
                    postfix.push_back(std::string(1, operators.top()));
                    operators.pop();
                }
                if (operators.empty()) {
                    setError(); // 括号不匹配
                    return;
                }
                operators.pop(); // 弹出 '('
            } else if (isOperator(c)) {
                while (!operators.empty() && getPriority(operators.top()) >= getPriority(c)) {
                    postfix.push_back(std::string(1, operators.top()));
                    operators.pop();
                }
                operators.push(c);
            }
        }
    }

    if (!number.empty()) {
        postfix.push_back(number);
    }

    while (!operators.empty()) {
        if (operators.top() == '(') {
            setError(); // 括号不匹配
            return;
        }
        postfix.push_back(std::string(1, operators.top()));
        operators.pop();
    }
}

// 计算后缀表达式
void Calculator::evaluatePostfix() {
    std::stack<double> values;

    for (const auto &token : postfix) {
        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1) || token.find('e') != std::string::npos) {
            values.push(std::stod(token)); // 转为数字
        } else {
            if (values.size() < 2) {
                setError();
                return;
            }
            double b = values.top(); values.pop();
            double a = values.top(); values.pop();
            values.push(applyOperation(a, b, token[0]));
        }
    }

    if (values.size() != 1) {
        setError();
    } else {
        result = values.top();
    }
}

// 应用运算符
double Calculator::applyOperation(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return (b == 0) ? (setError(), 0) : a / b;
        default: setError(); return 0;
    }
}

// 设置错误状态
void Calculator::setError() {
    isError = true;
}

// 核心计算方法
void Calculator::calculate() {
    formatExpression();
    if (isError || !isValidExpression()) {
        isError = true;
        return;
    }
    infixToPostfix();
    if (!isError) evaluatePostfix();
}

// 获取结果
std::string Calculator::getResult() const {
    return isError ? "ILLEGAL" : std::to_string(result);
}

// 判断是否是运算符
bool Calculator::isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// 判断是否是数字或小数点
bool Calculator::isDigitOrDot(char c) {
    return isdigit(c) || c == '.';
}

#endif // EXPRESSION_EVALUATOR_H
