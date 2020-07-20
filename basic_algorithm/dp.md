# 动态规划

## 背景

先从一道题目开始~

如题  [triangle](https://leetcode-cn.com/problems/triangle/)

> 给定一个三角形，找出自顶向下的最小路径和。每一步只能移动到下一行中相邻的结点上。

例如，给定三角形：

```text
[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]
```

自顶向下的最小路径和为  11（即，2 + 3 + 5 + 1 = 11）。

使用 DFS（遍历 或者 分治法）

遍历

![image.png](https://img.fuiboom.com/img/dp_triangle.png)

分治法

![image.png](https://img.fuiboom.com/img/dp_dc.png)

优化 DFS，缓存已经被计算的值（称为：记忆化搜索 本质上：动态规划）

![image.png](https://img.fuiboom.com/img/dp_memory_search.png)

动态规划就是把大问题变成小问题，并解决了小问题重复计算的方法称为动态规划

动态规划和 DFS 区别

- 二叉树 子问题是没有交集，所以大部分二叉树都用递归或者分治法，即 ```DFS```，就可以解决
- 像 ```triangle``` 这种是有重复走的情况，**子问题是有交集**，所以可以用动态规划来解决

动态规划，自底向上

```go
func minimumTotal(triangle [][]int) int {
	if len(triangle) == 0 || len(triangle[0]) == 0 {
		return 0
	}
	// 1、状态定义：f[i][j] 表示从i,j出发，到达最后一层的最短路径
	var l = len(triangle)
	var f = make([][]int, l)
	// 2、初始化
	for i := 0; i < l; i++ {
		for j := 0; j < len(triangle[i]); j++ {
			if f[i] == nil {
				f[i] = make([]int, len(triangle[i]))
			}
			f[i][j] = triangle[i][j]
		}
	}
	// 3、递推求解
	for i := len(triangle) - 2; i >= 0; i-- {
		for j := 0; j < len(triangle[i]); j++ {
			f[i][j] = min(f[i+1][j], f[i+1][j+1]) + triangle[i][j]
		}
	}
	// 4、答案
	return f[0][0]
}
func min(a, b int) int {
	if a > b {
		return b
	}
	return a
}

```

动态规划，自顶向下

```cpp
// 测试用例：
// [
// [2],
// [3,4],
// [6,5,7],
// [4,1,8,3]
// ]
int minimumTotal(vector<vector<int>>& triangle) {
    if(triangle.size() == 0 || triangle[0].size() == 0) return 0;

    int m = triangle.size();
    vector<vector<int>> dp;    // 1、状态定义：f[i][j] 表示从0,0出发，到达i,j的最短路径


    int sum = 0;
    for(int i = 0; i < m; i++){
        vector<int> row = triangle[i];
        sum += row[0];
        vector<int> rd(row.size(), 0);
        rd[0] = sum;
        dp.push_back(rd);  // 初始化
    }

    int res = dp[m-1][0];
    for(int i = 1; i < m; i++){
        vector<int> row = triangle[i];
        for(int j = 1; j < row.size(); j++){
            if(j < row.size() - 1)
                dp[i][j] = min(dp[i-1][j], dp[i-1][j-1]) + row[j]; //上一层有左值
            else
                dp[i][j] = dp[i-1][j-1] + row[j]; //上一层没有左值
            if(i == m - 1) res = min(res, dp[i][j]);
        }
    }

    return res;
}
```

## 递归和动规关系

递归是一种程序的实现方式：函数的自我调用

```go
Function(x) {
	...
	Funciton(x-1);
	...
}
```

动态规划：是一种解决问题的思想，大规模问题的结果，是由小规模问题的结果运算得来的。动态规划可用递归来实现(Memorization Search)

## 使用场景

满足两个条件

- 满足以下条件之一
  - 求最大/最小值（Maximum/Minimum）
  - 求是否可行（Yes/No ）
  - 求可行个数（Count(\*) ）
- 满足不能排序或者交换（Can not sort / swap ）

如题：[longest-consecutive-sequence](https://leetcode-cn.com/problems/longest-consecutive-sequence/)  位置可以交换，所以不用动态规划

## 四点要素

1. **状态 State**
   - 灵感，创造力，存储小规模问题的结果
2. **方程 Function**
   - 状态之间的联系，怎么通过小的状态，来算大的状态
3. **初始化 Intialization**
   - 最极限的小状态是什么, 起点
4. **答案 Answer**
   - 最大的那个状态是什么，终点

## 常见四种类型

1. Matrix DP (10%)
1. Sequence (40%)
1. Two Sequences DP (40%)
1. Backpack (10%)

> 注意点
>
> - 贪心算法大多题目靠背答案，所以如果能用动态规划就尽量用动规，不用贪心算法。

## 1、矩阵类型（10%）

### [minimum-path-sum](https://leetcode-cn.com/problems/minimum-path-sum/)

> 给定一个包含非负整数的  *m* x *n*  网格，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。

思路：动态规划
  - 1、state: f[x][y]从起点走到 x,y 的最短路径
  - 2、function: f[x][y] = min(f[x-1][y], f[x][y-1]) + A[x][y]
  - 3、intialize: f[0][0] = A[0][0]、f[i][0] = sum(0,0 -> i,0)、 f[0][i] = sum(0,0 -> 0,i)
  - 4、answer: f[n-1][m-1]

```cpp
int minPathSum(vector<vector<int>>& grid) {
    if(grid.empty() || grid[0].empty()) return 0;
    int m = grid.size();
    int n = grid[0].size();

    // vector<vector<int>> dp(m, vector<int>(n, INT_MAX));
    // dp[0][0] = grid[0][0];
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            int left = INT_MAX;
            int up = INT_MAX;
            if(i-1 >= 0) left = grid[i-1][j];
            if(j-1 >= 0) up = grid[i][j-1];
            if(i != 0 || j != 0 ) grid[i][j] = min(left, up) + grid[i][j];  //直接复用原始矩阵
        }
    }

    return grid[m-1][n-1];
}
```

### [unique-paths](https://leetcode-cn.com/problems/unique-paths/)

> 一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为“Start” ）。
> 机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为“Finish”）。
> 问总共有多少条不同的路径？

```cpp
int uniquePaths(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n));

    dp[0][0] = 1;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            int left = 0;
            int up = 0;
            if(i - 1 >= 0) left = dp[i-1][j];
            if(j - 1 >= 0) up = dp[i][j-1];
            if(i != 0 || j != 0)dp[i][j] = left + up;
        }
    }

    return dp[m-1][n-1];
}
```

### [unique-paths-ii](https://leetcode-cn.com/problems/unique-paths-ii/)

> 一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为“Start” ）。
> 机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为“Finish”）。
> 问总共有多少条不同的路径？
> 现在考虑网格中有障碍物。那么从左上角到右下角将会有多少条不同的路径？

```cpp
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    if(obstacleGrid.size() == 0 || obstacleGrid[0].size() == 0 || obstacleGrid[0][0]) return 0;
    
    int m = obstacleGrid.size();
    int n =obstacleGrid[0].size();

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(obstacleGrid[i][j]){
                obstacleGrid[i][j] = 0;
                continue;
            }
            if(i == 0 && j == 0){
                obstacleGrid[i][j] = 1;
                continue;
            }
            int left = 0;
            int up = 0;
            if(i - 1 >= 0) left = obstacleGrid[i-1][j];
            if(j - 1 >= 0) up = obstacleGrid[i][j-1];
            obstacleGrid[i][j] = left + up;
        }
    }

    return obstacleGrid[m-1][n-1];
}
```

## 2、序列类型（40%）

### [climbing-stairs](https://leetcode-cn.com/problems/climbing-stairs/)

> 假设你正在爬楼梯。需要  *n*  阶你才能到达楼顶。

```cpp
int climbStairs(int n) {
    if(n <= 2) return n;
    int res = 0;
    int f1 = 1;
    int f2 = 2;
    for(int i = 3; i <= n; i++){
        res = f1 + f2; //复用变量
        f1 = f2;
        f2 = res;
    }

    return res;
}
```

### [jump-game](https://leetcode-cn.com/problems/jump-game/)

> 给定一个非负整数数组，你最初位于数组的第一个位置。
> 数组中的每个元素代表你在该位置可以跳跃的最大长度。
> 判断你是否能够到达最后一个位置。

```cpp
bool canJump(vector<int>& nums) {
// 第一种解法：会超时，时间复杂度高
// 思路：看最后一跳
// 状态：f[i] 表示是否能从0跳到i
// 推导：f[i] = OR(f[j],j<i&&j能跳到i) 判断之前所有的点最后一跳是否能跳到当前点
// 初始化：f[0] = 0
// 结果： f[n-1]
    if(nums.empty()) return true;
    
    vector<bool> dp(nums.size());
    dp[0] = true;
    for(int i = 1; i < nums.size(); i++){
        for(int j = 0; j < i; j++){
            if(dp[j] && j + nums[j] >= i)  dp[i] = true;
        }
    }
    return dp[nums.size() - 1];  
}
```

```cpp
bool canJump(vector<int>& nums) {
    //version2: 直接找最远能跳到的距离
    if(nums.empty()) return true;
    int res = 0;
    for(int i = 0; i < nums.size(); i++){
        if(i > res) return false;
        res = max(res, i + nums[i]);
    }

    return true;

}
```


### [jump-game-ii](https://leetcode-cn.com/problems/jump-game-ii/)

> 给定一个非负整数数组，你最初位于数组的第一个位置。
> 数组中的每个元素代表你在该位置可以跳跃的最大长度。
> 你的目标是使用最少的跳跃次数到达数组的最后一个位置。

```cpp
int jump(vector<int>& nums) {
    // version 1
    // 状态：f[i] 表示从起点到当前位置最小次数
    // 推导：f[i] = f[j],a[j]+j >=i,min(f[j]+1)
    // 初始化：f[0] = 0
    // 结果：f[n-1]
    if(nums.empty()) return 0;
    vector<int> dp(nums.size(), INT_MAX);
    dp[0] = 0;  //第一个位置不需要跳跃.
    for(int i = 1; i < nums.size(); i++){
        for(int j = 0; j < i; j++){
            if(j + nums[j] >= i) dp[i] = min(dp[i], dp[j] + 1);
        }
    }

    return dp[nums.size() - 1];
}
```

```cpp
int jump(vector<int>& nums) {
    // version 2: 贪心算法
    if(nums.empty()) return 0;
    int end = 0;
    int res = 0;
    int maxPos = 0;
    for(int i = 0; i < nums.size() - 1; i++){
        maxPos = max(maxPos, i + nums[i]);
        if(i == end){
            end = maxPos;
            res++;
        }
    }
    return res;
}
```

### [palindrome-partitioning-ii](https://leetcode-cn.com/problems/palindrome-partitioning-ii/)

> 给定一个字符串 _s_，将 _s_ 分割成一些子串，使每个子串都是回文串。
> 返回符合要求的最少分割次数。

```cpp
int minCut(string s) {
    if(s.length() == 0) return 0;
    int n = s.length();
    vector<vector<bool>> isPalind(n, vector<bool>(n, false));  // 记录下s总那些是位置之间是回文子串

    for(int i = 0; i < n; i++)  isPalind[i][i] = true;  //单个字母都是回文

    for(int start = n - 1; start >= 0; start--){
        for(int end = start + 1; end < n; end++){
            if(s[start] == s[end]){
                if(end - start > 1)
                    isPalind[start][end] = isPalind[start+1][end-1];
                else isPalind[start][end] = true;
            }
            else isPalind[start][end] = false;
        }
    }

    // now lets populate the second table, every index in 'cuts' stores the minimum cuts needed
    // for the substring from that index till the end
    //cuts verson1:
    /*vector<int> cuts(n, 0);
    for (int startIndex = n - 1; startIndex >= 0; startIndex--) {
    int minCuts = n; // maximum cuts
    for (int endIndex = n - 1; endIndex >= startIndex; endIndex--) {
        if (isPalind[startIndex][endIndex]) {
        // we can cut here as we got a palindrome
        // also we dont need any cut if the whole substring is a palindrome
        minCuts = (endIndex == n - 1) ? 0 : min(minCuts, 1 + cuts[endIndex + 1]);
        }
    }
    cuts[startIndex] = minCuts;
    }
    
    return cuts[0];*/

    //////version 2
    vector<int> cuts(n + 1);
    cuts[0] = -1;
    cuts[1] = 0;
    for(int i = 1; i <= n; i++){
        cuts[i] = i - 1;
        for(int j = 0; j < i; j++){
            if(isPalind[j][i-1])
                cuts[i] = min(cuts[i], cuts[j] + 1);
        }
    }
    return cuts[n];
}    
}
```

注意点

- 判断回文字符串时，可以提前用动态规划算好，减少时间复杂度

### [longest-increasing-subsequence](https://leetcode-cn.com/problems/longest-increasing-subsequence/)

> 给定一个无序的整数数组，找到其中最长上升子序列的长度。

```cpp
int lengthOfLIS(vector<int>& nums) {
    // f[i] 表示从0开始到i结尾的最长序列长度
    // f[i] = max(f[j])+1 ,a[j]<a[i]
    // f[0...n-1] = 1
    // max(f[0]...f[n-1])
    if(nums.empty() || nums.size() == 1) return nums.size();
    int n = nums.size();

    vector<int> dp(n, 1);
    int res = 0;
    for(int i = 1; i < n; i++){
        for(int j = 0; j < i; j++){
            if(nums[i] > nums[j]) dp[i] = max(dp[i], dp[j] + 1);
        }
        res = max(res, dp[i]);
    }

    return res;
}
```
> 本题还有第二种解法，利用二分查找，降低复杂度
```cpp
int lengthOfLIS(vector<int>& nums) {
    if(nums.empty() || nums.size() == 1) return nums.size();
    int n = nums.size();

    vector<int> seq;
    seq.push_back(nums[0]);

    for(int i = 1; i < n; i++){
        int res = seq.size();
        if(seq[res-1] < nums[i]){
            seq.push_back(nums[i]);
        }
        else{ // 二分找到大于等于nums[i]的数
            int k = bisearch(seq, nums[i]);
            seq[k] = nums[i];
        }
    }

    return seq.size();
}

int bisearch(vector<int>& nums, int num){
    int left = 0, right = nums.size() - 1;
    while(left + 1 < right){
        int mid = left + (right - left) / 2;
        if(nums[mid] < num) left = mid;
        else right = mid;
    }

    if(nums[left] >= num) return left;
    else return right;
}
```


### [word-break](https://leetcode-cn.com/problems/word-break/)

> 给定一个**非空**字符串  *s*  和一个包含**非空**单词列表的字典  *wordDict*，判定  *s*  是否可以被空格拆分为一个或多个在字典中出现的单词。

```cpp
bool wordBreak(string s, vector<string>& wordDict) {
	// f[i] 表示前i个字符是否可以被切分
	// f[i] = f[j] && s[j+1~i] in wordDict
	// f[0] = true
	// return f[len]
    int n = s.length();
    int m = wordDict.size();

    vector<bool> dp(n + 1, false);
    dp[0] = true;

    for(int i = 1; i <= n; i++){
        for(int j = 0; j < m; j++){
            string word = wordDict[j];
            int w = word.length();
            if(i >= w && s.substr(i-w, w) == word && dp[i-w]){
                dp[i] = true;
                break;
            }
        }
    }

    return dp[n];

}
```

### [perfect-squares](https://leetcode-cn.com/problems/perfect-squares/)
> 给定正整数 n，找到若干个完全平方数（比如 1, 4, 9, 16, ...）使得它们的和等于 n。你需要让组成和的完全平方数的个数最少。

- 思路：动态规划法
- 思路2：广度优先搜索法
  
```cpp
int numSquares(int n) {
    vector<int> dp(n + 1, n);
    dp[0] = 0;
    for(int i = 1; i <= n; i++){
        int N = sqrt(i);
        for(int j = 1; j <= N; j++)
            dp[i] = min(dp[i], dp[i - j * j] + 1);
    }

    return dp[n];
}
```

```cpp
int numSquares(int n) {

    queue<int> qe;
    vector<bool> visited(n+1, false);
    qe.push(n);
    visited[n] = true;
    int steps = 0;

    while(!qe.empty()){
        int m = qe.size();
        for(int i = 0; i < m; i++){
            int N = qe.front();
            qe.pop();
            if(N == 0) return steps;
            for(int j = 1; j <= sqrt(N); j++){
                int k = N - j * j;
                if(!visited[k]){
                    qe.push(k);
                    visited[k] = true;
                }
            }
        }
        steps++;
    }

    return steps;
}
```
- 注意bfs的时候要剪枝，利用一个数组记录已经计算过的节点

小结

常见处理方式是给 0 位置占位，这样处理问题时一视同仁，初始化则在原来基础上```length+1```，返回结果 f[n]

- 状态可以为前 i 个
- 初始化 ```length+1```
- 取值 ```index=i-1```
- 返回值：```f[n]```或者 ```f[m][n]```

## Two Sequences DP（40%）

### [longest-common-subsequence](https://leetcode-cn.com/problems/longest-common-subsequence/)

> 给定两个字符串  text1 和  text2，返回这两个字符串的最长公共子序列。
> 一个字符串的   子序列   是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。
> 例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列。两个字符串的「公共子序列」是这两个字符串所共同拥有的子序列。

```cpp
int longestCommonSubsequence(string text1, string text2) {
    // dp[i][j] a前i个和b前j个字符最长公共子序列
    // dp[m+1][n+1]
    //   ' a d c e
    // ' 0 0 0 0 0
    // a 0 1 1 1 1
    // c 0 1 1 2 1
    //
    int s1 = text1.length();
    int s2 = text2.length();

    vector<vector<int>> dp(s1 + 1, vector<int>(s2 + 1));
    dp[0][0] = 0;

    for(int i = 1; i <= s1; i++){
        for(int j = 1; j <= s2; j++){
            if(text1[i-1] == text2[j-1]) dp[i][j] = 1 + dp[i-1][j-1];
            else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }

    return dp[s1][s2];
}
```

注意点

- go 切片初始化

```go
dp:=make([][]int,len(a)+1)
for i:=0;i<=len(a);i++ {
    dp[i]=make([]int,len(b)+1)
}
```

- 从 1 开始遍历到最大长度
- 索引需要减一

### [edit-distance](https://leetcode-cn.com/problems/edit-distance/)

> 给你两个单词  word1 和  word2，请你计算出将  word1  转换成  word2 所使用的最少操作数  
> 你可以对一个单词进行如下三种操作：
> 插入一个字符
> 删除一个字符
> 替换一个字符

思路：和上题很类似，相等则不需要操作，否则取删除、插入、替换最小操作次数的值+1

```go
int minDistance(string word1, string word2) {
    // dp[i][j] 表示a字符串的前i个字符编辑为b字符串的前j个字符最少需要多少次操作
    // dp[i][j] = OR(dp[i-1][j-1]，a[i]==b[j],min(dp[i-1][j],dp[i][j-1],dp[i-1][j-1])+1)
    int s1 = word1.length();
    int s2 = word2.length();

    vector<vector<int>> dp(s1 + 1, vector<int>(s2 + 1));
    
    for(int i = 0; i <= s1; i++) dp[i][0] = i;
    for(int j = 0; j <= s2; j++) dp[0][j] = j;

    for(int i = 1; i <= s1; i++){
        for(int j = 1; j <= s2; j++){
            if(word1[i-1] == word2[j-1]) dp[i][j] = dp[i-1][j-1]; //相等不需要操作
            else dp[i][j] = min(dp[i-1][j], min(dp[i][j-1], dp[i-1][j-1])) + 1; // 插入，删除，替换
        }
    }

    return dp[s1][s2];
}
```

说明

> 另外一种做法：MAXLEN(a,b)-LCS(a,b)

## 零钱和背包（10%）

### [coin-change](https://leetcode-cn.com/problems/coin-change/)

> 给定不同面额的硬币 coins 和一个总金额 amount。编写一个函数来计算可以凑成总金额所需的最少的硬币个数。如果没有任何一种硬币组合能组成总金额，返回  -1。

思路：和其他 DP 不太一样，i 表示钱或者容量

```cpp
    // 状态 dp[i]表示金额为i时，组成的最小硬币个数
    // 推导 dp[i]  = min(dp[i-1], dp[i-2], dp[i-5])+1, 前提 i-coins[j] > 0
    // 初始化为最大值 dp[i]=amount+1
    // 返回值 dp[n] or dp[n]>amount =>-1
int coinChange(vector<int>& coins, int amount) {
    if(coins.empty()) return -1;
    vector<int> dp(amount + 1, amount+1);
    dp[0] = 0;
    for(int i = 1; i <= amount; i++){
        for(int j = 0; j < coins.size(); j++){
            if(i >= coins[j]) dp[i] = min(dp[i-coins[j]] + 1, dp[i]);
        }
    }

    return dp[amount] == amount+1?-1: dp[amount];
}
```

注意

> dp[i-a[j]] 决策 a[j]是否参与

### [backpack](https://www.lintcode.com/problem/backpack/description)

> 在 n 个物品中挑选若干物品装入背包，最多能装多满？假设背包的大小为 m，每个物品的大小为 A[i]

```cpp
int backPack(vector<int>& A, int m) {
    // write your code here
    if(A.empty()) return 0;
    int n = A.size();
    vector<vector<int>> dp(n, vector<int>(m + 1)); //最多能装多少东西
    
    for(int i = 0; i < n; i++){
        dp[i][0] = 0;   //背包大小为0，能装下最多也是0
    }
    
    for(int i = 0; i <= m; i++){
        if(A[0] <= i)  dp[0][i] = A[0];  //只有一件物品
    }
    
    for(int i = 1; i < n; i++){
        for(int j = 1; j <= m; j++){
            int weight1 = dp[i-1][j];
            int weight2 = 0;
            if(A[i] <= j) weight2 = dp[i-1][j-A[i]] + A[i];
            dp[i][j] = max(weight1, weight2);
        }
    }
    
    return dp[n-1][m];
}
```
观察上面循环过程就会发现，每次迭代只用到```i```和```i-1```两行，所以可以优化如下：
```cpp
int backPack(vector<int>& A, int m){
    if(A.empty()) return 0;
    int n = A.size();
    vector<vector<int>> dp(2, vector<int>(m + 1)); //只需要保存上一次循环结果就行了

    for(int i = 0; i <= m; i++)
        if(A[0] <= i) dp[0][i] = dp[1][i] = A[0];  //只有一件物品

    for(int i = 1; i < n; i++){
        for(int j = 1; j <= m; j++){
            int weight1 = dp[i%2-1][j];
            int weight2 = 0;
            if(A[i] <= j) weight2 = dp[i%2-1][j-A[i]] + A[i];
            dp[i%2][j] = max(weight1, weight2);
        }
    }

    return dp[n%2 - 1][m];

}
```


### [backpack-ii](https://www.lintcode.com/problem/backpack-ii/description)

> 有 `n` 个物品和一个大小为 `m` 的背包. 给定数组 `A` 表示每个物品的大小和数组 `V` 表示每个物品的价值.
> 问最多能装入背包的总价值是多大?

思路：f[i][j] 前 i 个物品，装入 j 背包 最大价值
- 跟上一题类似，只不过重量换成了利润
- 可以优化成上一题

```cpp
int backPackII(int m, vector<int> &A, vector<int> &V) {
    // write your code here
    if(A.empty()) return 0;
    int n = A.size();
    vector<vector<int>> dp(n, vector<int>(m + 1));
    
    for(int i = 0; i < n; i++){
        dp[i][0] = 0;
    }
    
    for(int i = 0; i <= m; i++){
        if(A[0] <= i)  dp[0][i] = V[0];
    }
    
    for(int i = 1; i < n; i++){
        for(int j = 1; j <= m; j++){
            int profit1 = dp[i-1][j];
            int profit2 = 0;
            if(A[i] <= j) profit2 = dp[i-1][j-A[i]] + V[i];
            dp[i][j] = max(profit1, profit2);
        }
    }
    
    return dp[n-1][m];
}
```

## 练习

Matrix DP (10%)

- [ ] [triangle](https://leetcode-cn.com/problems/triangle/)
- [ ] [minimum-path-sum](https://leetcode-cn.com/problems/minimum-path-sum/)
- [ ] [unique-paths](https://leetcode-cn.com/problems/unique-paths/)
- [ ] [unique-paths-ii](https://leetcode-cn.com/problems/unique-paths-ii/)

Sequence (40%)

- [ ] [climbing-stairs](https://leetcode-cn.com/problems/climbing-stairs/)
- [ ] [jump-game](https://leetcode-cn.com/problems/jump-game/)
- [ ] [jump-game-ii](https://leetcode-cn.com/problems/jump-game-ii/)
- [ ] [palindrome-partitioning-ii](https://leetcode-cn.com/problems/palindrome-partitioning-ii/)
- [ ] [longest-increasing-subsequence](https://leetcode-cn.com/problems/longest-increasing-subsequence/)
- [ ] [word-break](https://leetcode-cn.com/problems/word-break/)
- [ ] [perfect-squares](https://leetcode-cn.com/problems/perfect-squares/)

Two Sequences DP (40%)

- [ ] [longest-common-subsequence](https://leetcode-cn.com/problems/longest-common-subsequence/)
- [ ] [edit-distance](https://leetcode-cn.com/problems/edit-distance/)

Backpack & Coin Change (10%)

- [ ] [coin-change](https://leetcode-cn.com/problems/coin-change/)
- [ ] [backpack](https://www.lintcode.com/problem/backpack/description)
- [ ] [backpack-ii](https://www.lintcode.com/problem/backpack-ii/description)
