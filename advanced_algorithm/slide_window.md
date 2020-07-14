# 滑动窗口

## 模板

```cpp
/* 滑动窗口算法框架 */
void slidingWindow(string s, string t) {
    unordered_map<char, int> need, window;
    for (char c : t) need[c]++;

    int left = 0, right = 0;
    int valid = 0;
    while (right < s.size()) {
        // c 是将移入窗口的字符
        char c = s[right];
        // 右移窗口
        right++;
        // 进行窗口内数据的一系列更新
        ...

        /*** debug 输出的位置 ***/
        printf("window: [%d, %d)\n", left, right);
        /********************/

        // 判断左侧窗口是否要收缩
        while (window needs shrink) {
            // d 是将移出窗口的字符
            char d = s[left];
            // 左移窗口
            left++;
            // 进行窗口内数据的一系列更新
            ...
        }
    }
}
```

需要变化的地方

- 1、右指针右移之后窗口数据更新
- 2、判断窗口是否要收缩
- 3、左指针右移之后窗口数据更新
- 4、根据题意计算结果

## 示例

[minimum-window-substring](https://leetcode-cn.com/problems/minimum-window-substring/)

> 给你一个字符串 S、一个字符串 T，请在字符串 S 里面找出：包含 T 所有字母的最小子串
```cpp
string minWindow(string s, string t) {
	int m = s.length();
	int n = t.length();

	unordered_map<char, int> mp;
	for(int i = 0; i < n; i++) mp[t[i]]++;  // 保存需要的字符集

	int winStart = 0;
	int matched = 0;  //t里面已经匹配好的字母次数
	int start = 0;  
	int minL = INT_MAX; //最小窗口的长度
	for(int winEnd = 0; winEnd < m; winEnd++){
		char w = s[winEnd];
		if(mp.find(w) != mp.end()){
			mp[w]--;
			if(mp[w] == 0) matched++;  // 如果当前字符的数量匹配需要的字符的数量，则match值+1
		}

		// 当所有字符数量都匹配之后，开始缩紧窗口
		while(matched == mp.size()){
			if(minL > winEnd - winStart + 1){
				start = winStart;
				minL = winEnd - winStart + 1;
			}
			// 左指针指向字符数量和需要的字符相等时，右移之后match值就不匹配则减一
			// 因为win里面的字符数可能比较多，如有10个A，但需要的字符数量可能为3
			// 所以在压死骆驼的最后一根稻草时，match才减一，这时候才跳出循环
			// minL = min(minL, winEnd - winStart + 1);
			char w = s[winStart];
			if(mp.find(w) != mp.end()){
				if(mp[w] == 0){
					matched--;
					// break;
				}
				mp[w]++;
			}
			winStart++;
		}
	}

	return minL == INT_MAX?"":s.substr(start, minL);
}
```

[permutation-in-string](https://leetcode-cn.com/problems/permutation-in-string/)

> 给定两个字符串  **s1**  和  **s2**，写一个函数来判断  **s2**  是否包含  **s1 **的排列。

```cpp
bool checkInclusion(string s1, string s2) {
	int n1 = s1.length();
	int n2 = s2.length();

	unordered_map<char, int> mp;
	for(int i = 0; i < n1; i++) mp[s1[i]]++;

	int winStart = 0;
	int matched = 0;

	for(int winEnd = 0; winEnd < n2; winEnd++){
		char w = s2[winEnd];
		if(mp.find(w) != mp.end()){
			mp[w]--;
			if(mp[w] == 0) matched++;  //相同字母都匹配完了
		}

		if(matched == mp.size()) return true;

		if(winEnd - winStart + 1 >= n1){  //窗口长度大于等于pattern的长度时，收缩窗口
			char w = s2[winStart];
			if(mp.find(w) != mp.end()){
				if(mp[w] == 0) matched--;
				mp[w]++;
			}
			winStart++;
		}
	}

	return false;
}

```

[find-all-anagrams-in-a-string](https://leetcode-cn.com/problems/find-all-anagrams-in-a-string/)

> 给定一个字符串  **s **和一个非空字符串  **p**，找到  **s **中所有是  **p **的字母异位词的子串，返回这些子串的起始索引。

```cpp
//跟上一题一样，本题只不过要遍历全部位置，同时记录下满足条件的起始index
vector<int> findAnagrams(string s, string p) {
	int m = s.length();
	int n = p.length();

	unordered_map<char, int> mp;
	for(int i = 0; i < n; i++) mp[p[i]]++;

	vector<int> res;
	int winStart = 0;
	int matched = 0;

	for(int winEnd = 0; winEnd < m; winEnd++){
		char w = s[winEnd];
		if(mp.find(w) != mp.end()){
			mp[w]--;
			if(mp[w] == 0) matched++;
		}

		if(matched == mp.size()) res.push_back(winStart);

		if(winEnd - winStart + 1 >= n){
			char w = s[winStart];
			if(mp.find(w) != mp.end()){
				if(mp[w] == 0) matched--;
				mp[w]++;
			}
			winStart++;
		}

	}   

	return res;
}
```

[longest-substring-without-repeating-characters](https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/)

> 给定一个字符串，请你找出其中不含有重复字符的   最长子串   的长度。
> 示例  1:
>
> 输入: "abcabcbb"
> 输出: 3
> 解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。

```go
int lengthOfLongestSubstring(string s) {
    // 滑动窗口核心点：1、右指针右移 2、根据题意收缩窗口 3、左指针右移更新窗口 4、根据题意计算结果
	int n = s.length();
	if(n <= 1) return n;

	int winStart = 0;
	int maxL = INT_MIN;
	unordered_map<char, int> mp;
	for(int winEnd = 0; winEnd < n; winEnd++){
		char w = s[winEnd];
		if(mp.find(w) != mp.end()){
			winStart = max(mp[w] + 1, winStart);
		}
		mp[w] = winEnd;

		maxL = max(maxL, winEnd - winStart + 1);
	}
	return maxL;
}
```

## 总结

- 和双指针题目类似，更像双指针的升级版，滑动窗口核心点是维护一个窗口集，根据窗口集来进行处理
- 核心步骤
  - right 右移
  - 收缩
  - left 右移
  - 求结果

## 练习

- [ ] [minimum-window-substring](https://leetcode-cn.com/problems/minimum-window-substring/)
- [ ] [permutation-in-string](https://leetcode-cn.com/problems/permutation-in-string/)
- [ ] [find-all-anagrams-in-a-string](https://leetcode-cn.com/problems/find-all-anagrams-in-a-string/)
- [ ] [longest-substring-without-repeating-characters](https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/)
