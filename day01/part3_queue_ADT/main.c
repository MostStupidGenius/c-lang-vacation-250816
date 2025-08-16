#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

// Qeueue �ڷᱸ��
// ���Լ���(FIFO)�� ������ ������ �ڷᱸ���� �̾߱��Ѵ�.
// �ַ� �۾� �����ٸ�, ��⿭ ���� ������ �� ���Ǵ� �ڷᱸ����.
// ����ü�� Queue�� �� �Ӽ��� �����Ѵ�.

// ����ü ����
// Queue ADT ����
typedef struct { // typedef ����� ���� Ÿ�� ����
	// ���� �����͸� ������ items
	int* items;
	// ���� ������ ����� ������ ����(�뷮)
	int capacity;
} Queue;

// Queue�� ����� �Լ�. �̶� ť�� �뷮�� �����Ͽ� ũ�⸦ ���ϵ��� �Ѵ�.
Queue* createQueue(int capacity) {
	// ���� �Ҵ��� ���ؼ� Queue�� �����.
	int size = sizeof(Queue); // Queue�ڷ����� ũ�⸦ �����Ѵ�.
	Queue* queue = (Queue*)malloc(size);
	if (queue == NULL) { return NULL;}
	// ���޹��� �뷮(����� ����)�� �����ϴ� Ÿ���� ������ ���Ͽ� items �Ӽ��� ũ�⸦ �������� �����Ѵ�.
	queue->items = (int*)malloc(sizeof(int) * capacity);
	if (queue->items == NULL) { return NULL; }
	queue->capacity = capacity;

	// ť�� ���� ��� ��������� 0���� �ʱ�ȭ
	// malloc ��ſ� calloc�� ����ϸ� �ڵ����� �ʱ�ȭ���ش�.
	for (int i = 0; i < capacity; i++) {
		queue->items[i] = 0;
	}

	return queue;
}

// Queue �ڷᱸ���� ���� �Լ��� ����(�ٵ� �������� �ʴ´�)

void printElements(Queue* queue);

// ������ ����
// enqueue
int enqueue(Queue* queue, int data);

// ������ ���� �� ����
// dequeue
int dequeue(Queue* queue);

// ���� ������ �� ������ ����(����x) �� Ȯ��
// peek
int peek(Queue* queue);

// ����ִ��� ����
// isEmpty
int isEmpty(Queue* queue);

// �� �� �ִ��� ����
// isFull
int isFull(Queue* queue);

int main() {
	// createQueue �Լ��� �̿��Ͽ� Queue�ڷ��� ������ ������.
	// �̶� Queue �ڷ����� �ּҰ����� ���޹ޱ� ������ �ڷ����ڿ� *�� �ٿ���
	// ������ ������ ������־�� �Ѵ�.
	Queue* queue = createQueue(10);
	// ������ ������ ���ؼ� ���� �Ӽ��� ������ ������
	// ȭ��ǥ������ -> �� ���ؼ� �����Ѵ�.
	printf("%d\n", queue->capacity);

	enqueue(queue, 3);
	enqueue(queue, 1);
	enqueue(queue, 4);
	enqueue(queue, 2);
	enqueue(queue, 5);
	printElements(queue); // 3 1 4 2 5
	// ��ť�� ���ؼ� ù��° ����� 3�� ����
	dequeue(queue);
	printElements(queue); // 1 4 2 5
	enqueue(queue, 10);
	enqueue(queue, 11);
	enqueue(queue, 12);
	enqueue(queue, 13);
	enqueue(queue, 14);
	enqueue(queue, 15); // ������� �����Ͱ� ����.
	enqueue(queue, 16); // �� ���� �� ����.
	enqueue(queue, 17);
	enqueue(queue, 18);
	printElements(queue); // 1 4 2 5 10

	free(queue);
	return 0;
}

void printElements(Queue* queue) {
	printf("[");
	for (int i = 0; i < queue->capacity; i++) {
		int data = queue->items[i];
		printf("%d ", data);
		/*// 0�� �� ��� ����
		if (data == 0) {
			break;
		}
		else {
			printf("%d ", data);
		}*/
	}
	printf("\b]\n");
}

// ������ ����
int enqueue(Queue* queue, int data) {
	if (isFull(queue)) {
		printf("ť�� �������� ���� �� �����ϴ�.\n");
		return 0; // ������ ����
	}
	// �����͸� �߰�
	// ��� ��Ҹ� �˻��Ͽ� 0�� ó������ ������ �ε�����
	// �����͸� �����ϰ� �Լ��� �����Ѵ�.
	// ť�� ��ü ����
	int size = queue->capacity; 
	for (int i = 0; i < size; i++){
		if (queue->items[i] == 0) {
			queue->items[i] = data;
			break; // �ݺ��� ����
		}
	}
	return data;
}

// ������ ���� �� ����
// dequeue
int dequeue(Queue* queue) {
	// ���� ť�� ��������� 0 ��ȯ
	if (isEmpty(queue)) return 0;
	// 0��° ��� ����
	int extract = queue->items[0];
	for (int i = 0; i < queue->capacity; i++){
		// ���� ���(i+1)�� ���� ���� ���(i)�� ����� �Ѵ�.
		queue->items[i] = queue->items[i + 1];
		// ���� ��Ұ� 0�̸� �����Ͱ� ���̻� ���� ���̹Ƿ�
		// ���������Ѵ�.
		if (queue->items[i+1] == 0) break;
	}

	// ������ ������ ��ȯ
	return extract;
}

// ���� ������ �� ������ ����(����x) �� Ȯ��
// peek
int peek(Queue* queue) {
	// ���� ť�� ��������� 0 ��ȯ
	if (isEmpty(queue)) return 0;
	// 0��° ��� ����
	int extract = queue->items[0];
	// ������ ������ ��ȯ
	return extract;
}

// ����ִ��� ����
// isEmpty
int isEmpty(Queue* queue) {
	// 0��°���� ���� 0�̸� ��� �����Ͱ� 0�� ���̹Ƿ� ����ִٰ� �Ǵ��Ѵ�.
	return queue->items[0] == 0;
};

// �� �� �ִ��� ����
// isFull
int isFull(Queue* queue) {
	// ������ ���(queue->capacity-1��°���)�� ���� 0�� �ƴ��� ����
	// 0�� �ƴϸ� �� �� �ִٴ� �ǹ��̹Ƿ� �״�� ��ȯ�ϸ� �ȴ�.
	return queue->items[queue->capacity-1] != 0;
}