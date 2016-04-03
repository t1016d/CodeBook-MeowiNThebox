const int SASIZE=100020;  // >= (max length of string + 20)
struct SA{
	char S[SASIZE]; // put target string into S[0:(len-1)]
	// you can change the type of S into int if required
	// if the string is in int, please avoid number < 0
	int R[SASIZE*2],SA[SASIZE];
	int tR[SASIZE*2],tSA[SASIZE];
	int cnt[SASIZE],len;      // set len before calling build()
	int H[SASIZE];

	void build_SA() {
		int maxR=0;
		for(int i=0;i<len;i++)
			R[i]=S[i];
		for(int i=0;i<=len;i++)
			R[len+i]=-1;
		memset(cnt,0,sizeof(cnt));
		for(int i=0;i<len;i++)
			maxR=max(maxR,R[i]);
		for(int i=0;i<len;i++)
			cnt[R[i]+1]++;
		for(int i=1;i<=maxR;i++)
			cnt[i]+=cnt[i-1];
		for(int i=0;i<len;i++)
			SA[cnt[R[i]]++]=i;
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
		}
	}
	void build_H() {
		memset(H,0,sizeof(int)*(len+10));
		for(int i=0;i<len;i++)
		{
			if(R[i]==0)
				continue;
			int &t=H[R[i]];
			if(i>0)
				t=max(0,H[R[i-1]]-1);
			while(S[i+t]==S[SA[R[i]-1]+t]) t++;
		}
	}
}sa;
