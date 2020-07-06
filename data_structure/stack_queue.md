# 栈和队列

## 简介

栈的特点是**后入先出**

![image.png](https://img.fuiboom.com/img/stack.png)

根据这个特点可以临时保存一些数据，之后用到依次再弹出来，常用于 ```DFS``` 深度搜索

队列的特点是**先入先出**， 一般常用于 ```BFS``` 广度搜索，类似一层一层的搜索

## Stack 栈

[min-stack](https://leetcode-cn.com/problems/min-stack/)

> 设计一个支持 push，pop，top 操作，并能在常数时间内检索到最小元素的栈。

思路：
- 用两个栈实现，一个最小栈始终保证最小值在顶部
- 用```pair```数据结构保存值和当前栈中最小值

```cpp
class MinStack {

public:
    stack<pair<int, int>> st;  //value, minVal

    /** initialize your data structure here. */
    MinStack() {
    }

    void push(int x) {
        if(st.empty()){
            st.push(make_pair(x, x));
            return;
        }
        st.push(make_pair(x, min(x, st.top().second)));
    }

    void pop() {
        st.pop();
    }

    int top() {
        return st.top().first;
    }

    int getMin() {
        return st.top().second;
    }
}

/**
 * Your MinStack object will be instantiated and called as such:
 * obj := Constructor();
 * obj.Push(x);
 * obj.Pop();
 * param_3 := obj.Top();
 * param_4 := obj.GetMin();
 */
```

[evaluate-reverse-polish-notation](https://leetcode-cn.com/problems/evaluate-reverse-polish-notation/)

> **波兰表达式计算** > **输入:** ["2", "1", "+", "3", "*"] > **输出:** 9
> **解释:** ((2 + 1) \* 3) = 9

思路：通过栈保存原来的元素，遇到表达式弹出运算，再推入结果，重复这个过程

```cpp
int evalRPN(vector<string>& tokens) {
    stack<int> st;
    for(int i = 0; i < tokens.size(); i++){
        string k = tokens[i];
        if(k == "+" || k == "-" || k == "*" || k == "/"){
            int a = st.top(); st.pop();
            int b = st.top(); st.pop();
            if(tokens[i] == "+") st.push(b + a);
            if(tokens[i] == "-") st.push(b - a);
            if(tokens[i] == "*") st.push(b * a);
            if(tokens[i] == "/") st.push(b / a); //注意后pop出来的是除数
        }
        else st.push(stoi(k));
    }
    return st.top();

}
```

[decode-string](https://leetcode-cn.com/problems/decode-string/)

> 给定一个经过编码的字符串，返回它解码后的字符串。
> s = "3[a]2[bc]", 返回 "aaabcbc".
> s = "3[a2[c]]", 返回 "accaccacc".
> s = "2[abc]3[cd]ef", 返回 "abcabccdcdcdef".

思路：通过栈辅助进行操作

```cpp
string decodeString(string s) {
    if(s.length() == 0) return "";
    int n = s.length();

    stack<char> st;
    for(int i = 0; i < n; i++){
        if(s[i] == ']'){
            string tmp = "";
            while(!st.empty() && st.top() != '['){
                tmp += st.top();
                st.pop();
            }
            // pop out [
            if(!st.empty()) st.pop();
            string num = "";
            //get the number
            while(!st.empty() && st.top() >= '0' && st.top() <= '9'){
                num += st.top();
                st.pop();
            }

            int count = 0;
            for(int t = num.length() - 1; t >= 0; t--)
                count = count * 10 + num[t] - '0';

            //repeat number times
            for(int j = 0; j < count; j++){
                for(int k = tmp.length() - 1; k >= 0; k--) st.push(tmp[k]);  //倒过来输入到```stack```里面去
            }
        }
        else st.push(s[i]);
    }

    vector<char> res;
    while(!st.empty()){
        res.push_back(st.top());
        st.pop();
    }
    reverse(res.begin(), res.end());
    string ss(res.begin(), res.end());
    return ss;
}
```

**利用栈进行 ```DFS``` 递归搜索模板**

```cpp
boolean DFS(int root, int target) {
    Set<Node> visited;
    Stack<Node> s;
    add root to s;
    while (s is not empty) {
        Node cur = the top element in s;
        return true if cur is target;
        for (Node next : the neighbors of cur) {
            if (next is not in visited) {
                add next to s;
                add next to visited;
            }
        }
        remove cur from s;
    }
    return false;
}
```

[binary-tree-inorder-traversal](https://leetcode-cn.com/problems/binary-tree-inorder-traversal/)

> 给定一个二叉树，返回它的*中序*遍历。

```cpp
// 思路：通过stack 保存已经访问的元素，用于原路返回
vector<int> inorderTraversal(TreeNode* root) {
    if(root == nullptr) return {};
    stack<TreeNode*> st;
    vector<int> res;

    while(true){
        if(root){
            st.push(root);
            root = root->left; //一直向左
        }
        else if(!st.empty()){
            root = st.top();
            st.pop(); //弹出
            res.push_back(root->val);
            root = root->right; //转到右子树
        }
        else break;
    }

    return res;

}
```

[clone-graph](https://leetcode-cn.com/problems/clone-graph/)

> 给你无向连通图中一个节点的引用，请你返回该图的深拷贝（克隆）。

```cpp
Node* cloneGraph(Node* node) {
    
    unordered_map<Node*, Node*> visited;
    return clone(node, visited);
}

Node* clone(Node* node, unordered_map<Node*, Node*>& visited){
    if(node == nullptr) return nullptr;

    if(visited.find(node) != visited.end()) return visited[node];

    vector<Node*> listNode(node->neighbors.size(), nullptr);
    Node* cloneNode = new Node(node->val, listNode);
    visited[node] = cloneNode;
    for(int i = 0; i < node->neighbors.size(); i++){
        cloneNode->neighbors[i] = clone(node->neighbors[i], visited);
    }

    return cloneNode;
}
```

[number-of-islands](https://leetcode-cn.com/problems/number-of-islands/)

> 给定一个由  '1'（陆地）和 '0'（水）组成的的二维网格，计算岛屿的数量。一个岛被水包围，并且它是通过水平方向或垂直方向上相邻的陆地连接而成的。你可以假设网格的四个边均被水包围。

思路：通过深度搜索遍历可能性（注意标记已访问元素）

```cpp
int numIslands(vector<vector<char>>& grid) {
    if(grid.empty()) return 0;
    int count = 0;
    int rows = grid.size();
    int cols = grid[0].size();

    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            if(grid[r][c] == '1') count++;
            dfs(grid, r, c);
        }
    }

    return count;
}

void dfs(vector<vector<char>>& grid, int i, int j){
    if(i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size()) return;
    if(grid[i][j] == '0') return;
    grid[i][j] = '0';  //标记为已经访问
    dfs(grid, i-1, j);
    dfs(grid, i+1, j);
    dfs(grid, i, j-1);
    dfs(grid, i, j+1);
}
```

**单调栈**
```cpp
stack<int> st;
for(int i = 0; i < nums.size(); i++){
    while(!st.empty() && st.top() > nums[i]){  //单增栈
        st.pop();
        //do something
    }
    st.push(nums[i]);
}
```

[largest-rectangle-in-histogram](https://leetcode-cn.com/problems/largest-rectangle-in-histogram/)

> 给定 _n_ 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。
> 求在该柱状图中，能够勾勒出来的矩形的最大面积。

思路：求以当前柱子为高度的面积，即转化为寻找小于当前值的左右两边值

![image.png](https://img.fuiboom.com/img/stack_rain.png)

用栈保存小于当前值的左的元素

![image.png](https://img.fuiboom.com/img/stack_rain2.png)

- 利用**单调栈**去做这件事情

```cpp
int largestRectangleArea(vector<int>& heights) {
    // 单调栈
    int n = heights.size();
    if(n == 0) return 0;
    heights.push_back(0);
    int res = INT_MIN;
    stack<int> st;
    for(int i = 0; i < n + 1; i++){
        while(!st.empty() && heights[i] <= heights[st.top()]){
            int idx = st.top(); st.pop();
            int idx2 = st.size() > 0?st.top():-1;
            res = max(res, heights[idx] * (i - idx2 - 1));
        }
        st.push(i);
    }
    return res;

}
```

## Queue 队列

常用于 BFS 宽度优先搜索

[implement-queue-using-stacks](https://leetcode-cn.com/problems/implement-queue-using-stacks/)

> 使用栈实现队列

```go
type MyQueue struct {
    stack []int
    back  []int
}

/** Initialize your data structure here. */
func Constructor() MyQueue {
    return MyQueue{
        stack: make([]int, 0),
        back:  make([]int, 0),
    }
}

// 1
// 3
// 5

/** Push element x to the back of queue. */
func (this *MyQueue) Push(x int) {
    for len(this.back) != 0 {
        val := this.back[len(this.back)-1]
        this.back = this.back[:len(this.back)-1]
        this.stack = append(this.stack, val)
    }
    this.stack = append(this.stack, x)
}

/** Removes the element from in front of queue and returns that element. */
func (this *MyQueue) Pop() int {
    for len(this.stack) != 0 {
        val := this.stack[len(this.stack)-1]
        this.stack = this.stack[:len(this.stack)-1]
        this.back = append(this.back, val)
    }
    if len(this.back) == 0 {
        return 0
    }
    val := this.back[len(this.back)-1]
    this.back = this.back[:len(this.back)-1]
    return val
}

/** Get the front element. */
func (this *MyQueue) Peek() int {
    for len(this.stack) != 0 {
        val := this.stack[len(this.stack)-1]
        this.stack = this.stack[:len(this.stack)-1]
        this.back = append(this.back, val)
    }
    if len(this.back) == 0 {
        return 0
    }
    val := this.back[len(this.back)-1]
    return val
}

/** Returns whether the queue is empty. */
func (this *MyQueue) Empty() bool {
    return len(this.stack) == 0 && len(this.back) == 0
}

/**
 * Your MyQueue object will be instantiated and called as such:
 * obj := Constructor();
 * obj.Push(x);
 * param_2 := obj.Pop();
 * param_3 := obj.Peek();
 * param_4 := obj.Empty();
 */
```

二叉树层次遍历

```cpp
vector<vector<int>> levelOrder(TreeNode* root){
    vector<vector<int>> res;
    if(root == nullptr) return res;
    queue<TreeNode*> nodes;
    nodes.push(root);
    // 通过上一层的长度确定下一层的元素
    while(!nodes.empty()){
        int levelSize = nodes.size(); //记录当前层有多少元素，遍历当前层，并添加下一层
        vector<int> levelVals;
        for(int i = 0; i < levelSize; i++){
            TreeNode* tmpNode = nodes.front();
            nodes.pop();
            levelVals.push_back(tmpNode->val);
            if(tmpNode->left != nullptr) nodes.push(tmpNode->left);
            if(tmpNode->right != nullptr) nodes.push(tmpNode->right);
        }
        res.push_back(levelVals);
    }

    return res;
}
```

[01-matrix](https://leetcode-cn.com/problems/01-matrix/)

> 给定一个由 0 和 1 组成的矩阵，找出每个元素到最近的 0 的距离。
> 两个相邻元素间的距离为 1

```go
// BFS 从0进队列，弹出之后计算上下左右的结果，将上下左右重新进队列进行二层操作
// 0 0 0 0
// 0 x 0 0
// x x x 0
// 0 x 0 0

// 0 0 0 0
// 0 1 0 0
// 1 x 1 0
// 0 1 0 0

// 0 0 0 0
// 0 1 0 0
// 1 2 1 0
// 0 1 0 0
func updateMatrix(matrix [][]int) [][]int {
    q:=make([][]int,0)
    for i:=0;i<len(matrix);i++{
        for j:=0;j<len(matrix[0]);j++{
            if matrix[i][j]==0{
                // 进队列
                point:=[]int{i,j}
                q=append(q,point)
            }else{
                matrix[i][j]=-1
            }
        }
    }
    directions:=[][]int{{0,1},{0,-1},{-1,0},{1,0}}
    for len(q)!=0{
        // 出队列
        point:=q[0]
        q=q[1:]
        for _,v:=range directions{
            x:=point[0]+v[0]
            y:=point[1]+v[1]
            if x>=0&&x<len(matrix)&&y>=0&&y<len(matrix[0])&&matrix[x][y]==-1{
                matrix[x][y]=matrix[point[0]][point[1]]+1
                // 将当前的元素进队列，进行一次BFS
                q=append(q,[]int{x,y})
            }
        }
    }
    return matrix

}
```

## 总结

- 熟悉栈的使用场景
  - 后进先出，保存临时值
  - 利用栈 DFS 深度搜索
- 熟悉队列的使用场景
  - 利用队列 BFS 广度搜索
- 单调栈
  - 单调递增/减栈：栈内元素保持递增/减的栈
  - 以单增栈为例：
    - 如果新元素比栈顶元素大，就入栈
    - 否则一直弹出栈顶元素，知道栈顶元素比新元素小，再将其压栈
  - 用处：
    - 栈内元素递增
    - 当元素出栈时，这个**新元素**是栈顶元素**往后**找第一个比之小的元素
    - 当元素出栈后，新**栈顶元素**是出栈元素**往前**找第一个比之小的元素
  - 

## 练习

- [ ] [min-stack](https://leetcode-cn.com/problems/min-stack/)
- [ ] [evaluate-reverse-polish-notation](https://leetcode-cn.com/problems/evaluate-reverse-polish-notation/)
- [ ] [decode-string](https://leetcode-cn.com/problems/decode-string/)
- [ ] [binary-tree-inorder-traversal](https://leetcode-cn.com/problems/binary-tree-inorder-traversal/)
- [ ] [clone-graph](https://leetcode-cn.com/problems/clone-graph/)
- [ ] [number-of-islands](https://leetcode-cn.com/problems/number-of-islands/)
- [ ] [largest-rectangle-in-histogram](https://leetcode-cn.com/problems/largest-rectangle-in-histogram/)
- [ ] [implement-queue-using-stacks](https://leetcode-cn.com/problems/implement-queue-using-stacks/)
- [ ] [01-matrix](https://leetcode-cn.com/problems/01-matrix/)
