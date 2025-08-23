#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#include "node.h" // 사용자 정의 헤더는 큰따옴표에 파일이름을 작성하여
// 그 기능을 빌려서 사용할 수 있다.

int main() {
	Node* head = NULL; // 첫번째 노드를 가리킬 포인터 변수

	// 노드 삽입
	prependNode(&head, 10);
	prependNode(&head, 20);
	prependNode(&head, 30);

	displayNode(head);
	// 리스트 출력
	// Node* current = head;
	// 반복: 현재 요소가 NULL이 아닌 동안 반복
	//while (current != NULL) {
	//	printf("%d -> ", current->data);

	//	// 현재 노드의 다음 노드를 가리키는 next의 값을
	//	// current에 저장한다.
	//	// 이를 통해 전체 요소를 순회할 수 있다.
	//	current = current->next;
	//}
	//printf("\b\b\b  \n");

	// 연결 리스트 뒤쪽에 새로운 데이터 추가(append)
	appendNode(&head, 40); // 30->20->10->40
	
	// 특정 데이터를 가진 첫번째 노드를 제거(free)
	deleteNode(&head, 10); // 30->20->40
	
	// 특정 데이터를 가진 노드를 제거한 뒤, 그 주소값을 여기서 만든 변수에 저장
	Node* poped = NULL;
	popNode(&head, 20, &poped); // 30->40
	if (poped == NULL) return 1;

	// 찾은 노드는 연결 리스트에서는 제거되고, 전달된 result 포인터변수에 저장된다.
	printf("result: %d\n", poped->data); // 20
	
	// 데이터 순회, 출력
	displayNode(head); 
	/*current = head;
	while (current != NULL) {
		printf("%d -> ", current->data);
		current = current->next;
	}
	printf("\b\b\b  \n");*/

	// head로부터 시작하여 30이라는 값을 가진 노드 뒤에
	// 50 값을 가진 노드를 삽입
	insertNode(&head, 30, 50);
	displayNode(head); // 30->50->40

	return 0;
}