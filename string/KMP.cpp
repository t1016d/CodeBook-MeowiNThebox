void KMP_build(const char *S,int *F) {
	int p=F[0]=-1;
	for(int i=1;S[i];i++) {
		while(p!=-1 && S[p+1]!=S[i])
			p=F[p];
		if(S[p+1]==S[i])
			p++;
		F[i]=p;
	}
}

VI KMP_match(const char *S,const int *F,const char *T) {
	VI ans;
	int p=-1;
	for(int i=0;T[i];i++) {
		while(p!=-1 && S[p+1]!=T[i])
			p=F[p];
		if(S[p+1]==T[i])
			p++;
		if(!S[p+1]) {
			ans.PB(i-p);
			p=F[p];
		}
	}
	return ans;
}
