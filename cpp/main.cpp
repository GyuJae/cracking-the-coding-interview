#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>
#include <array>

using namespace std;

/* 1.1 중복이 없는가
 * - ASCII 문자열인지, 유니코드 문자열인지 구분필요
 * -
 */

bool is_unique_chars(const string &str) {
    array<bool, 26> seen{};
    for (const auto ch: str) {
        if (ch < 'a' || ch > 'z') return false;
        const int idx = ch - 'a';
        if (seen[idx]) return false;
        seen[idx] = true;
    }
    return true;
}

bool is_unique_chars2(const string &str) {
    int seen = 0;
    for (const auto ch: str) {
        if (ch < 'a' || ch > 'z') return false;
        const int idx = ch - 'a';
        if (seen & (1 << idx)) return false;
        seen |= (1 << idx);
    }
    return true;
}

bool is_unique_chars3(const string &str) {
    if (str.size() > 128) return false;
    bitset<128> seen;
    for (const unsigned char ch: str) {
        if (seen.test(ch)) return false;
        seen.set(ch);
    }
    return true;
}

bool is_unique_chars4(string str) {
    if (str.size() > 128) return false;
    ranges::sort(str);
    return ranges::adjacent_find(str) == str.end();
}

/* 1.2 순열확인
 */

bool is_permutation1(string a, string b) {
    if (a.size() != b.size()) return false;
    ranges::sort(a);
    ranges::sort(b);
    return a == b;
}

bool is_permutation2(const string &a, const string &b) {
    if (a.size() != b.size()) return false;

    array<int, 128> letters{};
    for (const char ch: a) letters[ch]++;
    for (const char ch: b) {
        letters[ch]--;
        if (letters[ch] < 0) return false;
    }
    return true;
}

bool is_permutation3(const string &a, const string &b) {
    return ranges::is_permutation(a, b);
}

int main() {
    return 0;
}