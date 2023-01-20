#include <bits/stdc++.h>

using namespace std;

typedef long double ld;
typedef long long ll;

#define PI 3.1415926535897932384626433832795028841971693993751058209749445
#define gcd __gcd

#define MAXN 1000000

struct SegTree {
    vector<int> t;
    void build(vector<int> &a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tr];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v * 2, tl, tm);
            build(a, v * 2 + 1, tm + 1, tr);
            t[v] = t[v * 2] + t[v * 2 + 1];
        }
    }

    int sum(int v, int tl, int tr, int l, int r) {
        if (l > r) {
            return 0;
        }
        if (tl == l && tr == r) {
            return t[v];
        }
        int tm = (tl + tr) / 2;
        return sum(v * 2, tl, tm, l, min(tm, r)) + sum(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
    }

    void update(int v, int tl, int tr, int pos, int val) {
        if (tl == tr) {
            t[v] = val;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm) {
                update(v * 2, tl, tm, pos, val);
            } else {
                update(v * 2 + 1, tm + 1, tr, pos, val);
            }
            t[v] = t[v * 2] + t[v * 2 + 1];
        }
    }
};


struct DSU {
    int p[MAXN], s[MAXN];

    int leader(int v) {
        return (p[v] == v) ? v : p[v] = leader(p[v]);
    }

    void unite(int a, int b) {
        a = leader(a), b = leader(b);
        if (s[a] > s[b])
            swap(a, b);
        s[b] += s[a];
        p[a] = b;
    }

    void init(int n) {
        for (int i = 0; i < n; i++)
            p[i] = i, s[i] = 1;
    }
};

vector<bool> sieve(int n) {
    vector<bool> prime(n + 1, true);
    prime[0] = prime[1] = false;
    for (int i = 2; i <= n; ++i) {
        if (prime[i]) {
            if (i * 1ll * i <= n) {
                for (int j = i * i; j <= n; j += i) {
                    prime[j] = false;
                }
            }
        }
    }
    return prime;
}

int bin_pow(int a, int n) {
    if (n == 0) {
        return 1;
    }
    if (n & 1) {
        return bin_pow(a, n - 1) * a;
    } else {
        int b = bin_pow(a, n / 2);
        return b * b;
    }
}

const int mod = 1e9 + 7;
int bin_pow_mod(int a, int n) {
    if (n == 0) {
        return 1;
    }
    if (n & 1) {
        return (bin_pow_mod(a, n - 1) * a) % mod;
    } else {
        int b = bin_pow_mod(a, n / 2) % mod;
        return (b * b) % mod;
    }
}
//a^p = a (mod p)
//p is prime
//a^(p - 2) = a^(-1) (mod p)
int inv(int a) {
    return bin_pow_mod(a, mod - 2);
}

vector<int> prefix_function(string s) {
    int n = (int) s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j]) ++j;
        pi[i] = j;
    }
    return pi;
}

vector<int> z_function(string s) {
    int n = (int) s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

vector<int> manacher_odd(string s) {
    int n = s.size();
    vector<int> d(n, 1);
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (i <= r) {
            d[i] = min(r - i + 1, d[r - i + l]);
        }
        while (d[i] + i < n && i - d[i] >= 0 && s[d[i] + i] == s[i - d[i]]) {
            d[i]++;
        }
        if (i + d[i] - 1 > r) {
            r = i + d[i] - 1;
            l = i - d[i] + 1;
        }
    }
    return d;
}

//hash
// Разумно выбирать для P простое число, большее количества символов во входном алфавите
// h[0] = 0, h[1] = h[0] + (s[0] * P^0), h[2] = h[1] + (s[1] * P^1), ...
// если вам нужно хранить n различных хешей, то безопасный модуль — это число порядка 10 * (n ^ 2)

bool isPrime(int n) {
    for (int i = 2; i <= n / i; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return n > 1;
}

int prevPrime(int n) {
    while (true) {
        if (isPrime(n)) {
            return n;
        }
        --n;
    }
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
// prime modules
// нужно вычислять хэши по неск простым модулям
// операции с хэшами нужно проводить по этим модулям
int m1 = prevPrime(uniform_int_distribution<int>(1ll * 2900 * 1000 * 1000, 1ll * 3000 * 1000 * 1000)(rng));
int m2 = prevPrime(uniform_int_distribution<int>(1ll * 2900 * 1000 * 1000, 1ll * 3000 * 1000 * 1000)(rng));


//Количество разных подстрок. Посчитаем хеши от всех подстрок за O(n^2)
// и добавим их все в std::set. Чтобы получить ответ, просто вызовем set.size().
//
//Поиск подстроки в строке. Можно посчитать хеши от шаблона (строки, которую ищем) и пройтись «окном» размера шаблона по тексту, поддерживая хеш текущей подстроки. Если хеш какой-то из этих подстрок совпал с хешом шаблона, то мы нашли нужную подстроку. Это называется алгоритмом Рабина-Карпа.
//
//Сравнение подстрок на больше-меньше, а не только на равенство. У любых двух строк есть какой-то общий префикс (возможно, пустой). Сделаем бинпоиск по его длине, а дальше в обеих подстроках возьмём идущий за ним символ и сравним. Это будет работать за O(\log n)O(logn).
//
//Палиндромность подстроки. Можно посчитать два массива — обратные хеши и прямые. Проверка на палиндром будет заключаться в сравнении значений hash_substring() на первом массиве и на втором.
//
//Количество палиндромов. Можно перебрать центр палиндрома, а для каждого центра — бинпоиском его размер. Проверять подстроку на палиндромность мы уже умеем. Как и всегда в задачах на палиндромы, случаи четных и нечетных палиндромов нужно обрабатывать отдельно. Это будет работать за O(n \log n)O(nlogn), хотя это можно решить и линейно.
//hash

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

/*bridges
 const int MAXN = ...;
vector<int> g[MAXN];
bool used[MAXN];
int timer, tin[MAXN], fup[MAXN];
 
void dfs (int v, int p = -1) {
	used[v] = true;
	tin[v] = fup[v] = timer++;
	for (size_t i=0; i<g[v].size(); ++i) {
		int to = g[v][i];
		if (to == p)  continue;
		if (used[to])
			fup[v] = min (fup[v], tin[to]);
		else {
			dfs (to, v);
			fup[v] = min (fup[v], fup[to]);
			if (fup[to] > tin[v])
				IS_BRIDGE(v,to);
		}
	}
}
 
void find_bridges() {
	timer = 0;
	for (int i=0; i<n; ++i)
		used[i] = false;
	for (int i=0; i<n; ++i)
		if (!used[i])
			dfs (i);
}
 */

/*
 int n, k;
vector < vector<int> > g;
vector<int> mt;
vector<char> used;
 
bool try_kuhn (int v) {
	if (used[v])  return false;
	used[v] = true;
	for (size_t i=0; i<g[v].size(); ++i) {
		int to = g[v][i];
		if (mt[to] == -1 || try_kuhn (mt[to])) {
			mt[to] = v;
			return true;
		}
	}
	return false;
}
 
int main() {
	... чтение графа ...
 
	mt.assign (k, -1);
	for (int v=0; v<n; ++v) {
		used.assign (n, false);
		try_kuhn (v);
	}
 
	for (int i=0; i<k; ++i)
		if (mt[i] != -1)
			printf ("%d %d\n", mt[i]+1, i+1);
}
 */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}
