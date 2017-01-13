#include <bits/stdc++.h>
#define PB push_back
#define MP make_pair
#define F first
#define S second
#define SZ(x) ((int)(x).size())
#define ALL(x) (x).begin(),(x).end()
#ifdef _DEBUG_
	#define debug(...) printf(__VA_ARGS__)
#else
	#define debug(...) (void)0
#endif
using namespace std;
typedef unsigned long long ull;
typedef pair<int,int> PII;
typedef vector<int> VI;

ull as[7] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022}; // cheat numbers!

inline ull add(ull x, ull y, ull M) { x += y; if(x >= M) x -= M; return x; }

ull bigmul(ull x, ull y, ull M) {
	ull r = 0, t = x % M;
	while(y) {
		if(y % 2 == 1) r = add(r, t, M);
		t = add(t, t, M);
		y /= 2;
	}
	return r;
}

ull bigpow(ull a, ull b, ull M) {
	ull r = 1, t = a % M;
	while(b) {
		if(b % 2 == 1) r = bigmul(r, t, M);
		t = bigmul(t, t, M);
		b /= 2;
	}
	return r;
}

bool test(ull x, ull b) {
	b %= x;
	if(b == 0) return true;
	if(__gcd(x, b) > 1) return false;
	ull d = x - 1;
	while(d % 2 == 0) d /= 2;
	b = bigpow(b, d, x);
	if(b == 1) return true;
	while(d < x - 1) {
		if(b == x - 1) return true;
		if(b == 1) return false;
		b = bigmul(b, b, x);
		d *= 2;
	}
	return false;
}

bool prime(ull x) {
	for(int i = 0; i < 7; i++)
		if(!test(x, as[i]))
			return false;
	return true;
}

int main() {
	int T;
	cin >> T;
	while(T--) {
		ull N;
		cin >> N;
		cout << (prime(N) ? "YES" : "NO") << endl;
	}
	return 0;
}
