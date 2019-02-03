#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int H[100];
//힙을 저장할 배열 포인터
int n;
//힙의 크기(현재 총 키 개수)

void downHeap(int index) {
	int switch_index = index;
	int bigger_index = 0;
	int tmp = 0;
	while (1) {
		if (H[switch_index * 2] == 0 && H[(switch_index * 2) + 1] == 0) {
			return;
		}
		if ((H[switch_index * 2] <= H[(switch_index * 2) + 1]) && (H[(switch_index * 2) + 1] != 0)) {
			bigger_index = (switch_index * 2) + 1;
		}
		else {
			bigger_index = switch_index * 2;
		}
		if(H[switch_index] < H[bigger_index]){
			tmp = H[switch_index];
			H[switch_index] = H[bigger_index];
			H[bigger_index] = tmp;
			switch_index = bigger_index;
		}
		else {
			switch_index = switch_index * 2;
		}
	}
	return;
}

void rBuildHeap(int index) {
	if (index > n) {
		return;
	}
	rBuildHeap(2 * index);
	rBuildHeap((2 * index) + 1);
	downHeap(index);
	return;
}

void printHeap() {
	int i = 0;
	for (i = 1; i <= n; i++) {
		printf(" %d", H[i]);
	}
	printf("\n");
}

void main() {
	int key, i = 0;
	scanf("%d", &n);
	getchar();
	for (i = 1; i <= n; i++) {
		scanf("%d", &key);
		H[i] = key;
	}
	rBuildHeap(1);
	printHeap();
}
