//      1   1
// H =  1  -1
//      /sqrt(2)
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
