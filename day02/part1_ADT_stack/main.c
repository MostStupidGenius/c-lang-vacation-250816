#include <stdio.h>
#include <stdbool.h> // ���ڷ����� ��������� ����� �� �ְ� ���ִ� ���
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

// ���� �ڷᱸ��
// ���߿� ���� �����Ͱ� ���� ������(Last In First Out) LIFO ������ ����Ų��.

// ���� �ڷᱸ���� C���� �����ϴ� ���
// 1. �迭�� Ȱ��
// �����͸� ������ ���̸� �̸� ����
#define MAX_SIZE 100 // ������ �ִ� ũ��(����) ����

// �����͸� ������ �迭�� �Ӽ����� ������ ����ü�� ����
typedef struct {
	// �����͸� ������ �迭
	int data[MAX_SIZE];
	// ������ �� ���� ����Ű�� �ε���
	int top; // �����Ͱ� ������ -1�� ����(�⺻��)
} Stack;

// ������ ����/�ʱ�ȭ�ϴ� �Լ�
void initStack(Stack *stack) {
	stack->top = -1; // �� ������ top�� -1�� ����
}

// ���ÿ� �����͸� �߰��ϴ� �Լ�(push)
bool push(Stack* stack, int data);
// ���ÿ��� �����͸� �����ϰ� ��ȯ�ϴ� �Լ�(pop)
// value ������ ������ �Լ� ���ο��� ����� ������ �����ϴ� �뵵�̸�
// �ܺο����� �ش� ������ ������ �� �ֱ� ������ �����͸� ������ ���� �����Ѵٰ� �����ص� �����ϴ�.
bool pop(Stack* stack, int *value);
// ���ÿ��� �� �� �����͸� Ȯ���ϴ� �Լ�(peek, top)
bool peek(Stack* stack, int* value);
// ������ ��� ��Ҹ� ����ϴ� �Լ�(display)
void display(Stack* stack);
// ������ ���� �ִ��� ���θ� ��ȯ(isFull)
bool isFull(Stack* stack);
// ������ ����ִ��� ���θ� ��ȯ(isEmpty)
bool isEmpty(Stack* stack);

// 2. ���Ḯ��Ʈ Ȱ��




int main() {


	return 0;
}

bool push(Stack* stack, int data) {
	// ���� ������ ��� �� ������ ���� �����÷ο��� ������� ���
	if (isFull(stack)) {
		printf("���� �����÷ο�: ������ ���� á���ϴ�.");
		return false; // ���������� �������� ����
	}

	// top�� �ش��ϴ� �ε������� 1�� �߰��� ��ġ�� ���ο� �����͸� �߰��ؾ� �Ѵ�.
	// ���� �߰��Ϸ��� ����� �ε���
	int newIndex = ++(stack->top);
	// top�� ���� 1 ������Ű�鼭 �� ���� ���ο� �������� �ε����� ��´�.
	// �� ����� ���� data�� �Ҵ��Ѵ�.
	stack->data[newIndex] = data;
	// ���������� ������ ������ �Ϸ��
	return true;
}

// top �ε����� �����͸� �����ϰ� �� ���� ���޹��� ������ ������ ���� ��ȯ�ϴ� �Լ�
bool pop(Stack* stack, int* value) {
	// ������ ����ִ��� �˻�
	if (isEmpty(stack)) {
		printf("���� ����÷ο�: ������ ��� �ֽ��ϴ�.");
		return false;
	}

	// ������ ������� �����Ƿ� �����Ѵ�.
	// ���� top�� ����Ű�� �ε����� currentIdx�� ����� ��
	// top�� ���� 1 ���ҽ�Ų��.
	int currentIdx = stack->top--;
	*value = stack->data[currentIdx];
	//stack->top--; // ������ �������������ڸ� ���� ������ ���ս�Ų��.

	return true;
}

bool peek(Stack* stack, int* value) {

}
void display(Stack* stack) {

}
bool isFull(Stack* stack) {

}
bool isEmpty(Stack* stack) {

}