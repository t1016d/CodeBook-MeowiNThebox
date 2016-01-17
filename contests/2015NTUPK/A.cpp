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

char s[MAXN];
int ans[20][MAXN];
VI vec[4];


int main() {
	scanf("%s", s);
	int n = strlen(s);

	char str[5] = "easy";
	for(int i=0;i<n;i++)
		for(int j=0;j<4;j++)
			if(s[i]==str[j]) {
				vec[j].PB(i);
				break;
			}
	for(int j=0;j<4;j++)
		vec[j].PB(n);
	
	for(int u:vec[0]) {
		int e,a,s,y;
		e=*lower_bound(ALL(vec[0]),u);
		a=*lower_bound(ALL(vec[1]),e);
		s=*lower_bound(ALL(vec[2]),a);
		y=*lower_bound(ALL(vec[3]),s);
		ans[0][u]=y;
	}
	ans[0][n]=n;
	for(int i=n-1;i>=0;i--)
		if(ans[0][i]==0)
			ans[0][i]=ans[0][i+1];

	for(int i=0;i<n;i++)
		debug("%d: %d\n",i,ans[0][i]);
	for(int i=1;i<20;i++)
		for(int j=0;j<=n;j++) {
			ans[i][j]=ans[i-1][ans[i-1][j]];
		}

	int q;
	scanf("%d", &q);
	while(q--) {
		int l, r;
		scanf("%d%d", &l, &r);
		l--;
		r--;
		int at=l;
		int tmp=0;
		for(int i=19;i>=0;i--) {
			debug("%d %d\n",i,at);
			if(ans[i][at]<=r) {
				tmp+=(1<<i);
				at=ans[i][at];
			}
		}

		printf("%d\n",tmp);
	}

	return 0;
}
