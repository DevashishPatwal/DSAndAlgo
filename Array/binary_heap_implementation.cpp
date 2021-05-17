#include <iostream>
#include <vector>
#include <exception>
using namespace std;

class outOfBoundsException : public exception
{
public:
    const char *what()
    {
        return "Index out of bounds";
    }
};
// A heap  class

class Heap
{
    vector<int> heapArray;
    void swap(int parentIndex, int childIndex)
    {
        int temp = heapArray[parentIndex];
        heapArray[parentIndex] = heapArray[childIndex];
        heapArray[childIndex] = temp;
    }

public:
    void insert(int element)
    {
        heapArray.push_back(element);
        sift_up(heapArray.size() - 1);
    }
    void sift_up(int childIndex)
    {
        int parentIndex = (childIndex - 1) / 2;

        while (childIndex && heapArray[parentIndex] < heapArray[childIndex])
        {
            swap(parentIndex, childIndex);
            childIndex = parentIndex;
            parentIndex = (childIndex - 1) / 2;
        }
    }
    int extract_max()
    {
        return remove(0);
    }
    int remove(int index)
    {
        if (is_empty())
        {
            return 0;
        }
        else if (index >= get_size())
        {
            throw outOfBoundsException();
        }
        int removedElement = heapArray[index];
        heapArray[index] = heapArray[heapArray.size() - 1];
        heapArray.pop_back();
        sift_down(index);
        return removedElement;
    }
    void sift_down(int parentIndex)
    {
        int leftChildIndex = parentIndex * 2 + 1;
        int rightChildIndex = parentIndex * 2 + 2;
        int maxNodeIndex = -1;
        int heapSize = get_size();
        while (leftChildIndex < heapSize)
        {

            if (rightChildIndex >= heapSize)
            {
                maxNodeIndex = leftChildIndex;
            }
            else if (heapArray[leftChildIndex] > heapArray[rightChildIndex])
            {
                maxNodeIndex = leftChildIndex;
            }
            else
            {
                maxNodeIndex = rightChildIndex;
            }
            if (heapArray[parentIndex] < heapArray[maxNodeIndex])
            {
                swap(parentIndex, maxNodeIndex);
                parentIndex = maxNodeIndex;
                leftChildIndex = parentIndex * 2 + 1;
                rightChildIndex = parentIndex * 2 + 2;
            }
            else
            {
                break;
            }
        }
    }
    bool is_empty()
    {
        return heapArray.size() == 0 ? true : false;
    }
    int get_max()
    {
        return heapArray[0];
    }
    int get_size()
    {
        return heapArray.size();
    }

    void printHeap()
    {
        if (is_empty())
        {
            cout << "Empty List\n";
            return;
        }
        for (auto element : heapArray)
        {
            cout << element << ',';
        }
    }
};
// A util class containing heapify and heapSort Function
class HeapUtils
{
    void static swap(int parentIndex, int maxNodeIndex, int *heapArray)
    {
        int temp = heapArray[parentIndex];
        heapArray[parentIndex] = heapArray[maxNodeIndex];
        heapArray[maxNodeIndex] = temp;
    }
    void static sift_down(int *heapArray, int heapSize, int parentIndex)
    {
        int leftChildIndex = parentIndex * 2 + 1;
        int rightChildIndex = parentIndex * 2 + 2;
        int maxNodeIndex = 0;
        while (leftChildIndex < heapSize)
        {
            if (rightChildIndex >= heapSize)
            {
                maxNodeIndex = leftChildIndex;
            }
            else if (heapArray[leftChildIndex] > heapArray[rightChildIndex])
            {
                maxNodeIndex = leftChildIndex;
            }
            else
            {
                maxNodeIndex = rightChildIndex;
            }
            if (heapArray[parentIndex] >= heapArray[maxNodeIndex])
            {
                break;
            }
            else
            {
                swap(parentIndex, maxNodeIndex, heapArray);
                parentIndex = maxNodeIndex;
                leftChildIndex = parentIndex * 2 + 1;
                rightChildIndex = parentIndex * 2 + 2;
            }
        }
    }

    static int extract_max(int *heapArray, int size)
    {
        int max = heapArray[0];
        heapArray[0] = heapArray[size - 1];
        sift_down(heapArray, size - 1, 0);
        return max;
    }
    static void heapSortHelper(int *heapArray, int size)
    {
        if (size == 1)
        {
            return;
        }
        heapArray[size - 1] = extract_max(heapArray, size);
        heapSortHelper(heapArray, size - 1);
    }

public:
    static void heapify(int *heapArray, int size)
    {
        for (int i = ((size - 2) / 2); i >= 0; i--)
        {
            sift_down(heapArray, size, i);
        }
    }
    static void heapSort(int *heapArray, int size)
    {
        heapify(heapArray, size);
        heapSortHelper(heapArray, size);
    }
    static void print(int *a, int size)
    {

        for (int i = 0; i < size - 1; i++)
        {
            cout << a[i] << ",";
        }
        cout << a[size - 1] << endl;
    }
};
int main()
{

    // int a[] = {2, 45, 23, 12, 1, 87, 55, 0, 18, 2, 2, 15};
    // // int a[] = {11, 61, 13, 5, 8, 4, 7, 2, 10, 55};
    // int size = sizeof(a) / sizeof(int);
    // cout << "Original : ";
    // HeapUtils::print(a, size);

    // HeapUtils::heapify(a, size);
    // cout << "\nHeapify : ";
    // HeapUtils::print(a, size);

    // HeapUtils::heapSort(a, size);
    // cout << "\nSorted : ";
    // HeapUtils::print(a, size);
    int choice, value;
    Heap h;
    while (1)
    {
        cout << "Size : " << h.get_size() << " isEmpty : " << h.is_empty() << endl
             << "1. Insert\n"
             << "2. Remove\n"
             << "3. Extract Max\n"
             << "4. Exit\n"
             << "Enter your choice : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Insert element value : ";
            cin >> value;
            h.insert(value);
            break;
        case 2:
            cout << "Input index to remove : ";
            cin >> value;
            cout << "Removed Element = " << h.remove(value) << endl;
            break;
        case 3:
            cout << "Max extracted = " << h.extract_max() << endl;
            break;
        case 4:
            exit(0);
        default:
            cout << "Enter a valid option...\n";
        }
    }

    try
    {
        h.extract_max();
    }
    catch (exception ex)
    {
        cout << ex.what();
    }

    h.printHeap();
    return 0;
}

/*
 Implement a max-heap:
 insert ✅
 sift_up - needed for insert ✅
 get_max - returns the max item, without removing it ✅
 get_size() - return number of elements stored ✅
 is_empty() - returns true if heap contains no elements ✅
 extract_max - returns the max item, removing it ✅
 sift_down - needed for extract_max ✅
 remove(i) - removes item at index x ✅
 heapify - create a heap from an array of elements, needed for heap_sort ✅
 heap_sort() - take an unsorted array and turn it into a sorted array in-place using a max heap or min heap ✅
 */