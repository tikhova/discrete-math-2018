#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
 
int main() {
    freopen("bwt.in", "r", stdin);
    freopen("bwt.out", "w", stdout);
    string s;
    vector<string> a;
    cin >> s;
    for (int i = 0; i < s.length(); i++) {
        a.push_back(s);
        rotate(a.at(i).begin(), a.at(i).begin() + i, a.at(i).end());
    }
    sort(a.begin(), a.end());
    for (int i = 0; i < s.length(); i++) {
        printf("%c", a.at(i)[s.length() - 1]);
    }
    return 0;
}
