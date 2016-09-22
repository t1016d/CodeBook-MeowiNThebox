//    MOD     Wn_      LGN
//    5767169    177147 19
//    7340033      2187 20
// 2013265921 440564289 27
const int MOD=786433;
const int Wn_=5; // 25 625
const int LGN=18;// 17  16
inline int add(int x,int y) { return (x+y)%MOD; }
inline int mul(int x,int y) { return 1ll*x*y%MOD; }
inline int sub(int x,int y) { return (x-y+MOD)%MOD; }

int pW[MOD]; // power of Wn
int divN;
int inv(int a) {
	int re=1, k=MOD-2, t=a;
	while(k) {
		if(k%2) re=mul(re, t);
		k/=2;
		t=mul(t, t);
	}
	return re;
}
void NTTinit(int lgn) { // call every time using new lgn !
	int Wn=Wn_;
	for(int i=lgn;i<LGN;i++) Wn=mul(Wn,Wn);
	divN=inv(1<<lgn);
	pW[0]=1;
	for(int i=1;;i++) {
		pW[i]=mul(pW[i-1], Wn);
		if(pW[i]==1) break;
	}
}

int rev_int(int x,int lgn) {
	int re=0;
	for(int i=0;i<lgn;i++) {
		re=(re<<1)+(x&1);
		x>>=1;
	}
	return re;
}
void ntt(int *A,int lgn,bool inv=false) {
	int n=1<<lgn;
	for(int i=0;i<n;i++)
		if(i<rev_int(i,lgn))
			swap(A[i], A[rev_int(i,lgn)]);
	for(int i=1;i<n;i*=2) {
		int W=1, Wn;
		if(inv) Wn=pW[n-(n/2/i)];
		else Wn=pW[n/2/i];
		for(int j=0;j<n;j++) {
			if(j&i) {
				W=1;
				continue;
			}
			int x=A[j], y=mul(A[j+i],W);
			A[j]=add(x,y);
			A[j+i]=sub(x,y);
			W=mul(W,Wn);
		}
	}
	if(inv)
		for(int i=0;i<n;i++)
			A[i]=mul(A[i],divN);
}
