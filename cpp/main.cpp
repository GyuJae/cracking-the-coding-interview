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

// 1.3 URLify
void urlify(string& s, size_t trueLen) {
    // 1) 공백 개수
    size_t spaces = 0;
    for (size_t i = 0; i < trueLen; ++i)
        if (s[i] == ' ') ++spaces;

    // 2) 새 길이 = trueLen + spaces*2
    size_t write = trueLen + spaces * 2;
    s.resize(write);

    // 3) 뒤에서 앞으로 복사
    for (size_t read = trueLen; read-- > 0; ) {
        if (s[read] == ' ') {
            s[--write] = '0';
            s[--write] = '2';
            s[--write] = '%';
        } else {
            s[--write] = s[read];
        }
    }
}

// 1.4 회문 수열
bool is_permutation_of_palindrome(const string &s) {
    array<int, 128> freq{};
    for (unsigned char ch: s) {
        if (ch < 'a' || ch > 'z') continue;
        if (ch == ' ') continue;
        ch = tolower(ch);
        ++freq[ch];
    }

    bool oddFound = false;
    for (const int cnt: freq) {
        if (cnt & 1) {
            if (oddFound) return false;
            oddFound = true;
        }
    }
    return true;
}

bool is_permutation_of_palindrome2(const string &s) {
    int bit = 0;
    for (unsigned char ch: s) {
        if (ch == ' ') continue;
        ch = tolower(ch);
        if (ch < 'a' || ch > 'z') continue;
        int idx = ch - 'a';
        bit ^= (1 << idx);
    }
    return __builtin_popcount(bit) <= 1;
}

int main() {
    cout << is_permutation_of_palindrome("tact coa") << endl;
    cout << is_permutation_of_palindrome2("tact coa") << endl;
    return 0;
}