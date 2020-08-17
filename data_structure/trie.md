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
```cpp
struct TrieNode {
    bool isEnd = false;
    unordered_map<char, TrieNode*> next;
    ~TrieNode() {  // 析构
        for (auto& [key, value] : next) {
            if (value) delete value;
        }
    }
};

class Trie {
private:
    std::unique_ptr<TrieNode> root;  // 智能指针
    
public:
    Trie(): root(new TrieNode()) {}
    
    void insert(string word) {
        TrieNode *p = root.get();
        for (const char c : word) {
            if (!p->next.count(c)) {
                p->next[c] = new TrieNode();
            }
            p = p->next[c];
        }
        p->isEnd = true;
    }
    
    bool search(string word) {
        TrieNode *p = root.get();
        for (const char c : word) {
            if (!p->next.count(c)) {
                return false;
            }
            p = p->next[c];
        }
        return p->isEnd;
    }
    
    bool startsWith(string prefix) {
        TrieNode *p = root.get();
        for (const char c : prefix) {
            if (!p->next.count(c)) {
                return false;
            }
            p = p->next[c];
        }
        return p != nullptr;
    }
};
```

### [map-sum-pairs](https://leetcode-cn.com/problems/map-sum-pairs/)
> 键值映射
```cpp
class MapSum {
    struct TrieNode {
        bool isEnd = false;
        int val;
        unordered_map<char, TrieNode*> next;
        //析构函数
        ~TrieNode() {
            for(auto item: next){
                if(item.second != nullptr) delete item.second;
            }
        }
    };

private:
    TrieNode* root; 
public:
    /** Initialize your data structure here. */
    MapSum() {
        root = new TrieNode();
    }
    
    void insert(string key, int val) {
        TrieNode* p = root;
        for(int i = 0; i < key.length(); i++){
            char c = key[i];
            if(p->next.find(c) == p->next.end()) p->next[c] = new TrieNode(); 
            p = p->next[c];
        }
        p->isEnd = true;
        p->val = val;
        return;
    }
    
    int sum(string prefix) {
        TrieNode* p = root;
        int sum = 0;
        for(int i = 0; i < prefix.length(); i++){
            char c = prefix[i];
            if(p->next.find(c) != p->next.end())
                p = p->next[c];
            else return 0;
        }
        //宽度优先遍历
        queue<TrieNode*> qe;
        qe.push(p);
        while(!qe.empty()){
            int n = qe.size();
            for(int i = 0; i < n; i++){
                TrieNode* node = qe.front();
                if(node->isEnd) sum += node->val;
                qe.pop();
                for(auto item: node->next){
                    qe.push(item.second);
                }
            }
        }

        return sum;
    }
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum* obj = new MapSum();
 * obj->insert(key,val);
 * int param_2 = obj->sum(prefix);
 */
```

### [replace-words](https://leetcode-cn.com/problems/replace-words/)
> 单词替换

```cpp
class Solution {
struct TrieNode{
    bool isEnd=false;
    unordered_map<char, TrieNode*> next;
    ~TrieNode(){
        for(auto item:next){
            if(item.second != nullptr) delete item.second;
        }
    }
};
private:
  TrieNode* root;
public:
    string replaceWords(vector<string>& dict, string sentence) {
        root = new TrieNode();

        insertDict(dict);

        string res = "";
        string word = "";
        int i = 0;
        int n = sentence.length();
        while(i < n){
            if(sentence[i] == ' ' && word.length() > 0){
                string ser = search(word);
                if(ser.length()) res += ser;
                else res += word;
                res += ' ';
                word = "";
            }
            else word += sentence[i];
            i++;
        }
        
        string ser = search(word);
        if(ser.length()) res += ser;
        else res += word;

        return res;
    }

    void insertDict(vector<string>& dict){
        for(int i = 0; i < dict.size(); i++) insert(dict[i]);
        return;
    }
    void insert(string& word){
        TrieNode* p = root;
        for(int i = 0; i < word.length(); i++){
            char c = word[i];
            if(p->next.find(c) == p->next.end()) p->next[c] = new TrieNode();
            p = p->next[c];
        }
        p->isEnd = true;
    }

    string search(string& word){
        TrieNode* p = root;
        string res = "";
        for(int i = 0; i < word.length(); i++){
            char c = word[i];
            if(p->isEnd) return res;
            if(p->next.find(c) != p->next.end()){
                res += c;
                p = p->next[c];
            }
            else  return "";
        }
        return "";
    }

};
```
