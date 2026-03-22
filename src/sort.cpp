#include <iostream>
#include <algorithm>
using namespace std;

// ============================================================
// 1. Selection Sort
// ============================================================
void selectionSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (a[j] < a[minIdx]) minIdx = j;
        swap(a[i], a[minIdx]);
    }
}

// ============================================================
// 2. Insertion Sort
// ============================================================
void insertionSort(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

// ============================================================
// 3. Shell Sort
// ============================================================
void shellSort(int a[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = a[i];
            int j = i;
            while (j >= gap && a[j - gap] > temp) {
                a[j] = a[j - gap];
                j -= gap;
            }
            a[j] = temp;
        }
    }
}

// ============================================================
// 4. Bubble Sort
// ============================================================
void bubbleSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; j++) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// ============================================================
// 5. Heap Sort
// ============================================================
void heapify(int a[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && a[l] > a[largest]) largest = l;
    if (r < n && a[r] > a[largest]) largest = r;
    if (largest != i) {
        swap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}

void heapSort(int a[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}

// ============================================================
// 6. Merge Sort
// ============================================================
void merge(int a[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int* L = new int[n1];
    int* R = new int[n2];
    for (int i = 0; i < n1; i++) L[i] = a[l + i];
    for (int i = 0; i < n2; i++) R[i] = a[m + 1 + i];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
        a[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) a[k++] = L[i++];
    while (j < n2) a[k++] = R[j++];
    delete[] L;
    delete[] R;
}

void mergeSort(int a[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(a, l, m);
        mergeSort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

void mergeSort(int a[], int n) { mergeSort(a, 0, n - 1); }

// ============================================================
// 7. Quick Sort
// ============================================================
int partition(int a[], int l, int r) {
    int pivot = a[r];
    int i = l - 1;
    for (int j = l; j < r; j++) {
        if (a[j] <= pivot) {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[r]);
    return i + 1;
}

void quickSort(int a[], int l, int r) {
    if (l < r) {
        int p = partition(a, l, r);
        quickSort(a, l, p - 1);
        quickSort(a, p + 1, r);
    }
}

void quickSort(int a[], int n) { quickSort(a, 0, n - 1); }

// ============================================================
// 8. Radix Sort
// ============================================================
void countingSortByDigit(int a[], int n, int exp) {
    int* output = new int[n];
    int count[10] = {0};
    for (int i = 0; i < n; i++)
        count[(a[i] / exp) % 10]++;
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        output[count[(a[i] / exp) % 10] - 1] = a[i];
        count[(a[i] / exp) % 10]--;
    }
    for (int i = 0; i < n; i++)
        a[i] = output[i];
    delete[] output;
}

void radixSort(int a[], int n) {
    int maxVal = *max_element(a, a + n);
    for (int exp = 1; maxVal / exp > 0; exp *= 10)
        countingSortByDigit(a, n, exp);
}

// ============================================================
// 9. Counting Sort
// ============================================================
void countingSort(int a[], int n) {
    int maxVal = *max_element(a, a + n);
    int minVal = *min_element(a, a + n);
    int range = maxVal - minVal + 1;
    int* count = new int[range]();
    int* output = new int[n];
    for (int i = 0; i < n; i++)
        count[a[i] - minVal]++;
    for (int i = 1; i < range; i++)
        count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        output[count[a[i] - minVal] - 1] = a[i];
        count[a[i] - minVal]--;
    }
    for (int i = 0; i < n; i++)
        a[i] = output[i];
    delete[] count;
    delete[] output;
}

// ============================================================
// 10. Binary Insertion Sort
// ============================================================
void binaryInsertionSort(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int lo = 0, hi = i - 1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (a[mid] > key) hi = mid - 1;
            else lo = mid + 1;
        }
        for (int j = i - 1; j >= lo; j--)
            a[j + 1] = a[j];
        a[lo] = key;
    }
}

// ============================================================
// 11. Shaker Sort (Cocktail Shaker Sort)
// ============================================================
void shakerSort(int a[], int n) {
    int left = 0, right = n - 1;
    while (left < right) {
        for (int i = left; i < right; i++)
            if (a[i] > a[i + 1]) swap(a[i], a[i + 1]);
        right--;
        for (int i = right; i > left; i--)
            if (a[i] < a[i - 1]) swap(a[i], a[i - 1]);
        left++;
    }
}

// ============================================================
// 12. Flash Sort
// ============================================================
void flashSort(int a[], int n) {
    if (n <= 1) return;

    int minVal = a[0], maxIdx = 0;
    for (int i = 1; i < n; i++) {
        if (a[i] < minVal) minVal = a[i];
        if (a[i] > a[maxIdx]) maxIdx = i;
    }
    if (a[maxIdx] == minVal) return;

    int m = max(1, (int)(0.45 * n));
    int* L = new int[m]();
    double c = (double)(m - 1) / (a[maxIdx] - minVal);

    for (int i = 0; i < n; i++)
        L[(int)(c * (a[i] - minVal))]++;
    for (int k = 1; k < m; k++)
        L[k] += L[k - 1];

    swap(a[maxIdx], a[0]);

    int j = 0, k = m - 1, nmove = 0;
    while (nmove < n - 1) {
        while (j > L[k] - 1) {
            j++;
            k = (int)(c * (a[j] - minVal));
        }
        int flash = a[j];
        while (j != L[k]) {
            k = (int)(c * (flash - minVal));
            int hold = a[L[k] - 1];
            a[L[k] - 1] = flash;
            flash = hold;
            L[k]--;
            nmove++;
        }
    }
    delete[] L;

    // Final insertion sort pass to fix small remaining disorder
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int jj = i - 1;
        while (jj >= 0 && a[jj] > key) {
            a[jj + 1] = a[jj];
            jj--;
        }
        a[jj + 1] = key;
    }
}

// ============================================================
// Main - demo
// ============================================================
int main() {
    auto printArr = [](int a[], int n) {
        for (int i = 0; i < n; i++) cout << a[i] << " ";
        cout << "\n";
    };

    int data[] = {64, 25, 12, 22, 11, 90, 3, 47};
    int n = sizeof(data) / sizeof(data[0]);

    int a[8];

    auto reset = [&]() { for (int i = 0; i < n; i++) a[i] = data[i]; };

    reset(); selectionSort(a, n);     cout << "Selection:        "; printArr(a, n);
    reset(); insertionSort(a, n);     cout << "Insertion:        "; printArr(a, n);
    reset(); shellSort(a, n);         cout << "Shell:            "; printArr(a, n);
    reset(); bubbleSort(a, n);        cout << "Bubble:           "; printArr(a, n);
    reset(); heapSort(a, n);          cout << "Heap:             "; printArr(a, n);
    reset(); mergeSort(a, n);         cout << "Merge:            "; printArr(a, n);
    reset(); quickSort(a, n);         cout << "Quick:            "; printArr(a, n);
    reset(); radixSort(a, n);         cout << "Radix:            "; printArr(a, n);
    reset(); countingSort(a, n);      cout << "Counting:         "; printArr(a, n);
    reset(); binaryInsertionSort(a,n);cout << "BinaryInsertion:  "; printArr(a, n);
    reset(); shakerSort(a, n);        cout << "Shaker:           "; printArr(a, n);
    reset(); flashSort(a, n);         cout << "Flash:            "; printArr(a, n);

    return 0;
}
