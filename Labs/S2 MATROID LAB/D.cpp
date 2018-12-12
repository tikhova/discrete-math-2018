#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <math.h>

using namespace std;


int main() {
	freopen("cycles.in", "r", stdin);
	freopen("cycles.out", "w", stdout);
	
	// Input & check 1 axiom
	int n, m;
	cin >> n >> m;
	vector<vector<int>> s(m);
	vector<int> masks(m, 0);
	vector<bool> belongs((1 << n), false);
	int count, x;
	bool nontrivial = false;
	for (int i = 0; i < m; ++i) {
		cin >> count;
		if (count == 0) nontrivial = true;
		for (int j = 0; j < count; ++j) {
			cin >> x;
			--x;
			s[i].push_back(x);
			masks[i] |= (1 << x);
		}
		belongs[masks[i]] = true;
	}
	if (!nontrivial) {
		cout << "NO" << endl;
		return 0;
	}

	// Check 2 axiom
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; ++j)
			if ((masks[i] & (1 << j)) && !belongs[masks[i] ^ (1 << j)]) {
				cout << "NO" << endl;
				return 0;
			}
	}

	// Check 3 axiom
	for (int i = 0; i < m; i++) 
		for (int j = 0; j < m; j++)
			if (s[i].size() > s[j].size()) {
				int a = masks[i];
				int b = masks[j];
				for (int k = 0; k < n; k++)
					if ((a & (1 << k)) && (b & (1 << k))) 
						a ^= (1 << k);
				// now a = mask[i]\mask[b]

				bool isReplacable = false;
				for (int k = 0; k < n; k++)
					if ((a & (1 << k))  && belongs[b + (1 << k)]) {
						isReplacable = true;
						break;
					}			

				if (!isReplacable) {
					cout << "NO" << endl;
					return 0;
				}
			}
		
	cout << "YES" << endl;
	return 0;
}