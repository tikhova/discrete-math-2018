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
    map<char, int> connection;
    set<int> linked;
};
 
vector<node *> state1;
vector<node *> state2;
 
void addLink(node * x, int y, char c) {
    x->connection.insert(pair<char, int>(c, y));
}
 
 
bool dfs(int x, int y, bool * visited) {
    if (visited[x]) {
        return true;
    }
    visited[x] = true;
    if (state1.at(x)->terminal != state2.at(y)->terminal) {
        return false;
    }
     
    bool result = true;
    for (map<char, int>::iterator it = state1.at(x)->connection.begin();
        it != state1.at(x)->connection.end(); ++it) {
        int x1 = it->second;
        if (state2.at(y)->connection.find(it->first) == state2.at(y)->connection.end()) {
            return false;
        }
        int y1 = state2.at(y)->connection.find(it->first)->second;
        result = dfs(x1, y1, visited);
    }
    return result;
}
 
 
int main() {
    freopen("isomorphism.in", "r", stdin);
    freopen("isomorphism.out", "w", stdout);
 
    int n, m, k, x, y;
    char c;
 
    scanf("%d %d %d\n", &n, &m, &k);
 
    bool *visited = new bool[n];
 
    for (int i = 0; i < n; ++i) {
        state1.push_back(new node);
        visited[i] = false;
    }
 
    for (int i = 0; i < k; ++i) {
        scanf("%d", &x);
        state1.at(x - 1)->terminal = true;
    }
 
    for (int i = 0; i < m; ++i) {
        scanf("%d %d %c\n", &x, &y, &c);
        addLink(state1.at(x - 1), y - 1, c);
    }
 
    scanf("%d %d %d\n", &n, &m, &k);
 
    for (int i = 0; i < n; ++i) {
        state2.push_back(new node);
    }
 
    for (int i = 0; i < k; ++i) {
        scanf("%d", &x);
        state2.at(x - 1)->terminal = true;
    }
 
    for (int i = 0; i < m; ++i) {
        scanf("%d %d %c\n", &x, &y, &c);
        addLink(state2.at(x - 1), y - 1, c);
    }
 
    if(dfs(0, 0, visited)) {
        printf("YES");
    }
    else {
        printf("NO");
    }
    return 0;
}