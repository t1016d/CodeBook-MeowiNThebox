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

const int MAXN = 100000 + 10;

struct SplayTree {
	int val, mx, ch[2], pa;
	bool rev;
	void init() {
		val = mx = -1;
		rev = false;
		pa = ch[0] = ch[1] = 0;
	}
} node[MAXN*2];

inline bool isroot(int x) {
	return node[node[x].pa].ch[0]!=x && node[node[x].pa].ch[1]!=x;
}

inline void pull(int x) {
	node[x].mx = max(node[x].val, max(node[node[x].ch[0]].mx, node[node[x].ch[1]].mx));
}

inline void push(int x) {
	if(node[x].rev) {
		node[node[x].ch[0]].rev ^= 1;
		node[node[x].ch[1]].rev ^= 1;
		swap(node[x].ch[0], node[x].ch[1]);
		node[x].rev ^= 1;
	}
}

void push_all(int x) {
	if(!isroot(x))	push_all(node[x].pa);
	push(x);
}

inline void rotate(int x) {
	int y = node[x].pa, z = node[y].pa, d = node[y].ch[1]==x;
	node[x].pa = z;
	if(!isroot(y))	node[z].ch[node[z].ch[1]==y] = x;
	node[y].ch[d] = node[x].ch[d^1];
	node[node[x].ch[d^1]].pa = y;
	node[x].ch[!d] = y;
	node[y].pa = x;
	pull(y);
	pull(x);
}

void splay(int x) {
	push_all(x);
	while(!isroot(x)) {
		int y = node[x].pa;
		if(!isroot(y)) {
			int z = node[y].pa;
			if((node[z].ch[1]==y) ^ (node[y].ch[1]==x))	rotate(y);
			else	rotate(x);
		}
		rotate(x);
	}
}

inline int access(int x) {
	int last = 0;
	while(x) {
		splay(x);
		node[x].ch[1] = last;
		pull(x);
		last = x;
		x = node[x].pa;
	}
	return last;
}

inline void make_root(int x) {
	node[access(x)].rev ^= 1;
	splay(x);
}

inline void link(int x, int y) {
	make_root(x);
	node[x].pa = y;
}

inline void cut(int x, int y) {
	make_root(x);
	access(y);
	splay(y);
	node[y].ch[0] = 0;
	node[x].pa = 0;
}

inline void cut_parent(int x) {
	x = access(x);
	splay(x);
	node[node[x].ch[0]].pa = 0;
	node[x].ch[0] = 0;
	pull(x);
}

inline int find_root(int x) {
	x = access(x);
	while(node[x].ch[0])	x = node[x].ch[0];
	splay(x);
	return x;
}

int find_mx(int x) {
	if(node[x].val == node[x].mx)	return x;
	return node[node[x].ch[0]].mx==node[x].mx ? find_mx(node[x].ch[0]) : find_mx(node[x].ch[1]);
}

inline void change(int x,int b){
		splay(x);
		node[x].data=b;
		up(x);
}
inline int query_lca(int u,int v){
/*retrun: sum of weight of vertices on the chain (u->v)
sum: total weight of the subtree
data: weight of the vertex */
	access(u);
	int lca=access(v);
	splay(u);
	if(u==lca){
		return node[lca].data+node[node[lca].ch[1]].sum;
	}else{
		return node[lca].data+node[node[lca].ch[1]].sum+node[u].sum;
	}
}
