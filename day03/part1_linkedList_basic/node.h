// ��� ����
// ���� ���Ͽ��� ���������� ����ϰ��� �ϴ� ����̳� ����ü ���� ��ƼƼ�� �����ϴ� �����̴�.
// �ݺ������� ����ϴ� ����̳� ����ü ���� �̸� �����ص����ν�
// �ݺ����� �ڵ� �ۼ��� �̿��� ������ �� �ִ�.
// �̷� ������ �ڵ带 ����� �ۼ��Ͽ� ���� �װ� �Ǹ� �̸� '���̺귯��'��� ��Ī����
// ��� ����� �� �ְ� �ȴ�.

// ��ó����
// ��������� ���� ���Ͽ��� include(����) �� �� �ֱ� ������
// �ߺ����� ������ �Ǵ� ��� ������ �߻��� �� �ִ�.
// �̸� �����ϱ� ���ؼ��� include�� ��� ������ ������ ��ü�� �ʿ��ϴ� -> ��ó����
// ��ó���⿡�� ���� �� ����� ���ǵǾ� �ִٸ�~�̶�� ������ �˷��ָ�
// �ߺ� ������ ������ �� �ִ�.

// #ifdef
// �� ��� ������ �̹� �����Ǿ� �ִٸ�~�̶�� �ǹ��̴�.
// #ifdef NODE_H // �̹� �����Ǿ� �ִٸ� �̴�� ���ڴ�.
// #else // �����Ǿ� ���� ���� �� ó��
// #endif // if���� ���� �˸�

// #ifndef
// ���� ifdef�� �ݴ��̴�.
// ��, ���� ������ ���� ���ٸ� ���� �̸����� �����ϰڴ�-��� �ǹ��̴�.
#ifndef NODE_H
// ifndef�� endif ���̿� �����ϰ��� �ϴ� ������ �ۼ����ָ� �ȴ�.
#define NODE_H // ���⼭ �����ϰڴ�.
#include <stdlib.h>
// ��� ����ü ����
typedef struct Node {
	// ��忡 ������ ������ �߰�
	int data;
	// ���� ��带 ����Ű�� ������ ����
	struct Node* next;
} Node;

// ��忡 ���� ����
// ��忡 ���� ���Ǹ� ������ �ܺο��� ���� ������ ���� ���� �ƴ϶�
// �� �ȿ��� �ش� ��带 Ȱ���ϴ� ���� ������ ��������.

// ���ο� ��带 �����ϴ� �Լ�
// ������ �����͸� �Ű������� �޾Ƽ� ����� �����ͷ� �����Ѵ�.
Node* createNode(int data) {
	// ���ο� ��带 ��ȯ�ؾ� �ϹǷ� ��ȯ�� ��带 �̸� �����.
	Node* newNode;
	// ���ο� ��带 ���� �޸𸮸� �������� �Ҵ�
	newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL) return NULL;
	// ����� ������ �ʵ�(�Ӽ�)�� ���޹��� ��(data)�� ����
	newNode->data = data;
	// ���� ��带 ����Ű�� �����͸� NULL�� �ʱ�ȭ
	newNode->next = NULL;
	// ������ ���ο� ��带 ��ȯ
	// �̶�, �ּҰ��� ��ȯ���� �ʴ� ����, ����ü�� �� ��ü�� ������(�ּ�)�̱� �����̴�.
	return newNode;
}

// ��� ����
// � ��忡 � �����͸� ���޹޾Ƽ� ���ο� ��带 �ڿ� �߰������� �ۼ��ؾ� �Ѵ�.
// �̶� ���޹޴� ����� �����͸� ���޹޾ƾ� �ϹǷ�
// ���������ͷ� ����� �ּҰ��� ���޹޾ƾ� �Ѵ�.
// ��ȯ�� ����
// ���޹��� head����� �տ� ���ο� �����͸� ������ ��带 ����
// head�� �ش��ϴ� �ּҰ��� ���ο� ����� �ּҰ����� ��ȯ
void prependNode(Node** head, int data) {
	// ���ο� ��� ����
	Node* newNode;
	// ���ο� ��� ���� �� ������ ����
	newNode = createNode(data);
	// ���ο� ����� ���� ��� �ּҰ��� �ִ� next �Ӽ���
	// ���� head�� ����Ű�� ù��° ����� �ּҰ���
	// ���ο� ����� next���� ���� -> ���� ��� �տ� ���ο� ��尡 �߰���.
	newNode->next = *head;
	// ���ο� ����� �ּҰ��� head�� ��(*head)�� ����
	*head = newNode;
}

// ��带 ������ ��� �ڿ� �߰�
void appendNode(Node** head, int data) {
	// ���޹��� head�� ��������� NULL ��ȯ
	if (*head == NULL) return NULL;
	// ���޹��� head�� current�� ������ ��, while������ �ݺ������� next �Ӽ� ��ȸ
	Node* current = *head; // �ܺο��� ���޹��� head ���� �����Ϳ� ����� ��� �ּҰ���
	// current ������ ������ ����
	// next �Ӽ��� null�̸�, �ݺ��� ����
	while (current->next != NULL) {
		current = current->next;
	}
	// current->next = ���ο� ���
	current->next = createNode(data);
}

// ��� ����
// �ش� ���� ����Ʈ���� ������ �����͸� ���� ù��° ��带 ����Ʈ �󿡼� ����(free)
// ���̳� ���� ��ȯ���� �ʴ´�.
void deleteNode(Node** head, int data) {
	// ���� ù��° ��带 �ӽ÷� ������ ��� ������ ����
	Node* currentNode = *head;
	// ���� ��带 �ӽ÷� ������ ��� ������ ����
	Node* prev = NULL;

	// ���޵� head�� �����Ͱ� ���޹��� data�� ���ٸ�
	// head->next�� *head�� ������ �ٲٸ� �ȴ�.
	if (currentNode->data == data) {
		*head = currentNode->next;
		free(currentNode);
		return;
	}

	// �ݺ������� next �Ӽ�(���)�� �����Ͽ� �� �����Ͱ� ���޵� �����Ϳ� ������ ���Ѵ�.
	// ���� ���� �����͸� ���� ��带 ã�� �Ǹ�, ���� ����� next�� NULL�� �ٲ� ��
	// ���� ��带 free���־�� �Ѵ�.
	//while (currentNode != NULL && currentNode->data != data) {
	while(1){
		// ���� �ݺ����� currentNode�� ������ �ּҰ��� NULL�̶�� ��
		// ã�� ���� ���ٴ� �ǹ��̴�. -> �Լ� ����
		// while�� ���� �Ŀ� currentNode�� ���ؼ� free�� �� ���̹Ƿ�
		// ���⼭ �ٷ� �Լ��� �����ؾ� �Ѵ�.
		if (currentNode == NULL) { return; }
		// ���� ���� �ִ� ����� �����Ͱ� ���޹��� �����Ϳ� ���ٸ�
		// �ݺ��� Ż���Ͽ� ������ �����ؾ� �Ѵ�.
		if(currentNode->data == data){
			// �����͸� ã�����Ƿ� �ݺ����� �����Ѵ�.
			break;
		}
		
		// ���� ��忡 ���� ��� �ּҸ� �����ϰ�
		prev = currentNode;
		// ���� ����� �ּҴ� next ��� �ּҸ� �ִ´�.
		currentNode = currentNode->next;
	}
	// ������� �Դٸ� currentNode->data�� ã�� �����Ͷ�� ���̴�.
	// ���� ����� next�� ���� ����� next�� �ٲ��־�� �Ѵ�.
	prev->next = currentNode->next;
	// ���� ��带 free�Ͽ� �޸� ����
	free(currentNode);
}

// ��� ���� -> ������ ��带 ��ȯ
// free�� �ش� ��带 �޸� �������� �ʰ�, �ش� ��忡 ���� �ּҰ��� ��ȯ�Ѵ�.
// -> or ���޵� ��� ���� �����Ϳ� ������ ����� �ּҰ��� ��ƺ�����.
void popNode(Node** head, int data, Node** result) {
	// ���޹��� headNode�κ��� data�� ������ ������ ��带
	// �ش� ���� ����Ʈ���� ������ ��, �ش� �����͸� ���� ��带 ���޹��� result�����Ϳ�
	// �ּҸ� �����Ѵ�.
	
	Node* currentNode = *head;
	Node* prev = NULL;

	if (currentNode->data == data) {
		*head = currentNode->next;
		*result = currentNode;
		return;
	}

	while (1) {
		if (currentNode == NULL) {
			*result = currentNode;
			return;
		}
		if (currentNode->data == data) {
			break;
		}
		prev = currentNode;
		currentNode = currentNode->next;
	}

	prev->next = currentNode->next;

	// currentNode�� �ּҰ��� ���޹��� result�� �����Ѵ�
	*result = currentNode;
}

void displayNode(Node* head) {
	Node* current = head;
	while (current != NULL) {
		printf("%d -> ", current->data);
		current = current->next;
	}
	printf("\b\b\b  \n");
}

// ���޹��� �����͸� ���� ���(A)�� ã�� ��, ���ο� �����͸� ���޹޾Ƽ� �ش� ���ο� �����͸� ����
// ���(B)�� A�� next�� �����ϴ� �Լ�
void insertNode(Node** head, int target, int newData) {
	Node* currentNode = *head;
	Node* newNode = createNode(newData);
	
	// ��尡 ������� �� ���ο� ��带 �ְ� ������ �Ʒ� �ڵ� �ּ� Ǯ��
	/*if (*head == NULL) {
		*head = newNode;
		return;
	}*/

	while (1) {
		if (currentNode == NULL) { return; }
		if (currentNode->data == target) { break; }
		currentNode = currentNode->next;
	}
	// Ÿ�� �����͸� ���� ��带 ã�Ҵ� -> currentNode
	newNode->next = currentNode->next;
	// ���� ã�� ����� ���� ���� ���Ӱ� ���� ����� �ּҸ� �ִ´�
	currentNode->next = newNode;
}


#endif