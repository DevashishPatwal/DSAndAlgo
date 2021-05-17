#include <iostream>
#include <queue>
using namespace std;

template <class T>
class TreeNode
{
public:
    TreeNode<T> *leftChild;
    T item;
    TreeNode<T> *rightChild;
    TreeNode(T item)
    {
        this->item = item;
        this->leftChild = nullptr;
        this->rightChild = nullptr;
    }
    TreeNode(TreeNode<T> leftChild, T item, TreeNode<T> rightChild)
    {
        this->leftChild = leftChild;
        this->item = item;
        this->rightChild = rightChild;
    }
};

template <class T>
class BinaryTree
{

    TreeNode<T> *root = nullptr;
    int size;

    T minHelper(TreeNode<T> *node)
    {
        if (node == nullptr)
        {
            return -1;
        }
        else if (node->leftChild == nullptr)
        {
            return node->item;
        }
        return minHelper(node->leftChild);
    }
    T maxHelper(TreeNode<T> *node)
    {
        if (node == nullptr)
        {
            return -1;
        }
        else if (node->rightChild == nullptr)
        {
            return node->item;
        }
        return maxHelper(node->rightChild);
    }
    int countHelper(TreeNode<T> *root)
    {
        if (root == nullptr)
        {
            return 0;
        }
        return 1 + countHelper(root->leftChild) + countHelper(root->rightChild);
    }
    void inorderHelper(TreeNode<T> *root)
    {
        if (root->leftChild)
            inorderHelper(root->leftChild);
        cout << root->item << " ";
        if (root->rightChild)
            inorderHelper(root->rightChild);
    }
    TreeNode<T> *deleteNodeWithZeroOrOneChildren(TreeNode<T> *root, TreeNode<T> *node)
    {
        if (root == node)
        {
            TreeNode<T> *returnAddress = nullptr;
            if (node->leftChild)
            {
                returnAddress = node->leftChild;
            }
            else if (node->rightChild)
            {
                returnAddress = node->rightChild;
            }
            delete root;
            return returnAddress;
        }
        if (root->item > node->item)
        {
            root->leftChild = deleteNodeWithZeroOrOneChildren(root->leftChild, node);
        }
        else
        {
            root->rightChild = deleteNodeWithZeroOrOneChildren(root->rightChild, node);
        }

        return root;
    }
    TreeNode<T> *searchHelper(TreeNode<T> *root, T valueToSearch)
    {
        if (root == nullptr)
        {
            return nullptr;
        }
        if (root->item == valueToSearch)
        {
            return root;
        }
        else if (root->item > valueToSearch)
        {
            return searchHelper(root->leftChild, valueToSearch);
        }
        else
        {
            return searchHelper(root->rightChild, valueToSearch);
        }
    }
    int noOfChild(TreeNode<T> *node)
    {
        if (node->rightChild && node->leftChild)
        {
            return 2;
        }
        else if (node->rightChild == nullptr && node->leftChild == nullptr)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    void preorderHelper(TreeNode<T> *root)
    {
        cout << root->item << " ";
        if (root->leftChild)
            preorderHelper(root->leftChild);
        if (root->rightChild)
            preorderHelper(root->rightChild);
    }
    void postorderHelper(TreeNode<T> *root)
    {
        if (root->leftChild)
            postorderHelper(root->leftChild);
        if (root->rightChild)
            postorderHelper(root->rightChild);
        cout << root->item << " ";
    }
    int heightHelper(TreeNode<T> *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        int leftCount = heightHelper(node->leftChild);
        int rightCount = heightHelper(node->rightChild);
        if (leftCount > rightCount)
        {
            return leftCount + 1;
        }
        else
        {

            return rightCount + 1;
        }
    }
    TreeNode<T> *insertHelper(TreeNode<T> *node, T value)
    {
        if (node == nullptr)
        {
            ++size;
            return new TreeNode<T>(value);
        }
        if (value > node->item)
        {
            node->rightChild = insertHelper(node->rightChild, value);
        }
        else
        {
            node->leftChild = insertHelper(node->leftChild, value);
        }
        return node;
    }
    TreeNode<T> *inorderSuccessor(TreeNode<T> *node)
    {
        node = node->rightChild;
        while (node->leftChild)
        {
            node = node->leftChild;
        }
        return node;
    }
    void nukeHelper(TreeNode<T> *node)
    {

        if (node == nullptr)
        {
            return;
        }
        nukeHelper(node->leftChild);
        nukeHelper(node->rightChild);
        cout << "deleting " << node->item << "...\n";
        delete node;
    }

public:
    BinaryTree()
    {
        size = 0;
    }
    ~BinaryTree()
    {
        delete root;
    }
    void insert(T value)
    {
        root = insertHelper(root, value);
    }

    void display()
    {
        display(root);
    }
    void display(TreeNode<T> *node)
    {
        if (node == nullptr)
        {
            return;
        }
        display(node->leftChild);
        cout << node->item << " ";
        display(node->rightChild);
    }

    //O(n/2) - space
    //O(n) - Time
    void BFS()
    {
        queue<TreeNode<T> *> q;
        q.push(root);
        while (!q.empty())
        {
            TreeNode<T> *node = q.front();
            cout << node->item << " ";
            if (node->leftChild != nullptr)
                q.push(node->leftChild);
            if (node->rightChild != nullptr)
                q.push(node->rightChild);
            q.pop();
        }
        cout << endl;
    }

    T min()
    {
        minHelper(root);
    }
    int height()
    {
        heightHelper(root);
    }

    T max()
    {
        maxHelper(root);
    }
    bool search(T valueToSearch)
    {
        return searchHelper(root, valueToSearch) ? 1 : 0;
    }

    int count()
    {
        return countHelper(root);
    }

    void inorder()
    {
        inorderHelper(root);
    }

    void postorder()
    {
        postorderHelper(root);
    }

    void preorder()
    {
        preorderHelper(root);
    }

    void remove(int valueToDelete)
    {
        TreeNode<T> *addOfNodeToDelete = searchHelper(root, valueToDelete);
        cout << "Log Item " << addOfNodeToDelete->item;
        if (addOfNodeToDelete == nullptr)
        {
            return;
        }
        else
        {
            int noOfChildrens = noOfChild(addOfNodeToDelete);
            cout << "Log childrens " << noOfChildrens;
            switch (noOfChildrens)
            {
            case 0:
                root = deleteNodeWithZeroOrOneChildren(root, addOfNodeToDelete);
                break;
            case 1:
                root = deleteNodeWithZeroOrOneChildren(root, addOfNodeToDelete);
                break;
            case 2:
                TreeNode<T> *inOrderSuccessor = inorderSuccessor(addOfNodeToDelete);
                addOfNodeToDelete->item = inOrderSuccessor->item;
                root = deleteNodeWithZeroOrOneChildren(root, inOrderSuccessor);

                break;
            }
        }
    }
    void nuke()
    {
        nukeHelper(root);
        root = nullptr;
    }

    bool isEmpty()
    {
        return root ? 0 : 1;
    }
};
int main()
{
    int choice;
    BinaryTree<int> tree;
    tree.insert(10);
    tree.insert(4);
    tree.insert(14);
    tree.insert(2);
    tree.insert(12);
    tree.insert(16);
    tree.insert(18);
    int value;
    while (true)
    {
        if (!tree.isEmpty())
        {

            cout << "Min : " << tree.min()
                 << " Max : " << tree.max()
                 << " Count : " << tree.count() << endl;
            cout << "Height : " << tree.height() << endl;
        }
        cout << "1. Insert" << endl;
        cout << "2. Delete" << endl;
        cout << "3. Search" << endl;
        cout << "4. BFS" << endl;
        cout << "5. Inorder/Sorted" << endl;
        cout << "6. Postorder" << endl;
        cout << "7. Preorder" << endl;
        cout << "Enter your choice : " << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            cin >> value;
            tree.insert(value);
            break;
        case 2:
            cin >> value;
            tree.remove(value);
            break;
        case 3:
            cin >> value;
            cout << tree.search(value);

            break;
        case 4:
            tree.BFS();
            break;
        case 5:
            tree.inorder();
            break;
        case 6:
            tree.postorder();
            break;
        case 7:
            tree.preorder();
            break;
        case 8:
            tree.nuke();
            break;
        default:
            cout << "Invalid Choice \n";
        }
    }
}

/*
 insert // insert value into tree ✅
 get_node_count // get count of values stored ✅
 print_values // prints the values in the tree, from min to max ✅
 delete_tree ✅
 is_in_tree // returns true if given value exists in the tree ✅
 get_height // returns the height in nodes (single node's height is 1) ✅
 get_min // returns the minimum value stored in the tree ✅
 get_max // returns the maximum value stored in the tree ✅
 is_binary_search_tree
 delete_value ✅
 get_successor ✅
 */