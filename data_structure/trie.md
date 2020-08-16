# 前缀树

## 背景

```前缀树```, 又称```字典树```, 是```N```叉树的一种。它是用来```存储字符串```的，前缀树的每一个节点代表一个 ```字符串（前缀）```。每一个节点会有多个子节点，通往不同子节点的路径上有着不同的字符。子节点代表的字符串是由节点本身的 ```原始字符串``` ，以及 ```通往该子节点路径上所有的字符``` 组成的。

示例：

![trie](../images/trie.png)

节点的值是从根节点开始，与其经过的路径中的字符串按顺序组成。

前缀树的一个重要的特性是，节点所有的后代都与该节点相关的字符串有着共同的前缀，利用公共前缀来降低查询时间开销，这就是 ```前缀树``` 名称的由来。

前缀树有着广泛的应用，例如自动补全，拼写检查等等。

> 根节点是```空字符串```

## 表示

```前缀树```的特别在于字符和子节点之间的对应关系，怎样高效表示这种对应关系是重点。

- 数组
  - 假如只存储```a```到```z```的字符串，可以每个节点声明一个```26```维的数据保存子节点。
  - 对于特定字符```c```，使用```c-'a'```来作为索引查找数组中相应节点。
```cpp
// change this value to adapt to different cases
#define N 26

struct TrieNode {
    bool isEnd; //该节点是否是一个串的结束
    TrieNode* children[N];
    
    // you might need some extra values according to different cases
};

/** Usage:
 *  Initialization: TrieNode root = new TrieNode();
 *  Return a specific child node with char c: (root->children)[c - 'a']
 */
```

- Map
  - 使用```HashMap```存储子节点
  - 每个节点声明一个HashMap, 键是字符，值则是对应的子节点
```cpp
struct TrieNode {
    unordered_map<char, TrieNode*> children;
    
    // you might need some extra values according to different cases
};

/** Usage:
 *  Initialization: TrieNode root = new TrieNode();
 *  Return a specific child node with char c: (root->children)[c]
 */
```
> 通过相应的字符来访问特定的子节点 ```更为容易``` 。但它可能比使用数组 ```稍慢一些``` 。但是，由于我们只存储我们需要的子节点，因此 ```节省了空间``` 。这个方法也更加 ```灵活``` ，因为我们不受到```固定长度和固定范围```的限制。

> https://leetcode-cn.com/leetbook/read/trie/x7ke5m/

### [implement-trie-prefix-tree](https://leetcode-cn.com/problems/implement-trie-prefix-tree/)
> 实现前缀树的```insert```,```search```和```startWith```三个操作

思路：两种实现，一种是使用数组，一种是使用哈希表，前者查找更快，但浪费空间，后者节省内存空间，但查找效率上低一级。

```cpp
class Trie {
private:
    bool isEnd;
    Trie* next[26];
public:
    Trie() {
        isEnd = false;
        memset(next, 0, sizeof(next));
    }
    
    void insert(string word) {
        Trie* node = this;
        for (char c : word) {
            if (node->next[c-'a'] == NULL) {
                node->next[c-'a'] = new Trie();
            }
            node = node->next[c-'a'];
        }
        node->isEnd = true;
    }
    
    bool search(string word) {
        Trie* node = this;
        for (char c : word) {
            node = node->next[c - 'a'];
            if (node == NULL) {
                return false;
            }
        }
        return node->isEnd;
    }
    
    bool startsWith(string prefix) {
        Trie* node = this;
        for (char c : prefix) {
            node = node->next[c-'a'];
            if (node == NULL) {
                return false;
            }
        }
        return true;
    }
};
```

哈希
```java
public class Trie {
    public class TrieNode{
    public int path;
    public int end;
    public HashMap<Character, TrieNode> next;

    public TrieNode(){
        path = 0;
        end = 0;
        next = new HashMap<>();
    }
}

    private TrieNode root;
    public Trie(){
        root = new TrieNode();
    }

    public void insert(String word){
        if(word == null || word.equals(""))  return ;
        TrieNode node = root;
        for(int i = 0; i<word.length(); i++){
            char ch = word.charAt(i);
            if(!node.next.containsKey(ch)) {
                node.next.put(ch,new TrieNode());
            }
            node = node.next.get(ch);
            node.path++;
        }
        node.end++;
    }

    public boolean search(String word){
        if(word == null || word.equals("")) return false;
        TrieNode node = root;
        for(int i = 0; i<word.length(); i++){
            char ch = word.charAt(i);
            if(!node.next.containsKey(ch)) return false;
            node = node.next.get(ch);
        }
        if(node.end == 0) return false;
        return true;
    }
    public boolean startsWith(String word){
        if(word == null || word.equals("")) return false;
        TrieNode node = root;
        for(int i = 0; i<word.length(); i++){
            char ch = word.charAt(i);
            if(!node.next.containsKey(ch)) return false;
            node = node.next.get(ch);
        }
        return true;
    }
};
```