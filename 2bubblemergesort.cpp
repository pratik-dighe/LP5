#include <iostream>
#include <omp.h>
using namespace std;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Parallel Bubble Sort
void bubbleSort(int *a, int n) {
    for (int i = 0; i < n; i++) {
        int first = i % 2;
#pragma omp parallel for shared(a, first)
        for (int j = first; j < n - 1; j += 2) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

// Merge function for Merge Sort
void merge(int a[], int i1, int j1, int i2, int j2) {
    int temp[1000];
    int i = i1, j = i2, k = 0;
    while (i <= j1 && j <= j2) {
        if (a[i] < a[j]) temp[k++] = a[i++];
        else temp[k++] = a[j++];
    }
    while (i <= j1) temp[k++] = a[i++];
    while (j <= j2) temp[k++] = a[j++];
    for (i = i1, j = 0; i <= j2; i++, j++) {
        a[i] = temp[j];
    }
}

// Parallel Merge Sort
void mergeSort(int a[], int i, int j) {
    if (i < j) {
        int mid = (i + j) / 2;
#pragma omp parallel sections
        {
#pragma omp section
            mergeSort(a, i, mid);
#pragma omp section
            mergeSort(a, mid + 1, j);
        }
        merge(a, i, mid, mid + 1, j);
    }
}

int main() {
    int *original, *bubbleArr, *mergeArr, n;

    cout << "\nEnter total number of elements: ";
    cin >> n;

    original = new int[n];
    bubbleArr = new int[n];
    mergeArr = new int[n];

    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> original[i];
        bubbleArr[i] = original[i];
        mergeArr[i] = original[i];
    }

    // Perform Bubble Sort
    bubbleSort(bubbleArr, n);

    // Perform Merge Sort
    mergeSort(mergeArr, 0, n - 1);

    // Output
    cout << "\nSorted array using Parallel Bubble Sort:\n";
    for (int i = 0; i < n; i++) {
        cout << bubbleArr[i] << " ";
    }

    cout << "\n\nSorted array using Parallel Merge Sort:\n";
    for (int i = 0; i < n; i++) {
        cout << mergeArr[i] << " ";
    }

    cout << endl;

    // Clean up
    delete[] original;
    delete[] bubbleArr;
    delete[] mergeArr;

    return 0;
}
