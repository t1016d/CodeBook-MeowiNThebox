#include <bits/stdc++.h>
#define PB push_back
#define MP make_pair
#define F first
#define S second
#define SZ(x) ((int)(x).size())
#define ALL(x) (x).begin(),(x).end()
#ifdef _DEBUG_
	#define debug(...) printf(__VA_ARGS__)
#else
	#define debug(...) (void)0
#endif
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
typedef vector<int> VI;

typedef ll tp;

const tp INF = 1e18;
struct coor {
	tp x, y;
	coor(tp _x=0, tp _y=0): x(_x), y(_y) {}
	coor operator+(const coor p) const {
		return coor(x+p.x, y+p.y);
	}
	coor operator-(const coor p) const {
		return coor(x-p.x, y-p.y);
	}
	coor operator*(const tp c) const {
		return coor(x*c, y*c);
	}
	tp operator*(const coor p) const {
		return x*p.x + y*p.y;
	}
	tp operator%(const coor p) const {
		return x*p.y - y*p.x;
	}
	bool operator==(const coor p) const {
		return x==p.x and y==p.y;
	}
	bool operator<(const coor p) const {
		if(x!=p.x)
			return x<p.x;
		return y<p.y;
	}
	void input() {
		scanf("%lld%lld", &x, &y);
	}
};

coor perp(coor p) {
	return coor(-p.y, p.x);
}

typedef vector<coor> VP;

VP CH(VP arr, bool keep=false) {
	sort(ALL(arr));
	VP upper, lower;
	for(int i=0; i<SZ(arr); i++) {
		if(i>0 and arr[i] == arr[i-1])
			continue;
		coor c = arr[i];
		while(SZ(upper)>=2) {
			int last = SZ(upper)-1;
			coor a = upper[last-1], b=upper[last];
			if((c-a)%(b-a)<0 or (!keep and (c-a)%(b-a)<=0))
				upper.pop_back();
			else
				break;
		}
		upper.PB(c);
		while(SZ(lower)>=2) {
			int last=SZ(lower)-1;
			coor a = lower[last-1], b=lower[last];
			if((c-a)%(b-a) > 0 or (!keep and (c-a)%(b-a)>=0))
				lower.pop_back();
			else
				break;
		}
		lower.PB(c);
	}
	for(int i=SZ(upper)-2; i>0; i--)
		lower.PB(upper[i]);
	return lower;
}

int n;

int prv(int i) {
	return (i+n-1)%n;
}
int nxt(int i) {
	return (i+1)%n;
}

bool flat(int i, const VP &cv) {
	coor v1 = cv[nxt(i)]-cv[i];
	coor v2 = cv[prv(i)]-cv[i];
	return v1%v2==0;
}

// vec: normal vector
bool check(int nl, int nr, const coor vec, const VP &cv) {
	int nlp = prv(nl);
	bool fl=false, fr=false;
	if((cv[nlp]-cv[nl])*vec > 0) {
		fl=true;
		nl = nlp;
		while(nl != nr && flat(nl, cv))
			nl = prv(nl);
	}
	int nrp = nxt(nr);
	if((cv[nrp]-cv[nr])*vec > 0) {
		fr=true;
		nr = nrp;
		while(nl != nr && flat(nr, cv))
			nr = nxt(nr);
	}
	if(nl==nr)
		return true;
	else if(nl==nxt(nr)) {
		coor vl = cv[nxt(nl)]-cv[nl];
		coor vr = cv[prv(nr)]-cv[nr];
		return !fl||!fr||vl%vr>0;
	} else
		return false;
}

VP pnts;
int main() {
	while(scanf("%d", &n) != EOF) {
		if(!n)
			break;
		pnts.clear();
		for(int i=0; i<n; i++) {
			coor p;
			p.input();
			pnts.PB(p);
		}
		if(n<=3) {
			puts("YES");
			continue;
		}
		bool colin=true;
		for(int i=0; i<n; i++)
			if(!flat(i, pnts)) {
				colin=false;
				break;
			}
		if(colin) {
			puts("YES");
			continue;
		}
		VP cv1 = CH(pnts, false);
		VP cv2 = CH(pnts, true);
		assert(SZ(cv2)<=n);
		debug("|| %d %d\n", SZ(cv1), SZ(cv2));
		if(SZ(cv2) < n) {
			puts("NO");
			continue;
		}
		if(SZ(cv1) <= 3) {
			puts("YES");
			continue;
		}
		int nl=-1, nr=-1;
		for(int i=0; i<n; i++) {
			if(flat(i, cv2)) {
				for(nl=prv(i); ; nl=prv(nl))
					if(!flat(nl, cv2))
						break;
				for(nr=nxt(i); ; nr=nxt(nr))
					if(!flat(nr, cv2))
						break;
			}
		}
		if(nl<0) {
			debug("small\n");
			if(n>6) {
				puts("NO");
				continue;
			}
			bool ans=false;
			for(int i=0; i<n; i++) {
				int np = nxt(i);
				coor vec = perp(cv2[np]-cv2[i]);
				if(check(prv(i), nxt(np), vec, cv2)) {
					debug("### %d\n", i);
					ans = true;
					break;
				}
			}
			puts(ans ? "YES" : "NO");
		} else {
			debug("large\n");
			debug("&&& %d %d\n", nl, nr);
			coor vec = perp(cv2[nr]-cv2[nl]);
			for(int i=nl; i!=nr; i=nxt(i))
				assert(vec*(cv2[i]-cv2[nl])==0);
			nl = prv(nl);
			nr = nxt(nr);
			bool ans = check(nl, nr, vec, cv2);
			puts(ans ? "YES" : "NO");
		}
	}
	return 0;
}
