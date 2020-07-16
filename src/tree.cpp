#include <algorithm>
#include <stack>

using namespace std;

// 二叉树的前中后序遍历
// 二叉树和链表的转换
template <typename T> struct treeNode{
    T val;
    treeNode* left;
    treeNode* right;
    treeNode* parent;
};

// 前序
//递归
template <typename T> 
void preOrderRecursion(treeNode<T>* root){
    if (root == nullptr) return;
    cout<<root->val<<" "<<endl;
    preOrderRecursion(root->left);
    preOrderRecursion(root->right);
}

void preOrder(treeNoder<T>* root){
    if (root == nullptr) return;
    stack<treeNode<T>*> treeStack;
    treeStack.push(root);
    while(!treeStack.empty()){
        treeNode* node = treeStack.pop();
        if(node->right != nullptr) treeStack.push(node->right);
        if(node->left != nullptr) treeStack.push(node->left);
    }
}

// 中序
template <typename T>
void inOrderRecursion(treeNode<T>* root){
    if (root == nullptr) return;
    inOrderRecursion(root->left);
    cout<<root->val<<endl;
    inOrderRecursion(root->right);
}

template <typename T>
void inOrder(treeNode<T>* root){
    if (root == nullptr) return;
    stack<treeNode<T>*> S;

    while(true){
        if(root != nullptr){
            S.push(root);
            root = root->left;
        }
        else if(!S.empty()){
            treeNode<T>* root = S.pop(); 
            cout<<root->val<<endl;// 访问祖先节点
            root = root->right; //遍历右子树
        }
        else break;
    }
}

//后续
// 递归
template <typename T>
void postOrder(treeNode<T>* root){
    if(root == nullptr) return;
    postOrder(root->left);
    postOrder(root->right);
    cout<<root->val<<endl;
}

// 迭代
    vector<int> postorderTraversal(TreeNode* root) {
        if (root == nullptr) return {};
        stack<TreeNode*> stk;
        stk.push(root);
        vector<int> res;
        while (!stk.empty()) {
            TreeNode* node = stk.top();
            if (node == nullptr) {
                stk.pop();
                res.push_back(stk.top()->val);
                stk.pop();
                continue;
            }
            stk.push(nullptr);
            if (node->right) {
                stk.push(node->right);
            }
            if (node->left) {
                stk.push(node->left);
            }
        }
        return res;
    }

