#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n = 0;

int rFindElement(int *L,int k, int l, int r) {
	int mid = 0;
	int cmp1 = 0, cmp2 = 0;
	if (l > r) {
		if (L[l] == k) {
			return l;
		}
		if (L[l] > k) {
			return -1;
		}
		if (L[l] < k) {
			return l;
		}
	}
	mid = (l + r) / 2;
	cmp1 = rFindElement(L, k, l, mid - 1);
	cmp2 = rFindElement(L, k, mid + 1, r);
	if (cmp1 == n) {
		return cmp2;
	}
	if (cmp2 == n) {
		return cmp1;
	}
	if (cmp1 == -1 || cmp2 == -1) {
		if (cmp1 == -1 && cmp2 == -1) {
			return -1;
		}
		else if (cmp1 != -1 && cmp2 == -1) {
			return cmp1;
		}
		else if (cmp1 == -1 && cmp2 != -1) {
			return cmp2;
		}
	}
	if (L[cmp1] == k) {
		return cmp1;
	}
	if (L[cmp2] == k) {
		return cmp2;
	}
	if (L[cmp1] < k && L[cmp2] < k) {
		if (cmp1 > cmp2) {
			return cmp1;
		}
		if (cmp1 < cmp2) {
			return cmp2;
		}
	}
	if (L[cmp1] > k && L[cmp2] < k) {
		return cmp2;
	}
	if (L[cmp1] < k && L[cmp2] > k) {
		return cmp1;
	}
}

int findElement(int *L, int k, int n) {
	return rFindElement(L, k, 0, n - 1);
}

int main() {
	int i = 0, e = 0, k = 0;
	int *L;
	scanf("%d %d", &n, &k);
	getchar();
	L = (int *)malloc(sizeof(int) * n);
	for (i = 0; i < n; i++) {
		scanf("%d", &e);
		L[i] = e;
	}
	e = findElement(L, k, n);
	printf(" %d\n", e);
	return 0;
}