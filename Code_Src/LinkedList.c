#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Node {
	char elem;
	struct Node *next;
	struct Node *prev;
};
struct Node *H;
struct Node *T;
int n=0;
void initList() {
	H = (struct Node *)malloc(sizeof(struct Node));
	T = (struct Node *)malloc(sizeof(struct Node));
	H->next = T;
	T->prev = H;
	n = 0;
	return;
}
struct Node *add(struct Node *p,int pos,char c) {
	struct Node *q;
	q = (struct Node *)malloc(sizeof(struct Node));
	int i = 0;
	for (i = 0;i < pos - 1;i++) {
		p = p->next;
	}
	q->elem = c;
	q->prev = p;
	q->next = p->next;
	(p->next)->prev = q;
	p->next = q;
	n = n + 1;
	return q;
}
char delete(struct Node *p, int pos) {
	int i = 0;
	char e = 0;
	for (i = 0;i < pos;i++) {
		p = p->next;
	}
	e = p->elem;
	(p->prev)->next = p->next;
	(p->next)->prev = p->prev;
	free(p);
	n = n - 1;
	return e;
}
void get(struct Node *p,int pos) {
	int i = 0;
	char e = 0;
	for (i = 0;i < pos;i++) {
		p = p->next;
	}
	printf("%c\n", p->elem);
	return;
}
void print(struct Node *p) {
	while (p != T) {
		p = p->next;
		printf("%c", p->elem);
	}
	printf("\n");
	return;
}
void main() {
	int i = 0, pos = 0, cnt = 0;
	char c = 0, com = 0;
	initList();
	scanf("%d", &cnt);
	getchar();
	for (i = 0;i < cnt;i++) {
		scanf("%c", &com);
		getchar();
		switch (com) {
		case 'A':
			scanf("%d %c", &pos, &c);
			getchar();
			if (pos > 0 && pos <= n + 1) {
				add(H, pos, c); break;
			}
			else {
				printf("invalid position\n"); break;
			}
		case 'D':
			scanf("%d", &pos);
			getchar();
			if (pos > 0 && pos <= n) {
				delete(H, pos); break;
			}
			else {
				printf("invalid position\n"); break;
			}
		case 'G':
			scanf("%d", &pos);
			getchar();
			if(pos > 0 && pos <= n){
				get(H, pos); break;
			}
			else {
				printf("invalid position\n"); break;
			}
		case 'P':
			print(H); break;
		}
	}
}
