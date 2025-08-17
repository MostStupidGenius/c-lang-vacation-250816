#include <stdio.h>
#include <stdbool.h> // 논리자료형을 명시적으로 사용할 수 있게 해주는 헤더
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

// 스택 자료구조
// 나중에 들어온 데이터가 먼저 나간다(Last In First Out) LIFO 구조를 가리킨다.

// 스택 자료구조를 C언어에서 구현하는 방법
// 1. 배열을 활용
// 데이터를 저장할 길이를 미리 정의
#define MAX_SIZE 100 // 스택의 최대 크기(길이) 정의

// 데이터를 저장할 배열을 속성으로 가지는 구조체를 정의
typedef struct {
	// 데이터를 저장할 배열
	int data[MAX_SIZE];
	// 스택의 맨 위를 가리키는 인덱스
	int top; // 데이터가 없으면 -1을 저장(기본값)
} Stack;

// 스택을 생성/초기화하는 함수
void initStack(Stack *stack) {
	stack->top = -1; // 빈 스택의 top은 -1로 설정
}

// 스택에 데이터를 추가하는 함수(push)
bool push(Stack* stack, int data);
// 스택에서 데이터를 제거하고 반환하는 함수(pop)
// value 포인터 변수는 함수 내부에서 추출된 정보를 저장하는 용도이며
// 외부에서도 해당 변수를 접근할 수 있기 때문에 데이터를 변수를 통해 전달한다고 생각해도 무방하다.
bool pop(Stack* stack, int *value);
// 스택에서 맨 위 데이터를 확인하는 함수(peek, top)
bool peek(Stack* stack, int* value);
// 스택의 모든 요소를 출력하는 함수(display)
void display(Stack* stack);
// 스택이 꽉차 있는지 여부를 반환(isFull)
bool isFull(Stack* stack);
// 스택이 비어있는지 여부를 반환(isEmpty)
bool isEmpty(Stack* stack);

// 2. 연결리스트 활용

int main() {
	// 스택 구조체를 실체화
	Stack stack; // 스택 엔티티(Entity)
	int value;	 // 함수를 통해서 값을 전달받는 용도로 쓰이는 저장공간

	// 스택 초기화
	initStack(&stack); // 해당 스택의 주소값을 전달해야 한다.

	// 데이터 삽입
	push(&stack, 10);
	push(&stack, 20);
	push(&stack, 30);

	// 스택 내용 출력
	display(&stack);

	// peek 연산
	// top인덱스의 값을 반환받는다.
	// 반환받을 때 main()함수에 선언해놓은 value 변수에 담아서 반환받는다.
	int got = peek(&stack, &value); // 함수 내부에서 value에 접근할 수 있도록
	// value의 주소값(&)을 전달해준다.
	if (got) {
		printf("스택의 맨 위 요소 값: %d\n", value);
	}

	// pop 연산
	// 맨 위의 요소를 제거하여 value에 담고 인덱스는 1감소시킨다.
	if (pop(&stack, &value)) {
		printf("팝(pop)한 요소: %d\n", value);
		display(&stack);
	}
	return 0;
}

bool push(Stack* stack, int data) {
	// 만약 스택이 모두 차 있으면 스택 오버플로우라는 경고문구를 출력
	if (isFull(stack)) {
		printf("스택 오버플로우: 스택이 가득 찼습니다.");
		return false; // 정상적으로 종료하지 못함
	}

	// top에 해당하는 인덱스에서 1을 추가한 위치에 새로운 데이터를 추가해야 한다.
	// 새로 추가하려는 요소의 인덱스
	int newIndex = ++(stack->top);
	// top의 값을 1 증가시키면서 그 값을 새로운 데이터의 인덱스로 삼는다.
	// 이 요소의 값에 data를 할당한다.
	stack->data[newIndex] = data;
	// 정상적으로 데이터 삽입이 완료됨
	return true;
}

// top 인덱스의 데이터를 제거하고 그 값을 전달받은 포인터 변수를 통해 반환하는 함수
bool pop(Stack* stack, int* value) {
	// 스택이 비어있는지 검사
	if (isEmpty(stack)) {
		printf("스택 언더플로우: 스택이 비어 있습니다.");
		return false;
	}

	// 스택이 비어있지 않으므로 진행한다.
	// 현재 top을 가리키는 인덱스를 currentIdx에 사용한 뒤
	// top의 값을 1 감소시킨다.
	int currentIdx = stack->top--;
	*value = stack->data[currentIdx];
	//stack->top--; // 위에서 후위증감연산자를 통해 연산을 통합시킨다.

	return true;
}

bool peek(Stack* stack, int* value) {
	// 만약 스택이 비어있으면 데이터 확인이 불가능할 것이다.
	if (isEmpty(stack)) {
		printf("언더플로우");
		return false;
	}
	// 전달받은 포인터변수 value에 stack->data 중 top 위치의 값을 담는다.
	*value = stack->data[stack->top];
	return true;
}

void display(Stack* stack) {
	if (isEmpty(stack)) {
		printf("언더플로우\n");
		return;
	}
	// top인덱스로부터 1씩 감소하며 데이터를 순회한다.
	for (int i = stack->top; i>=0 ; i--) {
		// 해당 데이터가 위치한 인덱스와 함께 그 값을 한 줄에 출력
		printf("%d. %d\n", i, stack->data[i]);
	}
}

bool isFull(Stack* stack) {
	// 스택 최대 크기의 1을 뺀 인덱스가 top이면
	// 데이터가 꽉찬 것이므로, 해당 여부를 반환하면 된다.
	return stack->top == (MAX_SIZE - 1);
}
bool isEmpty(Stack* stack) {
	// -1인덱스는 데이터가 없음을 나타내는 값이므로
	// 해당 여부를 반환하면 된다.
	return stack->top == -1;
}