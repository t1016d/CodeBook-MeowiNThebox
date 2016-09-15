const int MAXN=100050;
char s[MAXN];
int n; // n: string length

typedef pair<PII,int> PD;
vector<PD> pal;

int ch[MAXN][26], fail[MAXN], len[MAXN], cnt[MAXN];
int edp[MAXN];
int nid=1;
int new_node(int len_) {
	len[nid]=len_;
	return nid++;
}

void build_pa() {
	int odd_root=new_node(-1);
	int even_root=new_node(0);
	fail[even_root]=odd_root;
	int cur=even_root;
	for(int i=1;i<=n;i++) {
		while(1) {
			if(s[i-len[cur]-1] == s[i]) break;
			cur=fail[cur];
		}
		if(ch[cur][s[i]-'a']==0) {
			int nt=ch[cur][s[i]-'a']=new_node(len[cur]+2);
			int tmp=fail[cur];
			while(tmp && s[i-len[tmp]-1]!=s[i]) tmp=fail[tmp];
			if(tmp==0) fail[nt]=even_root;
			else {
				assert(ch[tmp][s[i]-'a']);
				fail[nt]=ch[tmp][s[i]-'a'];
			}
			edp[nt]=i;
		}
		cur=ch[cur][s[i]-'a'];
		cnt[cur]++;
	}
	for(int i=nid-1;i>even_root;i--) {
		cnt[fail[i]]+=cnt[i];
		pal.PB( MP( MP(edp[i]-len[i]+1, len[i]), cnt[i]) );
	}
}

