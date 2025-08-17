#include <stdio.h>
#include <stdlib.h> // 동적 할당을 위한 malloc, calloc, realloc 등을 지원
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

// 마지막 데이터 삭제
//void pop(List* list, int *value);

// 특정 인덱스의 값을 반환 받는다. 해당 인덱스가 size보다 크거나 같다면 Null 반환
//void find(List* list, int index, int* value);

int main() {
	List list;
	initList(&list, 10);
	printf("[0] %d\n", list.data[0]);
	append(&list, 20);
	for (int i = 0; i < list.size; i++) {
		printf("%d\n", list.data[i]);
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
	printf("malloc 50\n");
	if (list->data == NULL) {
		free(list);
		return NULL;
	}
	// 0번째 값을 전달받은 값을 설정
	list->data[0] = value;
	printf("malloc 56\n");
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
	dummy[list->size] = data;

	// 기존 리스트의 데이터는 이관작업이 끝났으므로 free()로 메모리에서 내려준다.
	free(list->data);

	// 새로운 데이터를 담은 dummy배열을 list의 데이터로 다시 지정한다.
	list->data = dummy;
}

// 마지막 데이터 삭제
//void pop(List* list, int* value);

// 특정 인덱스의 값을 반환 받는다. 해당 인덱스가 size보다 크거나 같다면 Null 반환
//void find(List* list, int index, int* value);

