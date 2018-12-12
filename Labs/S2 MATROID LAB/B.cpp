#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <math.h>

using namespace std;
vector<int> dsu;

struct edge {
	int first;
	int second;
	long long value;
	int index;

	friend bool operator<(edge const & x, edge const & y) {
		return x.value < y.value;
	}
};

int get_dsu(int x) {
	if (dsu[x] != x)
		dsu[x] = get_dsu(dsu[x]);
	return dsu[x];
}

int main() {
	freopen("destroy.in", "r", stdin);
	freopen("destroy.out", "w", stdout);

	// Input
	int n, m;
	long long s;
	cin >> n >> m >> s;

	vector<pair<long long, int>> deletable_edges;
	vector<edge> edges;
	vector<int> size(n, 0);
	dsu.resize(n);
	int a, b;
	long long c;

	for (int i = 0; i < m; ++i) {
		cin >> a >> b >> c;
		edges.push_back({ a - 1, b - 1, c, i });
	}
	for (int i = 0; i < n; dsu[i] = i, ++i);
	sort(edges.begin(), edges.end());

	// Find deletable edges
	for (int i = m - 1; i >= 0; --i) {
		if (get_dsu(edges[i].first) != get_dsu(edges[i].second)) {
			a = dsu[edges[i].first];
			b = dsu[edges[i].second];
			if (size[a] > size[b]) swap(a, b);
			if (size[a] == size[b]) ++size[b];
			dsu[a] = b;
		}
		else {
			deletable_edges.push_back({ edges[i].value,  edges[i].index });
		}
	}

	// Greedy choice
	sort(deletable_edges.begin(), deletable_edges.end());
	long long sum = 0;
	int index;
	for (index = 0; index < deletable_edges.size(); ++index) {
		sum += deletable_edges[index].first;
		if (sum > s) break;
	}

	// Output
	cout << index << endl;
	for (int i = 0; i < index; ++i) {
		cout << deletable_edges[i].second + 1 << " ";
	}
	return 0;
}