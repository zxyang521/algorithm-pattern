# 二叉树

## 知识点

### 二叉树遍历

**前序遍历**：**先访问根节点**，再前序遍历左子树，再前序遍历右子树
**中序遍历**：先中序遍历左子树，**再访问根节点**，再中序遍历右子树
**后序遍历**：先后序遍历左子树，再后序遍历右子树，**再访问根节点**

注意点

- 以根访问顺序决定是什么遍历
- 左子树都是优先右子树
  
#### TreeNode 定义

```cpp
struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    TreeNode(int x): val(x), left(nullptr), right(nullptr), parent(nullptr) {};
};
```

#### 前序递归

```cpp
//前中后序遍历只在这个函数有区别, 调整push_back的顺序
void preOrderRecursion(TreeNode* root, vector<int>& res){
    res.push_back(root->val);
    preOrderRecursion(root->left, res);
    preOrderRecursion(root->right, res);
}

vector<int> preOrderTraversal(TreeNode* root){
    if(root == nullptr) return {};
    
    vector<int> res;

    preOrderRecursion(root, res);

    return res;
}
```

#### 前序非递归

```cpp
// 通过非递归遍历: 用栈进行辅助
vector<int> preorderTraversal(TreeNode* root){
    // 非递归
    if(root == nullptr) return {};
    vector<int> res;

    stack<TreeNode*> st;
    st.push(root);

    while(!st.empty()){
        TreeNode* node = st.top();
        st.pop();
        res.push_nack(node->val);
        //注意先入右节点进栈
        if(!node->right) st.push(node->right);
        if(!node->left) st.push(node->left);
    }

    return res;
}
```

#### 中序非递归

```cpp
// 思路：通过stack 保存已经访问的元素，用于原路返回
vector<int> inorderTraversal(TreeNode* root){
    if(root == nullptr) return {};
    vector<int> res;

    stack<TreeNode*> st;

    while(true){
        if(root != nullptr){
            st.push(root);
            root = root->left; //一直向左
        }
        else if(!st.empty()){
            TreeNode* root = st.top();　//弹出
            st.pop();
            res.push_back(root->val);
            root = root->right;　　//右子树
        }
        else break;
    }

    return res;

}
```

#### 后序非递归

```cpp
vector<int> postorderTraversal(TreeNode* root){
	// 通过栈辅助，同时插入nullptr节点判断右子节点是否弹出
    if(root == nullptr) return {};
    vector<int> res;

    stack<TreeNode*> st;
    st.push(root);
    while(!st.empty()){
        TreeNode* node = st.top();
        if(node == nullptr){ //说明是根节点了
            st.pop();
            res.push_back(st.top()->val);
            st.pop();
            continue;
        }
        st.push(nullptr);
        if(node->right != nullptr) st.push(node->right);
        if(node->left != nullptr) st.push(node->left);
    }

    return res;
}
```

注意点

- 核心就是：根节点必须在右节点弹出之后，再弹出

#### DFS 深度搜索-从上到下

```cpp
vector<int> preorderTraversal(TreeNode* root){
    vector<int> res;
    dfs(root, res);
    return res;
}

// V1：深度遍历，结果指针作为参数传入到函数内部
void dfs(TreeNode* root, vector<int>& res) {
    if(root == nullptr) return;
    res.push_back(root->val);
    dfs(root->left, res);
    dfs(root->right, res);
}
```

#### DFS 深度搜索-从下向上（分治法）

```cpp
// V2：通过分治法遍历
vector<int> preorderTraversal(TreeNode* root){
    vector<int> res = divideAndConquer(root);
    return res;
}

vector<int> divideAndConquer(TreeNode* root){
    // 返回条件(null & leaf)
    if(root == nullptr) return {};
    // 分治(Divide)
    vector<int> res_left = divideAndConquer(root->left);
    vector<int> res_right = divideAndConquer(root->right);
    // 合并结果(Conquer)
    vector<int> res;
    res.push_back(root->val);
    res.insert(res.end(), res_left.begin(), res_right.end());

    return res;
}
```

注意点：

> DFS 深度搜索（从上到下） 和分治法（从下到上）区别：前者一般将最终结果通过指针参数传入，后者一般递归返回结果最后合并，会return一个值

#### BFS 层次遍历

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

### 分治法应用

先分别处理局部，再合并结果

适用场景

- 快速排序
- 归并排序
- 二叉树相关问题

分治法模板

- 递归返回条件
- 分段处理
- 合并结果

```cpp
template<typename T> 
T traversal(TreeNode* root){
    // null
    if(root == nullptr) {
        //do something and return
    }

    // Divide
    T left = traversal(root->left);
    T right = traversal(root->right);

    // Conquer
    T res = Merge from left and right

    return res;
}
```

#### 典型示例

```cpp
// V2：通过分治法遍历二叉树
vector<int> preorderTraversal(TreeNode* root){
    vector<int> res = divideAndConquer(root);
    return res;
}

vector<int> divideAndConquer(TreeNode* root){
    vector<int> res;
    if(root == nullptr) return res; //处理异常
    
    // Divide
    vector<int> left = divideAndConquer(root->left);
    vector<int> right = divideAndConquer(root->right);
    
    // Conquer
    res.push_back(root->val);
    res.insert(res.end(), left.begin(), left.end());
    res.insert(res.end(), right.begin(), right.end());

    return res;
}
```

#### 归并排序  

```cpp

void mergeSort(vector<int>& a){
    int n = a.size();
    vector<int> aux;
    merge_sort(a, aux, 0, n - 1);
}

void merge_sort(vector<int>& a, vector<int>& aux, int low, int high){
    if(low >= high) return;
    
    // 分治: middle分成两半
    int middle = low + (high - low) / 2;
    merge_sort(a, aux, low, middle);
    merge_sort(a, aux, middle + 1, high);

    // 合并
    merge(a, aux, low, middle, high);
}

void merge(vector<int>& a, vector<int>& aux, int low, int middle, int high){
    assert isSorted(a, low, middle);
    assert isSorted(a, middle + 1, high);

    for(int k = low; k < high; k++)
        aux[k] = a[k];
    
    int i = low, j = middle + 1;
    for(int k = low; k < high; k++){
        if(i > middle) a[k] = aux[j++];
        else if(j > high) a[k] = aux[i++];
        else if(aux[i] > aux[j]) a[k] = aux[j++];
        else a[k] = aux[i++];
    }

    assert isSorted(a, low, high);

}

//判断是否是排序好的数组
bool isSorted(vector<int>& a, int i, int j){
    for(int k = i; k < j; k++){
        if(a[k] > a[k + 1]) return false;
    }
    
    return true;
}
```

注意点

> 递归需要返回结果用于合并

#### 快速排序  

```cpp
void quickSort(vector<int>& a){
    //思路：找到数组中某个index，将数组分成两段，左段小于右段，类似分治法，但没有合并
    random_shuffle(a); //重要！保证快排复杂度下限
    int n = a.size();
    quick_sort(a, 0, n - 1);
}

void quick_sort(vector<int>& a, int low, int high){
    if(low >= high) return; //异常
    
    int pivot = partion(a, low, high); //找到某个数
    // 分治
    quick_sort(a, low, pivot - 1);
    quick_sort(a, pivot + 1, high);
}

int partion(vector<int>& a, int low, int high){
    if(low == high) return low;
    
    srand(time(0));
    int pivotIdx = low + rand() % (high - low);
    swap(a, pivotIdx, high);

    int pivot = a[high];
    for(int i = low; i < high; i++){
        // all elements less than 'pivot' will be before the index 'low'.
        if(a[i] < pivot){
            swap(a, i, low);
            low++;
        }
    }

    // put the pivot into the right place.
    swap(a, low, high);

    return low;
}

void swap(vector<int>& a, int i, int j){
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}
```

注意点：

> 快排由于是原地交换所以没有合并过程
> 传入的索引是存在的索引（如：0、length-1 等），越界可能导致崩溃

常见题目示例

#### maximum-depth-of-binary-tree

[maximum-depth-of-binary-tree](https://leetcode-cn.com/problems/maximum-depth-of-binary-tree/)

> 给定一个二叉树，找出其最大深度。

思路：分治法

```go
func maxDepth(root *TreeNode) int {
    // 返回条件处理
    if root == nil {
        return 0
    }
    // divide：分左右子树分别计算
    left := maxDepth(root.Left)
    right := maxDepth(root.Right)

    // conquer：合并左右子树结果
    if left > right {
        return left + 1
    }
    return right + 1
}
```

#### balanced-binary-tree

[balanced-binary-tree](https://leetcode-cn.com/problems/balanced-binary-tree/)

> 给定一个二叉树，判断它是否是高度平衡的二叉树。

思路：分治法，左边平衡 && 右边平衡 && 左右两边高度 <= 1，
因为需要返回是否平衡及高度，要么返回两个数据，要么合并两个数据，
所以用-1 表示不平衡，>0 表示树高度（二义性：一个变量有两种含义）。

```go
func isBalanced(root *TreeNode) bool {
    if maxDepth(root) == -1 {
        return false
    }
    return true
}
func maxDepth(root *TreeNode) int {
    // check
    if root == nil {
        return 0
    }
    left := maxDepth(root.Left)
    right := maxDepth(root.Right)

    // 为什么返回-1呢？（变量具有二义性）
    if left == -1 || right == -1 || left-right > 1 || right-left > 1 {
        return -1
    }
    if left > right {
        return left + 1
    }
    return right + 1
}
```

注意

> 一般工程中，结果通过两个变量来返回，不建议用一个变量表示两种含义

#### binary-tree-maximum-path-sum

[binary-tree-maximum-path-sum](https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/)

> 给定一个**非空**二叉树，返回其最大路径和。

思路：分治法，分为三种情况：左子树最大路径和最大，右子树最大路径和最大，左右子树最大加根节点最大，需要保存两个变量：一个保存子树最大路径和，一个保存左右加根节点和，然后比较这个两个变量选择最大值即可

```go
type ResultType struct {
    SinglePath int // 保存单边最大值
    MaxPath int // 保存最大值（单边或者两个单边+根的值）
}
func maxPathSum(root *TreeNode) int {
    result := helper(root)
    return result.MaxPath
}
func helper(root *TreeNode) ResultType {
    // check
    if root == nil {
        return ResultType{
            SinglePath: 0,
            MaxPath: -(1 << 31),
        }
    }
    // Divide
    left := helper(root.Left)
    right := helper(root.Right)

    // Conquer
    result := ResultType{}
    // 求单边最大值
    if left.SinglePath > right.SinglePath {
        result.SinglePath = max(left.SinglePath + root.Val, 0)
    } else {
        result.SinglePath = max(right.SinglePath + root.Val, 0)
    }
    // 求两边加根最大值
    maxPath := max(right.MaxPath, left.MaxPath)
    result.MaxPath = max(maxPath,left.SinglePath+right.SinglePath+root.Val)
    return result
}
func max(a,b int) int {
    if a > b {
        return a
    }
    return b
}
```

#### lowest-common-ancestor-of-a-binary-tree

[lowest-common-ancestor-of-a-binary-tree](https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/)

> 给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

思路：分治法，有左子树的公共祖先或者有右子树的公共祖先，就返回子树的祖先，否则返回根节点

```go
func lowestCommonAncestor(root, p, q *TreeNode) *TreeNode {
    // check
    if root == nil {
        return root
    }
    // 相等 直接返回root节点即可
    if root == p || root == q {
        return root
    }
    // Divide
    left := lowestCommonAncestor(root.Left, p, q)
    right := lowestCommonAncestor(root.Right, p, q)


    // Conquer
    // 左右两边都不为空，则根节点为祖先
    if left != nil && right != nil {
        return root
    }
    if left != nil {
        return left
    }
    if right != nil {
        return right
    }
    return nil
}
```

### BFS 层次应用

#### binary-tree-level-order-traversal

[binary-tree-level-order-traversal](https://leetcode-cn.com/problems/binary-tree-level-order-traversal/)

> 给你一个二叉树，请你返回其按  **层序遍历**  得到的节点值。 （即逐层地，从左到右访问所有节点）

思路：用一个队列记录一层的元素，然后扫描这一层元素添加下一层元素到队列（一个数进去出来一次，所以复杂度 O(logN)）

```go
func levelOrder(root *TreeNode) [][]int {
	result := make([][]int, 0)
	if root == nil {
		return result
	}
	queue := make([]*TreeNode, 0)
	queue = append(queue, root)
	for len(queue) > 0 {
		list := make([]int, 0)
        // 为什么要取length？
        // 记录当前层有多少元素（遍历当前层，再添加下一层）
		l := len(queue)
		for i := 0; i < l; i++ {
            // 出队列
			level := queue[0]
			queue = queue[1:]
			list = append(list, level.Val)
			if level.Left != nil {
				queue = append(queue, level.Left)
			}
			if level.Right != nil {
				queue = append(queue, level.Right)
			}
		}
		result = append(result, list)
	}
	return result
}
```

#### binary-tree-level-order-traversal-ii

[binary-tree-level-order-traversal-ii](https://leetcode-cn.com/problems/binary-tree-level-order-traversal-ii/)

> 给定一个二叉树，返回其节点值自底向上的层次遍历。 （即按从叶子节点所在层到根节点所在的层，逐层从左向右遍历）

思路：在层级遍历的基础上，翻转一下结果即可

```go
func levelOrderBottom(root *TreeNode) [][]int {
    result := levelOrder(root)
    // 翻转结果
    reverse(result)
    return result
}
func reverse(nums [][]int) {
	for i, j := 0, len(nums)-1; i < j; i, j = i+1, j-1 {
		nums[i], nums[j] = nums[j], nums[i]
	}
}
func levelOrder(root *TreeNode) [][]int {
	result := make([][]int, 0)
	if root == nil {
		return result
	}
	queue := make([]*TreeNode, 0)
	queue = append(queue, root)
	for len(queue) > 0 {
		list := make([]int, 0)
        // 为什么要取length？
        // 记录当前层有多少元素（遍历当前层，再添加下一层）
		l := len(queue)
		for i := 0; i < l; i++ {
            // 出队列
			level := queue[0]
			queue = queue[1:]
			list = append(list, level.Val)
			if level.Left != nil {
				queue = append(queue, level.Left)
			}
			if level.Right != nil {
				queue = append(queue, level.Right)
			}
		}
		result = append(result, list)
	}
	return result
}
```

#### binary-tree-zigzag-level-order-traversal

[binary-tree-zigzag-level-order-traversal](https://leetcode-cn.com/problems/binary-tree-zigzag-level-order-traversal/)

> 给定一个二叉树，返回其节点值的锯齿形层次遍历。Z 字形遍历

```go
func zigzagLevelOrder(root *TreeNode) [][]int {
	result := make([][]int, 0)
	if root == nil {
		return result
	}
	queue := make([]*TreeNode, 0)
	queue = append(queue, root)
	toggle := false
	for len(queue) > 0 {
		list := make([]int, 0)
		// 记录当前层有多少元素（遍历当前层，再添加下一层）
		l := len(queue)
		for i := 0; i < l; i++ {
			// 出队列
			level := queue[0]
			queue = queue[1:]
			list = append(list, level.Val)
			if level.Left != nil {
				queue = append(queue, level.Left)
			}
			if level.Right != nil {
				queue = append(queue, level.Right)
			}
		}
		if toggle {
			reverse(list)
		}
		result = append(result, list)
		toggle = !toggle
	}
	return result
}
func reverse(nums []int) {
	for i := 0; i < len(nums)/2; i++ {
		t := nums[i]
		nums[i] = nums[len(nums)-1-i]
		nums[len(nums)-1-i] = t
	}
}
```

### 二叉搜索树应用

#### validate-binary-search-tree

[validate-binary-search-tree](https://leetcode-cn.com/problems/validate-binary-search-tree/)

> 给定一个二叉树，判断其是否是一个有效的二叉搜索树。

思路 1：中序遍历，检查结果列表是否已经有序

思路 2：分治法，判断左 MAX < 根 < 右 MIN

```go
// v1
func isValidBST(root *TreeNode) bool {
    result := make([]int, 0)
    inOrder(root, &result)
    // check order
    for i := 0; i < len(result) - 1; i++{
        if result[i] >= result[i+1] {
            return false
        }
    }
    return true
}

func inOrder(root *TreeNode, result *[]int)  {
    if root == nil{
        return
    }
    inOrder(root.Left, result)
    *result = append(*result, root.Val)
    inOrder(root.Right, result)
}


```

```go
// v2分治法
type ResultType struct {
	IsValid bool
    // 记录左右两边最大最小值，和根节点进行比较
	Max     *TreeNode
	Min     *TreeNode
}

func isValidBST2(root *TreeNode) bool {
	result := helper(root)
	return result.IsValid
}
func helper(root *TreeNode) ResultType {
	result := ResultType{}
	// check
	if root == nil {
		result.IsValid = true
		return result
	}

	left := helper(root.Left)
	right := helper(root.Right)

	if !left.IsValid || !right.IsValid {
		result.IsValid = false
		return result
	}
	if left.Max != nil && left.Max.Val >= root.Val {
		result.IsValid = false
		return result
	}
	if right.Min != nil && right.Min.Val <= root.Val {
		result.IsValid = false
		return result
	}

	result.IsValid = true
    // 如果左边还有更小的3，就用更小的节点，不用4
    //  5
    // / \
    // 1   4
    //      / \
    //     3   6
	result.Min = root
	if left.Min != nil {
		result.Min = left.Min
	}
	result.Max = root
	if right.Max != nil {
		result.Max = right.Max
	}
	return result
}
```

#### insert-into-a-binary-search-tree

[insert-into-a-binary-search-tree](https://leetcode-cn.com/problems/insert-into-a-binary-search-tree/)

> 给定二叉搜索树（BST）的根节点和要插入树中的值，将值插入二叉搜索树。 返回插入后二叉搜索树的根节点。

思路：找到最后一个叶子节点满足插入条件即可

```go
// DFS查找插入位置
func insertIntoBST(root *TreeNode, val int) *TreeNode {
    if root == nil {
        root = &TreeNode{Val: val}
        return root
    }
    if root.Val > val {
        root.Left = insertIntoBST(root.Left, val)
    } else {
        root.Right = insertIntoBST(root.Right, val)
    }
    return root
}
```

## 总结

- 掌握二叉树递归与非递归遍历
- 理解 DFS 前序遍历与分治法
- 理解 BFS 层次遍历

## 练习

- [ ] [maximum-depth-of-binary-tree](https://leetcode-cn.com/problems/maximum-depth-of-binary-tree/)
- [ ] [balanced-binary-tree](https://leetcode-cn.com/problems/balanced-binary-tree/)
- [ ] [binary-tree-maximum-path-sum](https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/)
- [ ] [lowest-common-ancestor-of-a-binary-tree](https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/)
- [ ] [binary-tree-level-order-traversal](https://leetcode-cn.com/problems/binary-tree-level-order-traversal/)
- [ ] [binary-tree-level-order-traversal-ii](https://leetcode-cn.com/problems/binary-tree-level-order-traversal-ii/)
- [ ] [binary-tree-zigzag-level-order-traversal](https://leetcode-cn.com/problems/binary-tree-zigzag-level-order-traversal/)
- [ ] [validate-binary-search-tree](https://leetcode-cn.com/problems/validate-binary-search-tree/)
- [ ] [insert-into-a-binary-search-tree](https://leetcode-cn.com/problems/insert-into-a-binary-search-tree/)
