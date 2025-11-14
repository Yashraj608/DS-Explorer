#include <iostream>
#include <stack>
#include "Stack.h"
#include <string>
#include <cctype>
using namespace std;

// ========================= ARRAY-BASED STACK ========================= //
class ArrayStack
{
    int top;
    int capacity;
    int *arr;

public:
    ArrayStack(int size)
    {
        capacity = size;
        arr = new int[capacity];
        top = -1;
    }

    ~ArrayStack() { delete[] arr; }

    bool isEmpty() { return top == -1; }
    bool isFull() { return top == capacity - 1; }

    void push(int val)
    {
        if (isFull())
        {
            cout << "Stack Overflow!\n";
            return;
        }
        arr[++top] = val;
    }

    void pop()
    {
        if (isEmpty())
        {
            cout << "Stack Underflow!\n";
            return;
        }
        top--;
    }

    int peek()
    {
        if (!isEmpty())
            return arr[top];
        cout << "Stack is empty!\n";
        return -1;
    }

    void display()
    {
        if (isEmpty())
        {
            cout << "Stack is empty!\n";
            return;
        }
        cout << "Top -> ";
        for (int i = top; i >= 0; i--)
            cout << arr[i] << " -> ";
        cout << "NULL\n";
    }
};

// ========================= LINKED LIST-BASED STACK ========================= //
struct Node
{
    int data;
    Node *next;
};

class LinkedStack
{
    Node *top;

public:
    LinkedStack() { top = nullptr; }

    bool isEmpty() { return top == nullptr; }

    void push(int val)
    {
        Node *newNode = new Node{val, top};
        top = newNode;
    }

    void pop()
    {
        if (isEmpty())
        {
            cout << "Stack Underflow!\n";
            return;
        }
        Node *temp = top;
        top = top->next;
        delete temp;
    }

    int peek()
    {
        if (!isEmpty())
            return top->data;
        cout << "Stack is empty!\n";
        return -1;
    }

    void display()
    {
        if (isEmpty())
        {
            cout << "Stack is empty!\n";
            return;
        }
        cout << "Top -> ";
        Node *curr = top;
        while (curr)
        {
            cout << curr->data << " -> ";
            curr = curr->next;
        }
        cout << "NULL\n";
    }
};

// ========================= STACK APPLICATIONS ========================= //
void stackApplications()
{
    int choice;
    do
    {
        cout << "\n=== STACK APPLICATIONS ===\n";
        cout << "1. Reverse a String\n";
        cout << "2. Check Balanced Parentheses\n";
        cout << "3. Evaluate Postfix Expression\n";
        cout << "4. Evaluate Prefix Expression\n";
        cout << "5. Back\nEnter choice: ";
        cin >> choice;
        cin.ignore(); // ignore newline

        if (choice == 1)
        {
            string str;
            cout << "Enter string: ";
            getline(cin, str);
            stack<char> s;
            for (char c : str)
                s.push(c);
            cout << "Reversed string: ";
            while (!s.empty())
            {
                cout << s.top();
                s.pop();
            }
            cout << endl;
        }
        else if (choice == 2)
        {
            string expr;
            cout << "Enter expression with parentheses: ";
            getline(cin, expr);
            stack<char> s;
            bool balanced = true;
            for (char c : expr)
            {
                if (c == '(')
                    s.push(c);
                else if (c == ')')
                {
                    if (s.empty())
                    {
                        balanced = false;
                        break;
                    }
                    s.pop();
                }
            }
            if (!s.empty())
                balanced = false;
            cout << (balanced ? "Balanced\n" : "Not Balanced\n");
        }
        else if (choice == 3)
        {
            string postfix;
            cout << "Enter postfix expression (single-digit operands, no spaces): ";
            cin >> postfix;
            stack<int> s;
            for (char c : postfix)
            {
                if (isdigit(c))
                    s.push(c - '0');
                else
                {
                    int b = s.top();
                    s.pop();
                    int a = s.top();
                    s.pop();
                    switch (c)
                    {
                    case '+':
                        s.push(a + b);
                        break;
                    case '-':
                        s.push(a - b);
                        break;
                    case '*':
                        s.push(a * b);
                        break;
                    case '/':
                        s.push(a / b);
                        break;
                    }
                }
            }
            cout << "Result: " << s.top() << endl;
        }
        else if (choice == 4)
        {
            string prefix;
            cout << "Enter prefix expression (single-digit operands, no spaces): ";
            cin >> prefix;
            stack<int> s;
            for (int i = prefix.length() - 1; i >= 0; i--)
            {
                char c = prefix[i];
                if (isdigit(c))
                    s.push(c - '0');
                else
                {
                    int a = s.top();
                    s.pop();
                    int b = s.top();
                    s.pop();
                    switch (c)
                    {
                    case '+':
                        s.push(a + b);
                        break;
                    case '-':
                        s.push(a - b);
                        break;
                    case '*':
                        s.push(a * b);
                        break;
                    case '/':
                        s.push(a / b);
                        break;
                    }
                }
            }
            cout << "Result: " << s.top() << endl;
        }

    } while (choice != 5);
}

// ========================= STACK MODULE MENU ========================= //
void stackMenu()
{
    int choice;
    do
    {
        cout << "\n=== STACK MODULE ===\n";
        cout << "1. Array-based Stack\n";
        cout << "2. Linked List-based Stack\n";
        cout << "3. Stack Applications\n";
        cout << "4. Exit\nEnter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            int n, val, op;
            cout << "Enter stack size: ";
            cin >> n;
            ArrayStack stk(n);
            do
            {
                cout << "\nArray Stack Operations: 1.Push 2.Pop 3.Peek 4.Display 5.Back\nChoice: ";
                cin >> op;
                switch (op)
                {
                case 1:
                    cout << "Enter value: ";
                    cin >> val;
                    stk.push(val);
                    break;
                case 2:
                    stk.pop();
                    break;
                case 3:
                    cout << "Top = " << stk.peek() << endl;
                    break;
                case 4:
                    stk.display();
                    break;
                case 5:
                    break;
                default:
                    cout << "Invalid!\n";
                }
            } while (op != 5);
        }
        else if (choice == 2)
        {
            LinkedStack stk;
            int val, op;
            do
            {
                cout << "\nLinked Stack Operations: 1.Push 2.Pop 3.Peek 4.Display 5.Back\nChoice: ";
                cin >> op;
                switch (op)
                {
                case 1:
                    cout << "Enter value: ";
                    cin >> val;
                    stk.push(val);
                    break;
                case 2:
                    stk.pop();
                    break;
                case 3:
                    cout << "Top = " << stk.peek() << endl;
                    break;
                case 4:
                    stk.display();
                    break;
                case 5:
                    break;
                default:
                    cout << "Invalid!\n";
                }
            } while (op != 5);
        }
        else if (choice == 3)
            stackApplications();
    } while (choice != 4);
}


