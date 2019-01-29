#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isEmpty(int *Queue, int *n, int *front, int *rear) {
	if (*rear == *front) {
		return 1;
	}
	else {
		return 0;
	}
}

int isFull(int *Queue, int *n, int *front, int *rear) {
	if (((*rear + 1) % *n) == *front) {
		return 1;
	}
	else {
		return 0;
	}
}

int enQueue(int *Queue, int *n, int *front, int *rear, int e) {
	int i = 0;
	if (isFull(Queue, n, front, rear)) {
		printf("overflow ");
		for (i = 0; i < *n; i++) {
			printf("%d ", Queue[i]);
		}
		printf("\n");
		return 1;
	}
	*rear = (*rear + 1) % *n;
	Queue[*rear] = e;
	return 0;
}

int deQueue(int *Queue, int *n, int *front, int *rear) {
	int e = 0;
	if (isEmpty(Queue, n, front, rear)) {
		printf("underflow\n");
		return 1;
	}
	e = Queue[*front + 1];
	Queue[*front + 1] = 0;
	*front = (*front + 1) % *n;
	return 0;
}

void print_Queue(int *Queue, int *q) {
	int i = 0;
	for (i = 0; i < *q; i++) {
		printf(" %d", Queue[i]);
	}
	printf("\n");
}

int main() {
	int front = 0, rear = 0, *Queue, q = 0, n = 0, i = 0, e = 0;
	char cmd = 0;
	scanf("%d", &q);
	getchar();
	Queue = NULL;
	Queue = (int *)malloc(sizeof(int) * q);
	scanf("%d", &n);
	getchar();
	for (i = 0; i < q; i++) {
		Queue[i] = 0;
	}
	for (i = 0; i < n; i++) {
		scanf("%c", &cmd);
		getchar();
		if (cmd == 'I') {
			scanf("%d", &e);
			getchar();
			if (enQueue(Queue, &q, &front, &rear, e)) {
				free(Queue);
				return 0;
			}
		}
		if (cmd == 'D') {
			if (deQueue(Queue, &q, &front, &rear)) {
				free(Queue);
				return 0;
			}
		}
		if(cmd == 'P'){
			print_Queue(Queue, &q);
		}
	}
	free(Queue);
	return 0;
}
