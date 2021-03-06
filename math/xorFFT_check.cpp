#include <stdio.h>
#include <stdlib.h>

#include <vector>

#define SZ(x) ((int)(x).size())

using namespace std;

typedef long long ll;

vector<ll> FWHT(vector<ll> P, bool inverse) {
	for(int len = 1; 2 * len <= SZ(P); len <<= 1) {
		for(int i = 0; i < SZ(P); i += 2 * len) {
			for(int j = 0; j < len; j++) {
				ll u = P[i + j];
				ll v = P[i + len + j];
				P[i + j] = u + v;
				P[i + len + j] = u - v;
			}
		}
	}
	if (inverse) {
		for (int i = 0; i < SZ(P); i++)
			P[i] = P[i] / SZ(P);
	}
	return P;
}


int main()
{
	int n=1<<15;
	vector<ll> P(n),Q(n);
	vector<ll> PQ(n);
	vector<ll> ans(n);
	for(int i=0; i<n; i++){
		P[i] = rand()%1000;
		Q[i] = rand()%1000;
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			ans[i^j] += P[i]*Q[j];
		}
	}
	P = FWHT(P,false);
	Q = FWHT(Q,false);
	for(int i=0; i<n; i++)
		PQ[i] = P[i]*Q[i];
	PQ = FWHT(PQ,true);
	bool pass=true;
	for(int i=0; i<n; i++)
		if(PQ[i]!=ans[i])
			pass=false;
	puts(pass?"AC":"WA");
	return 0;
}

