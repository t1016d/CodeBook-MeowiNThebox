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

const int MAXN = 20000 + 10;
const int MAXQ = 300000 + 10;
const int MAXS = 500 + 10;

struct Seg {
	int sum;
	Seg *tl, *tr;
	Seg() {}
	Seg(int l, int r) {
		if(l == r) {
			tl = tr = NULL;
			sum = 0;
			return ;
		}
		int m = (l+r) / 2;
		tl = new Seg(l, m);
		tr = new Seg(m+1, r);
	}

	void init(int l, int r) {
		sum = 0;
		if(l != r) {
			int m = (l+r) / 2;
			tl->init(l, m);
			tr->init(m+1, r);
		}
	}

	void add(int k, int x, int l, int r) {
		if(l == r)	sum += x;
		else {
			int m = (l+r) / 2;
			if(k <= m)	tl->add(k, x, l, m);
			else		tr->add(k, x, m+1, r);
			sum = tl->sum+tr->sum;
		}
	}

	int query(int k, int l, int r) {
		debug("l %d r %d sum %d\n", l, r, sum);
		if(l == r)
			return sum==1 ? l : -1;
		int m = (l+r) / 2;
		if(tl->sum >= k)	return tl->query(k, l, m);
		return	tr->query(k-tl->sum, m+1, r);
	}
} *t;

string s;
string d[MAXN];
// id_of_str, cur
vector<PII> que[30];

// k, id
vector<PII> qs[MAXS][MAXS];
int ans[MAXQ];

int main() {
	cin >> s;
	int n, q;
	scanf("%d%d", &n, &q);
	for(int i=0; i<n; i++) {
		cin >> d[i];
	}
	for(int i=0; i<q; i++) {
		int l, r, k;
		scanf("%d%d%d", &l, &r, &k);
		l--;
		r--;
		qs[l][r].PB(MP(k, i));
	}
	t = new Seg(0, n);
	sort(d, d+n);
	for(int i=0; i<SZ(s); i++) {
		t->init(0, n);
		for(int j=0; j<26; j++)	que[j].clear();
		for(int j=0; j<n; j++) 
			que[d[j][0]-'a'].PB(MP(j, 0));

		for(int j=i; j<SZ(s); j++) {
			debug("%d %d\n", i, j);
			int c = s[j]-'a';
			vector<PII> tmp[30];
			for(PII pr : que[c]) {
				if(pr.S < SZ(d[pr.F])-1) {
					tmp[ d[pr.F][pr.S+1] - 'a' ].PB(MP(pr.F, pr.S+1));
				}
				else {
					debug("%d finished!\n", pr.F);
					t->add(pr.F, 1, 0, n);
				}
			}
			que[c].clear();
			for(int k=0; k<26; k++) {
				for(PII pr : tmp[k])	que[k].PB(pr);
			}

			for(PII qq : qs[i][j]) {
				int k2 = qq.F, id = qq.S;
				ans[id] = t->query(k2, 0, n);
				debug("query %d, %d=%d\n", id, k2, ans[i]);
			}
		}
	}

	for(int i=0; i<q; i++) {
		if(ans[i] == -1)	puts("NO SUCH WORD");
		else {
			for(int j=0; j<min(10, SZ(d[ans[i]])); j++)	putchar(d[ans[i]][j]);
			putchar('\n');
		}
	}
	return 0;
}
