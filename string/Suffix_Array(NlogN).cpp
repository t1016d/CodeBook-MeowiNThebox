// NTUJ448
#include <bits/stdc++.h>
#define pb push_back
#define F first
#define S second
#define SZ(x) ((int)(x).size())
#define MP make_pair
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
typedef vector<int> VI;

const int SASIZE=2500000;
char in[500];
int S[SASIZE],from[SASIZE];
int R[SASIZE],SA[SASIZE],H[SASIZE];
int tR[SASIZE],tSA[SASIZE];
int cnt[SASIZE];
int num[4010];

int main()
{
	int N;
	while(scanf("%d",&N)==1 && N)
	{
		int len=0,maxR=0;
		for(int i=0;i<N;i++)
		{
			scanf("%s",in);
			for(int j=0;in[j];j++)
			{
				from[len]=i;
				S[len++]=in[j]-'a';
			}
			from[len]=N;
			S[len++]=i+50;
		}
		memset(R,-1,sizeof(R));
		memset(cnt,0,sizeof(cnt));
		for(int i=0;i<len;i++)
		{
			R[i]=S[i];
			maxR=max(maxR,R[i]);
		}
		for(int i=0;i<len;i++)
			cnt[R[i]+1]++;
		for(int i=1;i<=maxR;i++)
			cnt[i]+=cnt[i-1];
		for(int i=0;i<len;i++)
			SA[cnt[R[i]]++]=i;
	/*	for(int i=0;i<len;i++)
			printf("R[%d]=%d, SA[%d]=%d\n",i,R[i],i,SA[i]);*/
		for(int i=1;i<len;i*=2)
		{
			memset(cnt,0,sizeof(int)*(maxR+10));
			memcpy(tSA,SA,sizeof(int)*(len+10));
			memcpy(tR,R,sizeof(int)*(len+i+10));
			for(int j=0;j<len;j++)
				cnt[R[j]+1]++;
			for(int j=1;j<=maxR;j++)
				cnt[j]+=cnt[j-1];
			for(int j=len-i;j<len;j++)
				SA[cnt[R[j]]++]=j;
			for(int j=0;j<len;j++)
			{
				int k=tSA[j]-i;
				if(k<0)
					continue;
				SA[cnt[R[k]]++]=k;
			}
			int num=0;
			maxR=0;
			R[SA[0]]=num;
			for(int j=1;j<len;j++)
			{
				if(tR[SA[j-1]]<tR[SA[j]] || tR[SA[j-1]+i]<tR[SA[j]+i])
					num++;
				R[SA[j]]=num;
				maxR=max(maxR,R[SA[j]]);
			}
		/*	puts("-------");
			for(int i=0;i<len;i++)
				printf("R[%d]=%d, SA[%d]=%d\n",i,R[i],i,SA[i]);*/
		}
		memset(H,0,sizeof(H));
		for(int i=0;i<len;i++)
		{
			if(R[i]==0)
				continue;
			int &t=H[R[i]];
			if(i>0)
				t=max(0,H[R[i-1]]-1);
			while(S[i+t]==S[SA[R[i]-1]+t]) t++;
		}
		/*for(int i=0;i<len;i++)
			printf("R[%d]=%d, SA[%d]=%d\n",i,R[i],i,SA[i]);
		for(int i=0;i<len;i++)
			printf("%3d %3d  %s\n",H[i],SA[i],S+SA[i]);*/
		/*for(int i=0;i<len;i++)
		{
			printf("%3d %3d %d|",H[i],SA[i],from[i]);
			for(int j=SA[i];j<len;j++)
				printf("%2d ",S[j]);
			puts("");
		}*/
		memset(num,0,sizeof(num));
		int anslen=0,ansfrom=-1;
		int get=0;
		deque<PII> deq;
	/*	for(int i=0;i<len;i++)
			printf("%d:%d\n",i,from[i]);*/
		for(int l=0,r=0;r<len;r++)
		{
			if(from[SA[r]]<N && num[from[SA[r]]]==0)
				get++;
			num[from[SA[r]]]++;
			while(deq.size()>0 && deq.back().F>=H[r]) deq.pop_back();
			deq.pb(MP(H[r],r));
			while(num[from[SA[l]]]>1)
			{
				num[from[SA[l]]]--;
				l++;
			}
			while(deq.size()>0 && deq.front().S<=l) deq.pop_front();
			if(get==N && deq.front().F>anslen)
				anslen=deq.front().F, ansfrom=SA[l];
		}
		//printf("(%d)\n",anslen);
		if(anslen==0)
			puts("IDENTITY LOST");
		else
		{
			for(int i=ansfrom;i<ansfrom+anslen;i++)
				putchar(S[i]+'a');
			puts("");
		}
	}
	return 0;
}
