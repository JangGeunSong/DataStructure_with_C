#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	struct Node *left;
	struct Node *right;
	int elem;
}node;

node *mkInternalNode(int n) {
	node *p;
	p = (node *)malloc(sizeof(node));
	p->elem = n;
	p->left = NULL;
	p->right = NULL;
}

node *searchNode(node *root, int n) {
	node *p = root, *m, *q;
	if (p == NULL) {
		return NULL;
	}
	if (p->elem == n) {
		return p;
	}
	else {
		m = searchNode(p->left, n);
		q = searchNode(p->right, n);
		if (m != NULL && m->elem == n) {
			return m;
		}
		if (q != NULL && q->elem == n) {
			return q;
		}
		if (q == NULL && m == NULL) {
			return m;
		}
	}
}

node *mkTree(node *root, int num) {
	int tree = 0, l = 0, r = 0, cnt = 0;
	node *search;
	while (cnt != num) {
		scanf("%d %d %d", &tree, &l, &r);
		getchar();
		if (cnt == 0) {
			root->elem = tree;
			if (l == 0) {
				root->left = NULL;
			}
			else {
				root->left = mkInternalNode(l);
			}
			if (r == 0) {
				root->right = NULL;
			}
			else {
				root->right = mkInternalNode(r);
			}
			cnt++;
		}
		else {
			search = searchNode(root, tree);
			search->left = mkInternalNode(l);
			search->right = mkInternalNode(r);
			cnt++;
		}
	}
	return root;
}

void findTreeElem(node *root, char *cmd) {
	node *p = root;
	int i = 0;
	printf(" %d", p->elem);
	for (i = 0; i < strlen(cmd); i++) {
		if (cmd[i] == 'L') {
			p = p->left;
			printf(" %d", p->elem);
		}
		if (cmd[i] == 'R') {
			p = p->right;
			printf(" %d", p->elem);
		}
	}
	printf("\n");
	return;
}

int main() {
	node *root;
	int i = 0, j = 0, num = 0, search_num = 0;
	char cmd[100];
	root = (node *)malloc(sizeof(node));
	scanf("%d", &num);
	getchar();
	root = mkTree(root, num);
	scanf("%d", &search_num);
	getchar();
	for (i = 0; i < search_num; i++) {
		gets(cmd);
		findTreeElem(root, cmd);
	}
	return 0;
}
