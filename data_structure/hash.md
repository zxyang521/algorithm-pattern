# 哈希表
## 哈希表包括哈希集合和哈希映射
- 哈希集合：**集合**数据结构的实现之一，用于存储**非重复值**
- 哈希映射：**映射**数据结构的实现之一，用于存储```(key, value)```键值对

### 哈希集合

- 集合的实现之一，存储```不重复值```的数据结构。
```cpp

#include <unordered_set>                // 0. include the library

int main() {
    // 1. initialize a hash set
    unordered_set<int> hashset;
    // 2. insert a new key
    hashset.insert(3);
    hashset.insert(2);
    hashset.insert(1);
    // 3. delete a key
    hashset.erase(2);
    // 4. check if the key is in the hash set
    if (hashset.count(2) <= 0) {
        cout << "Key 2 is not in the hash set." << endl;
    }
    // 5. get the size of the hash set
    cout << "The size of hash set is: " << hashset.size() << endl; 
    // 6. iterate the hash set
    for (auto it = hashset.begin(); it != hashset.end(); ++it) {
        cout << (*it) << " ";
    }
    cout << "are in the hash set." << endl;
    // 7. clear the hash set
    hashset.clear();
    // 8. check if the hash set is empty
    if (hashset.empty()) {
        cout << "hash set is empty now!" << endl;
    }
}
```

哈希集合可用来查重，```template```如下
```cpp
/*
 * Template for using hash set to find duplicates.
 */
bool findDuplicates(vector<Type>& keys) {
    // Replace Type with actual type of your key
    unordered_set<Type> hashset;
    for (Type key : keys) {
        if (hashset.count(key) > 0) {
            return true;
        }
        hashset.insert(key);
    }
    return false;
}

```

### 哈希映射
- 用于存储```(key, value)```键值对的一种实现。

```cpp
#include <unordered_map>                // 0. include the library

int main() {
    // 1. initialize a hash map
    unordered_map<int, int> hashmap;
    // 2. insert a new (key, value) pair
    hashmap.insert(make_pair(0, 0));
    hashmap.insert(make_pair(2, 3));
    // 3. insert a new (key, value) pair or update the value of existed key
    hashmap[1] = 1;
    hashmap[1] = 2;
    // 4. get the value of a specific key
    cout << "The value of key 1 is: " << hashmap[1] << endl;
    // 5. delete a key
    hashmap.erase(2);
    // 6. check if a key is in the hash map
    if (hashmap.count(2) <= 0) {
        cout << "Key 2 is not in the hash map." << endl;
    }
    // 7. get the size of the hash map
    cout << "the size of hash map is: " << hashmap.size() << endl; 
    // 8. iterate the hash map
    for (auto it = hashmap.begin(); it != hashmap.end(); ++it) {
        cout << "(" << it->first << "," << it->second << ") ";
    }
    cout << "are in the hash map." << endl;
    // 9. clear the hash map
    hashmap.clear();
    // 10. check if the hash map is empty
    if (hashmap.empty()) {
        cout << "hash map is empty now!" << endl;
    }
}

```

场景一：
根据键值拿到更多信息，帮助我们做出判断
```cpp
/*
 * Template for using hash map to find duplicates.
 * Replace ReturnType with the actual type of your return value.
 */
ReturnType aggregateByKey_hashmap(vector<Type>& keys) {
    // Replace Type and InfoType with actual type of your key and value
    unordered_map<Type, InfoType> hashtable;
    for (Type key : keys) {
        if (hashmap.count(key) > 0) {
            if (hashmap[key] satisfies the requirement) {
                return needed_information;
            }
        }
        // Value can be any information you needed (e.g. index)
        hashmap[key] = value;
    }
    return needed_information;
}
```

场景二：按键聚合
```cpp
/*
 * Template for using hash map to find duplicates.
 * Replace ReturnType with the actual type of your return value.
 */
ReturnType aggregateByKey_hashmap(vector<Type>& keys) {
    // Replace Type and InfoType with actual type of your key and value
    unordered_map<Type, InfoType> hashtable;
    for (Type key : keys) {
        if (hashmap.count(key) > 0) {
            update hashmap[key];
        }
        // Value can be any information you needed (e.g. index)
        hashmap[key] = value;
    }
    return needed_information;
}
```

### [contains-duplicate-ii](https://leetcode-cn.com/problems/contains-duplicate-ii/)
> 判断是否存在重复元素，且index差绝对值不大于K

采用```hashset```和滑动窗口的思想
```cpp
bool containsNearbyDuplicate(vector<int>& nums, int k) {
    unordered_set<int> hashset;

    for(int i = 0; i < nums.size(); i++){
        if(hashset.find(nums[i]) != hashset.end()) return true;
        hashset.insert(nums[i]);
        if(hashset.size() > k)
            hashset.erase(nums[i-k]);
    }
    return false;
}
```

### [find-duplicate-subtrees](https://leetcode-cn.com/problems/find-duplicate-subtrees/)
> 找到重复的子树

思路： 找重复的数字或者其他item的时候就要想到哈希表，本题还需要一个步骤就是树的序列化
```cpp
vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
    //序列化加dfs
    vector<TreeNode*> res;
    unordered_map<string, int> mp;
    dfs(root, res, mp);
    return res;
}

string dfs(TreeNode* root, vector<TreeNode*>& result, unordered_map<string, int>& mp){
    if(root == nullptr) return "";
    string st = to_string(root->val) + "," + dfs(root->left, result, mp) + "," + dfs(root->right, result, mp);
    if(mp[st] == 1) result.push_back(root);
    
    mp[st]++;
    return st;
}
```

### [group-shifted-stringss](https://leetcode-cn.com/problems/group-shifted-strings/)
> 移位字符串分组
```cpp
vector<vector<string>> groupStrings(vector<string>& strings) {
    unordered_map<string, vector<string>> mp;
    
    for(int i = 0; i < strings.size(); i++){
        string word = strings[i];
        string code = "0";
        for(int j = 1; j < word.size(); j++){
            int tmp = word[j] - word[0];
            if(tmp < 0) tmp += 26;
            code += tmp + '0';
        }
        mp[code].push_back(strings[i]);
    }

    vector<vector<string>> res;
    for(auto it = mp.begin(); it != mp.end(); ++it){
        res.push_back(it->second);
    }
    
    return res;
}
```

### [valid-sudoku](https://leetcode-cn.com/problems/valid-sudoku/)
> 判断有效的数独

思路： 判断9行，9列，9个box中没有重复数字出现
```cpp
bool isValidSudoku(vector<vector<char>>& board) {
    int rows[9][10] = {0};
    int cols[9][10] = {0};
    int box[9][10] = {0};

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(board[i][j] == '.') continue;
            int cur = board[i][j] - '0';
            //判断行
            if(rows[i][cur]) return false;
            if(cols[j][cur]) return false;
            if(box[3 * (i/3) + j/3][cur]) return false;

            rows[i][cur] = 1;
            cols[j][cur] = 1;
            box[3 * (i/3) + j/3][cur] = 1;
        }
    }

    return true;
}
```

### [find-duplicate-subtrees](https://leetcode-cn.com/problems/find-duplicate-subtrees/)
> 寻找重复子树

思路：看到重复二字就知道需要使用哈希，还需要对子树进行编码

```cpp
vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
    //序列化加dfs
    vector<TreeNode*> res;
    unordered_map<string, int> mp;
    dfs(root, res, mp);
    return res;
}

string dfs(TreeNode* root, vector<TreeNode*>& result, unordered_map<string, int>& mp){
    if(root == nullptr) return "";
    string st = to_string(root->val) + "," + dfs(root->left, result, mp) + "," + dfs(root->right, result, mp);
    if(mp[st] == 1) result.push_back(root);
    
    mp[st]++;
    return st;
}
```
