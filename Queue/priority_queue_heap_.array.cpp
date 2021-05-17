#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
template <class T>
class PriorityQueue
{
    vector<T> heap;

public:
    //O(logn)
    void insert(T element)
    {

        heap.push_back(element);
        int childIndex = heap.size() - 1;
        int parentIndex = (childIndex - 1) / 2;
        while (childIndex > 0 && heap[parentIndex] > heap[childIndex])
        {

            T temp = heap[parentIndex];
            heap[parentIndex] = heap[childIndex];
            heap[childIndex] = temp;
            childIndex = parentIndex;
            parentIndex = (childIndex - 1) / 2;
        }
    }
    //O(logn)
    void remove()
    {
        if (!isEmpty())
        {
            heap[0] = heap[heap.size() - 1];
            heap.pop_back();
            int parentIndex = 0;
            int leftChild = parentIndex * 2 + 1;
            int rightChild = parentIndex * 2 + 2;
            int swapIndex = 0;
            while ((heap[parentIndex] > heap[leftChild] || heap[parentIndex] > heap[rightChild]) && parentIndex != (int)log2(heap.size()))
            {

                if (heap[leftChild] < heap[rightChild])
                {
                    swapIndex = leftChild;
                }
                else
                {
                    swapIndex = rightChild;
                }
                T temp = heap[parentIndex];
                heap[parentIndex] = heap[swapIndex];
                heap[swapIndex] = temp;
                parentIndex = swapIndex;
                leftChild = parentIndex * 2 + 1;
                rightChild = parentIndex * 2 + 2;
            }
        }
    }
    bool isEmpty()
    {
        return heap.size() == 0 ? true : false;
    }
    T getMin()
    {
        if (!isEmpty())
        {
            return heap[0];
        }
    }
    void print()
    {
        for (T value : heap)
        {
            cout << value << " ";
        }
    }
    int size()
    {
        return heap.size();
    }
};

main()
{
    PriorityQueue<int> queue;
    int choice, element;

    while (1)
    {
        cout << "Min = " << queue.getMin() << " Size = " << queue.size() << " isEmpty = " << queue.isEmpty() << endl;
        cout << "1. Insert\n";
        cout << "2. Remove\n";
        cout << "3. Get Min\n";
        cout << "4. Print\n";
        cout << "5. Exit\n";
        cout << "Enter your choice : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter Element : ";
            cin >> element;
            queue.insert(element);
            break;
        case 2:
            queue.remove();
            break;
        case 3:
            cout << "Size -> " << queue.getMin() << endl;
            break;
        case 4:
            queue.print();
            break;
        case 5:
            exit(0);

        default:
            cout << "invalid Choice\n";
        }
    }
}