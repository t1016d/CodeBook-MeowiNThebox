typedef complex<double> CD;

const double PI=acos(-1.0);
inline CD ang(double t) { return CD(cos(t), sin(t)); }

int rev_int(int x,int lgn) {
	int re=0;
	for(int i=0;i<lgn;i++) {
		re=(re<<1)+(x&1);
		x>>=1;
	}
	return re;
}
void fft(CD* A, int lgn, bool inv=false) {
	int n=1<<lgn;
	for(int i=0;i<n;i++)
		if(i<rev_int(i, lgn)) swap(A[i], A[rev_int(i, lgn)]);
	for(int i=1;i<n;i*=2) {
		CD W(1.0, 0.0), Wn;
		if(inv) Wn=ang(-PI/i);
		else Wn=ang(PI/i);
		for(int j=0;j<n;j++) {
			if(j&i) {
				W=CD(1.0, 0.0);
				continue;
			}
			CD x=A[j], y=A[j+i]*W;
			A[j]=x+y;
			A[j+i]=x-y;
			W*=Wn;
		}
	}
	if(inv)
		for(int i=0;i<n;i++)
			A[i]/=n;
}
