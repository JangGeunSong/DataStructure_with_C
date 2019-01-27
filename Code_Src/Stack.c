#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void push(char *p, char k, int *top, int n) {
	int i = 0;
	if (*top >= n) {
		printf("Stack FULL\n");
	}
	else {
		for (i = *top - 1 ;i > -1;i--) {
			*(p + i + 1) = *(p + i);
		}
		*p = k;
		(*top)++;
	}
	return;
}
void pop(char *p, int *top, int n) {
	char t = 0;
	int i = 0;
	if ((*top) == 0) {
		printf("Stack Empty\n");
		return;
	}
	else {
		for (i = 0;i < *top - 1;i++) {
			*(p + i) = *(p + i + 1);
		}
		(*top)--;
		return;
	}
}
void peek(char *p, int *top, int n) {
	if ((*top) == 0) {
		printf("Stack Empty\n");
	}
	else {
		printf("%c\n", *p);
	}
	return;
}
void duplicate(char *p, int *top, int n) {
	char ch = 0;
	int i = 0;
	if ((*top) == 0) {
		printf("Stack Empty\n");
	}
	if ((*top) >= n) {
		printf("Stack FULL\n");
	}
	ch = *p;
	pop(p, top, n);
	push(p, ch, top, n);
	push(p, ch, top, n);
	return;
}
void upRotate(char *p, int r, int *top, int n) {
	char t = 0;
	int i = 0;
	if ((*top) == 0) {
		printf("Stack Empty\n");
		return;
	}
	if (r > (*top)) {
		return;
	}
	t = *p;
	for (i = 0;i < r - 1;i++) {
		*(p + i) = *(p + i + 1);
	}
	*(p + i) = t;
	return;
}
void downRotate(char *p, int r, int *top, int n) {
	char t = 0;
	int i = 0;
	if ((*top) == 0) {
		printf("Stack Empty\n");
		return;
	}
	if (r > (*top)) {
		return;
	}
	t = *(p + r - 1);
	for (i = r - 1;i > 0;i--) {
		*(p + i) = *(p + i - 1);
	}
	*(p + i) = t;
	return;
}
void print(char *p, int *top, int n) {
	int i = 0, cnt = 0;
	for (i = 0;i < *top;i++) {
		printf("%c", *(p + i));
		cnt++;
	}
	if (cnt != 0) {
		printf("\n");
	}
	return;
}
int main() {
	int num = 0, i = 0, r = 0;
	int top = 0, n = 0;
	char *p, cmd[20] = { 0 }, t = 0;
	scanf("%d", &n);
	scanf("%d", &num);
	getchar();
	p = (char *)malloc(sizeof(char)*n);
	for (i = 0;i < n;i++) {
		p[i] = 0;
	}
	for (i = 0;i < num;i++) {
		scanf("%s", cmd);
		getchar();
		if (strcmp(cmd, "POP") == 0) {
			pop(p, &top, n);
		}
		else if (strcmp(cmd, "PUSH") == 0) {
			scanf("%c", &t);
			getchar();
			push(p, t, &top, n);
		}
		else if (strcmp(cmd, "PEEK") == 0) {
			peek(p, &top, n);
		}
		else if (strcmp(cmd, "DUP") == 0) {
			duplicate(p, &top, n);
		}
		else if (strcmp(cmd, "UpR") == 0) {
			scanf("%d", &r);
			getchar();
			upRotate(p, r, &top, n);
		}
		else if (strcmp(cmd, "DownR") == 0) {
			scanf("%d", &r);
			downRotate(p, r, &top, n);
		}
		else if (strcmp(cmd, "PRINT") == 0) {
			print(p, &top, n);
		}
	}
	free(p);
	return 0;
}
