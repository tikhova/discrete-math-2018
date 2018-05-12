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
	set<int> * nodes;
	map<char, set<int> *> connection;
};

vector<node *> nfa;
vector<node *> dfa;
vector<node *> queue;

void addLink(vector<node *> v, int x, int y, char c) {
	map<char, set<int> *>::iterator it = v.at(x)->connection.find(c);
	if (it == v.at(x)->connection.end()) {
		v.at(x)->connection.insert(pair<char, set<int> *>(c, new set<int>{ y }));
		return;
	}
	it->second->insert(y);
}

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

int find(set<int> * s) {
	bool present = false;
	int number;
	for (int i = 0; i < dfa.size(); ++i) {
		if ((*s).size() == dfa.at(i)->nodes->size()) {
			present = true;
			number = i;
			for (set<int>::iterator it = s->begin();
				it != s->end(); ++it) {
				if (dfa.at(i)->nodes->find(*it) == dfa.at(i)->nodes->end()) {
					present = false;
				}
			}

			if (present) {
				break;
			}
		}
	}
	if (present) {
		return number;
	}
	else {
		return -1;
	}
}

void buildDFA() {
	queue.push_back(new node);
	dfa.push_back(new node{ nfa.at(0)->terminal, new set<int>{ 0 } });
	queue.at(0) = dfa.at(0);
	while (queue.size() > 0) {
		node * current = queue.back();
		queue.pop_back();
		for (char c = 'a'; c != 'z' + 1; ++c) {
			node * next = new node{false, new set<int>};
			for (set<int>::iterator it = current->nodes->begin();
				it != current->nodes->end(); ++it) {
				map<char, set<int>*>::iterator k = nfa.at(*it)->connection.find(c);
				if (k != nfa.at(*it)->connection.end()) {
					for (set<int>::iterator sit = k->second->begin();
						sit != k->second->end(); ++sit) {
						next->nodes->insert(*sit);
						next->terminal = next->terminal || nfa.at(*sit)->terminal;
					}
				}
			}
			int positionInDFA = find(next->nodes);
			if (positionInDFA == -1 && next->nodes->size() > 0) {
				dfa.push_back(next);
				queue.push_back(next);
				positionInDFA = dfa.size() - 1;
			}
			int currentPositionInDFA = find(current->nodes);
			for (set<int>::iterator it = next->nodes->begin();
				it != next->nodes->end(); ++it) {
				addLink(dfa, currentPositionInDFA, positionInDFA, c);
			}
		}
		
	}
}

int main() {
	freopen("problem5.in", "r", stdin);
	freopen("problem5.out", "w", stdout);

	int n, m, k, l, x, y;
	char c;

	scanf("%d %d %d %d\n", &n, &m, &k, &l);


	for (int i = 0; i < n; ++i) {
		nfa.push_back(new node);
		nfa.at(nfa.size() - 1)->nodes = new set<int>{ i };
	}

	for (int i = 0; i < k; ++i) {
		scanf("%d", &x);
		nfa.at(x - 1)->terminal = true;
	}

	for (int i = 0; i < m; ++i) {
		scanf("%d %d %c\n", &x, &y, &c);
		addLink(nfa, x - 1, y - 1, c);
	}


	buildDFA();

	long long ** matrix = new long long *[dfa.size()];

	for (int i = 0; i < dfa.size(); ++i) {
		matrix[i] = new long long[dfa.size()];
		for (int j = 0; j < dfa.size(); ++j) {
			matrix[i][j] = 0;
		}
		for (map<char, set<int> *>::iterator it = dfa.at(i)->connection.begin();
			it != dfa.at(i)->connection.end(); ++it) {
			for (set<int>::iterator sit = it->second->begin();
				sit != it->second->end(); ++sit) {
				matrix[i][*sit]++;
			}
		}
	}

	long long ** answer = binpow(matrix, dfa.size(), l);

	long long cnt = 0;
	for (int i = 0; i < dfa.size(); ++i) {
		if (dfa.at(i)->terminal) {
			cnt += answer[0][i];
			cnt %= MOD;
		}
	}
	printf("%lld", cnt);
	return 0;
}