#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <math.h>

using namespace std;

int n, m;

void markSupersets(vector<bool> & belongs, int mask) {
	belongs[mask] = false;
	for (int i = 0; i < n; ++i)
		if ((mask & (1 << i)) == 0 && belongs[mask | (1 << i)])
			markSupersets(belongs, mask | (1 << i));
}

int main() {
	freopen("cycles.in", "r", stdin);
	freopen("cycles.out", "w", stdout);

	// Input
	cin >> n >> m;

	vector<int> w(n);
	for (int i = 0; i < n; ++i)
		cin >> w[i];

	vector<int> masks(m, 0);
	vector<bool> belongs(1 << n, true); // true if the set is independent
	int count, x;
	for (int i = 0; i < m; ++i) {
		cin >> count;
		for (int j = 0; j < count; ++j) {
			cin >> x;
			masks[i] |= (1 << (x - 1));
		}

		markSupersets(belongs, masks[i]);
	}

	// Calculation
	int maxSum = 0;
	int maxSize = 0;
	int curSum, curSize;
	for (int mask = 1; mask < (1 << n); ++mask) {
		if (belongs[mask]) {
			curSum = 0;
			curSize = 0;
			for (int i = 0; i < n; ++i)
				if (mask & (1 << i)) {
					curSum += w[i];
					++curSize;
				}

			if (maxSize == curSize) maxSum = max(maxSum, curSum);
			else if (curSize > maxSize) {
				maxSize = curSize;
				maxSum = curSum;
			}

		}
	}

	// Output
	cout << maxSum << endl;
	return 0;
}