#include "HeapSort.h" 
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono> // 用于计时
#include <random> // 用于生成随机数
#include <cassert> // 用于断言

// 检查排序是否正确的函数
template<typename T>
bool check(const std::vector<T>& nums) {
    for (size_t i = 1; i < nums.size(); ++i) {
        if (nums[i] < nums[i - 1]) {
            return false; // 如果前一个元素比后一个元素大，排序失败
        }
    }
    return true;
}

// 生成随机序列
std::vector<int> generateRandomSequence(size_t size) {
    std::vector<int> nums(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);

    for (size_t i = 0; i < size; ++i) {
        nums[i] = dis(gen);
    }
    return nums;
}

// 生成有序序列
std::vector<int> generateOrderedSequence(size_t size) {
    std::vector<int> nums(size);
    for (size_t i = 0; i < size; ++i) {
        nums[i] = static_cast<int>(i);
    }
    return nums;
}

// 生成逆序序列
std::vector<int> generateReverseSequence(size_t size) {
    std::vector<int> nums(size);
    for (size_t i = 0; i < size; ++i) {
        nums[i] = static_cast<int>(size - i);
    }
    return nums;
}

// 生成部分重复的序列
std::vector<int> generatePartiallyRepeatedSequence(size_t size) {
    std::vector<int> nums(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100); // 限制重复范围

    for (size_t i = 0; i < size; ++i) {
        nums[i] = dis(gen);
    }
    return nums;
}

// 测试函数
void testSortingPerformance(const std::string& testName, std::vector<int> nums) {
    // 记录堆排序的时间
    auto numsCopy = nums; // 保留原始序列用于 std::sort_heap 对比
    auto start = std::chrono::high_resolution_clock::now();
    heapSort(nums); // 使用自定义的堆排序
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> heapSortTime = end - start;

    // 验证堆排序结果
    assert(check(nums)); // 如果排序不正确，程序会终止

    // 记录 std::sort_heap 的时间
    std::make_heap(numsCopy.begin(), numsCopy.end());
    start = std::chrono::high_resolution_clock::now();
    std::sort_heap(numsCopy.begin(), numsCopy.end());
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> stdSortHeapTime = end - start;

    // 验证 std::sort_heap 的结果
    assert(check(numsCopy));

    // 输出结果
    std::cout << testName << ": \n";
    std::cout << "  HeapSort time: " << heapSortTime.count() << " seconds\n";
    std::cout << "  std::sort_heap time: " << stdSortHeapTime.count() << " seconds\n";
    std::cout << std::endl;
}

int main() {
    constexpr size_t testSize = 1000000; // 测试序列的大小

    // 测试随机序列
    auto randomSeq = generateRandomSequence(testSize);
    testSortingPerformance("Random Sequence", randomSeq);

    // 测试有序序列
    auto orderedSeq = generateOrderedSequence(testSize);
    testSortingPerformance("Ordered Sequence", orderedSeq);

    // 测试逆序序列
    auto reverseSeq = generateReverseSequence(testSize);
    testSortingPerformance("Reverse Sequence", reverseSeq);

    // 测试部分重复序列
    auto partiallyRepeatedSeq = generatePartiallyRepeatedSequence(testSize);
    testSortingPerformance("Partially Repeated Sequence", partiallyRepeatedSeq);

    return 0;
}
