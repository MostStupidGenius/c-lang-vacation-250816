#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#include "node.h" // ����� ���� ����� ū����ǥ�� �����̸��� �ۼ��Ͽ�
// �� ����� ������ ����� �� �ִ�.

int main() {
	Node* head = NULL; // ù��° ��带 ����ų ������ ����

	// ��� ����
	prependNode(&head, 10);
	prependNode(&head, 20);
	prependNode(&head, 30);

	displayNode(head);
	// ����Ʈ ���
	// Node* current = head;
	// �ݺ�: ���� ��Ұ� NULL�� �ƴ� ���� �ݺ�
	//while (current != NULL) {
	//	printf("%d -> ", current->data);

	//	// ���� ����� ���� ��带 ����Ű�� next�� ����
	//	// current�� �����Ѵ�.
	//	// �̸� ���� ��ü ��Ҹ� ��ȸ�� �� �ִ�.
	//	current = current->next;
	//}
	//printf("\b\b\b  \n");

	// ���� ����Ʈ ���ʿ� ���ο� ������ �߰�(append)
	appendNode(&head, 40); // 30->20->10->40
	
	// Ư�� �����͸� ���� ù��° ��带 ����(free)
	deleteNode(&head, 10); // 30->20->40
	
	// Ư�� �����͸� ���� ��带 ������ ��, �� �ּҰ��� ���⼭ ���� ������ ����
	Node* poped = NULL;
	popNode(&head, 20, &poped); // 30->40
	if (poped == NULL) return 1;

	// ã�� ���� ���� ����Ʈ������ ���ŵǰ�, ���޵� result �����ͺ����� ����ȴ�.
	printf("result: %d\n", poped->data); // 20
	
	// ������ ��ȸ, ���
	displayNode(head); 
	/*current = head;
	while (current != NULL) {
		printf("%d -> ", current->data);
		current = current->next;
	}
	printf("\b\b\b  \n");*/

	// head�κ��� �����Ͽ� 30�̶�� ���� ���� ��� �ڿ�
	// 50 ���� ���� ��带 ����
	insertNode(&head, 30, 50);
	displayNode(head); // 30->50->40

	return 0;
}