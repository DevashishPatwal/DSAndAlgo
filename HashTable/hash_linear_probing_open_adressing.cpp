#include <iostream>
using namespace std;
template <class T, class S>

class item
{
public:
    T key = -1;
    S value = "";
};
template <class T, class S>

class Dictionary
{
    int capacity;
    int size = 0;
    item<T, S> *bucket;
    int hash(T key, int bucketSize)
    {
        return key % bucketSize;
    }
    void resize(int newCapacity)
    {
        item<T, S> *newBucket = new item<T, S>[newCapacity];
        for (int i = 0; i < capacity; i++)
        {
            T key = bucket[i].key;
            if (key >= 0)
            {
                int index = hash(key, newCapacity);

                while (newBucket[index].key != -1)
                {
                    index = (index + 1) % newCapacity;
                }
                newBucket[index].key = key;
                newBucket[index].value = bucket[i].value;
            }
        }
        delete[] bucket;
        bucket = newBucket;
        capacity = newCapacity;
    }

public:
    Dictionary()
    {
        capacity = 8;
        bucket = new item<T, S>[capacity];
    }
    //function to add a key-value pair in dictionary
    void add(T key, S value)
    {
        int index = hash(key, capacity);

        //loop till either index is empty or key is already present
        while (bucket[index].key > 0 && bucket[index].key != key)
        {
            index = (index + 1) % capacity;
        }

        //size increases only if key already not exists
        if (bucket[index].key != key)
        {
            ++size;
        }
        bucket[index].key = key;
        bucket[index].value = value;

        //grow table
        if (loadFactor() >= 0.75)
        {
            resize(capacity * 2);
        }
    }
    // function to check where a key is present, return -1 if not found otherwise index of found key
    int exists(T key)
    {

        int index = hash(key, capacity);
        //loop until either key is found or empty index found
        while (bucket[index].key != -1 && bucket[index].key != key)
        {
            index = (index + 1) % capacity;
        }
        //return -1 if empty index found
        if (bucket[index].key == -1)
        {
            return -1;
        }
        else
        {
            return index;
        }
    }
    //function to get a value of given key
    S get(T key)
    {
        int index = exists(key);

        if (index != -1)
        {
            return bucket[index].value;
        }
        else
        {
            return "-1";
        }
    }
    //function to remove a given key from dictionary
    void remove(T key)
    {
        int index = exists(key);
        if (index != -1)
        {
            bucket[index].key = -2;
            --size;
        }
        //shrink table
        if (loadFactor() <= 0.25 && capacity > 8)
        {
            cout << "what";
            resize(capacity / 2);
        }
    }
    void getKeys()
    {
        int j = 0;
        T *array = new T[size]{0};
        //loop until either key is found or empty index found
        for (int i = 0; i < capacity; i++)
            if (bucket[i].key != -1)
            {
                cout << bucket[i].key << ",";
            }
        cout << '\n';
    }
    void getValues()
    {
        int j = 0;
        T *array = new T[size]{0};
        //loop until either key is found or empty index found
        for (int i = 0; i < capacity; i++)
            if (bucket[i].key != -1)
            {
                cout << bucket[i].value << ",";
            }
        cout << '\n';
    }
    void display()
    {
        for (int i = 0; i < capacity; i++)
        {
            cout << "Index :" << i << " Key : " << bucket[i].key << " Value : " << bucket[i].value << endl;
        }
    }
    int _size()
    {
        return size;
    }
    int _capacity()
    {
        return capacity;
    }
    float loadFactor()
    {
        return (float)size / capacity;
    }
};

int main()
{
    int choice, key;
    string value;
    Dictionary<int, string> students;
    while (1)
    {
        cout << "Size = " << students._size() << " Capacity = " << students._capacity() << " Load Factor = " << students.loadFactor() << endl;
        cout << "1. Add\n";
        cout << "2. Get\n";
        cout << "3. Exists\n";
        cout << "4. Delete Key\n";
        cout << "5. Exit\n";
        cout << "6. Display\n";
        cout << "7. Get Keys\n";
        cout << "8. Get Values\n";
        cout << "Enter your choice : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter Key : ";
            cin >> key;
            cout << "Enter Value : ";
            cin >> value;
            students.add(key, value);
            break;
        case 2:
            cout << "Enter Key : ";
            cin >> key;
            cout << "value -> " << students.get(key) << endl;
            break;
        case 3:
            cout << "Enter Key : ";
            cin >> key;
            cout << (students.exists(key) != -1 ? "True\n" : "False\n");
            break;
        case 4:
            cout << "Enter Key : ";
            cin >> key;
            students.remove(key);
            break;
        case 5:
            exit(0);
        case 6:
            students.display();
            break;
        case 7:
            students.getKeys();
            break;
        case 8:
            students.getValues();
            break;

        default:
            cout << "invalid Choice\n";
        }
    }
}