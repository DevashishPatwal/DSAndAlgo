#include <iostream>
using namespace std;
ostream &operator<<(ostream &, AVLTree &);
class TreeNode
{
public:
    int key;
    int height = 0;
    TreeNode *parent;
    TreeNode *left;
    TreeNode *right;
    TreeNode(TreeNode *parent, int key)
    {
        this->key = key;
        this->parent = parent;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class AVLTree
{
    TreeNode *head = nullptr;
    int getHeight(TreeNode *);
    TreeNode *leftRotation(TreeNode *);
    TreeNode *rightRotation(TreeNode *x);
    TreeNode *insertHelper(TreeNode *, int, TreeNode *);
    int noOfChilds(TreeNode *);
    int getBalance(TreeNode *);

    friend ostream &operator<<(ostream &os, AVLTree &n);

public:
    void insert(int);
    void inOrderHelper(TreeNode *);
    void inorder();
};
ostream &operator<<(ostream &os, AVLTree &n)
{
    n.inorder();
    return os;
}
int AVLTree::getHeight(TreeNode *ptr)
{
    if (ptr == nullptr)
    {
        return -1;
    }
    else
    {
        return ptr->height;
    }
}
TreeNode *AVLTree::leftRotation(TreeNode *x)
{
    TreeNode *y = x->right;
    y->parent = x->parent;
    x->parent = y;
    x->right = y->left;
    if (x->right)
        x->right->parent = x;
    y->left = x;

    //fixing height after rotation
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}
TreeNode *AVLTree::rightRotation(TreeNode *x)
{
    TreeNode *y = x->left;
    y->parent = x->parent;
    x->parent = y;
    x->left = y->right;
    if (x->left)
        x->left->parent = x;
    y->right = x;
    //fixing height after rotation
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

TreeNode *AVLTree::insertHelper(TreeNode *ptr, int value, TreeNode *parent)
{
    if (ptr == nullptr)
    {
        return new TreeNode(parent, value);
    }
    else if (value > ptr->key)
    {
        ptr->right = insertHelper(ptr->right, value, ptr);
    }
    else
    {
        ptr->left = insertHelper(ptr->left, value, ptr);
    }

    ptr->height = max(getHeight(ptr->left), getHeight(ptr->right)) + 1;

    //fxing the tree in case insertion caused tree to be unbalanced
    if (abs(getBalance(ptr)) > 1)
    {
        // If there is an imbalance in left child of left subtree, then you perform a right rotation.
        if (ptr->left && getBalance(ptr->left) > 0)
        {
            return rightRotation(ptr);
        }
        // If there is an imbalance in left child of right subtree, then you perform a left-right rotation.
        else if (ptr->left && getBalance(ptr->left) < 0)
        {
            ptr->left = leftRotation(ptr->left);
            return rightRotation(ptr);
        }
        // If there is an imbalance in right child of right subtree, then you perform a left rotation.
        else if (ptr->right && getBalance(ptr->right) < 0)
        {
            return leftRotation(ptr);
        }
        // If there is an imbalance in right child of left subtree, then you perform a right-left rotation.
        else
        {
            ptr->right = rightRotation(ptr->right);
            return leftRotation(ptr);
        }
    }
    return ptr;
}
int AVLTree::noOfChilds(TreeNode *ptr)
{
    if (ptr->right && ptr->left)
    {
        return 2;
    }
    else if (ptr->right || ptr->left)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int AVLTree::getBalance(TreeNode *ptr)
{
    int noOfChild = noOfChilds(ptr);
    int balance = 0;

    if (noOfChild == 1)
    {
        if (ptr->left)
        {
            balance = ptr->left->height + 1;
        }
        else
        {
            balance = -(ptr->right->height + 1);
        }
    }
    else if (noOfChild == 2)
    {
        balance = ptr->left->height - ptr->right->height;
    }
    return balance;
}

void AVLTree::insert(int value)
{
    if (head == nullptr)
    {
        head = new TreeNode(nullptr, value);
    }
    else
    {
        head = insertHelper(head, value, nullptr);
    }
}
void AVLTree::inOrderHelper(TreeNode *root)
{
    if (root == nullptr)
    {
        return;
    }
    inOrderHelper(root->left);
    if (root->parent)
        cout << "Key = " << root->key << " Balance = " << getBalance(root) << " Height = " << root->height << " Parent = " << root->parent->key << endl;
    else
        cout << "Key = " << root->key << " Balance = " << getBalance(root) << " Height = " << root->height << " Parent = NULL" << endl;
    inOrderHelper(root->right);
}
void AVLTree::inorder()
{
    inOrderHelper(head);
}
int main()
{

    AVLTree tree;
    tree.insert(22);
    tree.insert(18);
    tree.insert(20);
    tree.insert(21);
    tree.insert(43);
    tree.insert(9);
    tree.insert(30);
    tree.insert(6);
    tree.insert(35);
    tree.inorder();
}