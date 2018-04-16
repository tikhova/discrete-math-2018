#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <string>
using namespace std;

int compare(const void * x1, const void * x2) {
	return (*(int*)x1 - *(int*)x2); 
}

int main() {
	freopen("huffman.in", "r", stdin);
	freopen("huffman.out", "w", stdout);
	int n;
	long long ans = 0;
	string s;
	scanf("%i", &n);
	int * a = new int[n];
	for (int i = 0; i < n; i++) {
		scanf("%i", &a[i]);
	}
	qsort(vector, n, sizeof(int), compare);
	ans += (n - 1) * a[0];
	for (int i = 1; i < n; i++) {
		ans += (n - i) * a[i];
	}
	printf("%lld", ans);
	return 0;
}