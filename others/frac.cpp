struct Frac {
	ll a,b; //  a/b
	void relax() {
		ll g=__gcd(a,b);
		if(g!=0 && g!=1)
			a/=g, b/=g;
		if(b<0)
			a*=-1, b*=-1;
	}
	Frac(ll a_=0,ll b_=1): a(a_), b(b_) {
		relax();
	}
	Frac operator + (Frac x) {
		relax();
		x.relax();
		ll g=__gcd(b,x.b);
		ll lcm=b/g*x.b;
		return Frac(a*(lcm/b)+x.a*(lcm/x.b),lcm);
	}
	Frac operator - (Frac x) {
		relax();
		x.relax();
		Frac t=x;
		t.a*=-1;
		return *this+t;
	}
	Frac operator * (Frac x) {
		relax();
		x.relax();
		return Frac(a*x.a,b*x.b);
	}
	Frac operator / (Frac x) {
		relax();
		x.relax();
		Frac t=Frac(x.b,x.a);
		return (*this)*t;
	}
	bool operator < (Frac x) {
		ll lcm=b/__gcd(b,x.b)*x.b;
		return ( (lcm/b)*a < (lcm/x.b)*x.a );
	}
};
