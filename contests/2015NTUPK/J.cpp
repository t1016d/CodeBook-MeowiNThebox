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

const int MAXN=200050;

int a[MAXN],b[MAXN],c[MAXN];
int at[MAXN],bt[MAXN];

int main() {
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++) {
		scanf("%d",a+i);
		at[a[i]]=i;
	}
	for(int i=0;i<n;i++) {
		scanf("%d",b+i);
		bt[b[i]]=i;
	}
	memset(c,-1,sizeof(c));
	int cnt=n;
	for(int s=n+n-2;s>=0 && cnt;s--) {
		for(int i=n-1;i>=0 && s-i<n;i--) {
			if(c[(at[i]+bt[s-i])%n]==-1) {
				c[(at[i]+bt[s-i])%n]=s;
				cnt--;
			}
		}
	}
	for(int i=0;i<n;i++)
		printf("%d%c",c[i]," \n"[i==n-1]);
	return 0;
}
