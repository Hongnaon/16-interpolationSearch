#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10000  // 배열의 크기 정의

// Quick Sort 함수
void QuickSort(int arr[], int left, int right) {
    if (left < right) {
        int pivot = arr[right];  // 피벗을 배열의 가장 오른쪽 값으로 설정
        int i = left - 1;  // 피벗보다 작은 값들의 인덱스를 추적
        for (int j = left; j < right; j++) {
            if (arr[j] <= pivot) {  // 현재 값이 피벗보다 작거나 같으면
                i++;  // 피벗보다 작은 값이므로 위치 변경
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        // 피벗을 적절한 위치에 배치
        int temp = arr[i + 1];
        arr[i + 1] = arr[right];
        arr[right] = temp;

        // 피벗을 기준으로 왼쪽과 오른쪽 부분을 재귀적으로 정렬
        QuickSort(arr, left, i);
        QuickSort(arr, i + 2, right);
    }
}

// Binary Search 함수
int BinarySearch(int* array, int size, int target) {
    int left = 0, right = size - 1, compareCount = 0;  // 시작과 끝 인덱스, 비교 횟수 초기화
    while (left <= right) {  // left가 right보다 작거나 같으면 탐색을 계속
        int mid = left + (right - left) / 2;  // 중간 인덱스 계산
        compareCount++;  // 비교 횟수 증가
        if (array[mid] == target)  // 중간 값이 target과 같으면 탐색 종료
            return compareCount;
        if (array[mid] < target)  // 중간 값보다 target이 크면 오른쪽으로 이동
            left = mid + 1;
        else  // 중간 값보다 target이 작으면 왼쪽으로 이동
            right = mid - 1;
    }
    return compareCount;  // target을 찾지 못하면 비교 횟수 리턴
}

// Interpolation Search 함수
int InterpolationSearch(int* array, int size, int target) {
    int left = 0, right = size - 1, compareCount = 0;  // 시작과 끝 인덱스, 비교 횟수 초기화
    while (left <= right && target >= array[left] && target <= array[right]) {  // target이 현재 범위 내에 있을 때
        compareCount++;  // 비교 횟수 증가
        if (left == right) {  // left와 right가 같으면
            if (array[left] == target) return compareCount;  // 찾으면 종료
            break;  // target을 찾지 못하면 종료
        }

        // target이 위치할 가능성이 높은 위치를 계산
        int pos = left + ((double)(right - left) / (array[right] - array[left]) * (target - array[left]));
        if (pos < left || pos > right) break;  // 계산된 위치가 범위 밖이면 종료

        if (array[pos] == target)  // 위치한 값이 target과 같으면 탐색 종료
            return compareCount;
        if (array[pos] < target)  // 찾고자 하는 값이 더 크면 오른쪽으로 이동
            left = pos + 1;
        else  // 찾고자 하는 값이 더 작으면 왼쪽으로 이동
            right = pos - 1;
    }
    return compareCount;  // target을 찾지 못하면 비교 횟수 리턴
}

// 평균 비교 횟수 계산 함수 (Binary Search)
double getAverageBinarySearchCompareCount(int* array) {
    double totalCompareCount = 0;
    for (int i = 0; i < SIZE; i++) {  // SIZE번만큼 탐색을 수행
        int target = array[rand() % SIZE];  // 배열에서 무작위로 target을 선택
        totalCompareCount += BinarySearch(array, SIZE, target);  // Binary Search로 비교 횟수 합산
    }
    return totalCompareCount / SIZE;  // 평균 비교 횟수 반환
}

// 평균 비교 횟수 계산 함수 (Interpolation Search)
double getAverageInterpolationSearchCompareCount(int* array) {
    double totalCompareCount = 0;
    for (int i = 0; i < SIZE; i++) {  // SIZE번만큼 탐색을 수행
        int target = array[rand() % SIZE];  // 배열에서 무작위로 target을 선택
        totalCompareCount += InterpolationSearch(array, SIZE, target);  // Interpolation Search로 비교 횟수 합산
    }
    return totalCompareCount / SIZE;  // 평균 비교 횟수 반환
}

// 임의 배열 생성 함수
void generateRandomArray(int* array) {
    for (int i = 0; i < SIZE; i++)
        array[i] = rand() % 10000;  // 0~9999 사이의 무작위 값으로 배열 채우기
}

// 배열 출력 함수
void printArray(int* array) {
    printf("Array Sorting Result:\n");
    for (int i = 0; i < 20; i++) {  // 배열의 처음 20개 값 출력
        printf("%4d ", array[i]);
    }
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++) {  // 배열의 끝에서 20개 값 출력
        printf("%4d ", array[i]);
    }
    printf("\n\n");
}

int main(int argc, char* argv[]) {
    srand(time(NULL));  // 랜덤 시드 초기화
    int array[SIZE];  // 배열 선언
    generateRandomArray(array);  // 무작위 배열 생성

    QuickSort(array, 0, SIZE - 1);  // 배열 정렬 (QuickSort 사용)
    printArray(array);  // 정렬된 배열 출력

    // Binary Search와 Interpolation Search의 평균 비교 횟수 출력
    printf("Average Compare Count of Binary Search: %.2f\n",
        getAverageBinarySearchCompareCount(array));
    printf("Average Compare Count of Interpolation Search: %.2f\n",
        getAverageInterpolationSearchCompareCount(array));

    return 0;
}
