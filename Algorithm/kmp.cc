#include <iostream>
#include <vector>
#include <string>
using namespace std;

/** 
 *  judge whether @pattern is in @str, return first appear index or -1
 *  @param str
 *  @param pattern
 *
 *  @return 
 */
int kmp(string str, string pattern) {
    vector<int> next(pattern.size(), 0);
    next[0] = -1;

    // set up next
    int k = -1, j = 0, i = 0;
    while (j < pattern.size()) {
        if (k == -1 || pattern[k] == pattern[j]) {
            k += 1;
            j += 1;
            if (pattern[j] != pattern[k]) next[j] = k;
            else next[j] = next[k];
        } else {
            k = next[k];
        }
    }

    // start search
    j = 0;
    int len1 = str.size(), len2 = pattern.size();
    while (i < len1 && j < len2) {
        if (j == -1 || str[i] == pattern[j]) {
            j += 1;
            i += 1;
        } else {
            j = next[j];
        }
    }

    return j == pattern.size() ? i - j : -1;
}

int main() {
    // cout << kmp("ababa", "babac") << endl;
    cout << kmp("here is an example", "example") << endl;
}