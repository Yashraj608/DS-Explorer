#include <iostream>
#include <vector>
#include "Queue.h"
#include <stack>
using namespace std;

// ========================= Array-based Queue ========================= //
class ArrayQueue
{
    int front, rear, capacity;
    vector<int> arr;

public:
    ArrayQueue(int size)
    {
        capacity = size;
        arr.resize(capacity);
        front = 0;
        rear = -1;
    }

    bool isFull() { return rear == capacity - 1; }
    bool isEmpty() { return rear < front; }

    void enqueue(int val)
    {
        if (isFull())
        {
            cout << "Queue is full!\n";
            return;
        }
        arr[++rear] = val;
        cout << val << " enqueued.\n";
    }

    void dequeue()
    {
        if (isEmpty())
        {
            cout << "Queue is empty!\n";
            return;
        }
        cout << arr[front++] << " dequeued.\n";
    }

    void peek()
    {
        if (isEmpty())
            cout << "Queue is empty!\n";
        else
            cout << "Front element: " << arr[front] << endl;
    }

    void display()
    {
        if (isEmpty())
        {
            cout << "Queue is empty!\n";
            return;
        }
        for (int i = front; i <= rear; i++)
            cout << arr[i] << " -> ";
        cout << "NULL\n";
    }
};

// ========================= Linked List-based Queue ========================= //
struct Node
{
    int data;
    Node *next;
    Node(int val) : data(val), next(nullptr) {}
};

class LinkedListQueue
{
    Node *front;
    Node *rear;

public:
    LinkedListQueue() { front = rear = nullptr; }

    bool isEmpty() { return front == nullptr; }

    void enqueue(int val)
    {
        Node *n = new Node(val);
        if (!front)
            front = rear = n;
        else
        {
            rear->next = n;
            rear = n;
        }
        cout << val << " enqueued.\n";
    }

    void dequeue()
    {
        if (isEmpty())
        {
            cout << "Queue is empty!\n";
            return;
        }
        Node *temp = front;
        cout << front->data << " dequeued.\n";
        front = front->next;
        delete temp;
        if (!front)
            rear = nullptr;
    }

    void peek()
    {
        if (isEmpty())
            cout << "Queue is empty!\n";
        else
            cout << "Front element: " << front->data << endl;
    }

    void display()
    {
        Node *temp = front;
        while (temp)
        {
            cout << temp->data << " → ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }

    // Getter for front node (for applications)
    Node *getFront() { return front; }

    // Getter for front value (for applications)
    int frontValue() { return front ? front->data : -1; }
};

// ========================= Circular Queue ========================= //
class CircularQueue
{
    vector<int> arr;
    int front, rear, capacity;

public:
    CircularQueue(int size)
    {
        capacity = size;
        arr.resize(capacity);
        front = rear = -1;
    }

    bool isFull() { return (front == 0 && rear == capacity - 1) || (rear + 1 == front); }
    bool isEmpty() { return front == -1; }

    void enqueue(int val)
    {
        if (isFull())
        {
            cout << "Queue is full!\n";
            return;
        }
        if (isEmpty())
            front = rear = 0;
        else if (rear == capacity - 1 && front != 0)
            rear = 0;
        else
            rear++;
        arr[rear] = val;
        cout << val << " enqueued.\n";
    }

    void dequeue()
    {
        if (isEmpty())
        {
            cout << "Queue is empty!\n";
            return;
        }
        cout << arr[front] << " dequeued.\n";
        if (front == rear)
            front = rear = -1;
        else if (front == capacity - 1)
            front = 0;
        else
            front++;
    }

    void peek()
    {
        if (isEmpty())
            cout << "Queue is empty!\n";
        else
            cout << "Front element: " << arr[front] << endl;
    }

    void display()
    {
        if (isEmpty())
        {
            cout << "Queue is empty!\n";
            return;
        }
        int i = front;
        while (true)
        {
            cout << arr[i] << " ->";
            if (i == rear)
                break;
            i = (i + 1) % capacity;
        }
        cout << "NULL\n";
    }
};

// ========================= Queue Applications ========================= //
void reverseQueueExample()
{
    LinkedListQueue q;
    int n, val;
    cout << "Enter number of elements to enqueue: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> val;
        q.enqueue(val);
    }

    cout << "Original Queue: ";
    q.display();

    // Reverse using stack
    stack<int> s;
    while (!q.isEmpty())
    {
        s.push(q.frontValue());
        q.dequeue();
    }

    LinkedListQueue revQ;
    while (!s.empty())
    {
        revQ.enqueue(s.top());
        s.pop();
    }

    cout << "Reversed Queue: ";
    revQ.display();
}

// ========================= Main Queue Module ========================= //
void queueMenu()
{
    int choice;
    ArrayQueue aQueue(100);
    LinkedListQueue lQueue;
    CircularQueue cQueue(100);

    do
    {
        cout << "\n=== QUEUE MODULE ===\n";
        cout << "1. Array-based Queue\n2. Linked List-based Queue\n3. Circular Queue\n4. Queue Applications\n5. Back\nEnter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int op, val;
            do
            {
                cout << "\nArray Queue Operations:\n1.Enqueue\n2.Dequeue\n3.Peek\n4.Display\n5.Back\nEnter choice: ";
                cin >> op;
                switch (op)
                {
                case 1:
                    cout << "Enter value: ";
                    cin >> val;
                    aQueue.enqueue(val);
                    break;
                case 2:
                    aQueue.dequeue();
                    break;
                case 3:
                    aQueue.peek();
                    break;
                case 4:
                    aQueue.display();
                    break;
                }
            } while (op != 5);
            break;
        }

        case 2:
        {
            int op, val;
            do
            {
                cout << "\nLinked List Queue Operations:\n1.Enqueue\n2.Dequeue\n3.Peek\n4.Display\n5.Back\nEnter choice: ";
                cin >> op;
                switch (op)
                {
                case 1:
                    cout << "Enter value: ";
                    cin >> val;
                    lQueue.enqueue(val);
                    break;
                case 2:
                    lQueue.dequeue();
                    break;
                case 3:
                    lQueue.peek();
                    break;
                case 4:
                    lQueue.display();
                    break;
                }
            } while (op != 5);
            break;
        }

        case 3:
        {
            int op, val;
            do
            {
                cout << "\nCircular Queue Operations:\n1.Enqueue\n2.Dequeue\n3.Peek\n4.Display\n5.Back\nEnter choice: ";
                cin >> op;
                switch (op)
                {
                case 1:
                    cout << "Enter value: ";
                    cin >> val;
                    cQueue.enqueue(val);
                    break;
                case 2:
                    cQueue.dequeue();
                    break;
                case 3:
                    cQueue.peek();
                    break;
                case 4:
                    cQueue.display();
                    break;
                }
            } while (op != 5);
            break;
        }

        case 4:
        {
            int appChoice;
            do
            {
                cout << "\nQueue Applications:\n1.Reverse Queue Example\n2.Back\nEnter choice: ";
                cin >> appChoice;
                switch (appChoice)
                {
                case 1:
                    reverseQueueExample();
                    break;
                }
            } while (appChoice != 2);
            break;
        }
        }
    } while (choice != 5);
}
