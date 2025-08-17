#include <stdio.h>
#include <stdlib.h> // ���� �Ҵ��� ���� malloc, calloc, realloc ���� ����
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

// ������ ������ ����
//void pop(List* list, int *value);

// Ư�� �ε����� ���� ��ȯ �޴´�. �ش� �ε����� size���� ũ�ų� ���ٸ� Null ��ȯ
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

// ����Ʈ �ʱ�ȭ
List* initList(List* list, int value) {
	// ����Ʈ�� ó�� ���� ���� ���̰� 1�̾�� �Ѵ�.
	// ù��° ���� value�� ���޹��� ���̸�, ���޹��� ���� �ϳ��̹Ƿ� ���̵� 1�̾�� �Ѵ�.
	list->size = 1;
	// �迭�� ũ�⸦ 1�� ����
	list->data = (int*)malloc(sizeof(int) * 1);
	printf("malloc 50\n");
	if (list->data == NULL) {
		free(list);
		return NULL;
	}
	// 0��° ���� ���޹��� ���� ����
	list->data[0] = value;
	printf("malloc 56\n");
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
	dummy[list->size] = data;

	// ���� ����Ʈ�� �����ʹ� �̰��۾��� �������Ƿ� free()�� �޸𸮿��� �����ش�.
	free(list->data);

	// ���ο� �����͸� ���� dummy�迭�� list�� �����ͷ� �ٽ� �����Ѵ�.
	list->data = dummy;
}

// ������ ������ ����
//void pop(List* list, int* value);

// Ư�� �ε����� ���� ��ȯ �޴´�. �ش� �ε����� size���� ũ�ų� ���ٸ� Null ��ȯ
//void find(List* list, int index, int* value);

