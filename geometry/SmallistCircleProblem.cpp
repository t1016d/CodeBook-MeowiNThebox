#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 1000000 + 10;

struct PT {
	double x, y;

	PT() {}
	PT(double x, double y):
		x(x), y(y) {}
	PT operator+(const PT &b) const {
		return (PT) {x+b.x, y+b.y};
	}
	PT operator-(const PT &b) const {
		return (PT) {x-b.x, y-b.y};
	}
	PT operator*(const double b) const {
		return (PT) {x*b, y*b};
	}
	PT operator/(const double b) const {
		return (PT) {x/b, y/b};
	}
	double operator%(const PT &b) const {
		return x*b.y - y*b.x;
	}

	double len() const {
		return sqrt(x*x + y*y);
	}
	PT T() const {
		return (PT) {-y, x};
	}
} p[N];

void update(PT a, PT b, PT c, PT &o, double &r) {
	if(c.x < 0.0)	o = (a+b) / 2.0;
	else {
		PT p1 = (a+b)/2.0, p2 = p1 + (b-a).T();
		PT p3 = (a+c)/2.0, p4 = p3 + (c-a).T();
		double a123 = (p2-p1)%(p3-p1), a124 = (p2-p1)%(p4-p1);
		if(a123 * a124 > 0.0)	a123 = -a123;
		else	a123 = abs(a123), a124 = abs(a124);
		o = (p4*a123 + p3*a124) / (a123 + a124);
	}
	r = (a-o).len();
}

int main() {
	srand(7122);

	int m, n;
	while(scanf("%d%d", &m, &n)) {
		if(!n && !m)	return 0;

		for(int i = 0; i < n; i++)	scanf("%lf%lf", &p[i].x, &p[i].y);

		for(int i = 0; i < n; i++)
			swap(p[i], p[rand() % (i+1)]);

		PT a = p[0], b = p[1], c(-1.0, -1.0), o = (a+b) / 2.0;
		double r = (a-o).len();
		for(int i = 2; i < n; i++) {
			if((p[i]-o).len() <= r)	continue;

			a = p[i];
			b = p[0];
			c = (PT) {-1.0, -1.0};
			update(a, b, c, o, r);
			for(int j = 1; j < i; j++) {
				if((p[j]-o).len() <= r)	continue;

				b = p[j];
				c = (PT) {-1.0, -1.0};
				update(a, b, c, o, r);

				for(int k = 0; k < j; k++) {
					if((p[k]-o).len() <= r)	continue;

					c = p[k];
					update(a, b, c, o, r);
				}
			}
		}

		printf("%.3f\n", r);
	}
}
