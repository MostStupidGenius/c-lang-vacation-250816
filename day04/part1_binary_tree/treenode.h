#ifndef B_TREE
#define B_TREE
#include <stdio.h>
#include <stdlib.h>
// #include "node.h"

// 이진트리
// 이진트리는 트리 구조 중에서도 자식 노드를 최대 2개까지만 가질 수 있는 트리구조를 가리킨다.
// 이러한 자식노드를 가지는 것은 C언어에서 구조체로 표현할 때
// 변수에 노드 타입의 변수를 선언하는 것으로 구현한다.
typedef struct TreeNode {
	int data; // 노드에 저장할 데이터 속성(변수)
	struct TreeNode* left;	// 왼쪽 자식을 저장할 변수
	struct TreeNode* right; // 오른쪽 자식을 저장할 변수
} TreeNode;

typedef struct QueueTreeNode{
	struct TreeNode* node;
	struct QueueTreeNode* next;
}QueueTreeNode;

// 데이터 값을 전달하면 동적 할당으로 노드 데이터를 생성해서 반환하는 함수
TreeNode* createTreeNode(int data);

// 노드 삽입
TreeNode* insert(TreeNode* root, int data);

// 노드 높이 계산
int getHeight(TreeNode* root);

// 메모리 관리, 모든 노드를 메모리 해제하는 함수
// 재귀적으로 하위 노드에 freeTree를 수행하여 모든 노드를 메모리 해제
void freeTree(TreeNode* root);

// 전위순회
void preorder(TreeNode* root);
// 중위순회
void inorder(TreeNode* root);
// 후위순회
void postorder(TreeNode* root);

enum ORDER_TYPE {
	PRE,
	IN,
	POST,
	LENGTH
};

// 순회 방식을 전달되는 enum 자료구조를 활용하여
// 동적으로 순회하도록 만들어보자.
void order(TreeNode* root, enum ORDER_TYPE type);

// =============함수 정의===============

TreeNode* createTreeNode(int data) {
	// 반환할 새로운 노드 엔티티를 담을 변수를 선언해준다.
	TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
	// 메모리 공간이 부족하여 동적 할당이 실패하면 NULL값이 들어간다.
	// 이러한 널 포인터에 대한 처리 추가
	if (newNode == NULL) { return NULL; }
	
	// 새로 만든 노드의 데이터 값은 전달받은 값
	newNode->data = data;
	// 좌우 자식 노드에 대한 주소값은 NULL로 초기화
	// newNode->left = newNode->right = NULL;
	newNode->left = NULL;
	newNode->right = NULL;

	// 새로운 노드의 주소값을 반환한다.
	return newNode;
}

QueueTreeNode* createQueueNode(TreeNode* node, QueueTreeNode* next) {
	QueueTreeNode* newNode = (QueueTreeNode*)malloc(sizeof(QueueTreeNode));
	if (newNode == NULL) { return NULL; }
	newNode->node = node;
	newNode->next = next;
	return newNode;
}


// 노드 삽입
// 트리노드의 주소값을 담을 수 있는 트리노드 포인터 배열을 매개변수로 받아서
// 0번째부터 트리노드를 저장하여 자식 노드 중 NULL값이 저장된 자식을 찾으면
// 해당 자식의 주소값을 새로운 노드의 주소값으로 바꾼다.
TreeNode* insert(TreeNode* root, int data, QueueTreeNode** queueHead) {
	// 이진트리의 모든 노드를 수평적으로, 각 깊이(depth)마다 순차적으로 들르면서
	// NULL인지 여부를 확인한 뒤, 처음으로 노드의 자식 중 NULL인 값이 나오면
	// 그 위치에 새로운 노드를 집어 넣는다.
	// Queue 자료구조를 활용하여 이를 구현할 수 있다.
	TreeNode* newNode = createTreeNode(data);
	// 트리 노드들을 순차적으로 방문하기 위한 Queue 자료구조를 먼저 선언한다.
	QueueTreeNode* queue = (QueueTreeNode*)malloc(sizeof(QueueTreeNode));
	*queueHead = queue;
	if (queue == NULL) { return NULL; }
	// 만든 큐에 전달받은 루트 노드를 먼저 담는다.
	queue->node = root;
	// 현재 큐에 다음 노드는 없는 상태다 -> NULL로 초기화
	queue->next = NULL;
	
	while (queue != NULL) {
		// 현재 보고 있는 큐 노드의 노드에서 좌우 자식을 queue에 연달아 추가한다.
		QueueTreeNode* newLeft = createQueueNode(queue->node->left, NULL); // (QueueTreeNode*)malloc(sizeof(QueueTreeNode));
		if (newLeft == NULL) { return NULL; }
		// 새롭게 만든 큐노드의 데이터를 현재 보고 있는 노드의 왼쪽 자식의 주소값을 전달한다.
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
		// 현재 노드의 다음 노드를 다음 반복에서 가리켜야 하므로
		// 다음 노드를 바라보게 만든다 -> 안하면 무한루프
		queue = queue->next;
	}

}

// 노드 높이 계산
// 재귀적으로 함수를 수행하여 깊이를 반환받는다(+1 된 상태로)
int getHeight(TreeNode* root) {
	// 기본 케이스
	// 전달받은 노드인 자식 노드가 NULL이면
	// 0을 반환한다(깊이0)
	if (root == NULL) {
		return 0;
	}

	// 재귀 케이스
	// 왼쪽 서브트리와 오른쪽 서브트리 양쪽에 그 깊이를 물어봐야 한다.
	int leftHeight = getHeight(root->left);
	int rightHeight = getHeight(root->right);

	// 양쪽의 깊이 중 더 깊은 값을 골라서 1을 추가(현재 층을 추가)하여
	// 반환한다.
	// 1.
	//return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
	// 2.
	//return ((leftHeight > rightHeight) ? leftHeight : rightHeight) + 1;
	// 3.
	int bigger = (leftHeight > rightHeight) ? leftHeight : rightHeight;
	return bigger + 1;
}

void freeTree(TreeNode* root) {
	// 기본 케이스
	if (root == NULL) return;
	// 전달받은 트리노드로부터 재귀적으로 하위 노드를 탐색하며
	// 메모리 해제해준다.
	if (root != NULL) { // 재귀 케이스
		// 왼쪽 자식에 대해서 메모리 해제
		freeTree(root->left);
		freeTree(root->right);
		// 자기 자신은 마지막에 메모리 해제해 준다.
		free(root);
	}
}

void order(TreeNode* root, enum ORDER_TYPE type) {
	if (root == NULL) { return; }
	// 스위치로 전달된 type에 따라 다르게 동작해보자.
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

// 전위순회
void preorder(TreeNode* root) {
	order(root, PRE);
}
// 중위순회
void inorder(TreeNode* root) {
	order(root, IN);
}
// 후위순회
void postorder(TreeNode* root) {
	order(root, POST);
}

// 연결리스트인 queue트리를 마지막 노드부터 재귀적으로 메모리 해제하는 함수
void freeQueueTree(QueueTreeNode* root) {
	// 전달된 노드가 비어 있다면 종료
	if (root == NULL) {
		return;
	}
	// 비어있지 않다면 다음 노드를 재귀적으로 메모리 해제
	freeQueueTree(root->next);
	// 다음 노드들이 모두 해제되었다면 현재 노드를 해제
	free(root);
}



#endif // !B_TREE
