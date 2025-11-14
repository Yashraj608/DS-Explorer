#include <iostream>
#include "Arrays.h"
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

// ========================= Utility ========================= //
void displayUseCase(const string &algo)
{
    cout << "\nUSE CASE of " << algo << ":\n";
    if (algo == "Bubble Sort")
        cout << "Simple sorting for small datasets or nearly sorted data.\n";
    else if (algo == "Selection Sort")
        cout << "Useful when memory writes are costly.\n";
    else if (algo == "Insertion Sort")
        cout << "Efficient for small or nearly sorted datasets.\n";
    else if (algo == "Quick Sort")
        cout << "Very fast for large datasets; general-purpose sorting.\n";
    else if (algo == "Merge Sort")
        cout << "Stable and ideal for linked lists or large datasets.\n";
    else if (algo == "Radix Sort")
        cout << "Best for integers or fixed-length keys.\n";
    else if (algo == "Comb Sort")
        cout << "Improved version of Bubble Sort for moderate datasets.\n";
}

// ========================= Sorting Functions ========================= //
void bubbleSort(vector<int> &arr)
{
    displayUseCase("Bubble Sort");
    for (size_t i = 0; i < arr.size() - 1; i++)
        for (size_t j = 0; j < arr.size() - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}

void selectionSort(vector<int> &arr)
{
    displayUseCase("Selection Sort");
    for (size_t i = 0; i < arr.size() - 1; i++)
    {
        size_t minIndex = i;
        for (size_t j = i + 1; j < arr.size(); j++)
            if (arr[j] < arr[minIndex])
                minIndex = j;
        swap(arr[i], arr[minIndex]);
    }
}

void insertionSort(vector<int> &arr)
{
    displayUseCase("Insertion Sort");
    for (size_t i = 1; i < arr.size(); i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int partition(vector<int> &arr, int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void merge(vector<int> &arr, int l, int m, int r)
{
    vector<int> L(arr.begin() + l, arr.begin() + m + 1);
    vector<int> R(arr.begin() + m + 1, arr.begin() + r + 1);
    size_t i = 0, j = 0;
    int k = l;

    while (i < L.size() && j < R.size())
    {
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    }

    while (i < L.size())
        arr[k++] = L[i++];
    while (j < R.size())
        arr[k++] = R[j++];
}

void mergeSort(vector<int> &arr, int l, int r)
{
    if (l < r)
    {
        int m = (l + r) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int getMax(vector<int> &arr)
{
    return *max_element(arr.begin(), arr.end());
}

void countSort(vector<int> &arr, int exp)
{
    int n = arr.size();
    vector<int> output(n);
    int count[10] = {0};

    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--)
    {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixSort(vector<int> &arr)
{
    displayUseCase("Radix Sort");
    int m = getMax(arr);
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, exp);
}

void combSort(vector<int> &arr)
{
    displayUseCase("Comb Sort");
    int n = arr.size();
    int gap = n;
    bool swapped = true;

    while (gap != 1 || swapped)
    {
        gap = max(1, (gap * 10) / 13);
        swapped = false;

        for (int i = 0; i < n - gap; i++)
        {
            if (arr[i] > arr[i + gap])
            {
                swap(arr[i], arr[i + gap]);
                swapped = true;
            }
        }
    }
}

// ========================= Sorting Menu ========================= //
void sortingMenu(vector<int> &arr)
{
    int choice;
    do
    {
        cout << "\n==== SORTING MENU ====\n";
        cout << "1. Bubble Sort\n2. Selection Sort\n3. Insertion Sort\n4. Quick Sort\n";
        cout << "5. Merge Sort\n6. Radix Sort\n7. Comb Sort\n8. Back\n";
        cout << "Choose an option: ";
        cin >> choice;

        vector<int> temp = arr;

        switch (choice)
        {
        case 1:
            bubbleSort(temp);
            break;
        case 2:
            selectionSort(temp);
            break;
        case 3:
            insertionSort(temp);
            break;
        case 4:
            displayUseCase("Quick Sort");
            quickSort(temp, 0, temp.size() - 1);
            break;
        case 5:
            displayUseCase("Merge Sort");
            mergeSort(temp, 0, temp.size() - 1);
            break;
        case 6:
            radixSort(temp);
            break;
        case 7:
            combSort(temp);
            break;
        case 8:
            return;
        default:
            cout << "Invalid choice!\n";
        }

        cout << "\nSorted Array: ";
        for (size_t i = 0; i < temp.size(); i++)
            cout << temp[i] << " ";
        cout << endl;

    } while (choice != 8);
}

// ========================= Searching ========================= //
void linearSearch1D(const vector<int> &arr, int key)
{
    for (size_t i = 0; i < arr.size(); i++)
        if (arr[i] == key)
        {
            cout << "Found at index " << i << endl;
            return;
        }
    cout << "Not found.\n";
}

void binarySearch1D(vector<int> arr, int key)
{
    sort(arr.begin(), arr.end());
    int low = 0, high = arr.size() - 1;

    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (arr[mid] == key)
        {
            cout << "Found at index " << mid << endl;
            return;
        }
        else if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    cout << "Not found.\n";
}

// ========================= 1D Array Menu ========================= //
void oneDArrayMenu()
{
    int n;
    cout << "Enter array size: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter elements: ";
    for (size_t i = 0; i < arr.size(); i++)
        cin >> arr[i];

    int choice;
    do
    {
        cout << "\n==== 1D ARRAY MENU ====\n";
        cout << "1. Display\n2. Searching\n3. Sorting\n4. Back\nEnter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            for (size_t i = 0; i < arr.size(); i++)
                cout << arr[i] << " ";
            cout << endl;
            break;

        case 2:
        {
            int key;
            cout << "Enter key: ";
            cin >> key;
            int sc;
            cout << "1. Linear Search\n2. Binary Search\nEnter choice: ";
            cin >> sc;
            if (sc == 1)
                linearSearch1D(arr, key);
            else
                binarySearch1D(arr, key);
            break;
        }

        case 3:
            sortingMenu(arr);
            break;
        case 4:
            cout << "Returning...\n";
            break;
        default:
            cout << "Invalid!\n";
        }

    } while (choice != 4);
}

// ========================= 2D Array Utilities ========================= //
void spiralDisplay(const vector<vector<int>> &arr, size_t rows, size_t cols)
{
    cout << "\nSpiral Order: ";
    size_t top = 0, bottom = rows - 1, left = 0, right = cols - 1;

    while (top <= bottom && left <= right)
    {
        for (size_t i = left; i <= right; i++)
            cout << arr[top][i] << " ";
        top++;
        for (size_t i = top; i <= bottom; i++)
            cout << arr[i][right] << " ";
        if (right > 0)
            right--;
        if (top <= bottom)
            for (size_t i = right; i >= left && i < arr[0].size(); i--)
                cout << arr[bottom][i] << " ";
        if (bottom > 0)
            bottom--;
        if (left <= right)
            for (size_t i = bottom; i >= top && i < arr.size(); i--)
                cout << arr[i][left] << " ";
        left++;
    }
    cout << endl;
}

// ========================= 2D Array Menu ========================= //
void twoDArrayMenu()
{
    size_t rows, cols;
    cout << "Enter rows and columns: ";
    cin >> rows >> cols;

    vector<vector<int>> arr(rows, vector<int>(cols));
    cout << "Enter elements:\n";
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            cin >> arr[i][j];

    int choice;
    do
    {
        cout << "\n===== 2D ARRAY MENU =====\n";
        cout << "1. Display\n2. Transpose\n3. Row Sum\n4. Column Sum\n";
        cout << "5. Addition\n6. Multiplication\n7. Linear Search\n8. Binary Search\n";
        cout << "9. Spiral Display\n10. Back\nEnter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            for (size_t i = 0; i < rows; i++)
            {
                for (size_t j = 0; j < cols; j++)
                    cout << setw(5) << arr[i][j];
                cout << endl;
            }
            break;

        case 2:
            cout << "\nTranspose:\n";
            for (size_t i = 0; i < cols; i++)
            {
                for (size_t j = 0; j < rows; j++)
                    cout << setw(5) << arr[j][i];
                cout << endl;
            }
            break;

        case 3:
            for (size_t i = 0; i < rows; i++)
            {
                int sum = 0;
                for (size_t j = 0; j < cols; j++)
                    sum += arr[i][j];
                cout << "Row " << i + 1 << " Sum = " << sum << endl;
            }
            break;

        case 4:
            for (size_t j = 0; j < cols; j++)
            {
                int sum = 0;
                for (size_t i = 0; i < rows; i++)
                    sum += arr[i][j];
                cout << "Column " << j + 1 << " Sum = " << sum << endl;
            }
            break;

        case 5:
        {
            vector<vector<int>> b(rows, vector<int>(cols));
            cout << "Enter second matrix for addition:\n";
            for (size_t i = 0; i < rows; i++)
                for (size_t j = 0; j < cols; j++)
                    cin >> b[i][j];

            cout << "Result:\n";
            for (size_t i = 0; i < rows; i++)
            {
                for (size_t j = 0; j < cols; j++)
                    cout << setw(5) << arr[i][j] + b[i][j];
                cout << endl;
            }
            break;
        }

        case 6:
        {
            size_t r2, c2;
            cout << "Enter rows and cols for second matrix: ";
            cin >> r2 >> c2;
            if (cols != r2)
            {
                cout << "Multiplication not possible!\n";
                break;
            }
            vector<vector<int>> b(r2, vector<int>(c2)), res(rows, vector<int>(c2, 0));
            cout << "Enter elements:\n";
            for (size_t i = 0; i < r2; i++)
                for (size_t j = 0; j < c2; j++)
                    cin >> b[i][j];

            for (size_t i = 0; i < rows; i++)
                for (size_t j = 0; j < c2; j++)
                    for (size_t k = 0; k < cols; k++)
                        res[i][j] += arr[i][k] * b[k][j];

            cout << "Result:\n";
            for (size_t i = 0; i < rows; i++)
            {
                for (size_t j = 0; j < c2; j++)
                    cout << setw(5) << res[i][j];
                cout << endl;
            }
            break;
        }

        case 7:
        {
            int key;
            cout << "Enter key: ";
            cin >> key;
            for (size_t i = 0; i < rows; i++)
            {
                bool found = false;
                for (size_t j = 0; j < cols; j++)
                {
                    if (arr[i][j] == key)
                    {
                        cout << "Found in row " << i << " at column " << j << endl;
                        found = true;
                    }
                }
                if (!found)
                    cout << "Not in row " << i << endl;
            }
            break;
        }

        case 8:
        {
            int key;
            cout << "Enter key: ";
            cin >> key;
            for (size_t i = 0; i < rows; i++)
            {
                vector<int> temp = arr[i];
                sort(temp.begin(), temp.end());
                int low = 0, high = temp.size() - 1;
                bool f = false;
                while (low <= high)
                {
                    int mid = (low + high) / 2;
                    if (temp[mid] == key)
                    {
                        cout << "Found in row " << i << endl;
                        f = true;
                        break;
                    }
                    else if (temp[mid] < key)
                        low = mid + 1;
                    else
                        high = mid - 1;
                }
                if (!f)
                    cout << "Not in row " << i << endl;
            }
            break;
        }

        case 9:
            spiralDisplay(arr, rows, cols);
            break;
        case 10:
            cout << "Returning...\n";
            break;
        default:
            cout << "Invalid!\n";
        }

    } while (choice != 10);
}

// ========================= Jagged Array ========================= //
void jaggedArrayMenu()
{
    size_t rows;
    cout << "Enter number of rows: ";
    cin >> rows;

    vector<vector<int>> jagged(rows);

    for (size_t i = 0; i < rows; i++)
    {
        size_t cols;
        cout << "Enter number of columns for row " << i + 1 << ": ";
        cin >> cols;
        jagged[i].resize(cols);
        cout << "Enter elements: ";
        for (size_t j = 0; j < cols; j++)
            cin >> jagged[i][j];
    }

    int choice;
    do
    {
        cout << "\n=== JAGGED ARRAY MENU ===\n"
             << "1.Display\n2.Row Sum\n3.Total Elements\n4.Search\n5.Max Element\n6.Min Element\n7.Back\nEnter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            for (size_t i = 0; i < jagged.size(); i++)
            {
                cout << "Row " << i + 1 << ": ";
                for (size_t j = 0; j < jagged[i].size(); j++)
                    cout << jagged[i][j] << " ";
                cout << endl;
            }
            break;

        case 2:
            for (size_t i = 0; i < jagged.size(); i++)
            {
                int sum = 0;
                for (size_t j = 0; j < jagged[i].size(); j++)
                    sum += jagged[i][j];
                cout << "Row " << i + 1 << " Sum = " << sum << endl;
            }
            break;

        case 3:
        {
            size_t total = 0;
            for (size_t i = 0; i < jagged.size(); i++)
                total += jagged[i].size();
            cout << "Total elements = " << total << endl;
            break;
        }

        case 4:
        {
            int key;
            cout << "Enter key to search: ";
            cin >> key;
            bool found = false;
            for (size_t i = 0; i < jagged.size(); i++)
            {
                for (size_t j = 0; j < jagged[i].size(); j++)
                {
                    if (jagged[i][j] == key)
                    {
                        cout << "Found at row " << i << ", col " << j << endl;
                        found = true;
                    }
                }
            }
            if (!found)
                cout << "Not found.\n";
            break;
        }

        case 5:
        {
            int mx = jagged[0][0];
            for (size_t i = 0; i < jagged.size(); i++)
                for (size_t j = 0; j < jagged[i].size(); j++)
                    if (jagged[i][j] > mx)
                        mx = jagged[i][j];
            cout << "Max = " << mx << endl;
            break;
        }

        case 6:
        {
            int mn = jagged[0][0];
            for (size_t i = 0; i < jagged.size(); i++)
                for (size_t j = 0; j < jagged[i].size(); j++)
                    if (jagged[i][j] < mn)
                        mn = jagged[i][j];
            cout << "Min = " << mn << endl;
            break;
        }

        case 7:
            cout << "Returning...\n";
            break;
        default:
            cout << "Invalid!\n";
        }
    } while (choice != 7);
}

// ========================= Main Menu ========================= //
void arrayMenu(){

    int choice;
    do
    {
        cout << "\n=== ARRAY MODULE MENU ===\n";
        cout << "1. 1D Array\n2. 2D Array\n3. Jagged Array\n4. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            oneDArrayMenu();
            break;
        case 2:
            twoDArrayMenu();
            break;
        case 3:
            jaggedArrayMenu();
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid!\n";
        }
    } while (choice != 4);

}
