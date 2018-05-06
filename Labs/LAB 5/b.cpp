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

struct node {
	bool terminal = false;
	map<char, vector<node*>*> connection;
};

vector<node *> state;

void addLink(int x, int y, char c) {
	map<char, vector<node*>*>::iterator link = state.at(x)->connection.find(c);
	if (link == state.at(x)->connection.end()) {
		state.at(x)->connection.insert(pair<char, vector<node*>*>(c, new vector<node*>));
	}
	state.at(x)->connection.find(c)->second->push_back(state.at(y));
}

bool check(string s, node * current) {
	int n = s.size();
	set<node *> * r = new set<node *>[n + 1];
	r[0].insert(state.at(0));
	for (int i = 0; i < n; ++i) {
		for (set<node *>::iterator it = r[i].begin(); it != r[i].end(); ++it) {
			map<char, vector<node*>*>::iterator v_it = (*it)->connection.find(s.at(i));
			if (v_it != (*it)->connection.end()) {
				vector<node*> * curr = v_it->second;
				for (int j = 0; j < curr->size(); ++j) {
					r[i + 1].insert(curr->at(j));
				}
			}
		}
	}
	for (set<node *>::iterator it = r[n].begin(); it != r[n].end(); ++it) {
		if ((*it)->terminal) {
			return true;
		}
	}
	return false;
}

int main() {
	freopen("problem2.in", "r", stdin);
	freopen("problem2.out", "w", stdout);

	string s;
	int n, m, k, x, y;
	char c;

	cin >> s;
	scanf("%d %d %d\n", &n, &m, &k);

	for (int i = 0; i < n; ++i) {
		state.push_back(new node);
	}

	for (int i = 0; i < k; ++i) {
		scanf("%d", &x);
		state.at(x - 1)->terminal = true;
	}

	for (int i = 0; i < m; ++i) {
		scanf("%d %d %c\n", &x, &y, &c);
		addLink(x - 1, y - 1, c);
	}

	if (check(s, state.at(0))) {
		cout << "Accepts";
	}
	else {
		cout << "Rejects";
	}
	return 0;
}