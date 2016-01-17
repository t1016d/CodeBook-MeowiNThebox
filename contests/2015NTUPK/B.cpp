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

struct Trie{
	Trie* c[2];
	int cnt;
	int num;
	Trie(int num_): cnt(0), num(num_) {
		c[0]=c[1]=NULL;
	}
};

const int MAXN=100010;
const int MAXP=1<<30;
int n, p[MAXN];

int DFS(Trie* a,Trie* b) {
	if(!(a->num))
		return 0;
	int re=MAXP;
	bool great=0;
	if(a->c[0] && b->c[0])
		re=min(re,DFS(a->c[0],b->c[0])), great=1;
	if(a->c[1] && b->c[1])
		re=min(re,DFS(a->c[1],b->c[1])), great=1;
	if(!great)
		for(int i=0;i<2;i++)
			if(a->c[i] && b->c[i^1])
				re=min(re,DFS(a->c[i],b->c[i^1]) | a->num);
	return re;
}

ll f(Trie* g) {
	if(g->cnt==1)
		return 0;
	ll ans=0;
	for(int i=0;i<2;i++)
		if(g->c[i])
			ans+=f(g->c[i]);
	if(g->c[0] && g->c[1]) {
		ans+=(DFS(g->c[0],g->c[1]) | g->num);
	}
	return ans;
}

int main() {
	Trie* root=new Trie(MAXP);
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",p+i);
	sort(p,p+n);

	for(int i=0;i<n;i++) {
		if(i && p[i]==p[i-1])
			continue;
		int t=MAXP;
		Trie* at=root;
		at->cnt++;
		while(t) {
			int s=__builtin_popcount(p[i]&t);
			if(!at->c[s])
				at->c[s]=new Trie(t/2);
			at=at->c[s];
			at->cnt++;
			t/=2;
		}
	}

	printf("%lld\n",f(root));
	return 0;
}
