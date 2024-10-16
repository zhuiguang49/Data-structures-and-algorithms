#include "List.h"
#include <iostream>

int main()
{
    // 1. 创建 List 对象并测试 push_back
    List<int> lst;
    for (int i = 0; i < 5; ++i) {
        lst.push_back(i);
    }

    // 2. 使用迭代器向后遍历
    std::cout << "Forward traversal: ";
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        std::cout << *it << " ";  // 输出 0 1 2 3 4
    }
    std::cout << std::endl;

    // 3. 使用迭代器向前遍历
    std::cout << "Backward traversal: ";
    for (auto it = --lst.end(); it != --lst.begin(); --it) {
        std::cout << *it << " ";  // 输出 4 3 2 1 0
    }
    std::cout << std::endl;

    // 4. 测试 push_front
    lst.push_front(2024);
    std::cout << "After push_front: " << lst.front() << std::endl;  // 输出 2024

    // 5. 测试 pop_back 和 pop_front
    lst.pop_back();
    std::cout << "After pop_back: ";
    for (auto it : lst) {
        std::cout << it << " ";  // 输出 2024 0 1 2 3
    }
    std::cout << std::endl;

    lst.pop_front();
    std::cout << "After pop_front: " << lst.front() << std::endl;  // 输出 0

    // 6. 测试 size 和 empty
    std::cout << "List size: " << lst.size() << std::endl;  // 输出 4
    std::cout << "List is empty: " << std::boolalpha << lst.empty() << std::endl;  // 输出 false

    // 7. 测试 insert
    auto it = lst.begin();
    ++it;
    lst.insert(it, 2024);  // 在第二个位置插入2024
    std::cout << "After insert: ";
    for (auto it : lst) {
        std::cout << it << " ";  // 输出 0 2024 1 2 3
    }
    std::cout << std::endl;

    // 8. 测试 erase
    lst.erase(--lst.end());  // 删除最后一个元素
    std::cout << "After erase: ";
    for (auto it : lst) {
        std::cout << it << " ";  // 输出 0 2024 1 2
    }
    std::cout << std::endl;

    // 9. 测试 clear
    lst.clear();
    std::cout << "After clear, list size: " << lst.size() << std::endl;  // 输出 0
    std::cout << "List is empty after clear: " << std::boolalpha << lst.empty() << std::endl;  // 输出 true

    // 10. 测试拷贝构造函数
    List<int> lst2 = {10, 20, 30};
    List<int> lst3(lst2);
    std::cout << "List3 (copy of list2): ";
    for (auto it : lst3) {
        std::cout << it << " ";  // 输出 10 20 30
    }
    std::cout << std::endl;

    // 11. 测试移动构造函数
    List<int> lst4 = std::move(lst2);
    std::cout << "List4 (moved from list2): ";
    for (auto it : lst4) {
        std::cout << it << " ";  // 输出 10 20 30
    }
    std::cout << std::endl;

    // 12. 定义 lst5
    List<int> lst5 = {10, 20, 30};

    // 13. 测试移动赋值运算符
    List<int> lst6 = {60, 70};
    lst6 = std::move(lst5);  // 移动赋值
    std::cout << "List6 after move assignment: ";
    for (auto it : lst6) {
        std::cout << it << " ";  // 输出 10 20 30
    }
    std::cout << std::endl;

    // 14. 测试 erase(iterator from, iterator to)
    List<int> lst7 = {1, 2, 3, 4, 5};
    auto it1 = lst7.begin();
    auto it2 = it1;
    for (int i = 0; i < 3; ++i) {
        ++it2;  // 手动前进迭代器3次
    }
    lst7.erase(it1, it2);  // 删除前3个元素
    std::cout << "List7 after range erase: ";
    for (auto it : lst7) {
        std::cout << it << " ";  // 输出 4 5
    }
    std::cout << std::endl;

    // 15. 测试拷贝赋值运算符
    List<int> lst8 = {40, 50};
    lst8 = lst3;  // 拷贝赋值
    std::cout << "List8 after copy assignment: ";
    for (auto it : lst8) {
        std::cout << it << " ";  // 输出 10 20 30
    }
    std::cout << std::endl; 

    return 0;
}
