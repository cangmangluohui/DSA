# 04 查找算法 

## 1. 二分查找 

### 核心思想
基于分治策略，在**有序**数据中每次将搜索区间缩小一半。
- 时间复杂度：O(log N)
- 空间复杂度：O(1) (迭代版)

### 核心避坑指南
1. **防溢出**：计算中点必须使用 `mid = left + (right - left) / 2`，严禁使用 `(left + right) / 2`，防止整数相加溢出。
2. **死循环防范**：循环条件（`left <= right` vs `left < right`）必须与边界更新（`mid + 1` vs `mid`）严格绑定,代码实现采用闭区间。

### 代码模板 
> 完整运行代码见：[binary_search.cpp](../src/04_Searching/binary_search.cpp)
> 二分查找变种代码见[binary_search_variants.cpp](../src/04_Searching/binary_search_variants.cpp)