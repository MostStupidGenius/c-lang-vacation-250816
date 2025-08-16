#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

// static �����
// static�̶� ����, �Լ� ���� ���� �Լ��� ����� ������ ������� �ʵ���
// �������� �����ֱ⸦ �ٲ��ִ� ������̴�.
// �̶�, �Լ� �� ���������� static�� ���̸� �ش� �Լ��� ����Ǵ���
// ���� �Լ� ȣ�� �� �ش� ������ ���� �����ǰ� �ȴ�.
// ���������� �����Լ��� static�� ���̸� �ش� ������ �ش� ��������
// �ܺ��� ���Ͽ��� �����ϰų� ȣ���� �� ���� �����.
// static�� ���� ������ ���α׷� ���� �� ���� ������� ����, �Ҵ�ȴ�.

// static ���������� Ȱ���Ͽ� �Ǻ���ġ ������ �����غ���.

// ��ȯ���� ���� �Ǻ���ġ ������ ��
int fibonacci() {
	// ���� ���� ���� ����ƽ ��������
	static int prev = 0;
	// ���� ���� ���� ����ƽ ��������
	static int curr = 1;
	// ������ �� ���� ����Ͽ� ���� ���� ���� ������ ����
	// ���� ���� ���� ���� ���ؼ� next�� ����
	int next = prev + curr;
	// ���� ���� ���� �� ������ ����
	prev = curr;
	// ���� ���� ���� ������ ���� ���� ����
	curr = next;
	// ���簪�̾��� ���� ������ ��ȯ
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
	// �Ǻ���ġ�������� Ȯ���ϰ� ���� ����
	int length = 10;
	// �Ǻ���ġ ���� �ݺ� ȣ��
	for (int i = 0; i < length; i++) {
		int value = fibonacci();
		printf("%d. %d\n", i+1, value);
	}
	return 0;
}






