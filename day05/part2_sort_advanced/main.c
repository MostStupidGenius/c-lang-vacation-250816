#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

// ��� ���� �˰���
// �� ����, ���� ����, �� ����
// �� ���İ� ���� ������ ���� ���� �˰����� Ȱ���� ���� �˰����̴�.
// ���� ���� �˰����̶�, ū ������ ���� ������ �ɰ��� �ذ��� ��,
// �׷��� �ذ�� ������ ���ļ� �� ū ������ �ش��� ã�ư��� ����̴�.
// -> ��������� ������ �����Ͽ� ���ʷ� �����س����� ����̴�.

// �� ����
// �� ������ ������ �� ��, ������ �Ǵ� ��Ҹ� �ϳ� �����ϴµ�,
// �̷��� ���õ� ��Ҹ� �ǹ�(pivot)�̶�� �θ���.
// �� �ǹ����� ���� ��Ҵ� �������� ������ �ٽ� �� ���ķ� �����Ѵ�.
// ū ��Ҵ� ������ ������ �� ���ķ� �����Ѵ�. -> ��� ���̽�
// ���� ���޹��� �迭�� ������ 1�� �����̸� 
// �״�� �Լ��� �����Ѵ�(����x)-> �⺻ ���̽�
// datas[]: ������ �迭
// lowIndex: ������ ������ ������ �ε���
// highIndex: ������ ������ ū�� �ε���
int partition(int datas[], int lowIndex, int highIndex);
void swap(int *num1, int *num2);
void displayArray(int datas[], int start, int end);
void quickSort(int datas[], int lowIndex, int highIndex) {
	// �⺻ ���̽�
	// ��Ұ� 2�� �̻��� ���, ������ �����Ѵ�.
	if (lowIndex < highIndex) { // ��� ���̽�
		// ������ �� �ǹ� ���� �� ����
		int pivot = partition(datas, lowIndex, highIndex);
		// �ǹ��� �������� ���� ��ҿ� ū ��Ҹ� �¿�� ������ ��������� ������ �����Ѵ�.
		quickSort(datas, lowIndex, pivot - 1);
		quickSort(datas, pivot + 1, highIndex);
		displayArray(datas, lowIndex, highIndex);
	}
}

// ������ �� �Ǻ�(�ε���)�� ���� �� �Ǻ��� �¿�� ũ�⿡ �´� ������ ��ġ�ϱ� ���� �Լ�
int partition(int datas[], int lowIndex, int highIndex) {
	// �ǹ��� ����. ��Ģ�� ���� ����.
	int pivotIndex = highIndex;
	int pivot = datas[pivotIndex];
	// i�� �ǹ� ���� ���� ��ҵ��� ��踦 ��Ÿ����.
	int i = (lowIndex - 1);
	
	// �迭�� ��ȸ�ϸ鼭 �ǹ����� ���� ��ҵ��� �������� �̵�
	for (int j = lowIndex;  j <= highIndex;  j++) {
		// ���� ��Ұ� �ǹ����� ������
		if (datas[j] < pivot) {
			// �ǹ����� ���� ���� ��踦 1 ����
			i++;
			// i��° ����� ���� j��°(pivot���� ����)��Ҹ� ���� �¹ٲ۴�.
			// i��° ����� ���� pivot���� ũ�ų� �������� �߿����� �ʴ�.
			swap(&datas[i], &datas[j]);
		}
	}
	// �ǹ����� ���� ������ i��° �ε������� ��ġ�Ǿ� ���� ���̴�.
	// i+1��° ��� ��ġ�� pivot�� ���� ���� �ȴ�(�±�ȯ)
	swap(&datas[i+1], &datas[pivotIndex]);

	return (i + 1);
}

// ���޹��� �� ������ ����� ���� �¹ٲٴ� �Լ�
void swap(int*num1, int* num2) {
	// num1�� ����� ���� �ӽ� ������ ��´�.
	int temp = *num1;
	// num1�� ���� num2�� ����� ������ ������.
	*num1 = *num2;
	// num2�� ���� temp�� ��� ������ �����.
	*num2 = temp;
}

// 08/31(��)
// ��������




void displayArray(int datas[], int start, int end) {
	// �Լ� ���ο����� �迭�� ���̸� ������ �� ���� ������
	// �ܺο��� �� ���̸� �޾ƿ;� �Ѵ�.
	//int len = sizeof(datas) / sizeof(int);
	//printf("�Լ� ���ο��� ���� ���: %d\n", len);
	if (start < 0) start = 0;
	for (int i = start; i < end; i++) {
		printf("%d ", datas[i]);
	}
	printf("\n");
}

int main() {
	int datas[] = { 7, 4, 1, 2, 8, 9, 5, 3, 6 };
	int length = sizeof(datas) / sizeof(int);
	printf("���� ��: \n");
	displayArray(datas, 0, length);
	printf("\n���� ��: \n");
	quickSort(datas, 0, length-1);
	displayArray(datas, 0, length);

	return 0;
}