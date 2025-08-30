#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

// 고급 정렬 알고리즘
// 퀵 정렬, 병합 정렬, 힙 정렬
// 퀵 정렬과 병합 정렬은 분할 정복 알고리즘을 활용한 정렬 알고리즘이다.
// 분할 정복 알고리즘이란, 큰 문제를 작은 문제로 쪼개어 해결한 뒤,
// 그렇게 해결된 문제를 합쳐서 더 큰 문제의 해답을 찾아가는 방식이다.
// -> 재귀적으로 문제를 분할하여 차례로 정복해나가는 방식이다.

// 퀵 정렬
// 퀵 정렬은 분할을 할 때, 기준이 되는 요소를 하나 선정하는데,
// 이렇게 선택된 요소를 피벗(pivot)이라고 부른다.
// 이 피벗보다 작은 요소는 왼쪽으로 보내어 다시 퀵 정렬로 전달한다.
// 큰 요소는 오른쪽 보내어 퀵 정렬로 전달한다. -> 재귀 케이스
// 만약 전달받은 배열의 범위가 1개 이하이면 
// 그대로 함수를 종료한다(동작x)-> 기본 케이스
// datas[]: 정렬할 배열
// lowIndex: 정렬할 범위의 작은쪽 인덱스
// highIndex: 정렬할 범위의 큰쪽 인덱스
int partition(int datas[], int lowIndex, int highIndex);
void swap(int *num1, int *num2);
void displayArray(int datas[], int start, int end);
void quickSort(int datas[], int lowIndex, int highIndex) {
	// 기본 케이스
	// 요소가 2개 이상인 경우, 정렬을 수행한다.
	if (lowIndex < highIndex) { // 재귀 케이스
		// 기준이 될 피벗 고르기 및 분할
		int pivot = partition(datas, lowIndex, highIndex);
		// 피벗을 기준으로 작은 요소와 큰 요소를 좌우로 나눠서 재귀적으로 정렬을 진행한다.
		quickSort(datas, lowIndex, pivot - 1);
		quickSort(datas, pivot + 1, highIndex);
		displayArray(datas, lowIndex, highIndex);
	}
}

// 기준이 될 피봇(인덱스)을 고르고 그 피봇의 좌우로 크기에 맞는 값들을 배치하기 위한 함수
int partition(int datas[], int lowIndex, int highIndex) {
	// 피벗을 고른다. 규칙은 따로 없다.
	int pivotIndex = highIndex;
	int pivot = datas[pivotIndex];
	// i는 피벗 보다 작은 요소들의 경계를 나타낸다.
	int i = (lowIndex - 1);
	
	// 배열을 순회하면서 피벗보다 작은 요소들을 왼쪽으로 이동
	for (int j = lowIndex;  j <= highIndex;  j++) {
		// 현재 요소가 피벗보다 작으면
		if (datas[j] < pivot) {
			// 피벗보다 작은 값의 경계를 1 증가
			i++;
			// i번째 요소의 값과 j번째(pivot보다 작은)요소를 서로 맞바꾼다.
			// i번째 요소의 값이 pivot보다 크거나 작은지는 중요하지 않다.
			swap(&datas[i], &datas[j]);
		}
	}
	// 피벗보다 작은 값들이 i번째 인덱스까지 배치되어 있을 것이다.
	// i+1번째 요소 위치에 pivot의 값이 들어가면 된다(맞교환)
	swap(&datas[i+1], &datas[pivotIndex]);

	return (i + 1);
}

// 전달받은 두 변수에 저장된 값을 맞바꾸는 함수
void swap(int*num1, int* num2) {
	// num1에 저장된 값을 임시 변수에 담는다.
	int temp = *num1;
	// num1의 값을 num2에 저장된 값으로 덮어씌운다.
	*num1 = *num2;
	// num2의 값을 temp에 담긴 값으로 덮어쓴다.
	*num2 = temp;
}

// 08/31(일)
// 병합정렬




void displayArray(int datas[], int start, int end) {
	// 함수 내부에서는 배열의 길이를 측정할 수 없기 때문에
	// 외부에서 그 길이를 받아와야 한다.
	//int len = sizeof(datas) / sizeof(int);
	//printf("함수 내부에서 길이 재기: %d\n", len);
	if (start < 0) start = 0;
	for (int i = start; i < end; i++) {
		printf("%d ", datas[i]);
	}
	printf("\n");
}

int main() {
	int datas[] = { 7, 4, 1, 2, 8, 9, 5, 3, 6 };
	int length = sizeof(datas) / sizeof(int);
	printf("정렬 전: \n");
	displayArray(datas, 0, length);
	printf("\n정렬 후: \n");
	quickSort(datas, 0, length-1);
	displayArray(datas, 0, length);

	return 0;
}