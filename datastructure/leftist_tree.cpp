#include <bits/stdc++.h>
using namespace std;

struct Left {
	Left *l,*r;
	int v,h;
	Left(int v_) : v(v_), h(1), l(0), r(0) {}
};

int height(Left *p) { return p ? p -> h : 0 ; }

Left* combine(Left *a,Left *b) {
	if(!a || !b) return a ? a : b ;
	Left *p ;
	if( a->v > b->v) {
		p = a;
		p -> r = combine( p -> r , b );
	}
	else {
		p = b;
		p -> r = combine( p -> r , a );
	}
	if( height( p->l ) < height( p->r ) )
		swap( p->l , p->r );
	p->h = min( height( p->l ) , height( p->r ) ) + 1;
	return p;
}
Left *root;

void push(int v) {
	Left *p = new Left(v);
	root = combine( root , p );
}
int top() { return root? root->v : -1; }
void pop() {
	if(!root) return;
	Left *a = root->l , *b = root->r ;
	delete root;
	root = combine( a , b );
}
void clear(Left* &p) {
	if(!p)
		return;
	if(p->l) clear(p->l);
	if(p->r) clear(p->r);
	delete p;
	p = 0 ;
}

int main() {
	int T,n,x,o,size;
	bool bst,bqu,bpq;
	scanf("%d",&T);
	while(T--) {
		bst=bqu=bpq=1;
		stack<int> st;
		queue<int> qu;
		clear(root);
		size=0;
		scanf("%d",&n);
		while(n--) {
			scanf("%d%d",&o,&x);
			if(o==1)
				st.push(x),qu.push(x),push(x),size++;
			else if(o==2) {
				size--;
				if(size<0)
					bst=bqu=bpq=0;
				if(bst) {
					if(st.top()!=x)
						bst=0;
					st.pop();
				}
				if(bqu) {
					if(qu.front()!=x)
						bqu=0;
					qu.pop();
				}
				if(bpq) {
				//	printf("(%d)\n",top());
					if(top()!=x)
						bpq=0;
					pop();
				}
			}
		}
		int count=0;
		if(bst)
			count++;
		if(bqu)
			count++;
		if(bpq)
			count++;
	
		if(count>1)
			puts("not sure");
		else if(count==0)
			puts("impossible");
		else if(bst)
			puts("stack");
		else if(bqu)
			puts("queue");
		else if(bpq)
			puts("priority queue");
	}
	return 0;
}
