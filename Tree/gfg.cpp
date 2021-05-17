#include <iostream>
#include <queue>
#include <stack>
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
private:
    TreeNode<T> *root = nullptr;

    TreeNode<T> *insertHelper(TreeNode<T> *node, T value)
    {
        if (node == nullptr)
        {
            size += 1;
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
    TreeNode<T> *treeBuilder()
    {
        int data, choice;
        cout << "Enter the data : ";
        cin >> data;
        TreeNode<T> *currentNode = new TreeNode<T>(data);
        cout << "Do you have left child of " << data << " ";
        cin >> choice;
        if (choice == 1)
        {
            currentNode->leftChild = treeBuilder();
        }
        cout << "Do you have right child of " << data << " ";
        cin >> choice;
        if (choice == 1)
        {
            currentNode->rightChild = treeBuilder();
        }
        return currentNode;
    }
    int height(TreeNode<T> *node)
    {
        if (node == nullptr)
        {
            return -1;
        }

        return max(height(node->leftChild), height(node->rightChild)) + 1;
    }
    /* O(n)
    *  First pair represent height second represents diameter
    */
    pair<int, int> diameter(TreeNode<T> *root)
    {
        if (root == nullptr)
        {
            return {-1, 0};
        }
        pair<int, int> left = diameter(root->leftChild);
        pair<int, int> right = diameter(root->rightChild);
        int height = 1 + max(left.first, right.first);
        int diameter = max((left.first + right.first + 2), max(left.second, right.second));
        return {height, diameter};
    }
    /*
      Complexity : O(n)
    */
    bool pathFromRoot(vector<int> &path, TreeNode<T> *root, int element)
    {
        if (root == nullptr)
        {
            return false;
        }
        path.push_back(root->item);
        if (root->item == element)
        {
            return true;
        }
        bool isPresentInLeft = pathFromRoot(path, root->leftChild, element);
        bool isPresentInRight = pathFromRoot(path, root->rightChild, element);
        //check if element is not present in either left or right subtree pop path element
        if (isPresentInLeft + isPresentInRight == 0)
            path.pop_back();
        return isPresentInLeft || isPresentInRight;
    } //O(n)
    bool commonAncestor(TreeNode<T> *root, int a, int b, T &common)
    {
        if (root == nullptr)
        {
            return false;
        }
        bool isPresentInLeftSubtree = commonAncestor(root->leftChild, a, b, common);
        bool isPresentInRightSubtree = commonAncestor(root->rightChild, a, b, common);
        //if both elements are present in left and right subtree then this node is common ancestor
        if (isPresentInLeftSubtree && isPresentInRightSubtree)
        {
            common = root->item;
        }

        if (root->item == a || root->item == b)
        {
            //check whether node itself is common ancestor
            if (isPresentInLeftSubtree || isPresentInRightSubtree)
            {
                common = root->item;
            }
            return true;
        }
        return isPresentInLeftSubtree || isPresentInRightSubtree;
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
    void leftViewRecursive(TreeNode<T> *node, int level, int &maxLevel)
    {
        if (node == nullptr)
        {
            return;
        }
        if (level > maxLevel)
        {
            cout << node->item << " ";
            maxLevel = level;
        }
        leftViewRecursive(node->leftChild, level + 1, maxLevel);
        leftViewRecursive(node->rightChild, level + 1, maxLevel);
    }
    void rightViewRecursive(TreeNode<T> *node, int level, int &maxLevel)
    {
        if (node == nullptr)
        {
            return;
        }
        if (level > maxLevel)
        {
            cout << node->item << " ";
            maxLevel = level;
        }
        rightViewRecursive(node->rightChild, level + 1, maxLevel);
        rightViewRecursive(node->leftChild, level + 1, maxLevel);
    }
    // first pair represents height second isBalanced property. O(n)
    pair<int, int> isBalanced(TreeNode<T> *root)
    {
        if (root == nullptr)
        {
            return {-1, 1};
        }
        pair<int, int> leftSubtree = isBalanced(root->leftChild);
        pair<int, int> rightSubtree = isBalanced(root->rightChild);
        int height = max(leftSubtree.first, rightSubtree.first) + 1;
        pair<int, int> currentNode = {height, 1};
        //left and right subtree should be balanced
        if (abs(leftSubtree.first - rightSubtree.first) > 1 || leftSubtree.second == 0 || rightSubtree.second == 0)
        {
            currentNode.second = 0;
        }
        return currentNode;
    }

    bool search(TreeNode<T> *root, T elementToSearch)
    {
        if (root == NULL)
        {
            return false;
        }
        else if (root->item == elementToSearch)
        {
            return true;
        }
        bool left = search(root->leftChild, elementToSearch);
        bool right = search(root->rightChild, elementToSearch);
        return left || right;
    }

public:
    int size;

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
    void insert()
    {
        root = treeBuilder();
    }

    void display()
    {
        display(root);
    }

    //Level Order Traversal
    void levelOrderTraversal()
    {
        int level = 0;
        queue<TreeNode<T> *> nodesToVisit;
        nodesToVisit.push(root);
        nodesToVisit.push(NULL);
        cout << "Level " << level << " : ";
        while (nodesToVisit.size() != 1)
        {
            TreeNode<T> *node = nodesToVisit.front();
            nodesToVisit.pop();
            if (node == NULL)
            {
                level += 1;
                cout << "\nLevel " << level << " : ";
                nodesToVisit.push(NULL);
                continue;
            }
            cout << node->item << " ";
            if (node->leftChild)
                nodesToVisit.push(node->leftChild);
            if (node->rightChild)
                nodesToVisit.push(node->rightChild);
        }
        cout << "\n";
    }
    //Reverse Level Order Traversal
    void reverseLevelOrderTraversal()
    {
        int level = 0;
        queue<TreeNode<T> *> nodesToVisit;
        nodesToVisit.push(root);
        nodesToVisit.push(NULL);
        stack<TreeNode<T> *> stack;
        while (nodesToVisit.size() != 1)
        {
            TreeNode<T> *node = nodesToVisit.front();
            stack.push(node);
            nodesToVisit.pop();
            if (node == NULL)
            {
                level += 1;
                nodesToVisit.push(NULL);
                continue;
            }
            if (node->rightChild)
                nodesToVisit.push(node->rightChild);
            if (node->leftChild)
                nodesToVisit.push(node->leftChild);
        }
        cout << "Level " << level << " : ";
        while (!stack.empty())
        {
            TreeNode<T> *node = stack.top();
            stack.pop();
            if (node == NULL)
            {
                level -= 1;
                cout << "\nLevel " << level << " : ";
                continue;
            }
            cout << node->item << " ";
        }

        cout << "\n";
    }

    void rightView()
    {
        queue<TreeNode<T> *> nodesToVisit;
        nodesToVisit.push(root);
        nodesToVisit.push(NULL);
        while (nodesToVisit.size() != 1)
        {
            TreeNode<T> *node = nodesToVisit.front();
            nodesToVisit.pop();
            if (node == NULL)
            {
                nodesToVisit.push(NULL);
                continue;
            }
            if (nodesToVisit.front() == NULL)
            {
                cout << node->item << " ";
            }
            if (node->leftChild)
                nodesToVisit.push(node->leftChild);
            if (node->rightChild)
                nodesToVisit.push(node->rightChild);
        }
        cout << "\n";
    }
    void leftView()
    {
        queue<TreeNode<T> *> nodesToVisit;
        nodesToVisit.push(NULL);
        nodesToVisit.push(root);
        while (nodesToVisit.size() != 1)
        {
            TreeNode<T> *node = nodesToVisit.front();
            nodesToVisit.pop();
            if (node == NULL)
            {
                cout << nodesToVisit.front()->item << " ";
                nodesToVisit.push(NULL);
                continue;
            }

            if (node->leftChild)
                nodesToVisit.push(node->leftChild);
            if (node->rightChild)
                nodesToVisit.push(node->rightChild);
        }
        cout << "\n";
    }

    void leftViewRecursive()
    {
        int maxLevel = 0;
        leftViewRecursive(root, 1, maxLevel);
        cout << "\n";
    }

    void rightViewRecursive()
    {
        int maxLevel = 0;
        rightViewRecursive(root, 1, maxLevel);
        cout << "\n";
    }
    bool isEmpty()
    {
        return root ? 0 : 1;
    }

    int height()
    {
        return height(root);
    }

    int diameter()
    {
        return diameter(root).second;
    }

    /*return path as vector and empty vector if no path exists,helper function
    *  Complexity : O(n)
    */
    vector<T> pathFromRoot(T element)
    {
        vector<T> path;
        pathFromRoot(path, root, element);
        return path;
    }

    //helper function
    T commonAncestor(T a, T b)
    {
        T common;
        commonAncestor(root, a, b, common);
        return common;
    }
    T commonAncestorEasy(T a, T b)
    {
        int commonAncestor = -1, i = 0;
        vector<T> pathA = pathFromRoot(a);
        vector<T> pathB = pathFromRoot(b);
        //if one of the path doesn't exists then return -1
        if (pathA.empty() || pathB.empty())
        {
            return commonAncestor;
        }
        for (i = 0; i < min(pathA.size(), pathB.size()); i++)
        {
            if (pathA[i] != pathB[i])
            {
                commonAncestor = pathA[i - 1];
                break;
            }
        }
        if (i == min(pathA.size(), pathB.size()))
        {
            commonAncestor = pathA[i - 1];
        }
        return commonAncestor;
    }

    //helper function
    bool search(T elementToSearch)
    {
        return search(root, elementToSearch);
    }

    bool isBalanced() { return isBalanced(root).second; }
    int pathBetween(T a, T b)
    {
        int commonAncestor = -1, i = 0;
        vector<T> pathA = pathFromRoot(a);
        vector<T> pathB = pathFromRoot(b);

        for (i = 0; i < min(pathA.size(), pathB.size()); i++)
        {
            if (pathA[i] != pathB[i])
            {
                commonAncestor = i;
                break;
            }
        }
        return (pathA.size() - commonAncestor) + (pathB.size() - commonAncestor);
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
    // tree.insert();
    // tree.display();
    cout << "Height : " << tree.height() << endl;
    cout << "Inorder : ";
    tree.display();
    cout << endl;
    cout << "Size : " << tree.size << endl;
    cout << "Balanced : " << tree.isBalanced() << endl;
    cout << "Commom Ancestor : " << tree.commonAncestor(12, 18) << endl;
    cout << "Distance of Path : " << tree.pathBetween(2, 18) << endl;
    cout << "Search : " << tree.search(12);

    // cout << "Diameter  : " << tree.diameter() << endl;
    // vector<int> path = tree.pathFromRoot(11);
    // if (path.empty())
    // {
    //     cout << "Element not present";
    // }
    // else
    // {

    //     cout << "Path : ";
    //     for (auto i : path)
    //     {
    //         cout << i << " ";
    //     }
    // }
    // cout << "\n";
    // int value;
    // while (true)
    // {
    //     if (!tree.isEmpty())
    //     {
    //         tree.display();
    //     }
    //     cout << "\n1. Level Order Traversal" << endl;
    //     cout << "2. Reverse Level Order Traversal" << endl;
    //     cout << "3. Height" << endl;
    //     cout << "4. Right View" << endl;
    //     cout << "5. Left View" << endl;
    //     cout << "6. Postorder" << endl;
    //     cout << "7. Preorder" << endl;
    //     cout << "Enter your choice : " << endl;
    //     cin >> choice;
    //     switch (choice)
    //     {
    //     case 1:
    //         tree.levelOrderTraversal();
    //         break;
    //     case 2:
    //         tree.reverseLevelOrderTraversal();
    //         break;
    //     case 3:
    //         tree.height();
    //         break;
    //     case 4:
    //         tree.rightView();
    //         tree.rightViewRecursive();
    //         break;
    //     case 5:
    //         tree.leftView();
    //         tree.leftViewRecursive();
    //         break;
    //     default:
    //         cout << "Invalid Choice \n";
    // }
    // }
}
