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

const int MAXN = 100 + 10;

int a[MAXN][MAXN];
bool used[MAXN][MAXN];
queue<PII> q;

int main() {
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	fill(a[0], a[n+1], n*m+10);
	for(int i=0; i<k; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		a[x][y] = 0;
		q.push(MP(x, y));
	}

	int ans = 0;
	while(!q.empty()) {
		auto pr = q.front();	q.pop();
		int x = pr.F, y = pr.S;
		if(used[x][y])	continue;
		used[x][y] = true;
		int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
		for(int i=0; i<4; i++) {
			int ax = x+dx[i], ay = y+dy[i];
			if(ax<1 || ax>n || ay<1 || ay>m || used[ax][ay])	continue;

			if(a[ax][ay] > a[x][y]+1) {
				a[ax][ay] = a[x][y]+1;
				ans = max(ans, a[ax][ay]);
				q.push(MP(ax, ay));
			}
		}
	}
	printf("%d\n", ans+1);
	return 0;
}
