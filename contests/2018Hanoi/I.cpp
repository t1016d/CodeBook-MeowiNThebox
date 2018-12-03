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

const int N = 55;
char str[N];

const int sizz = (1<<15) * N;
int nx[sizz][2], spt;
int fl[sizz], efl[sizz], ed[sizz];
int len[sizz];
int newnode(int len_ = 0) {
	fill(nx[spt], nx[spt] + 2, 0);
	ed[spt] = 0;
	len[spt] = len_;
	return spt++;
}
int add(char *S, int p) {
	debug("add [%s] from %d\n", S, p);
	int l = 1;
	for (int i = 0; S[i]; i++) {
		int a = S[i] - '0';
		if (nx[p][a] == 0)
			nx[p][a] = newnode(l);
		p = nx[p][a];
		l++;
	}
	ed[p] = 1;
	return p;
}
int q[sizz], qs, qe;
void make_fl(int root) {
	fl[root] = efl[root] = 0;
	qs = qe = 0;
	q[qe++] = root;
	while (qs != qe) {
		int p = q[qs++];
		for (int i = 0; i < 2; i++) {
			int t = nx[p][i];
			if (t == 0) continue;
			int tmp = fl[p];
			while (tmp && nx[tmp][i] == 0)
				tmp = fl[tmp];
			fl[t] = tmp ? nx[tmp][i] : root;
			efl[t] = ed[fl[t]] ? fl[t] : efl[fl[t]];
			q[qe++] = t;
		}
	}
}

ll dp[N][sizz];

int gra[sizz][2];

int main() {
	int n;
	scanf("%d", &n);
	scanf("%s", str);
	VI vec;
	for(int i=0; str[i]; i++)
		if(str[i] == '*')
			vec.PB(i);
	int m = strlen(str);
	//ll ans=0;
	spt = 1;
	int root = newnode();
	for(int i=0; i<(1<<SZ(vec)); i++) {
		char tmp[N] = {};
		for(int j=0; j<SZ(vec); j++)
			if(i&(1<<j))
				tmp[vec[j]] = '1';
			else
				tmp[vec[j]] = '0';
		for(int j=0; j<m; j++)
			if(tmp[j] == '\0')
				tmp[j] = str[j];
		debug("tmp: %s\n", tmp);
		add(tmp, root);
	}

	make_fl(root);

	for (int i = 1; i < spt; i++) {
		for (int j = 0; j <= 1; j++) {
			int p = i;
			debug("nx[%d][%d] = %d\n", i, j, nx[i][j]);
			while (p && nx[p][j] == 0) {
				debug("%d %d -- %d\n", i, j, p);
				p = fl[p];
			}
			debug("! %d %d -- %d\n", i, j, p);
			p = p ? nx[p][j] : root;
			debug("~ %d %d -- %d\n", i, j, p);
			gra[i][j] = p;
			debug("gra[%d][%d] = %d\n", i, j, gra[i][j]);
		}
	}
	memset(dp, 0, sizeof(dp));
	dp[0][root] = 1;
	for(int j=0; j<n; j++) {
		for(int k=1; k<spt; k++) {
			if (ed[k])
				continue;
			dp[j+1][gra[k][0]] += dp[j][k];
			dp[j+1][gra[k][1]] += dp[j][k];
		}
	}
	ll cnt = 0;
	for(int j=1; j<spt; j++) {
		if (ed[j])
			continue;
		cnt += dp[n][j];
		//debug("dp[%d][%d] = %lld\n", n, j, dp[n][j]);
	}
	debug("cnt = %lld\n", cnt);
	//ians += cnt;

	cout << (1ll << n) - cnt << endl;
	return 0;
}
