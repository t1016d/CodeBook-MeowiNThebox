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
	while (T--) {
		clear(root);
		/** do something **/
	}
	return 0;
}
