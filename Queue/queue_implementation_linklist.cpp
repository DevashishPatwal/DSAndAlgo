#include <iostream>
using namespace std;

template <class T>
class Node
{
public:
    T value;
    Node *next = nullptr;
    Node(T value)
    {
        this->value = value;
        this->next = nullptr;
    }
    Node(T value, Node *ptr)
    {
        this->value = value;
        this->next = ptr;
    }
};
template <class T>
class Queue
{
    Node<T> *head = nullptr, *tail = nullptr;
    int size = 0;

public:
    void enqueue(T value)
    {
        if (tail == nullptr)
        {
            tail = new Node<T>{value};
            head = tail;
        }
        else
        {

            tail->next = new Node<T>{value};
            tail = tail->next;
        }
        size++;
    }
    T dequeue()
    {
        T value;
        Node<T> *ptr = head;
        if (head == nullptr)
        {
            return "";
        }
        else if (head->next == nullptr)
        {
            tail = nullptr;
            head = nullptr;
        }
        else
        {
            head = head->next;
        }

        value = ptr->value;
        delete ptr;
        --size;
        return value;
    }
    bool empty()
    {
        return head == nullptr ? true : false;
    }
    int sizee()
    {
        return size;
    }
    void display()
    {
        if (head == nullptr)
        {
            cout << "Empty List\n";
        }
        else
        {
            Node<T> *ptr = head;
            cout << "Front-> ";
            for (; ptr->next != nullptr; ptr = ptr->next)
            {
                cout << ptr->value << ", ";
            }
            cout << ptr->value;
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
        cout << "Size = " << q.sizee() << " Empty = " << q.empty() << "\n";
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