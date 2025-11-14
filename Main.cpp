#include <iostream>
using namespace std;

// Include all module headers
#include "Arrays.h"
#include "Stack.h"
#include "Queue.h"
#include "LinkedList.h"
#include "Trees.h"
#include "Graphs.h"

// Forward declarations of menu functions from each module
void arrayMenu();
void stackMenu();
void queueMenu();
void linkedListMenu();
void treeMenu();
void graphMenu();

int main()
{
    int choice;

    do
    {
        cout << "\n===== DS EXPLORER MENU =====\n";
        cout << "1. Arrays\n";
        cout << "2. Stack\n";
        cout << "3. Queue\n";
        cout << "4. Linked List\n";
        cout << "5. Trees\n";
        cout << "6. Graphs\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            arrayMenu();
            break;
        case 2:
            stackMenu();
            break;
        case 3:
            queueMenu();
            break;
        case 4:
            linkedListMenu();
            break;
        case 5:
            treeMenu();
            break;
        case 6:
            graphMenu();
            break;
        case 7:
            cout << "Exiting DS Explorer. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 7);

    return 0;
}
