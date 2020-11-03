# 排序

```cpp
//help函数
//交换数组a中的i和j
void swap(vector<int> & a, int i, int j ){
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

//判断是否是排序好的数组
bool isSorted(vector<int>& a, int i, int j){
    for(int k = i; k < j; k++){
        if(a[k] > a[k + 1]) return false;
    }
    
    return true;
}
```

## 常考排序

### 选择排序
```cpp
//选择排序
void selectionSort(vector<int>& a){
    int n = a.size();
    for(int i = 0; i < n; i++){
        int min = i;
        for(int j = i + 1; j < n; j++){
            if(a[j] < a[min])
                min = j;
        }
        if(min != i)
        	swap(a, i, min);
    }

}
```

### 插入排序

```cpp
//插入排序
void insertionSort(vector<int>& a){
    int n = a.size();
    for(int i = 1; i < n; i ++){
        for(int j = i; j > 0; j--){
            if(a[j] < a[j - 1]){
                swap(a, j, j - 1);
            }
            else break;
        }
    }
}
```

### 希尔排序(壳排序)
```cpp
//壳排序
void shellSort(vector<int>& a){
    
    int n = a.size();
    int H = 1;
    while(H < n) H = 3 * H + 1; //壳的序列

    for(int h = H; h >= 1; h = (H - 1) / 3){
        // 插入排序
        for(int i = 1; i < n; i++){
            for(int j = i; j > h; j-=h){
                if(a[j] < a[j - h])   swap(a, j, j - h);
                else break;
            }
        }

    }
    
}
```

### 快速排序

```cpp
//快速排序，快排
void quickSort(vector<int>& a){

    random_shuffle(a);
    int n = a.size();
    quick_sort(a, 0, n - 1);
}

void quick_sort(vector<int>& a, int low, int high){
    if(low >= high) return;
    int pivot = partition(a, low, high);
    quick_sort(a, low, pivot - 1);
    quick_sort(a, pivot + 1, high);
}

static int partition(vector<int>& a, int low, int high){
    int i = low, j = high + 1;
    while(i < j){

        while(a[++i] < a[low])
            if(i == high) break;
        
        while(a[low] < a[--j])
            if(j == low) break;
        
        swap(a, i, j);
    }
    swap(a, low, j);
    return j;
}

// 选择k
static int select(vector<int>& a, int k){

    int low = 0, high = a.size() - 1;
    while(low < high){
        int pivot = partition(a, low, high);
        if(pivot < k) low = pivot + 1;
        else if(pivot > k) high = pivot - 1;
        else return a[k];
    }

    return a[k];

}

//重复键值，3-way partition
void quick3ways(vector<int>& a, int low, int high){
    // See page 289 for public sort() that calls this method.
    if (high <= low) return;
    int lt = low, i = low + 1, gt = high;
    int v = a[low];
    while (i <= gt)
    {
        if (a[i] < v) swap(a, lt++, i++); 
        else if (a[i] > v) swap(a, i, gt--); 
        else i++;
    } // Now a[lo..lt-1] < v = a[lt..gt] < a[gt+1..hi]. sort(a, lo, lt - 1);
    quick3ways(a, low, lt - 1);
    quick3ways(a, gt + 1, high);
}
```

### 归并排序

```cpp
//归并排序
/*version1 递归*/
void mergeSort(vector<int>& a){
    int n = a.size();
    vector<int> aux(n);
    merge_sort(a, aux, 0, n - 1);
}

void merge_sort(vector<int>& a, vector<int>& aux, int low, int high){
    if(low >= high) return;

    int middle = low + (high - low)/2;
    merge_sort(a, aux, low, middle);
    merge_sort(a, aux, middle + 1, high);
    merge(a, aux, low, middle, high);
}

void merge(vector<int>& a, vector<int>& aux, int low, int middle, int high){
    assert isSorted(a, low, middle);
    assert isSorted(a, middle + 1, high);

    for(int k = low; k <= high; k++)
        aux[k] = a[k];
    
    int i = low, j = middle + 1;
    int k = low;
    for(int k = low; k <= high; k++){
        if(i > middle) a[k] = aux[j++];
        else if(j > high) a[k] = aux[i++];
        else if(a[i] > a[j]) a[k] = aux[j++];
        else a[k] = aux[i++];
    }
}

/*version 2 bottom-up 归并排序 */
void buMergeSort(vector<int>& a){
    int n = a.size();
    vector<int> aux(n);
    for(int i = 1; i <= n; i = 2 * i){
        for(int low = 0; low < n - i; low += 2 * i){
            merge(a, aux, low, low + i - 1,  min(n - 1, low + 2 * i - 1));
        }
    }

}
```

### 堆排序

用数组表示的完美二叉树 complete binary tree

> 完美二叉树 VS 其他二叉树

![image.png](https://img.fuiboom.com/img/tree_type.png)

[动画展示](https://www.bilibili.com/video/av18980178/)

![image.png](https://img.fuiboom.com/img/heap.png)

核心代码

```cpp
//堆排序
//核心代码
void heapSort(vector<int>& a){
    // 1. 无序数组a
    // 2. 构建成一个大根堆
    for(int i = a.size() / 2 - 1; i >= 0; i--){
        sink(a, i, a.size());
    }
    //3. 交换a[0] 和 a[a.size()-1]
    //4. 然后把前面这段数组持续下沉保持堆结构，如此循环
    for (int i = a.size() - 1; i >= 1; i--){
        // 从后往前填充
        swap(a, 0, i);
        // 前面的长度减一
        sink(a, 0, i);
    }
}

void sink(vector<int>& a, int i, int length){
    while(true){
        // 左节点索引(从0开始，所以左节点为i*2+1)
        int l = 2 * i + 1;
        //右节点索引
        int r = 2 * i + 2;
        //idx保存根左右三者较大值的索引
        idx = i;
        // 存在左节点，左节点值较大，则取左节点
        if (l < length && a[l] > a[idx])  idx = l;
        // 存在右节点，右节点值较大，则取右节点
        if (r < length && a[r] > a[idx]) idx = r;
        //根节点较大，不用下沉
        if(idx == i) break;
        swap(a, i, idx);
        i = idx;
    }
}

```

## 参考

[十大经典排序](https://www.cnblogs.com/onepixel/p/7674659.html)

[二叉堆](https://labuladong.gitbook.io/algo/shu-ju-jie-gou-xi-lie/er-cha-dui-xiang-jie-shi-xian-you-xian-ji-dui-lie)

## 练习

- [ ] 手写快排、归并、堆排序
