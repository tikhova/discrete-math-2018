#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <iterator>
#include <math.h>

using namespace std;

int main() {
	freopen("schedule.in", "r", stdin);
	freopen("schedule.out", "w", stdout);

	int n;
	cin >> n;

	set<pair<int, int>> tasks;
	set<int> times;

	int time, price;
	for (int i = 0; i < n; ++i) {
		cin >> time >> price;
		tasks.insert({ price, time});
		times.insert(i + 1);
	}

	long long loss = 0;
	set<int>::iterator it;
	set<pair<int, int>>::iterator cur;
	while (!times.empty() && !tasks.empty()) {
		cur = --tasks.end();
		time = cur->second;
		it = times.lower_bound(time);
		if (it != times.begin() && *it != time)
			--it;
		if (*it <= time)
			times.erase(it);
		else
			loss += cur->first;
		tasks.erase(cur);
	}
	cout << loss;
	return 0;
}