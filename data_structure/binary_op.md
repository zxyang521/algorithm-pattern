# 二进制

## 常见二进制操作

### 基本操作

a=0^a=a^0

0=a^a

由上面两个推导出：a=a^b^b

### 交换两个数

a=a^b

b=a^b

a=a^b

### 移除最后一个 1

a=n&(n-1)

### 获取最后一个 1

diff=(n&(n-1))^n

## 常见题目

[single-number](https://leetcode-cn.com/problems/single-number/)

> 给定一个**非空**整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。

```cpp
int singleNumber(vector<int>& nums) {
    int a = 0;
    for(int i = 0; i < nums.size(); i++){
        a = a^nums[i];
    }

    return a;
}
```

[single-number-ii](https://leetcode-cn.com/problems/single-number-ii/)

> 给定一个**非空**整数数组，除了某个元素只出现一次以外，其余每个元素均出现了三次。找出那个只出现了一次的元素。

```cpp
int singleNumber(vector<int>& nums) {
    // 统计位数上1出现的次数
    int res = 0;
    
    for(int i = 0; i < 32; i++){
        int sum = 0;

        for(int j = 0; j < nums.size(); j++)
            sum += (nums[j] >> i) & 1; //右移

        res ^= (sum % 3) << i;  //左移，这里可以推广到其他每个元素出现k次，找只出现1次的元素.
    }
    return res;

}
```

[single-number-iii](https://leetcode-cn.com/problems/single-number-iii/)

> 给定一个整数数组  `nums`，其中恰好有两个元素只出现一次，其余所有元素均出现两次。 找出只出现一次的那两个元素。

```cpp
vector<int> singleNumber(vector<int>& nums) {
    if(nums.empty()) return {-1, -1};
    int a = 0;
    for(int i = 0; i < nums.size(); i++){
        a ^= nums[i];
    }
    vector<int> res{a, a};
    //得到末尾的1
    a = (a&(a-1)) ^ a;
    for(int i = 0; i < nums.size(); i++){
        if((a & nums[i]) == 0)
            res[0] ^= nums[i];
        else
            res[1] ^= nums[i];
    }

    return res;
}
```

[number-of-1-bits](https://leetcode-cn.com/problems/number-of-1-bits/)

> 编写一个函数，输入是一个无符号整数，返回其二进制表达式中数字位数为 ‘1’  的个数（也被称为[汉明重量](https://baike.baidu.com/item/%E6%B1%89%E6%98%8E%E9%87%8D%E9%87%8F)）。

```cpp
int hammingWeight(uint32_t n) {
    int res = 0;
    while(n > 0){
        n = n & (n-1);
        res++;
    }
    return res;
}
```

[counting-bits](https://leetcode-cn.com/problems/counting-bits/)

> 给定一个非负整数  **num**。对于  0 ≤ i ≤ num  范围中的每个数字  i ，计算其二进制数中的 1 的数目并将它们作为数组返回。

```cpp
vector<int> countBits(int num) {
    vector<int> res;
    for(int i = 0; i <= num; i++){
        res.push_back(count(i));
    }
    return res;
}

int count(int n){
    int res = 0;
    while(n){
        n = n&(n-1);
        res++;
    }
    return res;
}
```

另外一种动态规划解法

```cpp
vector<int> countBits(int num) {
    vector<int> res(num+1, 0);
    for(int i = 1; i <= num; ++ i) {
        res[i] = res[i&(i-1)] + 1;
    }
    return res;
}
```

[reverse-bits](https://leetcode-cn.com/problems/reverse-bits/)

> 颠倒给定的 32 位无符号整数的二进制位。

思路：依次颠倒即可

```cpp
uint32_t reverseBits(uint32_t n) {
    uint32_t res = 0;
    int i = 31;
    while(n){
        res += (n&1)<<i;
        n>>=1;
        i--;
    }
    return res;
}
```

[bitwise-and-of-numbers-range](https://leetcode-cn.com/problems/bitwise-and-of-numbers-range/)

> 给定范围 [m, n]，其中 0 <= m <= n <= 2147483647，返回此范围内所有数字的按位与（包含 m, n 两端点）。

```cpp
// m 5 1 0 1
//   6 1 1 0
// n 7 1 1 1
// 把可能包含0的全部右移变成
// m 5 1 0 0
//   6 1 0 0
// n 7 1 0 0
// 所以最后结果就是m<<count
int rangeBitwiseAnd(int m, int n) {
    int i = 0;
    while(m != n){
        m >>= 1;
        n >>= 1;
        i++;
    }
    return m<<i;

}
```

## 练习

- [ ] [single-number](https://leetcode-cn.com/problems/single-number/)
- [ ] [single-number-ii](https://leetcode-cn.com/problems/single-number-ii/)
- [ ] [single-number-iii](https://leetcode-cn.com/problems/single-number-iii/)
- [ ] [number-of-1-bits](https://leetcode-cn.com/problems/number-of-1-bits/)
- [ ] [counting-bits](https://leetcode-cn.com/problems/counting-bits/)
- [ ] [reverse-bits](https://leetcode-cn.com/problems/reverse-bits/)
