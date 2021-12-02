#include <bits/stdc++.h>

using namespace std;

typedef long double ld;
typedef long long ll;

#define PI 3.1415926535897932384626433832795028841971693993751058209749445
#define gcd __gcd

template <typename T>
T bin_pow(T a, int n) {
    if (n == 0) {
        return 1;
    }
    if (n == 1) {
        return a;
    }
    if (n % 2 == 1) {
        return bin_pow(a, n - 1) * a;
    }
    T b = bin_pow(a, n / 2);
    return b * b;
}

ll to_dec(string s, int base) {
    ll n = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            n += (s[i] - 'A' + 10) * pow(base, s.size() - 1 - i);
        } else {
            n += (s[i] - '0') * pow(base, s.size() - 1 - i);
        }
    }
    return n;
}

string dec_to_base(ll number, int base) {
    stringstream s;
    while (number > 0) {
        if (number % base > 9) {
            s << char((number % base) - 10 + 'A');
        } else {
            s << number % base;
        }
        number /= base;
    }
    string t = s.str();
    reverse(t.begin(), t.end());
    return t;
}

template <typename T>
T lcm(T a, T b) {
    return abs(a * b) / gcd(a, b);
}

ld msin(ld a) {
    return sin(PI * a / 180);
}

ld mcos(ld a) {
    return cos(PI * a / 180);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}
