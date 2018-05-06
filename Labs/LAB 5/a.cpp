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
using namespace std;
 
struct node {
    bool terminal = false;
    map<char, node*> connection;
};
 
vector<node *> state;
 
void addLink(int x, int y, char c) {
    state.at(x)->connection.insert(pair<char, node*>(c, state.at(y)));
}
 
string check(string s) {
    node * current = state.at(0);
    map<char, node*>::iterator link;
    for (int i = 0; i < s.length(); ++i) {
        link = current->connection.find(s.at(i));
        if (link != current->connection.end()) {
            current = link->second;
        }
        else {
            return "Rejects";
        }
    }
    if (current->terminal) {
        return "Accepts";
    }
    return "Rejects";
}
 
int main() {
    freopen("problem1.in", "r", stdin);
    freopen("problem1.out", "w", stdout);
 
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
 
    cout << check(s);
    return 0;
}