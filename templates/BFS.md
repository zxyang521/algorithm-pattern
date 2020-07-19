# 广度优先搜索
## 遍历和找出最短路径。通常用于树和图结构。

> 在特定问题中执行**BFS**之前确定结点和边缘非常重要。通常来说，结点是实际结点或是状态。而边缘将是实际边缘或可能的转换

【**模板一**】

```java
/**
 * Return the length of the shortest path between root and target node.
 */
int BFS(Node root, Node target) {
    Queue<Node> queue;  // store all nodes which are waiting to be processed
    int step = 0;       // number of steps neeeded from root to current node
    // initialize
    add root to queue;
    // BFS
    while (queue is not empty) {
        step = step + 1;
        // iterate the nodes which are already in the queue
        int size = queue.size();
        for (int i = 0; i < size; ++i) {
            Node cur = the first node in queue;
            return step if cur is target;
            for (Node next : the neighbors of cur) {
                add next to queue;
            }
            remove the first node from queue;
        }
    }
    return -1;          // there is no path from root to target
}
```
- 每一轮中，队列中的节点是<font color=green>**等待处理的节点**</font>。
- 每个更外一层的```while```循环之后，我们```距离根节点更远一步```，用```step```记录根节点到当前节点的距离


【**模板二**】

> 有时<font color=green>**不会访问一个结点两次**</font>很重要，否则会陷入无限循环，我们需要加入一个哈希表```used```判断是否已经访问过本节点

```java
/**
 * Return the length of the shortest path between root and target node.
 */
int BFS(Node root, Node target) {
    Queue<Node> queue;  // store all nodes which are waiting to be processed
    Set<Node> used;     // store all the used nodes
    int step = 0;       // number of steps neeeded from root to current node
    // initialize
    add root to queue;
    add root to used;
    // BFS
    while (queue is not empty) {
        step = step + 1;
        // iterate the nodes which are already in the queue
        int size = queue.size();
        for (int i = 0; i < size; ++i) {
            Node cur = the first node in queue;
            return step if cur is target;
            for (Node next : the neighbors of cur) {
                if (next is not in used) {
                    add next to queue;
                    add next to used;
                }
            }
            remove the first node from queue;
        }
    }
    return -1;          // there is no path from root to target
}
```
> 两种情况不考虑哈希表
> - 确定完全没有循环，比如树遍历
> - 明确要把多次访问的节点都添加到队列中