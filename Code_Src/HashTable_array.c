#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NoSuchKey = -1;

typedef struct HashTable {
	struct HashTable *next;
	int key;
}ht;

void insertItem(ht *table, int M, int k) {
	int v = k % M;
	ht *newNode = NULL;
	newNode = (ht *)malloc(sizeof(ht));
	newNode->key = k;
	newNode->next = (table + v)->next;
	(table + v)->next = newNode;
	return;
}

int findElement(ht *table, int M, int k) {
	int e = 0;
	int v = k % M;
	int key = 0;
	ht *searchNode = NULL;
	searchNode = (table + v);
	while (searchNode != NULL) {
		if (searchNode->key == k) {
			key = k;
			break;
		}
		searchNode = searchNode->next;
		e++;
	}
	if (key == k) {
		return e;
	}
	else {
		return 0;
	}
}

int removeElement(ht *table, int M, int k) {
	int e = 0;
	int v = k % M;
	int key = 0;
	ht *searchNode = NULL;
	ht *saveNode = NULL;
	searchNode = ((table + v)->next);
	saveNode = (table + v);
	if (saveNode->key == k) {
		key = k;
		(table + v)->next = searchNode;
		free(saveNode);
		return e;
	}
	while (searchNode != NULL) {
		if (searchNode->key == k) {
			key = k;
			e++;
			break;
		}
		saveNode = saveNode->next;
		searchNode = searchNode->next;
		e++;
	}
	if (key == 0) {
		return 0;
	}
	saveNode->next = searchNode->next;
	free(searchNode);
	if (key == k) {
		return e;
	}
}

void traverse(ht *table, int M) {
	int i = 0;
	ht *trableNode = NULL;
	for (i = 0; i < M; i++) {
		trableNode = (table + i)->next;
		while (trableNode != NULL) {
			printf(" %d", trableNode->key);
			trableNode = trableNode->next;
		}
	}
	printf("\n");
}

ht *initBucketArray(ht *table, int n) {
	int i = 0;
	table = (ht *)malloc(sizeof(ht) * n);
	for (i = 0; i < n; i++) {
		(table + i)->next = NULL;
	}
	return table;
}

int main() {
	ht *table = NULL;
	int n = 0, key = 0;
	char cmd = 0;
	scanf("%d", &n);
	getchar();
	table = initBucketArray(table, n);
	while (1) {
		scanf("%c", &cmd);
		getchar();
		switch (cmd) {
		case 'i':
			scanf("%d", &key);
			getchar();
			insertItem(table, n, key);
			break;
		case 's':
			scanf("%d", &key);
			getchar();
			printf("%d\n", findElement(table, n, key));
			break;
		case 'd':
			scanf("%d", &key);
			getchar();
			printf("%d\n", removeElement(table, n, key));
			break;
		case 'p':
			traverse(table, n);
			break;
		case 'e':
			free(table);
			return 0;
		}
	}
	return 0;
}