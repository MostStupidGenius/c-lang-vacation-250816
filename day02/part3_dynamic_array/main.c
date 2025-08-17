#include <stdio.h>
#include <stdlib.h> // ���� �Ҵ��� ���� malloc, calloc, realloc ���� ����
#include <stdbool.h>
#define _CRT_SECURE_NO_WARNINGS

// �迭(Array)
// �⺻���� �����Ǵ� �迭�̶�� �ڷᱸ���� ���������̴�.
// ��, �����ϴ� �������� ���̸� ���ؼ� ������ �ؾ� �ϴ� ���̴�.
// �̷��� �迭�� �������̶�� Ư¡�� ���̺��� ���� �����͸� �������� �� ��������,
// ���̺��� ���� �����͸� �����ϰ� ���� �� ������ �ɸ��� �� ��������� ����.
// �̸� ����ü�� ���ؼ� ���� ���̸� �����ϴ� �迭�� �����غ���.

typedef struct {
	int *data;
	int size; // 0���� �������� ũ�⸦ �����ϴ� ����
} List;
// ����Ʈ �ʱ�ȭ
List* initList(List* list, int value);

// List ����ü�� �ּҿ� �����ϰ��� �ϴ� �����͸� �����Ͽ� �ش� ����Ʈ�� �����͸� �߰�
void append(List* list, int data);

// ���� pop �Լ��� ���� �̸�����, ���ڸ� �ٸ��� �Ͽ� �Լ��� �����غ���.
// Ư�� �ε����� ��Ҹ� �����ϴ� �Լ�
void pop2(List* list, int* value, int index);

// ������ ������ ����
void pop(List* list, int *value);

// Ư�� �ε����� ���� ��ȯ �޴´�. �ش� �ε����� size���� ũ�ų� ���ٸ� Null ��ȯ
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

	// ������ �����͸� �����ϰ� �� ���� value�� ��Ƽ� ��ȯ
	pop(&list, &value);
	
	// �����Ͱ� ������ ��ü �����͸� ����ϰ�
	for (int i = 0; i < list.size; i++) {
		printf("i: %d, data: %d\n", i, list.data[i]);
	}

	// ����� ������ �����͸� ���
	printf("value: %d\n", value);

	// Ư�� �ε����� �����͸� �����ϰ� value�� ���, ��ü �����͸� ���
	pop2(&list, &value, 1);
	printf("value: %d\n", value);

	for (int i = 0; i < list.size; i++) {
		printf("i: %d, data: %d\n", i, list.data[i]);
	}

	return 0;
}

// ����Ʈ �ʱ�ȭ
List* initList(List* list, int value) {
	// ����Ʈ�� ó�� ���� ���� ���̰� 1�̾�� �Ѵ�.
	// ù��° ���� value�� ���޹��� ���̸�, ���޹��� ���� �ϳ��̹Ƿ� ���̵� 1�̾�� �Ѵ�.
	list->size = 1;
	// �迭�� ũ�⸦ 1�� ����
	list->data = (int*)malloc(sizeof(int) * 1);
	if (list->data == NULL) {
		free(list);
		return NULL;
	}
	// 0��° ���� ���޹��� ���� ����
	list->data[0] = value;
}

// List ����ü�� �ּҿ� �����ϰ��� �ϴ� �����͸� �����Ͽ� �ش� ����Ʈ�� �����͸� �߰�
void append(List* list, int data) {
	// �߰��ϴ� �����Ͱ� �����Ƿ� ���̵� 1 �����ؾ� �Ѵ�.
	list->size++;
	// ����Ʈ�� ������ �迭�� ���ο� ���̷� ������ش�.
	int* dummy = (int*)malloc(sizeof(int) * list->size);
	if (dummy == NULL) {
		return;
	}
	// �ݺ����� ���ؼ� ���� ����Ʈ�� �����͸� �̰��Ѵ�.
	for (int i = 0; i < (list->size-1); i++) {
		dummy[i] = list->data[i];
	}
	// dummy �迭�� ������ ��ҷ� ���޹��� �����͸� �����Ѵ�.
	dummy[list->size-1] = data;

	// ���� ����Ʈ�� �����ʹ� �̰��۾��� �������Ƿ� free()�� �޸𸮿��� �����ش�.
	free(list->data);

	// ���ο� �����͸� ���� dummy�迭�� list�� �����ͷ� �ٽ� �����Ѵ�.
	list->data = dummy;
}


// Ư�� �ε����� ���� ��ȯ �޴´�. �ش� �ε����� size���� ũ�ų� ���ٸ� Null ��ȯ
int find(List* list, int index, int* value) {
	// ����Ʈ �������� �ش� �ε����� ���� ������� ũ�ų� ������ ������ �� �����Ƿ�
	// �̸� ó�����־�� �Ѵ�.
	if (list->size <= index) {
		*value = -1; // ��ȯ�� ���� ������ ������ ��Ÿ���� ���� -1�� �������ش�.
		return 0;
	}

	// Ư�� �ε����� ���� �����ϴ� �κ�
	*value = list->data[index];
	return 1;
}

// ���� �̸�, ���� Ÿ���� �Ű������� ���� �Լ��� �� �� �̻� �����ϸ�
// �Լ��� ������ �߻��Ѵ�.
//int find(List* list, int index, int* value) {
//	
//}

// ������ ������ ����
void pop(List* list, int* value) {
	if (list->size < 1) {
		return;
	}
	// ������ �����Ϳ� �����Ϸ��� size���� 1���� �ε��� ���� �����ؾ� �Ѵ�.
	*value = list->data[list->size - 1];

	// ���ο� ����� ������ ����
	int newSize = list->size - 1;

	// 1 ���� ũ��� ���ο� �迭 ����
	int* dummy = (int*)malloc(sizeof(int) * newSize);
	// dummy�� ����� �Ҵ�Ǿ����� �˻�
	if (dummy == NULL) { return; }

	for (int i = 0; i < newSize; i++) {
		dummy[i] = list->data[i];
	}

	// ������ ũ�� 1 ���̱�
	list->size--;
	return;
}


// ������ �ε����� �����͸� �����Ͽ� value�� ��ƺ�����
// ������ �ε����� ���� �� ���� ��Ұ� ������Ͽ� �����Ͱ� ������� �Ѵ�.
// ������� �°� �迭�� �����Ǿ�� �Ѵ�.
void pop2(List* list, int* value, int index) {
	if (list->size < 1) {
		return;
	}
	// ������ �����Ϳ� �����Ϸ��� size���� 1���� �ε��� ���� �����ؾ� �Ѵ�.
	*value = list->data[index];

	// ���ο� ����� ������ ����
	int newSize = list->size - 1;

	// 1 ���� ũ��� ���ο� �迭 ����
	int* dummy = (int*)malloc(sizeof(int) * newSize);
	// dummy�� ����� �Ҵ�Ǿ����� �˻�
	if (dummy == NULL) { return; }

	for (int i = 0; i < list->size; i++) {
		//if (i < index) {
		//	dummy[i] = list->data[i];
		//}
		//else if (i == index) {
		//	// �ε����� ������ �ε����� ���ٸ� �ǳʶٱ�
		//	continue;
		//}
		//else {
		//	dummy[i-1] = list->data[i];
		//}
		if (i == index) {
			// �ε����� ������ �ε����� ���ٸ� �ǳʶٱ�
			continue;
		}
		// ���� ����
		dummy[i>index ? i-1 : i] = list->data[i];
	}
	// ���� �����͸� free
	free(list->data);

	// ���Ӱ� ������� ���� �迭�� list�� data�� ���Ҵ�
	list->data = dummy;

	// ������ ũ�� 1 ���̱�
	list->size--;
	return;
}