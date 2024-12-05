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

    /**
     * @brief 设置需要计算的中缀表达式
     * @param expr 输入的中缀表达式字符串
     */
    void setExpression(const std::string &expr);

    /**
     * @brief 执行表达式的计算，包括格式化、合法性检查、后缀表达式转换和求值
     */
    void calculate();
    
    /**
     * @brief 获取计算结果
     * @return 如果表达式非法，返回 "ILLEGAL"，否则返回计算结果
     */
    std::string getResult() const;

private:
    std::string infix;             // 原始表达式
    std::string formattedInfix;    // 格式化后的表达式
    std::vector<std::string> postfix; // 后缀表达式
    double result;                 // 计算结果
    bool isError;                  // 是否发生错误

    // 私有辅助函数
    /**
     * @brief 格式化中缀表达式，补全缺失信息（如负号前补0）
     */
    void formatExpression();

    /**
     * @brief 检查中缀表达式是否合法
     * @return 合法返回 true，非法返回 false
     */
    bool isValidExpression();

    /**
     * @brief 获取运算符的优先级
     * @param op 运算符
     * @return 运算符的优先级（数字越大优先级越高）
     */
    int getPriority(char op);

    /**
     * @brief 将中缀表达式转换为后缀表达式
     * @details 使用栈来管理运算符优先级和括号匹配
     */
    void infixToPostfix();

    /**
     * @brief 对两个操作数和运算符执行具体计算
     * @param a 第一个操作数
     * @param b 第二个操作数
     * @param op 运算符
     * @return 运算结果，如果运算非法（如除零），则标记为错误
     */
    double applyOperation(double a, double b, char op);

    /**
     * @brief 计算后缀表达式的值
     * @details 逐步扫描后缀表达式，数字压栈，遇到运算符则弹出两个操作数进行运算
     */
    void evaluatePostfix();

    /**
     * @brief 标记当前表达式为非法状态
     */
    void setError(); 

    // 工具函数
    /**
     * @brief 判断字符是否是运算符
     * @param c 输入字符
     * @return 如果是运算符返回 true，否则返回 false
     */
    static bool isOperator(char c);

    /**
     * @brief 判断字符是否是数字或小数点
     * @param c 输入字符
     * @return 如果是数字或小数点返回 true，否则返回 false
     */
    static bool isDigitOrDot(char c);
};


// 实现

void Calculator::setExpression(const std::string &expr) {
    infix = expr;
    isError = false;// 重置错误状态
}

// 格式化表达式
void Calculator::formatExpression() {
    formattedInfix = infix;

    // 删除所有空格，确保格式化的表达式无多余字符
    formattedInfix.erase(remove(formattedInfix.begin(), formattedInfix.end(), ' '), formattedInfix.end());

    // 如果表达式以 `-` 开头，补充一个 0，使其成为 "0-..."
    if (formattedInfix.empty()) {
        setError();// 空表达式标记为错误
        return;
    }
    if (formattedInfix[0] == '-') {
        formattedInfix.insert(0, "0");
    }

    // 在 "( -" 或 "+(-" 这样的情况后插入 0，处理负数情况
    for (size_t i = 1; i < formattedInfix.size(); ++i) {
        if ((formattedInfix[i] == '-' && formattedInfix[i - 1] == '(') ||
            (formattedInfix[i] == '-' && isOperator(formattedInfix[i - 1]))) {
            formattedInfix.insert(i, "0");
        }
    }
}

// 检查表达式是否合法
bool Calculator::isValidExpression() {
    int bracketCount = 0; // 记录括号的平衡状态

    for (size_t i = 0; i < formattedInfix.size(); ++i) {
        char c = formattedInfix[i];

        // 如果是数字或科学计数法符号，则跳过检查
        if (isdigit(c) || c == '.' || c == 'e' || c == 'E') {
            continue; // 数字和科学计数法
        } else if (c == '(') {
            ++bracketCount; // 遇到左括号增加计数
        } else if (c == ')') {
            --bracketCount;  // 遇到右括号减少技术
            if (bracketCount < 0) return false; // 如果右括号多余左括号，非法
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
        // 如果是数学或科学计数法的符号，直接加入字符串
        if (isdigit(c) || c == '.' || c == 'e' || c == 'E') {
            number += c; // 读取数字或科学计数法
        } else {
            // 完成一个数字加入后缀表达式
            if (!number.empty()) {
                postfix.push_back(number);
                number.clear();
            }

            if (c == '(') {
                operators.push(c); // 左括号直接入栈
            } else if (c == ')') {
                // 右括号弹出栈内运算符直至匹配左括号
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

    // 如果有剩余数字，加入后缀表达式
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
