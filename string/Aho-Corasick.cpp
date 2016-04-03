// AC code of UVa 10679
#include <cstdio>
#include <cstring>
#include <new>

struct Trie {
	int c;
	bool fi=0;
	Trie *fail,*ch[52];
	Trie():c(0){memset(ch,0,sizeof(ch));}
}trie[1000100];

char m[1010],f[100100];
Trie *str[1010],*na,*root;

inline int c_i(char a) {
	return (a>='A' && a<='Z') ? a-'A' : a-'a'+26;
}

void insert(char *s,int num) {
	Trie *at=root;
	while(*s) {
		if(!at->ch[c_i(*s)])
			at->ch[c_i(*s)]=new (na++) Trie();
		at=at->ch[c_i(*s)],s++;
	}
	str[num]=at;
}

Trie *q[1000100];
int ql,qr;

void init() {
	ql=qr=-1;
	q[++qr]=root;
	root->fail=NULL;
	while(ql<qr) {
		Trie *n=q[++ql],*f;
		for(int i=0;i<52;i++) {
			if(!n->ch[i])
				continue;
			f=n->fail;
			while(f && !f->ch[i])
				f=f->fail;
			n->ch[i]->fail=f?f->ch[i]:root;
			q[++qr]=n->ch[i];
		}
	}
}

void go(char *s) {
	Trie*p=root;
	while(*s) {
		while(p && !p->ch[c_i(*s)])
			p=p->fail;
		p=p?p->ch[c_i(*s)]:root;
		p->fi=1;
		s++;
	}
}

void AC() {
	for(int i=qr;i>0;i--)
		q[i]->fail->c+=q[i]->c;
}

int main() {
	int T,q;
	scanf("%d",&T);
	while(T--) {
		na=trie;
		root=new (na++) Trie();
		scanf("%s",f);
		scanf("%d",&q);
		for(int i=0;i<q;i++) {
			scanf("%s",m);
			insert(m,i);
		}
		init();
		go(f);
		for(int i=0;i<q;i++)
			puts(str[i]->fi?"y":"n");
	}
	return 0;
}
