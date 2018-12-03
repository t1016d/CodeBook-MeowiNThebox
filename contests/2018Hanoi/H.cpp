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

int main() {
	int x, y;
	while(scanf("%d%d", &x, &y)) {
		if(!x && !y)	return 0;
		int ans = 0;
		x += (y/2 + y%2);
		ans = y/2 + 2*(y%2)+x/2;
		if(x%2) ans += 4;
		printf("%d\n", ans);
	}
	return 0;
}
