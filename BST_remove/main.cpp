#include <iostream>
#include "BinarySearchTree.h"  // 

void testBinarySearchTree() {
    BinarySearchTree<int> bst;

    // 插入一些元素构建树
    std::cout << "Inserting elements to create initial tree:" << std::endl;
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(3);
    bst.insert(7);
    bst.insert(12);
    bst.insert(18);
    bst.printTree();
    
    // 测试删除不存在的元素
    std::cout << "\nTesting removal of non-existent element 20:" << std::endl;
    bst.remove(20);
    bst.printTree();  // 树结构不变

    // 测试删除叶子节点
    std::cout << "\nRemoving leaf node 3:" << std::endl;
    bst.remove(3);
    bst.printTree();

    // 测试删除只有一个子节点的节点
    std::cout << "\nRemoving node 5 (which has one child):" << std::endl;
    bst.remove(5);
    bst.printTree();

    // 测试删除有两个子节点的节点
    std::cout << "\nRemoving node 10 (which has two children):" << std::endl;
    bst.remove(10);
    bst.printTree();

    // 测试删除根节点（当前根节点为 12）
    std::cout << "\nRemoving root node 12:" << std::endl;
    bst.remove(12);
    bst.printTree();

    // 重复删除相同节点
    std::cout << "\nAttempting to remove node 15 twice:" << std::endl;
    bst.remove(15);
    bst.printTree();
    bst.remove(15);  // 再次删除已不存在的节点
    bst.printTree();

    // 清空树并测试是否为空
    std::cout << "\nClearing the entire tree:" << std::endl;
    bst.makeEmpty();
    bst.printTree();

    // 再次验证是否为空
    std::cout << "Is tree empty? " << (bst.isEmpty() ? "Yes" : "No") << std::endl;

    // 插入更多元素进行重复测试，确保树可重复使用
    std::cout << "\nRe-inserting elements to test tree reuse:" << std::endl;
    bst.insert(25);
    bst.insert(20);
    bst.insert(30);
    bst.insert(27);
    bst.insert(35);
    bst.printTree();

    // 删除根节点（再次测试根节点删除情况）
    std::cout << "\nRemoving new root node 25:" << std::endl;
    bst.remove(25);
    bst.printTree();
}

int main() {
    testBinarySearchTree();
    return 0;
}
