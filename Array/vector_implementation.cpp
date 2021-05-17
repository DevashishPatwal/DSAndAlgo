#include <iostream>
using namespace std;
template <class T>
class Vector
{

    int count = 0;
    int _capacity = 2;
    T *array = nullptr;

public:
    Vector();
    // Vector(const Vector<T> &);
    bool insert(int index, T item);
    void prepend(T item);
    void remove(T item);
    T deletee(int index);
    int find(T item);
    T pop();
    void push(T item);
    int at(int index);
    bool is_empty();
    int size();
    int capacity();
    void print();
    ostream operator<<(ostream &os);

private:
    void
    resize(int newCapacity);
};

template <class T>
void Vector<T>::resize(int newCapacity)
{

    T *temp = new T[newCapacity];
    for (int i = 0; i < count; i++)
    {
        temp[i] = array[i];
    }
    delete[] array;
    array = temp;
    _capacity = newCapacity;
}
template <class T>
Vector<T>::Vector()
{
    array = new T[_capacity];
}
template <class T>
void Vector<T>::print()
{
    for (int i = 0; i < count; i++)
    {
        cout << array[i] << ' ';
    }
    cout << '\n';
}
template <class T>
int Vector<T>::size()
{
    return count;
}
template <class T>
int Vector<T>::capacity()
{
    return _capacity;
}
template <class T>
bool Vector<T>::is_empty()
{
    return count == 0 ? true : false;
}
template <class T>
int Vector<T>::at(int index)
{
    if (index >= count || index < 0)
        return -1;
    return array[index];
}
template <class T>
void Vector<T>::push(T item)
{
    if (count == _capacity)
    {
        resize(_capacity * 2);
    }
    array[count++] = item;
}

template <class T>
T Vector<T>::pop()
{
    if (count > 0)
    {
        T item = array[count - 1];
        count -= 1;
        if (count <= _capacity / 4)
        {
            resize(_capacity / 2);
        }
        return item;
    }
}

template <class T>
int Vector<T>::find(T item)
{
    for (int i = 0; i < count; i++)
    {
        if (array[i] == item)
        {
            return i;
        }
    }
    return -1;
}
template <class T>
T Vector<T>::deletee(int index)
{
    if (index >= count || index < 0)
    {
        return 0;
    }
    T item = array[index];

    for (int i = index; i < count - 1; i++)
    {
        array[i] = array[i + 1];
    }
    --count;
    return item;
}
//! Important
template <class T>
void Vector<T>::remove(T item)
{
    for (int i = 0; i < count; i++)
    {
        if (array[i] == item)
            deletee(i--);
    }
}
template <class T>
void Vector<T>::prepend(T item)
{
    insert(0, item);
}
template <class T>
bool Vector<T>::insert(int index, T item)
{
    if (index >= count || index < 0)
    {
        return false;
    }
    else if (count == _capacity)
    {
        resize(_capacity * 2);
    }

    for (int i = count; i > index; i--)
    {
        array[i] = array[i - 1];
    }
    array[index] = item;
    ++count;
    return true;
}
int main()
{
    string s;

    Vector<string> v;
    while (1)
    {
        int choice = 0;
        cout << "Size = " << v.size() << " Capacity = " << v.capacity();
        cout << "\n1. push\n";
        cout << "2. pop\n";
        cout << "3. size\n";
        cout << "4. capacity\n";
        cout << "5. print\n";
        cout << "6. insert\n";
        cout << "7. find\n";
        cout << "8. removeAll\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter element to push \n";
            cin >> s;
            v.push(s);
            break;
        case 2:
            v.pop();
            break;
        case 3:
            cout << v.size();
            break;
        case 4:
            cout << v.capacity();
            break;
        case 5:
            v.print();
            break;
        case 6:
            v.insert(2, "HEllo");
            break;
        case 7:
            cout << v.find("Test");
            break;
        case 8:
            v.remove("Tits");
            break;
        case 9:
            exit(0);
        default:
            cout << "Invalid";
        }
    }
    return 0;
}
