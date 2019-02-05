#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Vertex {
	int vertexNum;
	struct Vertex *next;
	struct AdjacencyList *node;
}V;

typedef struct Edge {
	int weight;
	struct Vertex *end1;
	struct Vertex *end2;
	struct Edge *next;
}E;

typedef struct AdjacencyList {
	struct Edge *edge;
	struct AdjacencyList *next;
}A;

V *opposite(V *ver, E *edge) {
	if (edge->end1 == ver) {
		return edge->end2;
	}
	else if (edge->end2 == ver) {
		return edge->end1;
	}
}

void listSort(A **root, A *tar, V *ver) {
	A *trav = *root;
	int nVer = 0, nOppo = 0;
	while (trav->next != NULL) {
		nOppo = opposite(ver, (trav->next)->edge)->vertexNum;
		nVer = opposite(ver, tar->edge)->vertexNum;
		if (nOppo <= nVer) {
			trav = trav->next;
		}
		else {
			break;
		}
	}
	tar->next = trav->next;
	trav->next = tar;
	return;
}

V *addVertex(int num) {
	V *node = (V *)malloc(sizeof(V));
	node->vertexNum = num;
	node->next = NULL;
	node->node = (A *)malloc(sizeof(A));
	node->node->edge = NULL;
	node->node->next = NULL;
	return node;
}

A *addAdjacencyList(E *edge) {
	A *node = (A *)malloc(sizeof(A));
	node->edge = edge;
	node->next = NULL;
	return node;
}

void removeAdjacencyNode(A **root, E *edge) {
	A *trav = (*root)->next;
	A *savePrev = NULL;
	while (trav->next != NULL) {
		if (trav->edge == edge) {
			break;
		}
		else {
			savePrev = trav;
			trav = trav->next;
		}
	}
	if (savePrev == NULL) {
		(*root)->next = trav->next;
		free(trav);
	}
	else {
		savePrev->next = trav->next;
		free(trav);
	}
	return;
}

E *addEdge(int weight, V *end1, V *end2) {
	E *node = (E *)malloc(sizeof(E));
	node->weight = weight;
	node->end1 = end1;
	node->end2 = end2;
	node->next = NULL;
	return node;
}

void removeEdge(E **root, E *edge) {
	E *trav = *root;
	E *savePrev = NULL;
	while (trav->next != NULL) {
		if (trav == edge) {
			break;
		}
		else {
			savePrev = trav;
			trav = trav->next;
		}
	}
	if (savePrev == NULL) {
		free(trav);
		*root = NULL;
	}
	else {
		savePrev->next = trav->next;
		free(trav);
	}
	return;
}

void linkToVertex(E *root, V *ver1, V *ver2, int weight) {
	E *r = root;
	A *list1 = ver1->node, *list2 = ver2->node;
	A *target1 = NULL, *target2 = NULL;
	while (r->next != NULL) {
		r = r->next;
	}
	r->next = addEdge(weight, ver1, ver2);
	if (ver1 == ver2) {
		target1 = addAdjacencyList(r->next);
		listSort(&list1, target1, ver1);
	}
	else {
		target1 = addAdjacencyList(r->next);
		listSort(&list1, target1, ver1);

		target2 = addAdjacencyList(r->next);
		listSort(&list2, target2, ver2);
	}
}

void removeVertexLink(E **root, E *edge, V *ver1, V *ver2) {
	if (ver1 == ver2) {
		removeAdjacencyNode(&(ver1->node), edge);
		removeEdge(root, edge);
	}
	else {
		removeAdjacencyNode(&(ver1->node), edge);
		removeAdjacencyNode(&(ver2->node), edge);
		removeEdge(root, edge);
	}
	return;
}

void travelAdjacenctVertex(A **root, V *ver) {
	A *trav = (*root);
	int Vnum = 0;
	int Eweight = 0;
	while (trav->next != NULL) {
		Vnum = opposite(ver, (trav->next)->edge)->vertexNum;
		Eweight = ((trav->next)->edge)->weight;
		printf(" %d %d", Vnum, Eweight);
		trav = trav->next;
	}
	printf("\n");
	return;
}

void changeWeight(E **root, V *ver1, V *ver2, int weight) {
	A *list = (ver1->node)->next;
	V *point = NULL;
	E *trav = *root;
	if (list == NULL) {
		if (weight == 0) {
			return;
		}
		else {
			linkToVertex(trav, ver1, ver2, weight);
			return;
		}
	}
	while (1) {
		if (list->next == NULL) {
			break;
		}
		point = opposite(ver1, list->edge);
		if (point == ver2) {
			break;
		}
		else {
			list = list->next;
		}
	}
	if (opposite(ver1, list->edge) != ver2) {
		if (weight == 0) {
			return;
		}
		else {
			linkToVertex(trav, ver1, ver2, weight);
		}
	}
	else {
		(list->edge)->weight = weight;
		if ((list->edge)->weight == 0) {
			removeVertexLink(root, (list->edge), ver1, ver2);
		}
	}
	return;
}

V *initVertex(V *root) {
	V *trav = NULL;
	root->next = addVertex(1);
	trav = root->next;
	trav->next = addVertex(2);
	trav = trav->next;
	trav->next = addVertex(3);
	trav = trav->next;
	trav->next = addVertex(4);
	trav = trav->next;
	trav->next = addVertex(5);
	trav = trav->next;
	trav->next = addVertex(6);
	return;
}

E *initEdge(V **v, E *root) {
	V *ver1 = (*v)->next, *ver2 = NULL, *ver3 = NULL;
	V *ver4 = NULL, *ver5 = NULL, *ver6 = NULL;
	E *trav = root;
	trav->next = NULL;
	ver2 = ver1->next;
	ver3 = ver2->next;
	ver4 = ver3->next;
	ver5 = ver4->next;
	ver6 = ver5->next;
	linkToVertex(trav, ver1, ver2, 1);
	linkToVertex(trav, ver1, ver3, 1);
	linkToVertex(trav, ver1, ver4, 1);
	linkToVertex(trav, ver1, ver6, 2);
	linkToVertex(trav, ver2, ver3, 1);
	linkToVertex(trav, ver3, ver5, 4);
	linkToVertex(trav, ver5, ver5, 4);
	linkToVertex(trav, ver5, ver6, 3);
	return trav;
}

V *findVertex(V **root, int num) {
	V *p = *root;
	while (1) {
		if (p == NULL) {
			return NULL;
		}
		if (p->vertexNum == num) {
			return p;
		}
		else {
			p = p->next;
		}
	}
}

int main() {
	V *vertex = NULL, *target1 = NULL, *target2 = NULL;
	E *edge = NULL;
	char cmd = 0;
	int a = 0, b = 0, weight = 0;
	vertex = (V *)malloc(sizeof(V));
	edge = (E *)malloc(sizeof(E));
	initVertex(vertex);
	edge = initEdge(&vertex, edge);
	while (1) {
		scanf("%c", &cmd);
		getchar();
		switch (cmd) {
		case 'a':
			scanf("%d", &a);
			getchar();
			if (a < 1) {
				printf("-1\n");
				break;
			}
			if (a > 6) {
				printf("-1\n");
				break;
			}
			target1 = findVertex(&vertex, a);
			travelAdjacenctVertex(&(target1->node), target1);
			break;
		case 'm':
			scanf("%d %d %d", &a, &b, &weight);
			getchar();
			if (a < 1) {
				printf("-1\n");
				break;
			}
			if (a > 6) {
				printf("-1\n");
				break;
			}
			if (b < 1) {
				printf("-1\n");
				break;
			}
			if (b > 6) {
				printf("-1\n");
				break;
			}
			target1 = findVertex(&vertex, a);
			target2 = findVertex(&vertex, b);
			changeWeight(&edge, target1, target2, weight);
			break;
		case 'q':
			return;
		}
	}
	return 0;
}
