void Z_build(const char *S,int *Z) {
	Z[0]=0;
	int bst=0;
	for(int i=1;S[i];i++) {
		if(Z[bst]+bst<i) Z[i]=0;
		else Z[i]=min(Z[bst]+bst-i,Z[i-bst]);
		while(S[Z[i]]==S[i+Z[i]]) Z[i]++;
		if(Z[i]+i>Z[bst]+bst) bst=i;
	}
}
