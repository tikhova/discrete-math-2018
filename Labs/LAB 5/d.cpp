#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstdio>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

const int MOD = 1000000007;

struct node {
	bool terminal = false;
	map<int, int> linked;
};

vector<node *> state;

long long ** multiply(long long ** a, long long ** b, int n) {
	long long ** m = new long long *[n];
	for (int i = 0; i < n; ++i) {
		m[i] = new long long[n];
		for (int j = 0; j < n; ++j) {
			m[i][j] = 0;
		}
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			for (int k = 0; k < n; ++k) {
				m[i][j] = (m[i][j] + a[i][k] * b[k][j]) % MOD;
			}
		}
	}

	return m;
}

long long ** binpow(long long ** a, int n, int k) {
	long long ** res = new long long *[n];
	for (int i = 0; i < n; ++i) {
		res[i] = new long long[n];
		for (int j = 0; j < n; ++j) {
			res[i][j] = 0;
		}
		res[i][i] = 1;
	}
	while (k) {
		if (k & 1) {
			res = multiply(res, a, n);
		}
		a = multiply(a, a, n);
		k >>= 1;
	}
	return res;
}

int main() {
	freopen("problem4.in", "r", stdin);
	freopen("problem4.out", "w", stdout);

	int n, m, k, l, x, y;
	char c;

	scanf("%d %d %d %d\n", &n, &m, &k, &l);

	long long ** matrix = new long long *[n];
	for (int i = 0; i < n; ++i) {
		state.push_back(new node);
		matrix[i] = new long long[n];
		for (int j = 0; j < n; ++j) {
			matrix[i][j] = 0;
		}
	}

	for (int i = 0; i < k; ++i) {
		scanf("%d", &x);
		state.at(x - 1)->terminal = true;
	}

	for (int i = 0; i < m; ++i) {
		scanf("%d %d %c\n", &x, &y, &c);
		matrix[x - 1][y - 1]++;
	}

	long long ** answer = binpow(matrix, n, l);

	long long cnt = 0;
	for (int i = 0; i < n; ++i) {
		if (state.at(i)->terminal) {
			cnt += answer[0][i];
			cnt %= MOD;
		}
	}
	printf("%lld", cnt);
	return 0;
}