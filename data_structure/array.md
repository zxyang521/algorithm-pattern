# 数组

## 基本技能

数组是数据结构中最基础的一块，基础考点：

- 边界处理
- 数据的插入删除
- 多维数组

## 常见题型

### [spiral-matrix](https://leetcode-cn.com/problems/spiral-matrix/)

> 给定一个包含 *m* x *n* 个元素的矩阵（*m* 行, *n* 列），请按照顺时针螺旋顺序，返回矩阵中的所有元素。

```cpp
vector<int> spiralOrder(vector<vector<int>>& matrix) {
    int rows = matrix.size();
    if( rows == 0) return {};
    int cols = matrix[0].size();
    int rl = 0, rh = rows - 1;
    int cl = 0, ch = cols - 1;

    vector<int> res;
    while(true) {
      for(int i = cl; i <= ch; i++) res.push_back(matrix[rl][i]); //从左往右
      if(++rl > rh) break; // 下一步从上往下，考虑边界
      for(int i = rl; i <= rh; i++) res.push_back(matrix[i][ch]); //从上往下
      if(--ch < cl) break; //下一步从右往左，考虑边界
      for(int i = ch; i >= cl; i--) res.push_back(matrix[rh][i]); // 从右往左
      if(--rh < rl) break; // 下一步从下往上，考虑边界；注意rl已经增加了
      for(int i = rh; i >= rl; i--) res.push_back(matrix[i][cl]);
      if(++cl > ch) break; //下一步循环从右往左，考虑边界
    }
    return res;
}
```

