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
	// ���� ����ü�� ��üȭ
	Stack stack; // ���� ��ƼƼ(Entity)
	int value;	 // �Լ��� ���ؼ� ���� ���޹޴� �뵵�� ���̴� �������

	// ���� �ʱ�ȭ
	initStack(&stack); // �ش� ������ �ּҰ��� �����ؾ� �Ѵ�.

	// ������ ����
	push(&stack, 10);
	push(&stack, 20);
	push(&stack, 30);

	// ���� ���� ���
	display(&stack);

	// peek ����
	// top�ε����� ���� ��ȯ�޴´�.
	// ��ȯ���� �� main()�Լ��� �����س��� value ������ ��Ƽ� ��ȯ�޴´�.
	int got = peek(&stack, &value); // �Լ� ���ο��� value�� ������ �� �ֵ���
	// value�� �ּҰ�(&)�� �������ش�.
	if (got) {
		printf("������ �� �� ��� ��: %d\n", value);
	}

	// pop ����
	// �� ���� ��Ҹ� �����Ͽ� value�� ��� �ε����� 1���ҽ�Ų��.
	if (pop(&stack, &value)) {
		printf("��(pop)�� ���: %d\n", value);
		display(&stack);
	}
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
	// ���� ������ ��������� ������ Ȯ���� �Ұ����� ���̴�.
	if (isEmpty(stack)) {
		printf("����÷ο�");
		return false;
	}
	// ���޹��� �����ͺ��� value�� stack->data �� top ��ġ�� ���� ��´�.
	*value = stack->data[stack->top];
	return true;
}

void display(Stack* stack) {
	if (isEmpty(stack)) {
		printf("����÷ο�\n");
		return;
	}
	// top�ε����κ��� 1�� �����ϸ� �����͸� ��ȸ�Ѵ�.
	for (int i = stack->top; i>=0 ; i--) {
		// �ش� �����Ͱ� ��ġ�� �ε����� �Բ� �� ���� �� �ٿ� ���
		printf("%d. %d\n", i, stack->data[i]);
	}
}

bool isFull(Stack* stack) {
	// ���� �ִ� ũ���� 1�� �� �ε����� top�̸�
	// �����Ͱ� ���� ���̹Ƿ�, �ش� ���θ� ��ȯ�ϸ� �ȴ�.
	return stack->top == (MAX_SIZE - 1);
}
bool isEmpty(Stack* stack) {
	// -1�ε����� �����Ͱ� ������ ��Ÿ���� ���̹Ƿ�
	// �ش� ���θ� ��ȯ�ϸ� �ȴ�.
	return stack->top == -1;
}