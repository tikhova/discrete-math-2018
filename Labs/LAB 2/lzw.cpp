#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
 
int main() {
    freopen("lzw.in", "r", stdin);
    freopen("lzw.out", "w", stdout);
    string s;
    vector <int> t;
    map<string, int> key;
    for (char i = 'a'; i <= 'z'; i++) {
        key.emplace(string (1, i), i - 'a');
    }
    cin >> s;
    int i = 0, j, max = 25;
    while (i < s.size()) {
        j = 1;
        while (i + j <= s.size() && key.find(s.substr(i, j)) != key.end()) {
            j++;
        }
        t.push_back(key.at(s.substr(i, j - 1)));
        if (i + j - 1 < s.size()) {
            key.emplace(s.substr(i, j), ++max);
            i += j - 1;
        }
        else {
            break;
        }
    }
    for (int i : t) {
        printf("%i ", i);
    }
    return 0;
}
