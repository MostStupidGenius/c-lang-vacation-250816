#include <stdio.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

// 기본 정렬 알고리즘
// 버블 정렬, 선택 정렬, 삽입 정렬
// 위 세 가지 기본 정렬 알고리즘을 구현해보자.
// 기본 정렬 알고리즘은 구현이 간단하고 적은 데이터에 대해서 유용하다.
// 그 중에서도 버블 정렬은 인접한 요소(원소)끼리 비교하여 더 큰 값이 오른쪽으로 이동하도록
// 두 요소의 자리를 바꾸는 방식으로 동작한다.
void bubbleSort(int arr[], int length) {
	// arr: 정수값이 나열된 배열 -> 정렬 대상 배열
	// length: 해당 배열의 요소 개수(0번째부터 몇번째까지 정렬을 할지 여부)
	// -> 부분정렬
	// 버블 정렬은 전체 요소 중 마지막 요소를 제외한 요소까지 반복적으로
	// 다음 요소와 비교하는 방식으로 동작한다
	// 때문에 이중 for문이 사용된다.
	// 외부 반복문은 한 바퀴 돌 때마다를 패스(path)라고 부른다.

	// 시행횟수를 기록할 변수 선언
	int count = 0, swapCount = 0;

	// length-2번째 요소까지만 반복하는 이유는, 마지막 요소는 다음 요소가 없기 때문이다.
	for (int i = 0; i < length-1; i++) {
		// 한번의 반복 안에서 반복 횟수와 1을 전체 길이에서 뺀 횟수만큼 반복한다.
		// 한번의 path가 끝날 때마다 마지막 요소는 정렬된 것으로 간주하기 위해서
		// 반복횟수(i)만큼을 빼는 것이다.
		for (int j = 0; j < length-1-i; j++) {
			// 현재 요소(j)가 다음 요소(j+1)보다 크다면
			if (arr[j] > arr[j+1]) {
				// 두 요소의 값을 맞바꾼다.
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
				swapCount++;
			}
			// 교환 여부와 무관하게 시행횟수를 증가시킨다.
			count++;
		}
	}
	// 전체 시행횟수와 요소에 들어간 값을 보여준다.
	printf("전체 시행 횟수: %d\n교환횟수: %d\n", count, swapCount);
	for (int i = 0; i < length; i++)
	{
		printf("%d ", arr[i]);
	}

}

// 선택 정렬
// 정렬이 안 된 데이터를 다른 요소와 비교하여 가장 작은 값을 가진 요소의 인덱스를 찾아서
// 현재 보고 있는 요소의 값과 맞교환하는 정렬 알고리즘
// -> 가장 작은 값을 찾아서 왼쪽으로 붙여 정렬한다.
void selectionSort(int datas[], int length) {
	// 패스 횟수를 기록할 i, 내부 반복을 기록할 j
	// 전체 시행 횟수를 기록할 count, 교환 횟수를 기록할 swapCount
	// 가장 작은 요소의 인덱스를 임시로 담을 변수 선언
	// 두 요소의 값을 교환할 때 임시로 담아두는 변수 선언
	int i, j, count, swapCount, minIndex, temp;
	count = swapCount = 0;
	for (i = 0; i < length-1; i++) {
		// 현재 보고 있는 요소의 인덱스 i를 가장 작은 값을 담은 변수에 초기화 한다.
		minIndex = i;
		// 가장 작은 값을 가진 요소의 인덱스를 minIndex에 업데이트 하는 반복문
		// 내부 반복의 시작은 다음 요소(i+1)부터 현재 요소(i)를 비교해야 하므로
		// 초기식의 값을 i+1로 설정한다.
		// 조건식은 요소의 끝까지 비교해야 하므로 length가 들어간다.
		for (j = i+1; j < length; j++) {
			if (datas[j] < datas[minIndex]) {
				minIndex = j;
			}
			count++;
		}
		// i번째 요소와 minIndex 번째 요소가 서로 다르다면 -> 바뀌었다.
		// 그 값을 맞교환한다.
		// 두 인덱스가 같으면 현재 보고 있는 i가 최소값이므로 다음 반복으로 넘어간다.
		if (i == minIndex) continue;

		temp = datas[minIndex];
		datas[minIndex] = datas[i];
		datas[i] = temp;
		swapCount++;
	}
	// 정렬된 datas를 출력
	for (i = 0; i < length; i++) {
		printf("%d ", datas[i]);
	}
	printf("\n총 시행횟수: %d\n교환횟수: %d\n", count, swapCount);
};
void insertionSort(int datas[], int length) {
	int i, j, key, count, swapCount;
	count = swapCount = 0;
	// 삽입 정렬에서 0번째 요소는 이미 정렬된 것으로 간주하기 때문에
	// 1번째 요소부터 마지막 요소까지만 정렬에 참여한다.
	for (i = 1; i < length; i++) { 
		// 현재 요소(i) 값을 key에 백업해둔다.
		key = datas[i];
		// 정렬된 부분의 요소를 순회하며 적절한 위치를 찾기 위해
		// 시작값을 i-1로 설정한다.
		j = i - 1;
		while (j >= 0 && datas[j] > key) {
			// 정렬된 값 중 가장 큰 값을 그 다음번째 요소(i)에 저장하고
			datas[j + 1] = datas[j];
			// j값을 1감소시킨다. 
			j = j - 1;
			count++;
		}
		// j+1번째 있는 요소의 값을 key값으로 바꾼다.
		datas[j + 1] = key;
		swapCount++;
	}
	// 정렬된 datas를 출력
	for (i = 0; i < length; i++) {
		printf("%d ", datas[i]);
	}
	printf("\n총 시행횟수: %d\n교환횟수: %d\n", count, swapCount);
}


int main() {
	// 섞인 데이터 생성
	int datas[] = {4, 2, 3, 1, 3, 1, 6, 7, 4, 2, 1, 2, 3, 1, 3, 1, 6, 7, 4, 2, 1 , 2, 3, 1, 3, 1, 6, 7, 4, 2, 1 , 2, 3, 1, 3, 1, 6, 7, 4, 2, 1 , 2, 3, 1, 3, 1, 6, 7, 4, 2, 1 , 2, 3, 1, 3, 1, 6, 7, 4, 2, 1 };

	// 데이터 길이 동적으로 구하기
	int length = sizeof(datas) / sizeof(int);
	printf("len: %d\n", length);
	// 함수 실행하기
	//bubbleSort(datas, length);
	printf("\n===========\n");
	//selectionSort(datas, length);
	insertionSort(datas, length);
	return 0;
}