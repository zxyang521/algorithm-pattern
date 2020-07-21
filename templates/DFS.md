# 深度优先遍历
### dfs跟bfs区别在于**遍历顺序**的不同

- BFS中：**更早访问的节点距离根结点更近**
- DFS中，找到的第一条路径**不一定是最短路径**

【**模板一**】
- 模板一是**递归**实现的
```java
/*
 * Return true if there is a path from cur to target.
 */
boolean DFS(Node cur, Node target, Set<Node> visited) {
    return true if cur is target;
    for (next : each neighbor of cur) {
        if (next is not in visited) {
            add next to visted;
            return true if DFS(next, target, visited) == true;
        }
    }
    return false;
}
```
> 以上算法实际调用了系统提供的<font color=green>**隐式栈**</font>，

【**模板二**】
- 要是递归栈太深，会导致溢出，可以利用显式栈优化

```java
/*
 * Return true if there is a path from cur to target.
 */
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
