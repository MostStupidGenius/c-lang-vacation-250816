// 헤더 파일
// 여러 파일에서 공통적으로 사용하고자 하는 기능이나 구조체 등의 엔티티를 정의하는 공간이다.
// 반복적으로 사용하는 기능이나 구조체 등을 미리 정의해둠으로써
// 반복적인 코드 작성을 미연에 방지할 수 있다.
// 이런 나만의 코드를 헤더로 작성하여 많이 쌓게 되면 이를 '라이브러리'라는 명칭으로
// 묶어서 사용할 수 있게 된다.

// 전처리기
// 헤더파일은 여러 파일에서 include(참조) 될 수 있기 때문에
// 중복으로 참조가 되는 경우 오류가 발생할 수 있다.
// 이를 방지하기 위해서는 include된 헤더 파일을 관리할 주체가 필요하다 -> 전처리기
// 전처리기에게 만약 이 헤더가 정의되어 있다면~이라는 식으로 알려주면
// 중복 참조를 방지할 수 있다.

// #ifdef
// 이 헤더 파일이 이미 참조되어 있다면~이라는 의미이다.
// #ifdef NODE_H // 이미 참조되어 있다면 이대로 쓰겠다.
// #else // 참조되어 있지 않을 때 처리
// #endif // if문의 끝을 알림

// #ifndef
// 위의 ifdef의 반대이다.
// 즉, 만약 참조된 적이 없다면 뒤의 이름으로 정의하겠다-라는 의미이다.
#ifndef NODE_H
// ifndef과 endif 사이에 정의하고자 하는 내용을 작성해주면 된다.
#define NODE_H // 여기서 정의하겠다.
#include <stdlib.h>
// 노드 구조체 정의
typedef struct Node {
	// 노드에 저장할 데이터 추가
	int data;
	// 다음 노드를 가리키는 포인터 변수
	struct Node* next;
} Node;

// 노드에 대한 연산
// 노드에 대한 정의를 했으니 외부에서 따로 연산을 만들 것이 아니라
// 이 안에서 해당 노드를 활용하는 여러 연산을 정의하자.

// 새로운 노드를 생성하는 함수
// 정수형 데이터를 매개변수로 받아서 노드의 데이터로 저장한다.
Node* createNode(int data) {
	// 새로운 노드를 반환해야 하므로 반환할 노드를 미리 만든다.
	Node* newNode;
	// 새로운 노드를 위한 메모리를 동적으로 할당
	newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL) return NULL;
	// 노드의 데이터 필드(속성)에 전달받은 값(data)을 저장
	newNode->data = data;
	// 다음 노드를 가리키는 포인터를 NULL로 초기화
	newNode->next = NULL;
	// 생성된 새로운 노드를 반환
	// 이때, 주소값을 반환하지 않는 것은, 구조체는 그 자체로 포인터(주소)이기 때문이다.
	return newNode;
}

// 노드 삽입
// 어떤 노드에 어떤 데이터를 전달받아서 새로운 노드를 뒤에 추가할지를 작성해야 한다.
// 이때 전달받는 노드의 포인터를 전달받아야 하므로
// 이중포인터로 노드의 주소값을 전달받아야 한다.
// 반환값 없음
// 전달받은 head노드의 앞에 새로운 데이터를 보유한 노드를 삽입
// head에 해당하는 주소값을 새로운 노드의 주소값으로 교환
void prependNode(Node** head, int data) {
	// 새로운 노드 선언
	Node* newNode;
	// 새로운 노드 생성 및 데이터 전달
	newNode = createNode(data);
	// 새로운 노드의 다음 노드 주소값을 넣는 next 속성에
	// 기존 head가 가리키던 첫번째 노드의 주소값을
	// 새로운 노드의 next값에 저장 -> 기존 헤드 앞에 새로운 노드가 추가됨.
	newNode->next = *head;
	// 새로운 노드의 주소값을 head의 값(*head)에 저장
	*head = newNode;
}

// 노드를 마지막 노드 뒤에 추가
void appendNode(Node** head, int data) {
	// 전달받은 head가 비어있으면 NULL 반환
	if (*head == NULL) return NULL;
	// 전달받은 head를 current에 저장한 뒤, while문으로 반복적으로 next 속성 순회
	Node* current = *head; // 외부에서 전달받은 head 이중 포인터에 저장된 노드 주소값을
	// current 포인터 변수에 저장
	// next 속성이 null이면, 반복문 종료
	while (current->next != NULL) {
		current = current->next;
	}
	// current->next = 새로운 노드
	current->next = createNode(data);
}

// 노드 삭제
// 해당 연결 리스트에서 전달한 데이터를 가진 첫번째 노드를 리스트 상에서 제거(free)
// 값이나 노드는 반환하지 않는다.
void deleteNode(Node** head, int data) {
	// 현재 첫번째 노드를 임시로 저장한 노드 포인터 변수
	Node* currentNode = *head;
	// 이전 노드를 임시로 저장할 노드 포인터 변수
	Node* prev = NULL;

	// 전달된 head의 데이터가 전달받은 data와 같다면
	// head->next를 *head의 값으로 바꾸면 된다.
	if (currentNode->data == data) {
		*head = currentNode->next;
		free(currentNode);
		return;
	}

	// 반복적으로 next 속성(노드)에 접근하여 그 데이터가 전달된 데이터와 같은지 비교한다.
	// 만약 같은 데이터를 가진 노드를 찾게 되면, 이전 노드의 next를 NULL로 바꾼 뒤
	// 현재 노드를 free해주어야 한다.
	//while (currentNode != NULL && currentNode->data != data) {
	while(1){
		// 이전 반복에서 currentNode에 저장한 주소값이 NULL이라는 건
		// 찾는 값이 없다는 의미이다. -> 함수 종료
		// while문 종료 후에 currentNode에 대해서 free를 할 것이므로
		// 여기서 바로 함수를 종료해야 한다.
		if (currentNode == NULL) { return; }
		// 현재 보고 있는 노드의 데이터가 전달받은 데이터와 같다면
		// 반복문 탈출하여 로직을 수행해야 한다.
		if(currentNode->data == data){
			// 데이터를 찾았으므로 반복문을 종료한다.
			break;
		}
		
		// 이전 노드에 현재 노드 주소를 저장하고
		prev = currentNode;
		// 현재 노드의 주소는 next 노드 주소를 넣는다.
		currentNode = currentNode->next;
	}
	// 여기까지 왔다면 currentNode->data가 찾는 데이터라는 것이다.
	// 이전 노드의 next를 현재 노드의 next로 바꿔주어야 한다.
	prev->next = currentNode->next;
	// 현재 노드를 free하여 메모리 해제
	free(currentNode);
}

// 노드 삭제 -> 삭제한 노드를 반환
// free로 해당 노드를 메모리 해제하지 않고, 해당 노드에 대한 주소값을 반환한다.
// -> or 전달된 노드 이중 포인터에 삭제한 노드의 주소값을 담아보낸다.
void popNode(Node** head, int data, Node** result) {
	// 전달받은 headNode로부터 data를 값으로 가지는 노드를
	// 해당 연결 리스트에서 제거한 뒤, 해당 데이터를 가진 노드를 전달받은 result포인터에
	// 주소를 저장한다.
	
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

	// currentNode의 주소값을 전달받은 result에 저장한다
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

// 전달받은 데이터를 가진 노드(A)를 찾은 뒤, 새로운 데이터를 전달받아서 해당 새로운 데이터를 가진
// 노드(B)를 A의 next로 삽입하는 함수
void insertNode(Node** head, int target, int newData) {
	Node* currentNode = *head;
	Node* newNode = createNode(newData);
	
	// 헤드가 비어있을 때 새로운 노드를 넣고 싶으면 아래 코드 주석 풀기
	/*if (*head == NULL) {
		*head = newNode;
		return;
	}*/

	while (1) {
		if (currentNode == NULL) { return; }
		if (currentNode->data == target) { break; }
		currentNode = currentNode->next;
	}
	// 타겟 데이터를 가진 노드를 찾았다 -> currentNode
	newNode->next = currentNode->next;
	// 현재 찾은 노드의 다음 노드로 새롭게 만든 노드의 주소를 넣는다
	currentNode->next = newNode;
}


#endif