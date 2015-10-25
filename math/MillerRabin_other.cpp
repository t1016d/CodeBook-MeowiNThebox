/* Miller Rabin code from ioicamp */
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
	#define debug(...) 0
#endif
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
typedef vector<int> VI;

ll mul(ll a, ll b, ll n) {
	ll r = 0;
	a %= n, b %= n;
	while(b) {
		if(b&1) r = (a+r>=n ? a+r-n : a+r);
		a = (a+a>=n ? a+a-n : a+a);
		b >>= 1;
	}
	return r;
}

ll bigmod(ll a, ll d, ll n) {
	if(d==0)	return 1LL;
	if(d==1) return a % n;
	return mul(bigmod(mul(a, a, n), d/2, n), d%2?a:1, n);
}

const bool PRIME = 1, COMPOSITE = 0;
bool miller_rabin(ll n, ll a) {
	if(__gcd(a, n) == n)	return PRIME;
	if(__gcd(a, n) != 1)	return COMPOSITE;
	ll d = n-1, r = 0, res;
	while(d%2==0) { ++r; d/=2; }
	res = bigmod(a, d, n);
	if(res == 1 || res == n-1)	return PRIME;
	while(r--) {
		res = mul(res, res, n);
		if(res == n-1)	return PRIME;
	}
	return COMPOSITE;
}

bool isprime(ll n) {
	if(n==1)
		return COMPOSITE;
	ll as[7] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
	for(int i=0; i<7; i++)
		if(miller_rabin(n, as[i]) == COMPOSITE)	return COMPOSITE;
	return PRIME;
}
