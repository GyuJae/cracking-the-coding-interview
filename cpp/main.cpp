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

// 1.5 하나 빼기
bool one_edit_away(const string &s1, const string &s2) {
    const int n1 = s1.size(), n2 = s2.size();
    if (n1 > n2 + 1 || n2 > n1 + 1) return false;

    if (n1 == n2) {
        bool diff_found = false;
        for (size_t i = 0; i < n1; i++) {
            if (s1[i] != s2[i]) {
                if (diff_found) return false;
                diff_found = true;
            }
        }
        return true;
    }

    const string longS = (n1 > n2) ? s1 : s2;
    const string shortS = (n1 > n2) ? s2 : s1;

    size_t idxLong = 0, idxShort = 0;
    bool skipped = false;
    while (idxShort < shortS.size()) {
        if (longS[idxLong] == shortS[idxShort]) {
            ++idxShort; ++idxLong;
        } else {
            if (skipped) return false;
            skipped = true;
            ++idxLong;
        }
    }
    return true;
}

// 1.6 문자열 압축
string compress(const string &s) {
    if (s.empty()) return "";

    string out;
    out.reserve(s.size());

    char current = s[0];
    size_t count = 1;

    for (size_t i = 1; i < s.size(); ++i) {
        if (s[i] == current) count++;
        else {
            out += current;
            out += to_string(count);
            current = s[i];
            count = 1;
        }
    }

    out += current;
    out += to_string(count);
    return out.size() < s.size() ? out : "";
}

// 1.7 행렬 회전
using Pixel = uint32_t;

void rotate90(vector<vector<Pixel>>& m) {
    const size_t n = m.size();
    if (n == 0) return;
    for (const auto& row: m) {
        if (row.size() != n) throw invalid_argument("Matrix must be NXM");
    }

    for (size_t layer = 0; layer < n / 2; layer++) {
        size_t first = layer;
        size_t last = n - 1 - layer;
        for (size_t k = 0; k < last - first; k++) {
            size_t top      = first;
            size_t left     = first + k;
            size_t bottom   = last;
            size_t right    = last;

            Pixel save                  = m[top][left];               // 위 → tmp
            m[top][left]                = m[bottom - k][first];       // 왼 ↙ 위
            m[bottom - k][first]        = m[bottom][right - k];       // 아래 ↖ 왼
            m[bottom][right - k]        = m[top + k][right];          // 오 ↘ 아래
            m[top + k][right]           = save;                       // tmp → 오
        }
    }
}

int main() {
    vector<vector<Pixel>> img{
            {1,  2,  3,  4},
            {5,  6,  7,  8},
            {9, 10, 11, 12},
            {13,14, 15, 16}
    };

    rotate90(img);

    for (const auto& row : img) {
        for (const auto v : row) cout << v << ' ';
        cout << '\n';
    }

    return 0;
}