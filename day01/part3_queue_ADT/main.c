#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

// Qeueue 자료구조
// 선입선출(FIFO)의 구조를 가지는 자료구조를 이야기한다.
// 주로 작업 스케줄링, 대기열 등을 구현할 때 사용되는 자료구조다.
// 구조체로 Queue에 들어갈 속성을 정의한다.

// 구조체 정의
// Queue ADT 예시
typedef struct { // typedef 사용자 정의 타입 선언
	// 정수 데이터를 저장할 items
	int* items;
	// 저장 가능한 요소의 개수를 정의(용량)
	int capacity;
} Queue;

// Queue를 만드는 함수. 이때 큐의 용량을 전달하여 크기를 정하도록 한다.
Queue* createQueue(int capacity) {
	// 동적 할당을 통해서 Queue를 만든다.
	int size = sizeof(Queue); // Queue자료형의 크기를 추출한다.
	Queue* queue = (Queue*)malloc(size);
	if (queue == NULL) { return NULL;}
	// 전달받은 용량(요소의 개수)을 저장하는 타입의 개수에 곱하여 items 속성의 크기를 동적으로 결정한다.
	queue->items = (int*)malloc(sizeof(int) * capacity);
	if (queue->items == NULL) { return NULL; }
	queue->capacity = capacity;

	// 큐에 담을 모든 저장공간을 0으로 초기화
	// malloc 대신에 calloc을 사용하면 자동으로 초기화해준다.
	for (int i = 0; i < capacity; i++) {
		queue->items[i] = 0;
	}

	return queue;
}

// Queue 자료구조에 쓰일 함수들 선언(바디를 구현하지 않는다)

void printElements(Queue* queue);

// 데이터 삽입
// enqueue
int enqueue(Queue* queue, int data);

// 데이터 추출 및 제거
// dequeue
int dequeue(Queue* queue);

// 지금 나가야 할 데이터 추출(제거x) 및 확인
// peek
int peek(Queue* queue);

// 비어있는지 여부
// isEmpty
int isEmpty(Queue* queue);

// 꽉 차 있는지 여부
// isFull
int isFull(Queue* queue);

int main() {
	// createQueue 함수를 이용하여 Queue자료형 변수를 만들어보자.
	// 이때 Queue 자료형은 주소값으로 전달받기 때문에 자료형뒤에 *를 붙여서
	// 포인터 변수로 만들어주어야 한다.
	Queue* queue = createQueue(10);
	// 포인터 변수를 통해서 하위 속성에 접근할 때에는
	// 화살표연산자 -> 를 통해서 접근한다.
	printf("%d\n", queue->capacity);

	enqueue(queue, 3);
	enqueue(queue, 1);
	enqueue(queue, 4);
	enqueue(queue, 2);
	enqueue(queue, 5);
	printElements(queue); // 3 1 4 2 5
	// 디큐를 통해서 첫번째 요소인 3을 제거
	dequeue(queue);
	printElements(queue); // 1 4 2 5
	enqueue(queue, 10);
	enqueue(queue, 11);
	enqueue(queue, 12);
	enqueue(queue, 13);
	enqueue(queue, 14);
	enqueue(queue, 15); // 여기까지 데이터가 들어간다.
	enqueue(queue, 16); // 꽉 차서 안 들어간다.
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
		/*// 0일 때 출력 중지
		if (data == 0) {
			break;
		}
		else {
			printf("%d ", data);
		}*/
	}
	printf("\b]\n");
}

// 데이터 삽입
int enqueue(Queue* queue, int data) {
	if (isFull(queue)) {
		printf("큐가 가득차서 넣을 수 없습니다.\n");
		return 0; // 문제가 있음
	}
	// 데이터를 추가
	// 모든 요소를 검사하여 0이 처음으로 나오는 인덱스에
	// 데이터를 저장하고 함수를 종료한다.
	// 큐의 전체 길이
	int size = queue->capacity; 
	for (int i = 0; i < size; i++){
		if (queue->items[i] == 0) {
			queue->items[i] = data;
			break; // 반복문 종료
		}
	}
	return data;
}

// 데이터 추출 및 제거
// dequeue
int dequeue(Queue* queue) {
	// 만약 큐가 비어있으면 0 반환
	if (isEmpty(queue)) return 0;
	// 0번째 요소 추출
	int extract = queue->items[0];
	for (int i = 0; i < queue->capacity; i++){
		// 다음 요소(i+1)의 값을 현재 요소(i)로 덮어쓰기 한다.
		queue->items[i] = queue->items[i + 1];
		// 다음 요소가 0이면 데이터가 더이상 없는 것이므로
		// 조기종료한다.
		if (queue->items[i+1] == 0) break;
	}

	// 추출한 데이터 반환
	return extract;
}

// 지금 나가야 할 데이터 추출(제거x) 및 확인
// peek
int peek(Queue* queue) {
	// 만약 큐가 비어있으면 0 반환
	if (isEmpty(queue)) return 0;
	// 0번째 요소 추출
	int extract = queue->items[0];
	// 추출한 데이터 반환
	return extract;
}

// 비어있는지 여부
// isEmpty
int isEmpty(Queue* queue) {
	// 0번째방의 값이 0이면 모든 데이터가 0일 것이므로 비어있다고 판단한다.
	return queue->items[0] == 0;
};

// 꽉 차 있는지 여부
// isFull
int isFull(Queue* queue) {
	// 마지막 요소(queue->capacity-1번째요소)의 값이 0이 아닌지 여부
	// 0이 아니면 꽉 차 있다는 의미이므로 그대로 반환하면 된다.
	return queue->items[queue->capacity-1] != 0;
}