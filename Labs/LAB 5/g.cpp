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
	bool good = false;
	bool checked = false;
	map<char, int> connection;
};

vector<node *> first;
vector<node *> second;
vector<pair<int, int>> queue;
set<pair<int, int>> visited;

void addLink(vector<node*> v, int x, int y, char c) {
	v.at(x)->connection.insert(pair<char, int>(c, y));
}

bool isGood(vector<node *> * v, int x) {
	if (!v->at(x)->checked) {
		v->at(x)->checked = true;
		for (map<char, int>::iterator it = v->at(x)->connection.begin();
			it != v->at(x)->connection.end(); ++it) {
			if (!v->at(it->second)->checked) {
				isGood(v, it->second);
			}
			if (v->at(it->second)->good) {
				v->at(x)->good = true;
				break;
			}
		}
	}
	return v->at(x)->good;
}

bool checkingBFS() {
	queue.push_back(pair<int, int>(0, 0));
	visited.insert(queue.back());
	pair<int, int> current;
	while (queue.size() > 0) {
		current = queue.back();
		queue.pop_back();
		node * f = first.at(current.first);
		node * s = second.at(current.second);
		if (f->terminal != s->terminal) {
			return false;
		}
		for (char c = 'a'; c != 'z' + 1; ++c) {
			if (f->connection.find(c) != f->connection.end() &&
				s->connection.find(c) == s->connection.end() &&
				isGood(&first, f->connection.find(c)->second)) {
				return false;
			}
			if (f->connection.find(c) == f->connection.end() &&
				s->connection.find(c) != s->connection.end() &&
				isGood(&second, s->connection.find(c)->second)) {
				return false;
			}
			if (f->connection.find(c) != f->connection.end() &&
				s->connection.find(c) != s->connection.end() &&
				visited.find(pair<int, int>(
					f->connection.find(c)->second,
					s->connection.find(c)->second)) == visited.end()) {
				queue.push_back(pair<int, int>(
					f->connection.find(c)->second,
					s->connection.find(c)->second));
				visited.insert(queue.back());
			}
		}
	}
	return true;
}

int main() {
	freopen("equivalence.in", "r", stdin);
	freopen("equivalence.out", "w", stdout);

	int n, m, k, x, y;
	char c;

	//Set the first dfa
	scanf("%d %d %d\n", &n, &m, &k);

	for (int i = 0; i < n; ++i) {
		first.push_back(new node);
	}

	for (int i = 0; i < k; ++i) {
		scanf("%d", &x);
		first.at(x - 1)->terminal = true;
		first.at(x - 1)->good = true;
		first.at(x - 1)->checked = true;
	}

	for (int i = 0; i < m; ++i) {
		scanf("%d %d %c\n", &x, &y, &c);
		addLink(first, x - 1, y - 1, c);
	}

	//Set the second dfa
	scanf("%d %d %d\n", &n, &m, &k);

	for (int i = 0; i < n; ++i) {
		second.push_back(new node);
	}

	for (int i = 0; i < k; ++i) {
		scanf("%d", &x);
		second.at(x - 1)->terminal = true;
		second.at(x - 1)->good = true;
		second.at(x - 1)->checked = true;
	}

	for (int i = 0; i < m; ++i) {
		scanf("%d %d %c\n", &x, &y, &c);
		addLink(second, x - 1, y - 1, c);
	}

	if (checkingBFS()) {
		printf("YES");
	}
	else {
		printf("NO");
	}
	return 0;
}