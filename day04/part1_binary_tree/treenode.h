#ifndef B_TREE
#define B_TREE
#include <stdio.h>
#include <stdlib.h>
// #include "node.h"

// ����Ʈ��
// ����Ʈ���� Ʈ�� ���� �߿����� �ڽ� ��带 �ִ� 2�������� ���� �� �ִ� Ʈ�������� ����Ų��.
// �̷��� �ڽĳ�带 ������ ���� C���� ����ü�� ǥ���� ��
// ������ ��� Ÿ���� ������ �����ϴ� ������ �����Ѵ�.
typedef struct TreeNode {
	int data; // ��忡 ������ ������ �Ӽ�(����)
	struct TreeNode* left;	// ���� �ڽ��� ������ ����
	struct TreeNode* right; // ������ �ڽ��� ������ ����
} TreeNode;

typedef struct QueueTreeNode{
	struct TreeNode* node;
	struct QueueTreeNode* next;
}QueueTreeNode;

// ������ ���� �����ϸ� ���� �Ҵ����� ��� �����͸� �����ؼ� ��ȯ�ϴ� �Լ�
TreeNode* createTreeNode(int data);

// ��� ����
TreeNode* insert(TreeNode* root, int data);

// ��� ���� ���
int getHeight(TreeNode* root);

// �޸� ����, ��� ��带 �޸� �����ϴ� �Լ�
// ��������� ���� ��忡 freeTree�� �����Ͽ� ��� ��带 �޸� ����
void freeTree(TreeNode* root);

// ������ȸ
void preorder(TreeNode* root);
// ������ȸ
void inorder(TreeNode* root);
// ������ȸ
void postorder(TreeNode* root);

enum ORDER_TYPE {
	PRE,
	IN,
	POST,
	LENGTH
};

// ��ȸ ����� ���޵Ǵ� enum �ڷᱸ���� Ȱ���Ͽ�
// �������� ��ȸ�ϵ��� ������.
void order(TreeNode* root, enum ORDER_TYPE type);

// =============�Լ� ����===============

TreeNode* createTreeNode(int data) {
	// ��ȯ�� ���ο� ��� ��ƼƼ�� ���� ������ �������ش�.
	TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
	// �޸� ������ �����Ͽ� ���� �Ҵ��� �����ϸ� NULL���� ����.
	// �̷��� �� �����Ϳ� ���� ó�� �߰�
	if (newNode == NULL) { return NULL; }
	
	// ���� ���� ����� ������ ���� ���޹��� ��
	newNode->data = data;
	// �¿� �ڽ� ��忡 ���� �ּҰ��� NULL�� �ʱ�ȭ
	// newNode->left = newNode->right = NULL;
	newNode->left = NULL;
	newNode->right = NULL;

	// ���ο� ����� �ּҰ��� ��ȯ�Ѵ�.
	return newNode;
}

QueueTreeNode* createQueueNode(TreeNode* node, QueueTreeNode* next) {
	QueueTreeNode* newNode = (QueueTreeNode*)malloc(sizeof(QueueTreeNode));
	if (newNode == NULL) { return NULL; }
	newNode->node = node;
	newNode->next = next;
	return newNode;
}


// ��� ����
// Ʈ������� �ּҰ��� ���� �� �ִ� Ʈ����� ������ �迭�� �Ű������� �޾Ƽ�
// 0��°���� Ʈ����带 �����Ͽ� �ڽ� ��� �� NULL���� ����� �ڽ��� ã����
// �ش� �ڽ��� �ּҰ��� ���ο� ����� �ּҰ����� �ٲ۴�.
TreeNode* insert(TreeNode* root, int data, QueueTreeNode** queueHead) {
	// ����Ʈ���� ��� ��带 ����������, �� ����(depth)���� ���������� �鸣�鼭
	// NULL���� ���θ� Ȯ���� ��, ó������ ����� �ڽ� �� NULL�� ���� ������
	// �� ��ġ�� ���ο� ��带 ���� �ִ´�.
	// Queue �ڷᱸ���� Ȱ���Ͽ� �̸� ������ �� �ִ�.
	TreeNode* newNode = createTreeNode(data);
	// Ʈ�� ������ ���������� �湮�ϱ� ���� Queue �ڷᱸ���� ���� �����Ѵ�.
	QueueTreeNode* queue = (QueueTreeNode*)malloc(sizeof(QueueTreeNode));
	*queueHead = queue;
	if (queue == NULL) { return NULL; }
	// ���� ť�� ���޹��� ��Ʈ ��带 ���� ��´�.
	queue->node = root;
	// ���� ť�� ���� ���� ���� ���´� -> NULL�� �ʱ�ȭ
	queue->next = NULL;
	
	while (queue != NULL) {
		// ���� ���� �ִ� ť ����� ��忡�� �¿� �ڽ��� queue�� ���޾� �߰��Ѵ�.
		QueueTreeNode* newLeft = createQueueNode(queue->node->left, NULL); // (QueueTreeNode*)malloc(sizeof(QueueTreeNode));
		if (newLeft == NULL) { return NULL; }
		// ���Ӱ� ���� ť����� �����͸� ���� ���� �ִ� ����� ���� �ڽ��� �ּҰ��� �����Ѵ�.
		// newLeft->node = queue->node->left;
		queue->next = newLeft;
		if (queue->next->node == NULL) {
			queue->next->node = newNode;
			queue->node->left = newNode;
			return root;
		}
		else {
			QueueTreeNode* newRight = createQueueNode(queue->node->right, NULL); // (QueueTreeNode*)malloc(sizeof(QueueTreeNode));
			if (newRight == NULL) { return NULL; }
			// newRight->node = queue->node->right;
			if(newRight->node == NULL){
				newRight->node = newNode;
				queue->node->right = newNode;
				return root;
			}
			newLeft->next = newRight;
		}
		// ���� ����� ���� ��带 ���� �ݺ����� �����Ѿ� �ϹǷ�
		// ���� ��带 �ٶ󺸰� ����� -> ���ϸ� ���ѷ���
		queue = queue->next;
	}

}

// ��� ���� ���
// ��������� �Լ��� �����Ͽ� ���̸� ��ȯ�޴´�(+1 �� ���·�)
int getHeight(TreeNode* root) {
	// �⺻ ���̽�
	// ���޹��� ����� �ڽ� ��尡 NULL�̸�
	// 0�� ��ȯ�Ѵ�(����0)
	if (root == NULL) {
		return 0;
	}

	// ��� ���̽�
	// ���� ����Ʈ���� ������ ����Ʈ�� ���ʿ� �� ���̸� ������� �Ѵ�.
	int leftHeight = getHeight(root->left);
	int rightHeight = getHeight(root->right);

	// ������ ���� �� �� ���� ���� ��� 1�� �߰�(���� ���� �߰�)�Ͽ�
	// ��ȯ�Ѵ�.
	// 1.
	//return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
	// 2.
	//return ((leftHeight > rightHeight) ? leftHeight : rightHeight) + 1;
	// 3.
	int bigger = (leftHeight > rightHeight) ? leftHeight : rightHeight;
	return bigger + 1;
}

void freeTree(TreeNode* root) {
	// �⺻ ���̽�
	if (root == NULL) return;
	// ���޹��� Ʈ�����κ��� ��������� ���� ��带 Ž���ϸ�
	// �޸� �������ش�.
	if (root != NULL) { // ��� ���̽�
		// ���� �ڽĿ� ���ؼ� �޸� ����
		freeTree(root->left);
		freeTree(root->right);
		// �ڱ� �ڽ��� �������� �޸� ������ �ش�.
		free(root);
	}
}

void order(TreeNode* root, enum ORDER_TYPE type) {
	if (root == NULL) { return; }
	// ����ġ�� ���޵� type�� ���� �ٸ��� �����غ���.
	switch (type)
	{
	case PRE:
		printf("%d -> ", root->data);
		order(root->left, type);
		order(root->right, type);
		break;
	case IN:
		order(root->left, type);
		printf("%d -> ", root->data);
		order(root->right, type);
		break;
	case POST:
		order(root->left, type);
		order(root->right, type);
		printf("%d -> ", root->data);
		break;
	}
}

// ������ȸ
void preorder(TreeNode* root) {
	order(root, PRE);
}
// ������ȸ
void inorder(TreeNode* root) {
	order(root, IN);
}
// ������ȸ
void postorder(TreeNode* root) {
	order(root, POST);
}

// ���Ḯ��Ʈ�� queueƮ���� ������ ������ ��������� �޸� �����ϴ� �Լ�
void freeQueueTree(QueueTreeNode* root) {
	// ���޵� ��尡 ��� �ִٸ� ����
	if (root == NULL) {
		return;
	}
	// ������� �ʴٸ� ���� ��带 ��������� �޸� ����
	freeQueueTree(root->next);
	// ���� ������ ��� �����Ǿ��ٸ� ���� ��带 ����
	free(root);
}



#endif // !B_TREE
