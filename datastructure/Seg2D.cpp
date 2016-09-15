struct Seg1D {
	Seg1D *tl, *tr;
	ll val;
	// ll tmp;
	//int _x, _y;
	Seg1D() :
		tl(NULL), tr(NULL), val(0), tmp(-1), _x(-1), _y(-1) {}
	ll query1D(int x1, int x2, int y1, int y2, int l, int r) {
		/*
		if no Brian improvement, dont need to pass x1 and x2
		if(tmp >= 0) {
			if(x1<=_x&&_x<=x2 && y1<=_y&&_y<=y2)	return tmp;
			else	return 0;
		}
		*/
		if(y1 <= l && r <= y2)	return val;
		else if(r < y1 || y2 < l)	return 0;
		else {
			int m = (l+r)/2;
			ll a = tl ? tl->query1D(x1, x2, y1, y2, l, m) : 0,
			   b = tr ? tr->query1D(x1, x2, y1, y2, m+1, r) : 0;
			return gcd(a, b);
		}
	}
	void update1D(int x, int y, ll num, int l, int r) {
		if(l == r) {
			val = num;
			return ;
		}
		/*
		if(tmp < 0 && !tl && !tr) {
			tmp = val = num;
			_x = x;
			_y = y;
			return ;
		}
		else if(tmp >= 0) {
			int m = (l+r)/2;
			if(_y <= m) {
				if(!tl)	tl = new Seg1D();
				tl->update1D(_x, _y, tmp, l, m);
			}
			else {
				if(!tr)	tr = new Seg1D();
				tr->update1D(_x, _y, tmp, m+1, r);
			}
			tmp = _x = _y = -1;
		}*/
		int m = (l+r)/2;
		if(y <= m) {
			if(!tl)	tl = new Seg1D();
			tl->update1D(x, y, num, l, m);
		}
		else {
			if(!tr)	tr = new Seg1D();
			tr->update1D(x, y, num, m+1, r);
		}
		ll a = tl ? tl->val : 0;
		ll b = tr ? tr->val : 0;
		val = gcd(a, b);
	}
};
struct Seg2D {
	Seg2D *tl, *tr;
	Seg1D *t2;
	Seg2D() :
		tl(NULL), tr(NULL), t2(NULL) {}
	ll query2D(int x1, int x2, int y1, int y2, int l, int r) {
		if(x1 <= l && r <= x2) {
			if(!t2)	t2 = new Seg1D();
			return t2->query1D(x1, x2, y1, y2, 0, C-1);
		}
		else if(x2 < l || r < x1)	return 0;
		else {
			int m = (l+r)/2;
			ll a = tl ? tl->query2D(x1, x2, y1, y2, l, m) : 0,
			   b = tr ? tr->query2D(x1, x2, y1, y2, m+1, r) : 0;
			return gcd(a, b);
		}
	}
	void update2D(int x, int y, ll num, int l, int r) {
		int m = (l+r)/2;
		if(l == r) {
			if(!t2)	t2 = new Seg1D();
			t2->update1D(x, y, num, 0, C-1);
			return ;
		}
		if(x <= m) {
			if(!tl)	tl = new Seg2D();
			tl->update2D(x, y, num, l, m);
		}
		else {
			if(!tr)	tr = new Seg2D();
			tr->update2D(x, y, num, m+1, r);
		}
		if(!tl)	tl = new Seg2D();
		if(!tr)	tr = new Seg2D();
		ll a = tl->t2 ? tl->t2->query1D(l, m, y, y, 0, C-1) : 0,
		   b = tr->t2 ? tr->t2->query1D(m+1, r, y, y, 0, C-1) : 0;
		if(!t2)	t2 = new Seg1D();
		t2->update1D(x, y, gcd(a, b), 0, C-1);
	}
};
