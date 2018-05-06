#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
 
int main() {
    freopen("mtf.in", "r", stdin);
    freopen("mtf.out", "w", stdout);
    string s;
    cin >> s;
    vector<int> ans;
    map<char, int> key;
    int min_key = 0;
    int difference = 1;
    for (char i = 'a'; i <= 'z'; i++) {
        key.emplace(i, i - 'a');
    }
    for (char c : s) {
        ans.push_back(1 + key.at(c));
        for (char i = 'a'; i <= 'z'; i++) {
            if (key.at(i) < key.at(c)) {
                key.at(i)++;
            }
        }
        key.at(c) = 0;
    }
    for (int i : ans) {
        printf("%i ", i);
    }
    return 0;
}
