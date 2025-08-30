#include <stdio.h>
#include "treenode.h"
#define _CRT_SECURE_NO_WARNINGS

// treenode.h�� ������ ������ include�Ͽ� �̰����� ����غ���.

int main() {
	// Ʈ�� ����
	TreeNode* root = createTreeNode(1);
	printf("root data: %d\n", root->data);
	QueueTreeNode* queue = createQueueNode(root, NULL);
	insert(root, 2, queue);
	insert(root, 3, queue);
	insert(root, 4, queue);
	insert(root, 5, queue);
	insert(root, 6, queue);
	freeQueueTree(queue);

	// ������ȸ ����
	order(root, PRE);
	printf("\n");
	order(root, IN);
	printf("\n");
	order(root, POST);
	printf("\n");

	return 0;
}