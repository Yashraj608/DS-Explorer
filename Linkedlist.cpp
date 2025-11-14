#include <iostream>
#include "Linkedlist.h"
#include <limits> // for numeric_limits
using namespace std;

// -------------------- Utility --------------------
void flushStdin()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// -------------------- Singly Linked List --------------------
struct SNode
{
    int data;
    SNode *next;
    SNode(int v) : data(v), next(nullptr) {}
};

// create / clear
SNode *clearSingly(SNode *head)
{
    while (head)
    {
        SNode *tmp = head;
        head = head->next;
        delete tmp;
    }
    return nullptr;
}

// count
size_t countSingly(SNode *head)
{
    size_t c = 0;
    while (head)
    {
        ++c;
        head = head->next;
    }
    return c;
}

// display
void displaySingly(SNode *head)
{
    cout << "Singly Linked List: ";
    if (!head)
    {
        cout << "EMPTY\n";
        return;
    }
    while (head)
    {
        cout << head->data << " -> ";
        head = head->next;
    }
    cout << "NULL\n";
}

// insert beginning
SNode *insertSinglyBeg(SNode *head, int val)
{
    SNode *nd = new SNode(val);
    nd->next = head;
    return nd;
}

// insert end
SNode *insertSinglyEnd(SNode *head, int val)
{
    SNode *nd = new SNode(val);
    if (!head)
        return nd;
    SNode *t = head;
    while (t->next)
        t = t->next;
    t->next = nd;
    return head;
}

// insert at position (1-based). If pos > size+1 -> error
SNode *insertSinglyPos(SNode *head, int val, size_t pos)
{
    if (pos == 1)
        return insertSinglyBeg(head, val);
    size_t n = countSingly(head);
    if (pos > n + 1)
    {
        cout << "Position out of range (1.." << (n + 1) << ")\n";
        return head;
    }
    SNode *t = head;
    for (size_t i = 1; i < pos - 1; ++i)
        t = t->next;
    SNode *nd = new SNode(val);
    nd->next = t->next;
    t->next = nd;
    return head;
}

// delete beginning
SNode *deleteSinglyBeg(SNode *head)
{
    if (!head)
    {
        cout << "List empty\n";
        return nullptr;
    }
    SNode *t = head;
    head = head->next;
    delete t;
    return head;
}

// delete end
SNode *deleteSinglyEnd(SNode *head)
{
    if (!head)
    {
        cout << "List empty\n";
        return nullptr;
    }
    if (!head->next)
    {
        delete head;
        return nullptr;
    }
    SNode *t = head;
    while (t->next && t->next->next)
        t = t->next;
    delete t->next;
    t->next = nullptr;
    return head;
}

// delete at position (1-based)
SNode *deleteSinglyPos(SNode *head, size_t pos)
{
    if (!head)
    {
        cout << "List empty\n";
        return nullptr;
    }
    size_t n = countSingly(head);
    if (pos < 1 || pos > n)
    {
        cout << "Position out of range (1.." << n << ")\n";
        return head;
    }
    if (pos == 1)
        return deleteSinglyBeg(head);
    SNode *t = head;
    for (size_t i = 1; i < pos - 1; ++i)
        t = t->next;
    SNode *del = t->next;
    t->next = del->next;
    delete del;
    return head;
}

// delete by value (first occurrence)
SNode *deleteSinglyByValue(SNode *head, int val)
{
    if (!head)
    {
        cout << "List empty\n";
        return nullptr;
    }
    if (head->data == val)
        return deleteSinglyBeg(head);
    SNode *t = head;
    while (t->next && t->next->data != val)
        t = t->next;
    if (!t->next)
    {
        cout << val << " not found\n";
        return head;
    }
    SNode *del = t->next;
    t->next = del->next;
    delete del;
    return head;
}

// search
void searchSingly(SNode *head, int val)
{
    size_t pos = 1;
    while (head)
    {
        if (head->data == val)
        {
            cout << val << " found at position " << pos << "\n";
            return;
        }
        head = head->next;
        ++pos;
    }
    cout << val << " not found\n";
}

// reverse (in-place)
SNode *reverseSingly(SNode *head)
{
    SNode *prev = nullptr;
    SNode *cur = head;
    while (cur)
    {
        SNode *nx = cur->next;
        cur->next = prev;
        prev = cur;
        cur = nx;
    }
    return prev;
}

// bubble sort (ascending) for singly linked list
SNode *sortSingly(SNode *head)
{
    if (!head || !head->next)
        return head;
    bool swapped;
    do
    {
        swapped = false;
        SNode **pp = &head; // pointer-to-pointer to iterate
        while ((*pp)->next)
        {
            if ((*pp)->data > (*pp)->next->data)
            {
                SNode *a = *pp;
                SNode *b = a->next;
                a->next = b->next;
                b->next = a;
                *pp = b;
                swapped = true;
            }
            pp = &((*pp)->next);
        }
    } while (swapped);
    return head;
}

// -------------------- Doubly Linked List --------------------
struct DNode
{
    int data;
    DNode *next;
    DNode *prev;
    DNode(int v) : data(v), next(nullptr), prev(nullptr) {}
};

// clear
DNode *clearDoubly(DNode *head)
{
    while (head)
    {
        DNode *t = head;
        head = head->next;
        delete t;
    }
    return nullptr;
}

// count
size_t countDoubly(DNode *head)
{
    size_t c = 0;
    while (head)
    {
        ++c;
        head = head->next;
    }
    return c;
}

// display forward/backward
void displayDoublyForward(DNode *head)
{
    cout << "Doubly Linked List (Forward): ";
    if (!head)
    {
        cout << "EMPTY\n";
        return;
    }
    while (head)
    {
        cout << head->data << " <-> ";
        head = head->next;
    }
    cout << "NULL\n";
}
void displayDoublyBackward(DNode *head)
{
    if (!head)
    {
        cout << "EMPTY\n";
        return;
    }
    while (head->next)
        head = head->next;
    cout << "Doubly Linked List (Backward): ";
    while (head)
    {
        cout << head->data << " <-> ";
        head = head->prev;
    }
    cout << "NULL\n";
}

// insert begin
DNode *insertDoublyBeg(DNode *head, int val)
{
    DNode *nd = new DNode(val);
    nd->next = head;
    if (head)
        head->prev = nd;
    return nd;
}
// insert end
DNode *insertDoublyEnd(DNode *head, int val)
{
    DNode *nd = new DNode(val);
    if (!head)
        return nd;
    DNode *t = head;
    while (t->next)
        t = t->next;
    t->next = nd;
    nd->prev = t;
    return head;
}
// insert pos (1-based)
DNode *insertDoublyPos(DNode *head, int val, size_t pos)
{
    if (pos == 1)
        return insertDoublyBeg(head, val);
    size_t n = countDoubly(head);
    if (pos > n + 1)
    {
        cout << "Position out of range (1.." << (n + 1) << ")\n";
        return head;
    }
    DNode *t = head;
    for (size_t i = 1; i < pos - 1; ++i)
        t = t->next;
    DNode *nd = new DNode(val);
    nd->next = t->next;
    nd->prev = t;
    if (t->next)
        t->next->prev = nd;
    t->next = nd;
    return head;
}
// delete begin
DNode *deleteDoublyBeg(DNode *head)
{
    if (!head)
    {
        cout << "List empty\n";
        return nullptr;
    }
    DNode *t = head;
    head = head->next;
    if (head)
        head->prev = nullptr;
    delete t;
    return head;
}
// delete end
DNode *deleteDoublyEnd(DNode *head)
{
    if (!head)
    {
        cout << "List empty\n";
        return nullptr;
    }
    if (!head->next)
    {
        delete head;
        return nullptr;
    }
    DNode *t = head;
    while (t->next)
        t = t->next;
    t->prev->next = nullptr;
    delete t;
    return head;
}
// delete pos
DNode *deleteDoublyPos(DNode *head, size_t pos)
{
    size_t n = countDoubly(head);
    if (pos < 1 || pos > n)
    {
        cout << "Position out of range (1.." << n << ")\n";
        return head;
    }
    if (pos == 1)
        return deleteDoublyBeg(head);
    DNode *t = head;
    for (size_t i = 1; i < pos; ++i)
        t = t->next;
    t->prev->next = t->next;
    if (t->next)
        t->next->prev = t->prev;
    delete t;
    return head;
}
// delete by value (first occurrence)
DNode *deleteDoublyByValue(DNode *head, int val)
{
    DNode *t = head;
    while (t && t->data != val)
        t = t->next;
    if (!t)
    {
        cout << val << " not found\n";
        return head;
    }
    if (!t->prev)
        return deleteDoublyBeg(head);
    if (!t->next)
        return deleteDoublyEnd(head);
    t->prev->next = t->next;
    t->next->prev = t->prev;
    delete t;
    return head;
}
// search
void searchDoubly(DNode *head, int val)
{
    size_t pos = 1;
    while (head)
    {
        if (head->data == val)
        {
            cout << val << " found at position " << pos << "\n";
            return;
        }
        head = head->next;
        ++pos;
    }
    cout << val << " not found\n";
}
// reverse (swap pointers) - return new head
DNode *reverseDoubly(DNode *head)
{
    DNode *cur = head;
    DNode *tmp = nullptr;
    while (cur)
    {
        tmp = cur->prev;
        cur->prev = cur->next;
        cur->next = tmp;
        cur = cur->prev;
    }
    if (tmp)
        head = tmp->prev;
    return head;
}
// sort (bubble) by swapping data (simple)
DNode *sortDoubly(DNode *head)
{
    if (!head)
        return head;
    bool swapped;
    do
    {
        swapped = false;
        DNode *t = head;
        while (t->next)
        {
            if (t->data > t->next->data)
            {
                int x = t->data;
                t->data = t->next->data;
                t->next->data = x;
                swapped = true;
            }
            t = t->next;
        }
    } while (swapped);
    return head;
}

// -------------------- Circular Singly Linked List --------------------
struct CNode
{
    int data;
    CNode *next;
    CNode(int v) : data(v), next(nullptr) {}
};

// clear
CNode *clearCircular(CNode *head)
{
    if (!head)
        return nullptr;
    if (head->next == head)
    {
        delete head;
        return nullptr;
    }
    CNode *cur = head->next;
    while (cur != head)
    {
        CNode *tmp = cur;
        cur = cur->next;
        delete tmp;
    }
    delete head;
    return nullptr;
}

// count
size_t countCircular(CNode *head)
{
    if (!head)
        return 0;
    size_t c = 0;
    CNode *cur = head;
    do
    {
        ++c;
        cur = cur->next;
    } while (cur != head);
    return c;
}

// display
void displayCircular(CNode *head)
{
    if (!head)
    {
        cout << "Circular List: EMPTY\n";
        return;
    }
    cout << "Circular Linked List: ";
    CNode *cur = head;
    do
    {
        cout << cur->data << " -> ";
        cur = cur->next;
    } while (cur != head);
    cout << "(head)\n";
}

// insert beginning
CNode *insertCircularBeg(CNode *head, int val)
{
    CNode *nd = new CNode(val);
    if (!head)
    {
        nd->next = nd;
        return nd;
    }
    CNode *tail = head;
    while (tail->next != head)
        tail = tail->next;
    nd->next = head;
    tail->next = nd;
    return nd;
}

// insert end
CNode *insertCircularEnd(CNode *head, int val)
{
    CNode *nd = new CNode(val);
    if (!head)
    {
        nd->next = nd;
        return nd;
    }
    CNode *tail = head;
    while (tail->next != head)
        tail = tail->next;
    tail->next = nd;
    nd->next = head;
    return head;
}

// delete beginning
CNode *deleteCircularBeg(CNode *head)
{
    if (!head)
    {
        cout << "List empty\n";
        return nullptr;
    }
    if (head->next == head)
    {
        delete head;
        return nullptr;
    }
    CNode *tail = head;
    while (tail->next != head)
        tail = tail->next;
    CNode *newHead = head->next;
    tail->next = newHead;
    delete head;
    return newHead;
}

// delete end
CNode *deleteCircularEnd(CNode *head)
{
    if (!head)
    {
        cout << "List empty\n";
        return nullptr;
    }
    if (head->next == head)
    {
        delete head;
        return nullptr;
    }
    CNode *cur = head;
    while (cur->next->next != head)
        cur = cur->next;
    delete cur->next;
    cur->next = head;
    return head;
}

// delete by value (first occurrence)
CNode *deleteCircularByValue(CNode *head, int val)
{
    if (!head)
    {
        cout << "List empty\n";
        return nullptr;
    }
    CNode *cur = head;
    CNode *prev = nullptr;
    // check head
    do
    {
        if (cur->data == val)
            break;
        prev = cur;
        cur = cur->next;
    } while (cur != head);
    if (cur->data != val)
    {
        cout << val << " not found\n";
        return head;
    }
    if (!prev)
    { // only node?
        if (head->next == head)
        {
            delete head;
            return nullptr;
        }
        // prev will be tail
        prev = head;
        while (prev->next != head)
            prev = prev->next;
    }
    if (cur == head)
        head = head->next;
    prev->next = cur->next;
    delete cur;
    return head;
}

// search
void searchCircular(CNode *head, int val)
{
    if (!head)
    {
        cout << "List empty\n";
        return;
    }
    CNode *cur = head;
    size_t pos = 1;
    do
    {
        if (cur->data == val)
        {
            cout << val << " found at position " << pos << "\n";
            return;
        }
        cur = cur->next;
        ++pos;
    } while (cur != head);
    cout << val << " not found\n";
}

// -------------------- Menus --------------------
void singlyMenu()
{
    SNode *head = nullptr;
    int choice = 0;
    while (true)
    {
        cout << "\n--- SINGLY LINKED LIST MENU ---\n"
             << "1. Insert at Beginning\n"
             << "2. Insert at End\n"
             << "3. Insert at Position\n"
             << "4. Delete at Beginning\n"
             << "5. Delete at End\n"
             << "6. Delete at Position\n"
             << "7. Delete by Value\n"
             << "8. Search\n"
             << "9. Count\n"
             << "10. Reverse\n"
             << "11. Sort (ascending)\n"
             << "12. Clear List\n"
             << "13. Display\n"
             << "14. Back\n"
             << "Enter choice: ";
        if (!(cin >> choice))
        {
            flushStdin();
            cout << "Invalid input\n";
            continue;
        }

        if (choice == 14)
            break;
        int val;
        size_t pos;
        switch (choice)
        {
        case 1:
            cout << "Value: ";
            cin >> val;
            head = insertSinglyBeg(head, val);
            break;
        case 2:
            cout << "Value: ";
            cin >> val;
            head = insertSinglyEnd(head, val);
            break;
        case 3:
            cout << "Value and Position(1-based): ";
            cin >> val >> pos;
            head = insertSinglyPos(head, val, pos);
            break;
        case 4:
            head = deleteSinglyBeg(head);
            break;
        case 5:
            head = deleteSinglyEnd(head);
            break;
        case 6:
            cout << "Position(1-based): ";
            cin >> pos;
            head = deleteSinglyPos(head, pos);
            break;
        case 7:
            cout << "Value: ";
            cin >> val;
            head = deleteSinglyByValue(head, val);
            break;
        case 8:
            cout << "Value: ";
            cin >> val;
            searchSingly(head, val);
            break;
        case 9:
            cout << "Count: " << countSingly(head) << "\n";
            break;
        case 10:
            head = reverseSingly(head);
            cout << "List reversed\n";
            break;
        case 11:
            head = sortSingly(head);
            cout << "List sorted\n";
            break;
        case 12:
            head = clearSingly(head);
            cout << "Cleared\n";
            break;
        case 13:
            displaySingly(head);
            break;
        default:
            cout << "Invalid choice\n";
            break;
        }
    }
    // free before leaving menu
    head = clearSingly(head);
}

void doublyMenu()
{
    DNode *head = nullptr;
    int choice = 0;
    while (true)
    {
        cout << "\n--- DOUBLY LINKED LIST MENU ---\n"
             << "1. Insert at Beginning\n"
             << "2. Insert at End\n"
             << "3. Insert at Position\n"
             << "4. Delete at Beginning\n"
             << "5. Delete at End\n"
             << "6. Delete at Position\n"
             << "7. Delete by Value\n"
             << "8. Search\n"
             << "9. Count\n"
             << "10. Reverse (change links)\n"
             << "11. Sort (ascending)\n"
             << "12. Clear List\n"
             << "13. Display Forward\n"
             << "14. Display Backward\n"
             << "15. Back\n"
             << "Enter choice: ";
        if (!(cin >> choice))
        {
            flushStdin();
            cout << "Invalid input\n";
            continue;
        }
        if (choice == 15)
            break;
        int val;
        size_t pos;
        switch (choice)
        {
        case 1:
            cout << "Value: ";
            cin >> val;
            head = insertDoublyBeg(head, val);
            break;
        case 2:
            cout << "Value: ";
            cin >> val;
            head = insertDoublyEnd(head, val);
            break;
        case 3:
            cout << "Value and Position(1-based): ";
            cin >> val >> pos;
            head = insertDoublyPos(head, val, pos);
            break;
        case 4:
            head = deleteDoublyBeg(head);
            break;
        case 5:
            head = deleteDoublyEnd(head);
            break;
        case 6:
            cout << "Position(1-based): ";
            cin >> pos;
            head = deleteDoublyPos(head, pos);
            break;
        case 7:
            cout << "Value: ";
            cin >> val;
            head = deleteDoublyByValue(head, val);
            break;
        case 8:
            cout << "Value: ";
            cin >> val;
            searchDoubly(head, val);
            break;
        case 9:
            cout << "Count: " << countDoubly(head) << "\n";
            break;
        case 10:
            head = reverseDoubly(head);
            cout << "List reversed\n";
            break;
        case 11:
            head = sortDoubly(head);
            cout << "List sorted\n";
            break;
        case 12:
            head = clearDoubly(head);
            cout << "Cleared\n";
            break;
        case 13:
            displayDoublyForward(head);
            break;
        case 14:
            displayDoublyBackward(head);
            break;
        default:
            cout << "Invalid choice\n";
            break;
        }
    }
    head = clearDoubly(head);
}

void circularMenu()
{
    CNode *head = nullptr;
    int choice = 0;
    while (true)
    {
        cout << "\n--- CIRCULAR LINKED LIST MENU ---\n"
             << "1. Insert at Beginning\n"
             << "2. Insert at End\n"
             << "3. Delete at Beginning\n"
             << "4. Delete at End\n"
             << "5. Delete by Value\n"
             << "6. Search\n"
             << "7. Count\n"
             << "8. Clear List\n"
             << "9. Display\n"
             << "10. Back\n"
             << "Enter choice: ";
        if (!(cin >> choice))
        {
            flushStdin();
            cout << "Invalid input\n";
            continue;
        }
        if (choice == 10)
            break;
        int val;
        switch (choice)
        {
        case 1:
            cout << "Value: ";
            cin >> val;
            head = insertCircularBeg(head, val);
            break;
        case 2:
            cout << "Value: ";
            cin >> val;
            head = insertCircularEnd(head, val);
            break;
        case 3:
            head = deleteCircularBeg(head);
            break;
        case 4:
            head = deleteCircularEnd(head);
            break;
        case 5:
            cout << "Value: ";
            cin >> val;
            head = deleteCircularByValue(head, val);
            break;
        case 6:
            cout << "Value: ";
            cin >> val;
            searchCircular(head, val);
            break;
        case 7:
            cout << "Count: " << countCircular(head) << "\n";
            break;
        case 8:
            head = clearCircular(head);
            cout << "Cleared\n";
            break;
        case 9:
            displayCircular(head);
            break;
        default:
            cout << "Invalid choice\n";
            break;
        }
    }
    head = clearCircular(head);
}

void linkedListMenu()
{
    int choice = 0;
    while (true)
    {
        cout << "\n=== LINKED LISTS MODULE ===\n"
             << "1. Singly Linked List\n"
             << "2. Doubly Linked List\n"
             << "3. Circular Linked List\n"
             << "4. Exit Module\n"
             << "Enter choice: ";
        if (!(cin >> choice))
        {
            flushStdin();
            cout << "Invalid input\n";
            continue;
        }
        if (choice == 4)
            break;
        switch (choice)
        {
        case 1:
            singlyMenu();
            break;
        case 2:
            doublyMenu();
            break;
        case 3:
            circularMenu();
            break;
        default:
            cout << "Invalid choice\n";
            break;
        }
    }
}

