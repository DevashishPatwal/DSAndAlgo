#include <iostream>
using namespace std;

template <class T>
class Queue
{
    T *array;
    int capacity = 5;

public:
    int front = 0;
    int rear = 0;
    Queue()
    {
        array = new T[capacity];
    }
    void enqueue(T value)
    {
        if (rear == front - 1 || (rear == capacity - 1 && front == 0))
        {
            return;
        }
        array[rear] = value;
        rear = (rear + 1) % capacity;
    }
    T dequeue()
    {
        if (empty())
        {
        }
        else
        {
            T value = array[front];
            front = (front + 1) % capacity;
            return value;
        }
    }
    bool empty()
    {
        return front == rear ? true : false;
    }
    int size()
    {
        return capacity;
    }
    void display()
    {
        if (empty())
        {
            cout << "Empty List\n";
        }
        else
        {
            int i = front, condition = rear - 1 < 0 ? capacity - 1 : rear - 1;
            cout << "Front-> ";

            for (; i != condition; i = (i + 1) % capacity)
            {
                cout << array[i] << ", ";
            }
            cout << array[i];
            cout << " <-Back\n";
        }
    }
};

int main()
{
    Queue<string> q;
    string s;
    int choice;
    while (1)
    {
        q.display();
        cout << "Size = " << q.size() << " Front = " << q.front << " Rear = " << q.rear << "\n";
        cout << "1. Enqueue\n";
        cout << "2. Dequeue\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter the value to enqueue : ";
            cin >> s;
            q.enqueue(s);
            break;
        case 2:
            cout << "Dequeued value is -> " << q.dequeue() << endl;
            break;
        case 3:
            exit(0);
        default:
            cout << "Invalid Choice";
        }
    }
}