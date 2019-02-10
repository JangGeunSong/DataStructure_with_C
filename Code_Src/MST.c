#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INFINITE 2147483647
//���Ѵ븦 �����ϱ� ���� ������ ����
typedef struct AdjacencyList {
	struct Edge *edge;
	struct AdjacencyList *next;
}A;
//��������Ʈ�� ������ �����̹Ƿ� �̿� ���� �ڷᱸ�� ����
typedef struct Vertex {
	int name;
	struct Vertex *next;
	struct Edge *parent;
	struct AdjacencyList *L;
	int ADL_length;
	int dist;
}V;
//������ ���� �ڷᱸ�� ADL_length�� ���� ����Ʈ�� �����̸� dist�� �� ������ ������ �ִܰŸ��̴�.
typedef struct Edge {
	struct Vertex *ver1, *ver2;
	int weight;
	struct Edge *next;
}E;
//Edge�� ���� �ڷᱸ�� ����
typedef struct Graph {
	struct Vertex *vertex;
	struct Edge *edge;
	int nVer, nEdge;
}G;
//�׷����� ���� �ڷᱸ�� ����
typedef struct Heap {
	int key;
	struct Vertex *elem;
}H;
//�ּ����� ������ �ϹǷ� �̿����� �ڷᱸ�� ����
H Q[101];
int nHeap;
G graph;
//�ּ����� ���� ������ ����
V *opposite(E *edge, V *ver) {
	if (edge->ver1 == ver) {
		return edge->ver2;
	}
	else if (edge->ver2 == ver) {
		return edge->ver1;
	}
}
//������ �ݴ��� ������ �����ϴ� �Լ�
void mkVertex(int num) {
	V *trav = graph.vertex;
	if (graph.nVer == 0) {
		graph.vertex = (V *)malloc(sizeof(V));
		graph.vertex->name = num;
		graph.vertex->next = NULL;
		graph.vertex->parent = NULL;
		graph.vertex->dist = INFINITE;
		graph.vertex->ADL_length = 0;
		graph.nVer++;
	}
	else {
		while (trav->next != NULL) {
			trav = trav->next;
		}
		trav->next = (V *)malloc(sizeof(V));
		trav->next->name = num;
		trav->next->next = NULL;
		trav->next->parent = NULL;
		trav->next->dist = INFINITE;
		trav->next->ADL_length = 0;
		graph.nVer++;
	}
	return;
}
//������ ����� �Լ� �׷����� ������ �ƿ� �������� �ڷᱸ�� ��ü�� ������ְ� ���Ŀ��� �� �ڿ� ���ϰ��̹Ƿ� �̿� ���� �б⸦ ������ ����
void mkEdge(int weight, V *ver1, V *ver2) {
	E *trav = graph.edge;
	if (graph.nEdge == 0) {
		graph.edge = (E *)malloc(sizeof(E));
		graph.edge->next = NULL;
		graph.edge->ver1 = ver1;
		graph.edge->ver2 = ver2;
		graph.edge->weight = weight;
		graph.nEdge++;
	}
	else {
		while (trav->next != NULL) {
			trav = trav->next;
		}
		trav->next = (E *)malloc(sizeof(E));
		trav->next->ver1 = ver1;
		trav->next->ver2 = ver2;
		trav->next->weight = weight;
		trav->next->next = NULL;
		graph.nEdge++;
	}
	return;
}
//������ ����� �Լ� �������� ������ ����� �Լ��� ���������� ���� ����
void upHeap(int index) {
	H tmp;
	int switch_index = 0;
	if (index == 1) {
		return;
	}
	switch_index = index;
	while (1) {
		if (switch_index == 1) {
			return;
		}
		if (Q[switch_index / 2].key > Q[switch_index].key) {
			tmp = Q[switch_index / 2];
			Q[switch_index / 2] = Q[switch_index];
			Q[switch_index] = tmp;
		}
		switch_index = switch_index / 2;
	}
	return;
}
//��ȭ�� �ϱ����� �Լ� upHeap
void downHeap(int index) {
	int switch_index = index;
	int smaller_index = 1;
	H tmp;
	while (1) {
		if ((switch_index * 2) > nHeap && (switch_index * 2 + 1) > nHeap) {
			return;
		}
		if ((switch_index * 2 + 1) <= nHeap) {
			if (Q[switch_index * 2].key > Q[switch_index * 2 + 1].key) {
				smaller_index = switch_index * 2 + 1;
			}
			else if (Q[switch_index * 2].key < Q[switch_index * 2 + 1].key) {
				smaller_index = switch_index * 2;
			}
		}
		else if ((switch_index * 2 + 1) > nHeap) {
			smaller_index = switch_index * 2;
		}
		if (Q[switch_index].key > Q[smaller_index].key) {
			tmp = Q[switch_index];
			Q[switch_index] = Q[smaller_index];
			Q[smaller_index] = tmp;
			switch_index = smaller_index;
		}
		else {
			switch_index = switch_index * 2;
		}
	}
	return;
}
//��ȭ�� �ϱ����� �Լ� downHeap
void buildHeap(V *ver) {
	nHeap++;
	Q[nHeap].elem = ver;
	Q[nHeap].key = ver->dist;
	upHeap(nHeap);
}
//���� ��带 �����ϴ� �Լ�
V *removeMin() {
	V *ver = NULL;
	H tmp;
	ver = Q[1].elem;
	tmp = Q[nHeap];
	Q[nHeap] = Q[1];
	Q[1] = tmp;
	nHeap--;
	downHeap(1);
	return ver;
}
//���� �ּҰ� �� ��Ʈ�� ��ȯ�ϰ� �ٽ� ����ȭ �ϴ� �Լ�
void replaceKey(V *ver, int k) {
	int i = 1;
	for (i = 1; i <= nHeap; i++) {
		if (Q[i].elem == ver) {
			if (Q[i].key < k) {
				Q[i].key = k;
				downHeap(i);
			}
			else if (Q[i].key > k) {
				Q[i].key = k;
				upHeap(i);
			}
			else {
				Q[i].key = k;
			}
			return;
		}
	}
}
//�Ϻ� Ű�� ����Ǿ�����, �̸� �����ϱ� ���� �Լ�
int isElement(V *ver) {
	int i = 0;
	for (i = 1; i <= nHeap; i++) {
		if (Q[i].elem == ver) {
			return 1;
		}
	}
	return 0;
}
//���� ������ ���� ���ԵǾ� �ִ°��� �Ǻ��ϴ� �Լ�
void addAdjacencyList(V *ver, E *edge) {
	A *trav = ver->L;
	if (ver->ADL_length == 0) {
		ver->L = (A *)malloc(sizeof(A));
		ver->L->edge = edge;
		ver->L->next = NULL;
		ver->ADL_length++;
	}
	else {
		while (trav->next != NULL) {
			trav = trav->next;
		}
		trav->next = (A *)malloc(sizeof(A));
		trav->next->edge = edge;
		trav->next->next = NULL;
		ver->ADL_length++;
	}
}
//���� ����Ʈ�� ����� �ռ�
void buildGraph(int n, int m) {
	E *edge = NULL;
	V *vertex = NULL, *target1 = NULL, *target2 = NULL;
	int i = 0, ver1 = 0, ver2 = 0, weight = 0;
	graph.nEdge = 0;
	graph.nVer = 0;
	if (n == 0 || m == 0) {
		printf("0\n");
		return;
	}
	for (i = 1; i <= n; i++) {
		mkVertex(i);
	}
	for (i = 0; i < m; i++) {
		vertex = graph.vertex;
		scanf("%d %d %d", &ver1, &ver2, &weight);
		getchar();
		while (vertex != NULL) {
			if (vertex->name == ver1) {
				target1 = vertex;
			}
			if (vertex->name == ver2) {
				target2 = vertex;
			}
			vertex = vertex->next;
		}
		mkEdge(weight, target1, target2);
		edge = graph.edge;
		for (i = 0; i < graph.nEdge - 1; i++) {
			edge = edge->next;
		}
		if (ver1 == ver2) {
			addAdjacencyList(target1, edge);
		}
		else {
			addAdjacencyList(target1, edge);
			addAdjacencyList(target2, edge);
		}
	}
	return;
}
//�ʱ� ���� ���Ǵ�� �׷����� ����� �Լ�
void Prim_JarnikMST() {
	V *trav = graph.vertex;
	V *s = NULL, *u = NULL, *z = NULL;
	A *adTrav = NULL;
	int totalWeight = 0;
	nHeap = 0;
	while (trav != NULL) {
		trav->dist = INFINITE;
		trav->parent = NULL;
		trav = trav->next;
	}
	s = graph.vertex;
	s->dist = 0;
	trav = graph.vertex;
	while (trav != NULL) {
		buildHeap(trav);
		trav = trav->next;
	}
	if (nHeap == 0) {
		return;
	}
	while (nHeap != 0) {
		u = removeMin();
		totalWeight = totalWeight + u->dist;
		printf(" %d", u->name);
		adTrav = u->L;
		while (adTrav != NULL) {
			z = opposite(adTrav->edge, u);
			if (isElement(z) && adTrav->edge->weight <= z->dist) {
				z->dist = adTrav->edge->weight;
				z->parent = adTrav->edge;
				replaceKey(z, z->dist);
			}
			adTrav = adTrav->next;
		}
	}
	printf("\n%d\n", totalWeight);
	return;
}
//Prim_Jarnik�˰����� ����� �ּ� ����Ʈ���� ����� �Լ�
int main() {
	int n = 0, m = 0;
	scanf("%d %d", &n, &m);
	getchar();
	if (n == 0 || m == 0) {
		printf("0\n");
		return 0;
	}
	buildGraph(n, m);
	Prim_JarnikMST();
	return 0;
}
//�����Լ�