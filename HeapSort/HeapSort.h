#ifndef HEAP_SORT_H
#define HEAP_SORT_H
#include <vector>
#include <algorithm>


/* 我和老妖采取的策略不太一样，我选择将0作为根节点的索引，因此左子结点
和右子节点的索引分别为2*i+1, 2*i+2*/

template<typename T>
// 这个函数用来执行堆化操作，这里我们采用的是大顶堆（最大堆）
void siftDown(std::vector<T> &nums, int n, int i){// 参数n是堆的有效长度，i是执行堆化操作的初始节点的索引
    while(true){
        // l即左子结点索引，r即右子节点索引，ma为较大子节点的索引
        int l = 2*i+1, r = 2*i+2, ma = i;

        // l索引没有越界且左子节点大于根节点时，记ma=l
        if(l < n && nums[l] > nums[ma]){
            ma = l;
        }
        // r索引没有越界且右子节点更大时，记ma=r
        if(r < n && nums[r] > nums[ma]){
            ma = r;
        }

        if (ma == i) break; // 如果当前节点已经是最大值，退出循环

        // 交换以修正满足堆性质
        std::swap(nums[i], nums[ma]);
        // 循环进行堆化操作
        i = ma;
    }
}

template<typename T>
void heapSort(std::vector<T> &nums){
    if (nums.empty()) return; // 如果数组为空，直接返回

    // 首先我们需要完成建堆操作，这里我们采取遍历序列建堆的方法
    for(int i = (nums.size()/2)-1; i >= 0; --i){ //由最后一个叶节点求出最后一个非叶节点的索引
        siftDown(nums, nums.size(), i); // 遍历非叶结点进行堆化操作
    }

    //提取最大元素完成堆排序
    for(int i = nums.size()-1; i > 0; --i){
        std::swap(nums[0], nums[i]); // 交换首尾元素
        siftDown(nums, i, 0);   // 堆化修复使其满足堆性质
    }
}

#endif // HEAP_SORT_H