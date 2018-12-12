#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <math.h>

using namespace std;
vector<bool> used;
vector<int> l;
vector<int> r;
vector<vector<int>> adj;

bool tryKuhn(int v) {
	if (used[v])  return false;
	used[v] = true;
	for (auto to: adj[v])
		if (l[to] == -1 || tryKuhn(l[to])) {
			l[to] = v;
			return true;
		}
	return false;
}

int main() {
	freopen("matching.in", "r", stdin);
	freopen("matching.out", "w", stdout);

	// Input
	int n;
	cin >> n;

	adj = vector<vector<int>>(n);
	vector<pair<int, int> > l_nodes;
	l = vector<int>(n, -1);
	r = vector<int>(n, -1);

	l_nodes.reserve(n);
	int val;
	for (int i = 0; i < n; ++i) {
		cin >> val;
		l_nodes.push_back({val, i});
	}
	sort(l_nodes.begin(), l_nodes.end(), [](pair<int, int> const & a, pair<int, int> const & b) {
		return a.first > b.first;
	});

	int count;
	for (int i = 0; i < n; ++i) {
		cin >> count;
		for (int j = 0; j < count; ++j) {
			cin >> val;
			adj[i].push_back(val - 1);
		}
	}

	// Kuhn
	for (auto v: l_nodes) {
		used.assign(n, false);
		tryKuhn(v.second);
	}

	for (int i = 0; i < n; ++i)
		if(l[i] != -1) r[l[i]] = i;

	// Output
	for (auto x : r)
		cout << x + 1 << " ";
	cout << endl;
	return 0;
}