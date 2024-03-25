#include <iostream>
#include <vector>

using namespace std;

// 快速排序函数
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        // 选择枢轴元素
        int pivot = arr[high];
        int i = low - 1;

        // 将小于枢轴的元素放在左侧，大于枢轴的元素放在右侧
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);

        int partitionIndex = i + 1;

        // 递归地对左右两个子数组进行排序
        quickSort(arr, low, partitionIndex - 1);
        quickSort(arr, partitionIndex + 1, high);
    }
}

int main() {
    vector<int> arr = {12, 4, 6, 3, 9, 2, 7, 8, 10, 5};
    int n = arr.size();

    cout << "Original array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    quickSort(arr, 0, n - 1);

    cout << "Sorted array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
