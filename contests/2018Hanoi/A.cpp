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

const int MAX = 100 + 10;

typedef pair<int,ll> PIL;
const int MAXV = MAX * MAX * 2;
const int MAXE = MAXV * 6;
const int INF = (int)1e9 + 10;
const ll cINF = (ll)1e18 + 10;

struct E {
	int to, ca, cost;
	E(int t = 0, int c = 0, int co = 0): to(t), ca(c), cost(co) {}
} eg[2 * MAXE];

struct Flow {
	VI e[MAXV];
	int ei, n;
	void init(int n_) {
		debug("n_ %d -- %d\n", n_, MAXV);
		n = n_;
		ei = 0;
		for (int i = 0; i < n; i++)
			e[i] = VI();
	}
	void add(int a, int b, int c, int d) {
		eg[ei] = E(b, c, d);
		e[a].PB(ei);
		ei++;
		eg[ei] = E(a, 0, -d);
		e[b].PB(ei);
		ei++;
	}

	PII d[MAXV] = {};
	bool inq[MAXV] = {};
	queue<int> que;
	VI pe;
	bool SPFA() {
		fill(d, d + n, MP(INF, INF));
		d[0] = MP(0, 0);
		que.push(0);
		inq[0] = 1;
		while (!que.empty()) {
			int v = que.front();
			que.pop();
			inq[v] = 0;
			for (int id : e[v]) {
				if (eg[id].ca > 0 && MP(d[v].F + eg[id].cost, d[v].S + 1) < d[eg[id].to]) {
					d[eg[id].to] = MP(d[v].F + eg[id].cost, d[v].S + 1);
					if (!inq[eg[id].to]) {
						que.push(eg[id].to);
						inq[eg[id].to] = 1;
					}
				}
			}
		}
		return d[n - 1].F < INF;
	}
	PIL go(ll cb = cINF) {
		if (!SPFA()) return MP(0, 0);
		pe.clear();
		int fl = INF;
		for (int v = n - 1; v != 0; ) {
			for (int id : e[v]) {
				int u = eg[id].to;
				const E& t = eg[id ^ 1];
				if (t.ca > 0 && MP(d[u].F + t.cost, d[u].S + 1) == d[v]) {
					fl = min(fl, t.ca);
					v = u;
					pe.PB(id ^ 1);
					break;
				}
			}
		}
		if (d[n - 1].F > 0)
			fl = min(1ll * fl, cb / d[n - 1].F);
		for (int id : pe) {
			eg[id].ca -= fl;
			eg[id ^ 1].ca += fl;
		}
		return MP(fl, 1ll * fl * d[n - 1].F);
	}
	PIL max_flow() {
		PIL ans = MP(0, 0), temp;
		while ((temp = go()).F > 0) {
			ans.F += temp.F;
			ans.S += temp.S;
		}
		return ans;
	}
} flow;

int N, M;
int get_id_in(int x, int y) {
	return 1 + x * M + y;
}
int get_id_out(int x, int y) {
	return N * M + 1 + x * M + y;
}
PII to_id_in(int id) {
	id--;
	return MP(id / M, id % M);
}
const int dx[4] = {0, -1, 0, 1};
const int dy[4] = {-1, 0, 1, 0};
const char sym[5] = "LDRU";

int main() {
	while (scanf("%d%d", &N, &M) == 2 && N) {
		int x[4], y[4], xn, yn;
		for (int i = 1; i <= 3; i++) {
			scanf("%d%d", &x[i], &y[i]);
			x[i]--, y[i]--;
		}
		scanf("%d%d", &xn, &yn);
		xn--, yn--;
		const int target = 2 * N * M + 1;
		assert(get_id_in(0, 0) == 1);
		assert(target == get_id_out(N - 1, M - 1) + 1);
		assert(get_id_in(N - 1, M - 1) + 1 == get_id_out(0, 0));

		flow.init(target + 1);
		flow.add(0, get_id_in(x[2], y[2]), 2, 0);
		flow.add(get_id_out(x[1], y[1]), target, 1, 0);
		flow.add(get_id_out(x[3], y[3]), target, 1, 0);

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (MP(i, j) == MP(x[2], y[2]))
					flow.add(get_id_in(i, j), get_id_out(i, j), 2, 0);
				else
					flow.add(get_id_in(i, j), get_id_out(i, j), 1, 0);
				for (int k = 0; k < 4; k++) {
					int tx = i + dx[k];
					int ty = j + dy[k];
					if (tx < 0 || tx >= N)
						continue;
					if (ty < 0 || ty >= M)
						continue;
					if (MP(i, j) == MP(xn, yn) || MP(tx, ty) == MP(xn, yn))
						continue;
					flow.add(get_id_out(i, j), get_id_in(tx, ty), 1, 1);
				}
			}
		}
		auto res = flow.max_flow();
		for (int i = 0; i < flow.ei; i++) {
			//debug("to %d -- c %d cost %d\n", eg[i].to, eg[i].ca, eg[i].cost);
		}
		if (res.F == 2) {
			puts("YES");
			VI path[2];
			for (int cnt = 0; cnt < 2; cnt++) {
				int at = 0;
				while (at != target) {
					if (at > 0 && at <= N * M)
						path[cnt].PB(at);
					for (int id : flow.e[at]) {
						if (id % 2 == 1 || eg[id ^ 1].ca == 0)
							continue;
						eg[id ^ 1].ca--;
						at = eg[id].to;
						break;
					}
				}
			}
			if (path[0].back() == get_id_in(x[3], y[3]))
				path[0].swap(path[1]);
			reverse(ALL(path[0]));
			for (int i = 1; i < SZ(path[1]); i++)
				path[0].PB(path[1][i]);
			for (int pt : path[0]) {
				debug("(%d, %d) ", to_id_in(pt).F, to_id_in(pt).S);
			}
			debug("\n");
			for (int i = 1; i < SZ(path[0]); i++) {
				PII lst = to_id_in(path[0][i - 1]);
				PII now = to_id_in(path[0][i]);
				for (int k = 0; k < 4; k++) {
					if (lst.F + dx[k] == now.F && lst.S + dy[k] == now.S) {
						putchar(sym[k]);
					}
				}
			}
			puts("");
		}
		else {
			puts("NO");
		}
	}
	return 0;
}
