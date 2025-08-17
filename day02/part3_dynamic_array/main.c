#include <stdio.h>
#include <stdlib.h> // 동적 할당을 위한 malloc, calloc, realloc 등을 지원
#include <stdbool.h>
#define _CRT_SECURE_NO_WARNINGS

// 배열(Array)
// 기본으로 제공되는 배열이라는 자료구조는 고정길이이다.
// 즉, 선언하는 순간부터 길이를 정해서 선언을 해야 하는 것이다.
// 이러한 배열의 고정길이라는 특징은 길이보다 적은 데이터를 저장했을 때 공간낭비,
// 길이보다 많은 데이터를 저장하고 싶을 때 제한이 걸리는 등 제약사항이 많다.
// 이를 구조체를 통해서 가변 길이를 지원하는 배열로 구현해보자.

typedef struct {
	int *data;
	int size; // 0부터 동적으로 크기를 저장하는 변수
} List;
// 리스트 초기화
List* initList(List* list, int value);

// List 구조체의 주소와 삽입하고자 하는 데이터를 전달하여 해당 리스트에 데이터를 추가
void append(List* list, int data);

// 위의 pop 함수와 같은 이름으로, 인자를 다르게 하여 함수를 선언해보자.
// 특정 인덱스의 요소를 삭제하는 함수
void pop2(List* list, int* value, int index);

// 마지막 데이터 삭제
void pop(List* list, int *value);

// 특정 인덱스의 값을 반환 받는다. 해당 인덱스가 size보다 크거나 같다면 Null 반환
int find(List* list, int index, int* value);

int main() {
	List list;
	initList(&list, 10);
	printf("[0] %d\n", list.data[0]);
	append(&list, 20);
	append(&list, 30);
	append(&list, 40);
	int value;
	if (find(&list, 2, &value)) {
		printf("value: %d\n", value);
	}
	printf("size: %d\n", list.size);
	for (int i = 0; i < list.size; i++) {
		printf("i: %d, data: %d\n", i, list.data[i]);
	}

	// 마지막 데이터를 삭제하고 그 값을 value에 담아서 반환
	pop(&list, &value);
	
	// 데이터가 삭제된 전체 데이터를 출력하고
	for (int i = 0; i < list.size; i++) {
		printf("i: %d, data: %d\n", i, list.data[i]);
	}

	// 추출된 마지막 데이터를 출력
	printf("value: %d\n", value);

	// 특정 인덱스의 데이터를 제거하고 value에 담고, 전체 데이터를 출력
	pop2(&list, &value, 1);
	printf("value: %d\n", value);

	for (int i = 0; i < list.size; i++) {
		printf("i: %d, data: %d\n", i, list.data[i]);
	}

	return 0;
}

// 리스트 초기화
List* initList(List* list, int value) {
	// 리스트를 처음 만들 때는 길이가 1이어야 한다.
	// 첫번째 값은 value로 전달받을 것이며, 전달받은 값은 하나이므로 길이도 1이어야 한다.
	list->size = 1;
	// 배열의 크기를 1로 설정
	list->data = (int*)malloc(sizeof(int) * 1);
	if (list->data == NULL) {
		free(list);
		return NULL;
	}
	// 0번째 값을 전달받은 값을 설정
	list->data[0] = value;
}

// List 구조체의 주소와 삽입하고자 하는 데이터를 전달하여 해당 리스트에 데이터를 추가
void append(List* list, int data) {
	// 추가하는 데이터가 있으므로 길이도 1 증가해야 한다.
	list->size++;
	// 리스트의 데이터 배열을 새로운 길이로 만들어준다.
	int* dummy = (int*)malloc(sizeof(int) * list->size);
	if (dummy == NULL) {
		return;
	}
	// 반복문을 통해서 기존 리스트의 데이터를 이관한다.
	for (int i = 0; i < (list->size-1); i++) {
		dummy[i] = list->data[i];
	}
	// dummy 배열의 마지막 요소로 전달받은 데이터를 삽입한다.
	dummy[list->size-1] = data;

	// 기존 리스트의 데이터는 이관작업이 끝났으므로 free()로 메모리에서 내려준다.
	free(list->data);

	// 새로운 데이터를 담은 dummy배열을 list의 데이터로 다시 지정한다.
	list->data = dummy;
}


// 특정 인덱스의 값을 반환 받는다. 해당 인덱스가 size보다 크거나 같다면 Null 반환
int find(List* list, int index, int* value) {
	// 리스트 데이터의 해당 인덱스가 실제 사이즈보다 크거나 같으면 가져올 수 없으므로
	// 이를 처리해주어야 한다.
	if (list->size <= index) {
		*value = -1; // 반환할 값에 문제가 있음을 나타내기 위해 -1을 저장해준다.
		return 0;
	}

	// 특정 인덱스의 값을 저장하는 부분
	*value = list->data[index];
	return 1;
}

// 같은 이름, 같은 타입의 매개변수를 가진 함수를 두 개 이상 정의하면
// 함수에 오류가 발생한다.
//int find(List* list, int index, int* value) {
//	
//}

// 마지막 데이터 삭제
void pop(List* list, int* value) {
	if (list->size < 1) {
		return;
	}
	// 마지막 데이터에 접근하려면 size보다 1적은 인덱스 값을 추출해야 한다.
	*value = list->data[list->size - 1];

	// 새로운 사이즈를 변수에 저장
	int newSize = list->size - 1;

	// 1 작은 크기로 새로운 배열 생성
	int* dummy = (int*)malloc(sizeof(int) * newSize);
	// dummy가 제대로 할당되었는지 검사
	if (dummy == NULL) { return; }

	for (int i = 0; i < newSize; i++) {
		dummy[i] = list->data[i];
	}

	// 사이즈 크기 1 줄이기
	list->size--;
	return;
}


// 전달한 인덱스의 데이터를 추출하여 value에 담아보내고
// 추출한 인덱스의 값을 그 다음 요소가 덮어쓰기하여 데이터가 당겨져야 한다.
// 사이즈와 맞게 배열이 조정되어야 한다.
void pop2(List* list, int* value, int index) {
	if (list->size < 1) {
		return;
	}
	// 마지막 데이터에 접근하려면 size보다 1적은 인덱스 값을 추출해야 한다.
	*value = list->data[index];

	// 새로운 사이즈를 변수에 저장
	int newSize = list->size - 1;

	// 1 작은 크기로 새로운 배열 생성
	int* dummy = (int*)malloc(sizeof(int) * newSize);
	// dummy가 제대로 할당되었는지 검사
	if (dummy == NULL) { return; }

	for (int i = 0; i < list->size; i++) {
		//if (i < index) {
		//	dummy[i] = list->data[i];
		//}
		//else if (i == index) {
		//	// 인덱스가 제거한 인덱스와 같다면 건너뛰기
		//	continue;
		//}
		//else {
		//	dummy[i-1] = list->data[i];
		//}
		if (i == index) {
			// 인덱스가 제거한 인덱스와 같다면 건너뛰기
			continue;
		}
		// 삼항 연산
		dummy[i>index ? i-1 : i] = list->data[i];
	}
	// 기존 데이터를 free
	free(list->data);

	// 새롭게 만들어진 더미 배열을 list의 data로 재할당
	list->data = dummy;

	// 사이즈 크기 1 줄이기
	list->size--;
	return;
}