#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10000  // �迭�� ũ�� ����

// Quick Sort �Լ�
void QuickSort(int arr[], int left, int right) {
    if (left < right) {
        int pivot = arr[right];  // �ǹ��� �迭�� ���� ������ ������ ����
        int i = left - 1;  // �ǹ����� ���� ������ �ε����� ����
        for (int j = left; j < right; j++) {
            if (arr[j] <= pivot) {  // ���� ���� �ǹ����� �۰ų� ������
                i++;  // �ǹ����� ���� ���̹Ƿ� ��ġ ����
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        // �ǹ��� ������ ��ġ�� ��ġ
        int temp = arr[i + 1];
        arr[i + 1] = arr[right];
        arr[right] = temp;

        // �ǹ��� �������� ���ʰ� ������ �κ��� ��������� ����
        QuickSort(arr, left, i);
        QuickSort(arr, i + 2, right);
    }
}

// Binary Search �Լ�
int BinarySearch(int* array, int size, int target) {
    int left = 0, right = size - 1, compareCount = 0;  // ���۰� �� �ε���, �� Ƚ�� �ʱ�ȭ
    while (left <= right) {  // left�� right���� �۰ų� ������ Ž���� ���
        int mid = left + (right - left) / 2;  // �߰� �ε��� ���
        compareCount++;  // �� Ƚ�� ����
        if (array[mid] == target)  // �߰� ���� target�� ������ Ž�� ����
            return compareCount;
        if (array[mid] < target)  // �߰� ������ target�� ũ�� ���������� �̵�
            left = mid + 1;
        else  // �߰� ������ target�� ������ �������� �̵�
            right = mid - 1;
    }
    return compareCount;  // target�� ã�� ���ϸ� �� Ƚ�� ����
}

// Interpolation Search �Լ�
int InterpolationSearch(int* array, int size, int target) {
    int left = 0, right = size - 1, compareCount = 0;  // ���۰� �� �ε���, �� Ƚ�� �ʱ�ȭ
    while (left <= right && target >= array[left] && target <= array[right]) {  // target�� ���� ���� ���� ���� ��
        compareCount++;  // �� Ƚ�� ����
        if (left == right) {  // left�� right�� ������
            if (array[left] == target) return compareCount;  // ã���� ����
            break;  // target�� ã�� ���ϸ� ����
        }

        // target�� ��ġ�� ���ɼ��� ���� ��ġ�� ���
        int pos = left + ((double)(right - left) / (array[right] - array[left]) * (target - array[left]));
        if (pos < left || pos > right) break;  // ���� ��ġ�� ���� ���̸� ����

        if (array[pos] == target)  // ��ġ�� ���� target�� ������ Ž�� ����
            return compareCount;
        if (array[pos] < target)  // ã���� �ϴ� ���� �� ũ�� ���������� �̵�
            left = pos + 1;
        else  // ã���� �ϴ� ���� �� ������ �������� �̵�
            right = pos - 1;
    }
    return compareCount;  // target�� ã�� ���ϸ� �� Ƚ�� ����
}

// ��� �� Ƚ�� ��� �Լ� (Binary Search)
double getAverageBinarySearchCompareCount(int* array) {
    double totalCompareCount = 0;
    for (int i = 0; i < SIZE; i++) {  // SIZE����ŭ Ž���� ����
        int target = array[rand() % SIZE];  // �迭���� �������� target�� ����
        totalCompareCount += BinarySearch(array, SIZE, target);  // Binary Search�� �� Ƚ�� �ջ�
    }
    return totalCompareCount / SIZE;  // ��� �� Ƚ�� ��ȯ
}

// ��� �� Ƚ�� ��� �Լ� (Interpolation Search)
double getAverageInterpolationSearchCompareCount(int* array) {
    double totalCompareCount = 0;
    for (int i = 0; i < SIZE; i++) {  // SIZE����ŭ Ž���� ����
        int target = array[rand() % SIZE];  // �迭���� �������� target�� ����
        totalCompareCount += InterpolationSearch(array, SIZE, target);  // Interpolation Search�� �� Ƚ�� �ջ�
    }
    return totalCompareCount / SIZE;  // ��� �� Ƚ�� ��ȯ
}

// ���� �迭 ���� �Լ�
void generateRandomArray(int* array) {
    for (int i = 0; i < SIZE; i++)
        array[i] = rand() % 10000;  // 0~9999 ������ ������ ������ �迭 ä���
}

// �迭 ��� �Լ�
void printArray(int* array) {
    printf("Array Sorting Result:\n");
    for (int i = 0; i < 20; i++) {  // �迭�� ó�� 20�� �� ���
        printf("%4d ", array[i]);
    }
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++) {  // �迭�� ������ 20�� �� ���
        printf("%4d ", array[i]);
    }
    printf("\n\n");
}

int main(int argc, char* argv[]) {
    srand(time(NULL));  // ���� �õ� �ʱ�ȭ
    int array[SIZE];  // �迭 ����
    generateRandomArray(array);  // ������ �迭 ����

    QuickSort(array, 0, SIZE - 1);  // �迭 ���� (QuickSort ���)
    printArray(array);  // ���ĵ� �迭 ���

    // Binary Search�� Interpolation Search�� ��� �� Ƚ�� ���
    printf("Average Compare Count of Binary Search: %.2f\n",
        getAverageBinarySearchCompareCount(array));
    printf("Average Compare Count of Interpolation Search: %.2f\n",
        getAverageInterpolationSearchCompareCount(array));

    return 0;
}
