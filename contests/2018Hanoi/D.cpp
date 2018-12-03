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
typedef long long ll;
typedef pair<int,int> PII;
typedef vector<int> VI;

const int M = 1e9;

int n;

int query(int a, int b) {
	printf("QUERY %d %d\n", a, b);
	fflush(stdout);
	int ret;
	scanf("%d", &ret);
	return ret - (n-ret);
}

void ans(int x) {
	printf("YES %d\n", x);
	fflush(stdout);
}

int main() {
	scanf("%d", &n);
	int L = (5e8) - 1;
	ll ret = query(0, L);
	if(!ret) {
		ans(0);
		return 0;
	}

	ll lb_ret = ret;
	int lb = 0, ub = L+1;
	while(ub-lb > 1) {
		int m = (ub+lb) / 2;
		if(ub-lb == 2) {
			ans(m);
			return 0;
		}
		ret = query(m, (m+L)%M);
		if(!ret) {
			ans(m);
			return 0;
		}
		if(ret*lb_ret > 0) {
			lb_ret = ret;
			lb = m;
		}
		else {
			ub = m;
		}
	}
	ans(lb);
	return 0;
}
