# 链表

## 基本技能

链表相关的核心点

- null/nil 异常处理
- dummy node 哑巴节点
- 快慢指针
- 插入一个节点到排序链表
- 从一个链表中移除一个节点
- 翻转链表
- k个一组翻转链表
- 合并两个链表
- 找到链表的中间节点

## 常见题型

### [remove-duplicates-from-sorted-list](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list/)

> 给定一个排序链表，删除所有重复的元素，使得每个元素只出现一次。

```cpp
ListNode* deleteDuplicates(ListNode* head) {
    if(head == nullptr) return head;

    ListNode* cur = head;
    ListNode* prev = head;

    while(cur->next != nullptr){
        cur = cur->next;
        if(cur->val != prev->val) { //删除所有相同元素，再移动到下一个元素
            prev->next = cur;
            prev = cur;
        }
    }
    prev->next = nullptr;
    return head;
}
```

### [remove-duplicates-from-sorted-list-ii](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list-ii/)

> 给定一个排序链表，删除所有含有重复数字的节点，只保留原始链表中，没有重复出现的数字。

思路：链表头结点可能被删除，所以用 dummy node 辅助删除

```cpp
ListNode* deleteDuplicates(ListNode* head) {
    ListNode* dummy = new ListNode(-1);
    dummy->next = head;
    ListNode* cur = dummy;

    while(cur->next){
        ListNode* node = cur->next;
        while(node != nullptr && node->val == cur->next->val) node = node->next;
        if(cur->next->next != node) cur->next = node;
        else cur = cur->next;
    }

    return dummy->next;
}
```

注意点
• A->B->C 删除 B，A.next = C
• 删除用一个 Dummy Node 节点辅助（允许头节点可变）
• 访问 X.next 、X.value 一定要保证 X != nil

### [reverse-linked-list](https://leetcode-cn.com/problems/reverse-linked-list/)

> 反转一个单链表。

思路：用一个 prev 节点保存向前指针，node 保存向后的临时指针

```cpp
ListNode* reverseList(ListNode* head) {
    if(head == nullptr) return head;
    ListNode* prev = nullptr;
    ListNode* cur = head;

    ListNode* node = nullptr;

    while(cur != nullptr){
        node = cur->next;
        cur->next = prev;
        prev = cur;
        cur = node;
    }

    return prev;

}
```

### [reverse-linked-list-ii](https://leetcode-cn.com/problems/reverse-linked-list-ii/)

> 反转从位置  *m*  到  *n*  的链表。请使用一趟扫描完成反转。

思路：先遍历到 m 处，翻转，再拼接后续，注意指针处理

```cpp
ListNode* reverseBetween(ListNode* head, int m, int n) {
    ListNode* prev = nullptr; // 利用nullptr指针
    ListNode* cur = head;

    for(int i = 0; i < m - 1; i++){
        prev = cur;
        cur = cur->next;
    }

    ListNode* firstPart = prev;  //第一段最后
    ListNode* lastSecondPart = cur; //翻转之后是第二段最后

    //翻转之后，prev是第二段开头，cur是第三段开头
    ListNode* temp = nullptr;
    for(int i = 0; i < n - m + 1; i++){
        temp = cur->next;
        cur->next = prev;
        prev = cur;
        cur = temp;
    }

    //三段连接起来
    if(firstPart == nullptr) head = prev; //注意head一起翻转的情况
    else firstPart->next = prev;

    lastSecondPart->next = cur;

    return head;
}
```

### [merge-two-sorted-lists](https://leetcode-cn.com/problems/merge-two-sorted-lists/)

> 将两个升序链表合并为一个新的升序链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。

思路：
- 通过 dummy node 链表，连接各个元素
- 利用优先队列```priority_queue```来merge

```cpp
struct cmp{
    bool operator()(const ListNode* a, const ListNode* b){
        return a->val > b->val;
    }
};

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    if(l1 == nullptr && l2 == nullptr) return nullptr;
    priority_queue<ListNode*, vector<ListNode*>, cmp> minHeap;
    
    ListNode* head = nullptr;
    ListNode* cur = nullptr;

    if(l1 != nullptr) minHeap.push(l1);
    if(l2 != nullptr) minHeap.push(l2);

    while(!minHeap.empty()){
        ListNode* node = minHeap.top();
        minHeap.pop();
        if(head == nullptr) head = node;
        else cur->next = node;
        cur = node;
        if(node->next != nullptr) minHeap.push(node->next);
    }
    return head;

}
```

### [partition-list](https://leetcode-cn.com/problems/partition-list/)

> 给定一个链表和一个特定值 x，对链表进行分隔，使得所有小于  *x*  的节点都在大于或等于  *x*  的节点之前。

思路：将大于 x 的节点，放到另外一个链表，最后连接这两个链表

```cpp
ListNode* partition(ListNode* head, int x) {
    if(head == nullptr || head->next == nullptr) return head;
    ListNode* dummy = new ListNode(-1);
    dummy->next = head;
    ListNode* cur = dummy;
    
    ListNode* tail = new ListNode(-1);
    ListNode* node = tail;

    while(cur->next != nullptr){
        if(cur->next->val < x)  cur = cur->next;
        else{
            ListNode* tmp = cur->next;
            cur->next = cur->next->next;
            node->next = tmp;
            node = node->next;
        }
    }
    node->next = nullptr;  //注意链表尾部

    cur->next = tail->next; // 链接起来
    return dummy->next;
}
```

哑巴节点使用场景

> 当头节点不确定的时候，使用哑巴节点

### [sort-list](https://leetcode-cn.com/problems/sort-list/)

> 在  *O*(*n* log *n*) 时间复杂度和常数级空间复杂度下，对链表进行排序。

思路：归并排序，找中点和合并操作

```cpp
ListNode* sortList(ListNode* head) {
    // 归并排序，找中点，合并操作
    return mergeSort(head);
}

ListNode* findMiddle(ListNode* head){
    ListNode* slow = head;
    ListNode* fast = head->next;  // 为了得到even nodes下的第一个节点

    while(fast != nullptr && fast->next != nullptr){
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

ListNode* mergeSort(ListNode* head){
    if(head == nullptr || head->next == nullptr) return head;

    ListNode* middle = findMiddle(head);

    ListNode* halfHead = middle->next;
    middle->next = nullptr;
    
    ListNode* newHead = mergeSort(head);
    ListNode* newHalf = mergeSort(halfHead);
    ListNode* node = merge(newHead, newHalf);
    return node;
}

ListNode* merge(ListNode* head1, ListNode* head2){
    ListNode* dummy = new ListNode(-1);
    ListNode* head = dummy;

    while(head1 != nullptr && head2 != nullptr){
        if(head1->val < head2->val){
            head->next = head1;
            head1 = head1->next;
        }
        else{
            head->next = head2;
            head2 = head2->next;
        }
        head = head->next;
    }

    while(head1 != nullptr){
        head->next = head1;
        head1 = head1->next;
        head = head->next;
    }
    while(head2 != nullptr){
        head->next = head2;
        head2 = head2->next;
        head = head->next;
    }

    return dummy->next;
}
```

注意点

- 快慢指针 判断 fast 及 fast.Next 是否为 nil 值
- 递归 mergeSort 需要断开中间节点
- 递归返回条件为 head 为 nil 或者 head.Next 为 nil

### [reorder-list](https://leetcode-cn.com/problems/reorder-list/)

> 给定一个单链表  *L*：*L*→*L*→…→*L\_\_n*→*L*
> 将其重新排列后变为： *L*→*L\_\_n*→*L*→*L\_\_n*→*L*→*L\_\_n*→…

思路：找到中点断开，翻转后面部分，然后合并前后两个链表

```cpp
void reorderList(ListNode* head) {
    if(head == nullptr || head->next == nullptr) return;
    // 找到中间节点
    ListNode* middle = findMiddle(head);
    //翻转第二个链表
    ListNode* secondHalf = reverse(middle->next);
    middle->next = nullptr;
    //merge
    merge(head, secondHalf);
}

//找到中间节点
ListNode* findMiddle(ListNode* head){
    ListNode* slow = head;
    ListNode* fast = head->next;

    while(fast != nullptr && fast->next != nullptr){
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

//翻转链表
ListNode* reverse(ListNode* head){
    ListNode* cur = head;
    ListNode* prev = nullptr;;

    ListNode* node = nullptr;
    while(cur != nullptr){
        node = cur->next;
        cur->next = prev;
        prev = cur;
        cur = node;
    }
    return prev;
}

//merge
void merge(ListNode* head, ListNode* head2){
    ListNode* head1 = head;

    ListNode* dummy = new ListNode(-1);
    ListNode* node = dummy;

    bool insertFirst = true;
    while(head1 != nullptr && head2 != nullptr){
        if(insertFirst){
            node->next = head1;
            head1 = head1->next;
        }
        else{
            node->next = head2;
            head2 = head2->next;
        }
        node = node->next;
        insertFirst = !insertFirst;
    }

    while(head1 != nullptr){
        node->next = head1;
        head1 = head1->next;
        node = node->next;
    }

    while(head2 != nullptr){
        node->next = head2;
        head2 = head2->next;
        node = node->next;
    }

    head = dummy->next;
}
```

### [linked-list-cycle](https://leetcode-cn.com/problems/linked-list-cycle/)

> 给定一个链表，判断链表中是否有环。

思路：快慢指针，快慢指针相同则有环，证明：如果有环每走一步快慢指针距离会减 1
![fast_slow_linked_list](https://img.fuiboom.com/img/fast_slow_linked_list.png)

```cpp
bool hasCycle(ListNode *head) {
    if(head == nullptr) return false;

    ListNode* fast = head;
    ListNode* slow = head;

    while(fast != nullptr && fast->next != nullptr){
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast) return true;
    }

    return false;
}
```

### [linked-list-cycle-ii](https://leetcode-cn.com/problems/linked-list-cycle-ii/)

> 给定一个链表，返回链表开始入环的第一个节点。  如果链表无环，则返回  `null`。

思路：快慢指针，快慢相遇之后，慢指针回到头，快慢指针步调一致一起移动，相遇点即为入环点
![cycled_linked_list](https://img.fuiboom.com/img/cycled_linked_list.png)

```cpp
ListNode *detectCycle(ListNode *head) {
    
    if(head == nullptr || head->next == nullptr) return nullptr;
    ListNode* slow = head;
    ListNode* fast = head;
    while(fast != nullptr && fast->next != nullptr){
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast) break;
    }
    if(fast == nullptr || fast->next == nullptr) return nullptr;
    fast = head;  // 从头开始
    while(slow != fast){
        fast = fast->next;
        slow = slow->next;
    }
    return slow;
}
```

坑点

- 指针比较时直接比较对象，不要用值比较，链表中有可能存在重复值情况
- 第一次相交后，快指针需要从下一个节点开始和头指针一起匀速移动

另外一种方式是 fast=head,slow=head

思路：快慢指针，快慢相遇之后，其中一个指针回到头，快慢指针步调一致一起移动，相遇点即为入环点
```cpp
ListNode *detectCycle(ListNode *head) {
    
    if(head == nullptr || head->next == nullptr) return nullptr;
    ListNode* slow = head;
    ListNode* fast = head;
    while(fast != nullptr && fast->next != nullptr){
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast){
            fast = head;
            while(fast != slow){
                fast = fast->next;
                slow = slow->next;
            }
            return slow;
        }
    }

    return nullptr;
}
```

这两种方式不同点在于，**一般用 fast=head.Next 较多**，因为这样可以知道中点的上一个节点，可以用来删除等操作。

- fast 如果初始化为 head.Next 则中点在 slow.Next
- fast 初始化为 head,则中点在 slow

### [palindrome-linked-list](https://leetcode-cn.com/problems/palindrome-linked-list/)

> 请判断一个链表是否为回文链表。

```cpp
bool isPalindrome(ListNode* head) {
    if(head == nullptr || head->next == nullptr) return true;
    ListNode* slow = head;
    ListNode* fast = head;
    while(fast != nullptr && fast->next != nullptr){
        slow = slow->next;
        fast = fast->next->next;
    }

    ListNode* rev = reverse(slow);
    ListNode* prev = head;
    while(rev != nullptr && prev != nullptr){
        if(rev->val != prev->val) return false;
        rev = rev->next;
        prev = prev->next;
    }
    return true;
}

ListNode* reverse(ListNode* curNode){
    ListNode* prev = nullptr;
    ListNode* node = nullptr;
    while(curNode != nullptr){
        node = curNode->next;
        curNode->next = prev;
        prev = curNode;
        curNode = node;
    }
    return prev;
}
```

### [copy-list-with-random-pointer](https://leetcode-cn.com/problems/copy-list-with-random-pointer/)

> 给定一个链表，每个节点包含一个额外增加的随机指针，该指针可以指向链表中的任何节点或空节点。
> 要求返回这个链表的 深拷贝。

思路：1、hash 表存储指针，2、复制节点跟在原节点后面

```cpp
Node* copyRandomList(Node* head) {
    if(head == nullptr) return head;
    //复制节点，放在原节点的后面
    Node* cur = head;
    Node* tmp = nullptr;
    while(cur != nullptr){
        Node* cloneNode = new Node(cur->val, cur->next, nullptr);
        tmp = cur->next;
        cur->next = cloneNode;
        cur = tmp;
    }

    //处理random指针
    cur = head;
    while(cur != nullptr){
        if(cur->random != nullptr){
            cur->next->random = cur->random->next;
        }
        cur = cur->next->next;
    }
    
    //分离两个链表
    cur = head;
    Node* clone = head->next;
    while(cur != nullptr && cur->next != nullptr){
        tmp = cur->next;
        cur->next = cur->next->next;
        cur = tmp;
    }

    return clone;
}
```

## 总结

链表必须要掌握的一些点，通过下面练习题，基本大部分的链表类的题目都是手到擒来~

- null/nil 异常处理
- dummy node 哑巴节点
- 快慢指针
- 插入一个节点到排序链表
- 从一个链表中移除一个节点
- 翻转链表
- 合并两个链表
- 找到链表的中间节点

## 练习

- [ ] [remove-duplicates-from-sorted-list](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list/)
- [ ] [remove-duplicates-from-sorted-list-ii](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list-ii/)
- [ ] [reverse-linked-list](https://leetcode-cn.com/problems/reverse-linked-list/)
- [ ] [reverse-linked-list-ii](https://leetcode-cn.com/problems/reverse-linked-list-ii/)
- [ ] [merge-two-sorted-lists](https://leetcode-cn.com/problems/merge-two-sorted-lists/)
- [ ] [partition-list](https://leetcode-cn.com/problems/partition-list/)
- [ ] [sort-list](https://leetcode-cn.com/problems/sort-list/)
- [ ] [reorder-list](https://leetcode-cn.com/problems/reorder-list/)
- [ ] [linked-list-cycle](https://leetcode-cn.com/problems/linked-list-cycle/)
- [ ] [linked-list-cycle-ii](https://leetcode-cn.com/problems/https://leetcode-cn.com/problems/linked-list-cycle-ii/)
- [ ] [palindrome-linked-list](https://leetcode-cn.com/problems/palindrome-linked-list/)
- [ ] [copy-list-with-random-pointer](https://leetcode-cn.com/problems/copy-list-with-random-pointer/)
