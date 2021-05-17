#include <iostream>
using namespace std;
template <class T>
class Node
{
public:
    T item;
    Node<T> *next;

    Node(T item)
    {
        this->item = item;
        next = nullptr;
    }
    Node(T item, Node *ptr)
    {
        this->item = item;
        next = ptr;
    }
};
template <class T>
class Linklist
{
    Node<T> *head = nullptr;
    int size = 0;
    Node<T> *tail = nullptr;

    void reversePrint(Node<T> *ptr)
    {
        if (ptr == nullptr)
        {
            return;
        }
        reverse(ptr->next);
        cout << ptr->item << "->";
    }

public:
    int count()
    {
        return size;
    }

    bool empty()
    {
        if (tail == nullptr)
            return true;
        return false;
    }

    T value_at(int index)
    {
        if (index >= size || index < 0)
        {
            return nullptr;
        }
        else if (index == size - 1)
        {
            return tail->item;
        }
        else
        {
            Node<T> *ptr = head;
            for (int i = 0; i < index; i++, ptr = ptr->next)
                ;

            return ptr->item;
        }
    }

    void push_front(T value)
    {
        if (head == nullptr)
        {
            head = new Node<T>{value};
            tail = head;
        }
        else
        {
            //! New trick learned
            head = new Node<T>{value, head};
        }
        size++;
    }

    T pop_front()
    {
        //No item is list
        if (head == nullptr)
        {
            return "";
        }
        else
        {
            Node<T> *itemToDelete = head;
            T item = itemToDelete->item;
            head = head->next;
            delete itemToDelete;
            --size;
            return item;
        }
    }

    void push_back(T value)
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
    T pop_back()
    {
        T item;
        if (head == nullptr)
        {
            item = "";
        }
        else
        {
            Node<T> *ptr = head;
            while (ptr->next != tail)
            {
                ptr = ptr->next;
            }
            ptr->next = nullptr;
            item = tail->item;
            delete tail;
            tail = ptr;
            --size;
        }
        return item;
    }
    T front()
    {
        return head != nullptr ? head->item : "NULL";
    }
    T back()
    {
        return tail != nullptr ? tail->item : "NULL";
    }
    void insert(int index, T value)
    {
        if (index < 0 || index > size)
        {
            return;
        }
        else if (index == 0)
        {
            head = new Node<T>{value, head};
        }
        else if (index == size)
        {
            tail->next = new Node<T>{value};
            tail = tail->next;
        }
        else
        {
            Node<T> *ptr = head;
            for (int i = 1; i < index; i++, ptr = ptr->next)
                ;
            ptr->next = new Node<T>{value, ptr->next};
        }
        ++size;
    }
    T erase(int index)
    {
        T item;
        if (index < 0 || index >= size)
        {
            item = "";
        }
        else if (index == 0)
        {
            item = pop_front();
        }
        else if (index == size - 1)
        {
            item = pop_back();
        }
        else
        {
            Node<T> *ptr = head, *prevptr = ptr;
            for (int i = 1; i <= index; i++, ptr = ptr->next)
            {
                prevptr = ptr;
            }
            prevptr->next = ptr->next;
            item = ptr->item;
            delete ptr;
            --size;
        }
        return item;
    }
    T value_n_from_end(int n)
    {
        return value_at(size - 1 - n);
    }

    T remove_value(T value)
    {
        T item;
        if (head != nullptr && head->item == value)
        {
            item = pop_front();
        }
        else
        {
            Node<T> *ptr = head->next, *prevptr = head;
            while (ptr != nullptr && ptr->item != value)
            {
                prevptr = ptr;
                ptr = ptr->next;
            }
            if (ptr == nullptr)
            {
                item = "";
            }
            else
            {
                prevptr->next = ptr->next;
                item = ptr->item;
                if (ptr == tail)
                {
                    tail = prevptr;
                }
                delete ptr;
                --size;
            }
        }
        return item;
    }
    void reverse()
    {
        if (size >= 2)
        {
            Node<T> *first = head;
            Node<T> *second = head->next;
            Node<T> *third = nullptr;
            while (second != nullptr)
            {
                third = second->next;
                second->next = first;
                first = second;
                second = third;
            }
            tail = head;
            tail->next = nullptr;
            head = first;
        }
    }
    void display()
    {
        if (head == nullptr)
        {
            cout << "List Empty\n";
        }
        else
        {

            for (Node<T> *ptr = head; ptr != nullptr; ptr = ptr->next)
            {
                cout << ptr->item << "->";
            }
            cout << "END\n";
        }
    }
};
int main()
{
    Linklist<string> l;
    string s;
    int choice;
    while (1)
    {
        l.display();
        cout << "Count = " << l.count() << " isEmpty = " << l.empty() << " Front = " << l.front() << " Back = " << l.back() << '\n';
        cout << "1. Push Back\n";
        cout << "2. Value At\n";
        cout << "3. Push Front\n";
        cout << "4. Pop Front\n";
        cout << "5. Pop Back\n";
        cout << "6. Insert At\n";
        cout << "7. Erase\n";
        cout << "8. Value from end\n";
        cout << "9. Reverse\n";
        cout << "10.Remove Value\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter element to push : ";
            cin >> s;
            l.push_back(s);
            break;
        case 2:
            cout << "Enter Index of item : ";
            cin >> choice;
            cout << "Item  fetched -> " << l.value_at(choice) << endl;
            break;
        case 3:
            cout << "Enter element to push : ";
            cin >> s;
            l.push_front(s);
            break;
        case 4:
            cout << "Item popped -> " << l.pop_front() << endl;
            break;
        case 5:
            cout << "Item popped -> " << l.pop_back() << endl;
            break;
        case 6:
            cout << "Enter the Index -> ";
            cin >> choice;
            cout << "Enter the Value -> ";
            cin >> s;
            l.insert(choice, s);
            break;
        case 7:
            cout << "Enter the index of element to be erased -> ";
            cin >> choice;
            cout << "Item popped -> " << l.erase(choice) << endl;
            break;
        case 8:
            cout << "Enter n : ";
            cin >> choice;
            cout << "Value " << choice << " from end -> " << l.value_n_from_end(choice) << endl;
            break;
        case 9:
            l.reverse();
            break;
        case 10:
            cout << "Enter the element to be deleted : ";
            cin >> s;
            l.remove_value(s);
            break;
        case 11:
            exit(0);
        default:
            break;
        }
    }
}