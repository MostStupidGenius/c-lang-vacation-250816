#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

// static 예약어
// static이란 변수, 함수 등을 메인 함수가 종료될 때까지 사라지지 않도록
// 스코프와 생명주기를 바꿔주는 예약어이다.
// 이때, 함수 내 지역변수에 static을 붙이면 해당 함수가 종료되더라도
// 다음 함수 호출 시 해당 변수의 값이 유지되게 된다.
// 전역변수나 전역함수에 static을 붙이면 해당 파일의 해당 변수들은
// 외부의 파일에서 접근하거나 호출할 수 없게 만든다.
// static을 붙인 대상들은 프로그램 실행 시 따로 모아져서 선언, 할당된다.

// static 지역변수를 활용하여 피보나치 수열을 구현해보자.

// 반환값은 현재 피보나치 수열의 값
int fibonacci() {
	// 이전 값을 담을 스태틱 지역변수
	static int prev = 0;
	// 현재 값을 담을 스태틱 지역변수
	static int curr = 1;
	// 다음에 올 값을 계산하여 현재 값을 담은 변수에 저장
	// 이전 값과 현재 값을 더해서 next에 저장
	int next = prev + curr;
	// 현재 값을 이전 값 변수에 저장
	prev = curr;
	// 현재 값을 담은 변수에 다음 값을 저장
	curr = next;
	// 현재값이었던 이전 변수를 반환
	return prev;
}

int main() {
	//int value = fibonacci();
	//printf("%d\n", value);
	//value = fibonacci();
	//printf("%d\n", value);
	//value = fibonacci();
	//printf("%d\n", value);
	//value = fibonacci();
	//printf("%d\n", value);
	printf("=============\n");
	// 피보나치수열에서 확인하고 싶은 길이
	int length = 10;
	// 피보나치 수열 반복 호출
	for (int i = 0; i < length; i++) {
		int value = fibonacci();
		printf("%d. %d\n", i+1, value);
	}
	return 0;
}






