# 二分搜索

## 二分搜索模板

给一个**有序数组**和目标值，找第一次/最后一次/任何一次出现的索引，如果没有出现返回-1

模板**四点**要素

- 1、初始化：start=0、end=len-1
- 2、循环退出条件：start + 1 < end
- 3、比较中点和目标值：A[mid] ==、 <、> target
- 4、判断最后两个元素是否符合：A[start]、A[end] ? target

时间复杂度 O(logn)，使用场景一般是有序数组的查找

典型示例

[binary-search](https://leetcode-cn.com/problems/binary-search/)

> 给定一个  n  个元素有序的（升序）整型数组  nums 和一个目标值  target  ，写一个函数搜索  nums  中的 target，如果目标值存在返回下标，否则返回 -1。

```cpp
// 二分搜索最常用模板
int search(vector<int>& nums, int target) {
    if(nums.empty()) return -1;

    int left = 0, right = nums.size() - 1;
    //处理循环
    while(left + 1 < right){
        int middle = left + (right - left) / 2;
        if(nums[middle] == target) return middle;
        else if(nums[middle] < target) left = middle;  //比较middle跟target的值
        else right = middle;
    }
    
    //最后还剩下left right两个值，做单独判断
    if(nums[left] == target) return left;
    if(nums[right] == target) return right;

    return -1;
}
```

大部分二分查找类的题目都可以用这个模板，然后做一点特殊逻辑即可

另外二分查找还有一些其他模板如下图，大部分场景模板#3 都能解决问题，而且还能找第一次/最后一次出现的位置，应用更加广泛

![binary_search_template](https://img.fuiboom.com/img/binary_search_template.png)

所以用模板#3 就对了，详细的对比可以这边文章介绍：[二分搜索模板](https://leetcode-cn.com/explore/learn/card/binary-search/212/template-analysis/847/)

如果是最简单的二分搜索，不需要找第一个、最后一个位置、或者是没有重复元素，可以使用模板#1，代码更简洁

```cpp
// 无重复元素搜索时，更方便
int search(vector<int>& nums, int target) {
    if(nums.empty()) return -1;
    int left = 0, right = nums.size() - 1;
    //处理循环
    while(left <= right){
        int middle = left + (right - left) / 2;
        if(nums[middle] == target) return middle;
        else if(nums[middle] < target) left = middle-1;  //比较middle跟target的值
        else right = middle+1;
    }

    // 如果找不到，start 是第一个大于target的索引
    // 如果在B+树结构里面二分搜索，可以return start
    // 这样可以继续向子节点搜索，如：node:=node.Children[start]
    return -1
}
```

## 常见题目

### [search-for-range](https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array/)

> 给定一个包含 n 个整数的排序数组，找出给定目标值 target 的起始和结束位置。
> 如果目标值不在数组中，则返回`[-1, -1]`

思路：核心点就是找第一个 target 的索引，和最后一个 target 的索引，所以用两次二分搜索分别找第一次和最后一次的位置

```cpp
vector<int> searchRange(vector<int>& nums, int target) {
    if(nums.empty()) return {-1, -1};
    int low = findTarget(nums, target, true);
    if(low == -1) return {-1, -1};
    int high = findTarget(nums, target, false);
    return {low, high};
}

int findTarget(vector<int>& nums, int target, bool findLeft){
    int left = 0, right = nums.size() - 1;
    while(left + 1 < right){
        int middle = left + (right - left)/2;
        if(nums[middle] < target) left = middle;
        else if(nums[middle] > target) right = middle;
        else{
            if(findLeft) right = middle;
            else left = middle;
        }
    }

    if(findLeft) {
        if(nums[left] == target) return left;
        else if(nums[right] == target) return right;
        else return -1;
    }
    else{
        if(nums[right] == target) return right;
        else if(nums[left] == target) return left;
        else return -1;
    }

}
```

### [search-insert-position](https://leetcode-cn.com/problems/search-insert-position/)

> 给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。

```cpp
int searchInsert(vector<int>& nums, int target) {
    if(nums.empty()) return 0;
    int left = 0, right = nums.size() - 1;

    while(left + 1 < right){
        int middle = left + (right - left) / 2;
        if(nums[middle] == target) return middle;
        else if(nums[middle] < target) left = middle;
        else right = middle;
    }

    if(target <= nums[left]) return left;
    else if(target <= nums[right]) return right;
    else return right + 1;
}
```

### [search-a-2d-matrix](https://leetcode-cn.com/problems/search-a-2d-matrix/)

> 编写一个高效的算法来判断  m x n  矩阵中，是否存在一个目标值。该矩阵具有如下特性：
>
> - 每行中的整数从左到右按升序排列。
> - 每行的第一个整数大于前一行的最后一个整数。

```cpp
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    if(matrix.empty() || matrix[0].empty()) return false;
    int rows = matrix.size();
    int cols = matrix[0].size(); 
    
    int left = 0, right = rows * cols - 1;
    while(left + 1 < right){
        int mid = left + (right - left) / 2;
        int valM = matrix[mid/cols][mid%cols];
        if(target == valM) return true;
        else if(target < valM) right = mid;
        else left = mid;
    }

    if(matrix[left/cols][left%cols] == target || matrix[right/cols][right%cols] == target) return true;
    
    return false;
}
```

### [first-bad-version](https://leetcode-cn.com/problems/first-bad-version/)

> 假设你有 n 个版本 [1, 2, ..., n]，你想找出导致之后所有版本出错的第一个错误的版本。
> 你可以通过调用  bool isBadVersion(version)  接口来判断版本号 version 是否在单元测试中出错。实现一个函数来查找第一个错误的版本。你应该尽量减少对调用 API 的次数。

```cpp
int firstBadVersion(int n) {
    int left = 1, right = n;
    while(left + 1 < right){
        int mid = left + (right - left) / 2;
        if(isBadVersion(mid)) right = mid;
        else left = mid;
    }
    if(isBadVersion(left)) return left;
    return right;
}
```

### [find-minimum-in-rotated-sorted-array](https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array/)

> 假设按照升序排序的数组在预先未知的某个点上进行了旋转( 例如，数组  [0,1,2,4,5,6,7] 可能变为  [4,5,6,7,0,1,2] )。
> 请找出其中最小的元素。

```cpp
int findMin(vector<int>& nums) {
    if(nums.empty()) return 0;

    int left = 0, right = nums.size() - 1;
    if(nums[right] > nums[left]) return nums[left]; //说明没有旋转

    while(left + 1 < right){
        int mid = left + (right - left) / 2;
        if(nums[mid] > nums[left]) left = mid;
        else right = mid;
    }

    return min(nums[left], nums[right]);
}
```

### [find-minimum-in-rotated-sorted-array-ii](https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array-ii/)

> 假设按照升序排序的数组在预先未知的某个点上进行了旋转
> ( 例如，数组  [0,1,2,4,5,6,7] 可能变为  [4,5,6,7,0,1,2] )。
> 请找出其中最小的元素。(包含重复元素)

// 思路：跳过重复元素，mid值和end值比较，分为两种情况进行处理
```cpp
int findMin(vector<int>& nums) {
    if(nums.empty()) return 0;
    int left = 0, right = nums.size() - 1;
    if(nums[left] < nums[right]) return nums[left]; // 说明没旋转
    while(left + 1 < right){
        //去重
        while(left < right && nums[left + 1] == nums[left]) left++;
        while(left < right && nums[right - 1] == nums[right]) right--;
        int mid = left + (right - left) / 2;
        if(nums[mid] >= nums[left]) left = mid;
        else right = mid;
    }
    return min(nums[left], nums[right]);
}
```

### [search-in-rotated-sorted-array](https://leetcode-cn.com/problems/search-in-rotated-sorted-array/)

> 假设按照升序排序的数组在预先未知的某个点上进行了旋转。
> ( 例如，数组  [0,1,2,4,5,6,7]  可能变为  [4,5,6,7,0,1,2] )。
> 搜索一个给定的目标值，如果数组中存在这个目标值，则返回它的索引，否则返回  -1 。
> 你可以假设数组中不存在重复的元素。

```cpp
int search(vector<int>& nums, int target) {
    if(nums.empty()) return -1;
    int left = 0, right = nums.size() - 1;
    while(left + 1 < right){
        int mid = left + (right - left) / 2;
        if(nums[mid] == target) return mid;
        if(nums[mid] > nums[left]){
            if(target >= nums[left] && target <= nums[mid]) right = mid;
            else left = mid;
        }
        else{
            if(target <= nums[right] && target >= nums[mid]) left = mid;
            else right = mid;
        }
    }

    if(nums[left] == target) return left;
    else if(nums[right] == target) return right;
    else return -1;

}
```

注意点

> 面试时，可以直接画图进行辅助说明，空讲很容易让大家都比较蒙圈

### [search-in-rotated-sorted-array-ii](https://leetcode-cn.com/problems/search-in-rotated-sorted-array-ii/)

> 假设按照升序排序的数组在预先未知的某个点上进行了旋转。
> ( 例如，数组  [0,0,1,2,2,5,6]  可能变为  [2,5,6,0,0,1,2] )。
> 编写一个函数来判断给定的目标值是否存在于数组中。若存在返回  true，否则返回  false。(包含重复元素)

```cpp
bool search(vector<int>& nums, int target) {
    if(nums.empty()) return false;
    int left = 0, right = nums.size() - 1;
    while(left + 1 < right){
        while(left < right && nums[left+1] == nums[left]) left++;
        while(left < right && nums[right-1] == nums[right]) right--;
        int mid = left + (right - left) / 2;
        if(nums[mid] == target) return true;
        if(nums[mid] >= nums[left]){   //注意是等号
            if(target >= nums[left] && target <= nums[mid]) right = mid;
            else left = mid;
        }
        else{
            if(target >= nums[mid] && target <= nums[right]) left = mid;
            else right = mid;
        }
    }
    if(nums[left] == target || nums[right] == target) return true;
    else return false;
}
```

## 总结

二分搜索核心四点要素（必背&理解）

- 1、初始化：start=0、end=len-1
- 2、循环退出条件：start + 1 < end
- 3、比较中点和目标值：A[mid] ==、 <、> target
- 4、判断最后两个元素是否符合：A[start]、A[end] ? target

## 练习题

- [ ] [search-for-range](https://www.lintcode.com/problem/search-for-a-range/description)
- [ ] [search-insert-position](https://leetcode-cn.com/problems/search-insert-position/)
- [ ] [search-a-2d-matrix](https://leetcode-cn.com/problems/search-a-2d-matrix/)
- [ ] [first-bad-version](https://leetcode-cn.com/problems/first-bad-version/)
- [ ] [find-minimum-in-rotated-sorted-array](https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array/)
- [ ] [find-minimum-in-rotated-sorted-array-ii](https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array-ii/)
- [ ] [search-in-rotated-sorted-array](https://leetcode-cn.com/problems/search-in-rotated-sorted-array/)
- [ ] [search-in-rotated-sorted-array-ii](https://leetcode-cn.com/problems/search-in-rotated-sorted-array-ii/)
