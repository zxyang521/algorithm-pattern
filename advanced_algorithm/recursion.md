# 递归

## 介绍

将大问题转化为小问题，通过递归依次解决各个小问题

## 示例

[reverse-string](https://leetcode-cn.com/problems/reverse-string/)

> 编写一个函数，其作用是将输入的字符串反转过来。输入字符串以字符数组  `char[]`  的形式给出。

```cpp
void reverseString(vector<char>& s) {
    if(s.size() <= 1) return;

    int left = 0, right = s.size() - 1;
    while(left < right){
        swap(s[left++], s[right--]);
    }
    return;
}
```

[swap-nodes-in-pairs](https://leetcode-cn.com/problems/swap-nodes-in-pairs/)

> 给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。
> **你不能只是单纯的改变节点内部的值**，而是需要实际的进行节点交换。

```cpp
    ListNode* swapPairs(ListNode* head) {
        //用递归算法写
        // 思路：将链表翻转转化为一个子问题，然后通过递归方式依次解决
        // 先翻转两个，然后将后面的节点继续这样翻转，然后将这些翻转后的节点连接起来
        return swapListNode(head);
    }

    ListNode* swapListNode(ListNode* head){
        if(head == nullptr || head->next == nullptr) return head;

        // 保存下一阶段的头指针
        ListNode* nextHead = head->next->next;
        // 翻转当前阶段指针
        ListNode* next = head->next;
        next->next = head;
        head->next = swapListNode(nextHead);
        return next;
    }
```

[unique-binary-search-trees-ii](https://leetcode-cn.com/problems/unique-binary-search-trees-ii/)

> 给定一个整数 n，生成所有由 1 ... n 为节点所组成的二叉搜索树。

```cpp
vector<TreeNode*> generateTrees(int n) {
    if(n == 0) return vector<TreeNode*> {};
    return generate(1, n);
}

vector<TreeNode*> generate(int low, int hi){
    if(low > hi) return {nullptr};

    vector<TreeNode*> res;
    for(int i = low; i <= hi; i++){
        //递归生成左右子树
        vector<TreeNode*> lefts = generate(low, i - 1);
        vector<TreeNode*> rights = generate(i + 1, hi);
        //拼接两边
        for(int j = 0; j < lefts.size(); j++){
            for(int k = 0; k < rights.size(); k++){
                TreeNode* root = new TreeNode(i);
                root->left = lefts[j];
                root->right = rights[k];
                res.push_back(root);
            }
        }
    }
    return res;
}
```

## 递归+备忘录

[fibonacci-number](https://leetcode-cn.com/problems/fibonacci-number/)

> 斐波那契数，通常用  F(n) 表示，形成的序列称为斐波那契数列。该数列由  0 和 1 开始，后面的每一项数字都是前面两项数字的和。也就是：
> F(0) = 0,   F(1) = 1
> F(N) = F(N - 1) + F(N - 2), 其中 N > 1.
> 给定  N，计算  F(N)。

```cpp
int fib(int N) {
    if(N <= 1) return N;
    int f0 = 0; 
    int f1 = 1;
    int res = 0;
    for(int i = 2; i <= N; i++){
        res = f0 + f1;
        f0 = f1;
        f1 = res;
    }
    return res;
}
```

## 练习

- [ ] [reverse-string](https://leetcode-cn.com/problems/reverse-string/)
- [ ] [swap-nodes-in-pairs](https://leetcode-cn.com/problems/swap-nodes-in-pairs/)
- [ ] [unique-binary-search-trees-ii](https://leetcode-cn.com/problems/unique-binary-search-trees-ii/)
- [ ] [fibonacci-number](https://leetcode-cn.com/problems/fibonacci-number/)
