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

int main() {
	int N, M;
	while (scanf("%d%d", &N, &M) == 2 && N > 0) {
		if (N == M) {
			puts("YES");
			for (int i = 1; i < N; i++)
				printf("%d %d\n", i, i + 1);
			printf("%d %d\n", N, 1);
		}
		else if (M == N * (N - 1) / 2) {
			puts("YES");
			for (int i = 1; i <= N; i++)
				for (int j = i + 1; j <= N; j++)
					printf("%d %d\n", i, j);
		}
		else if (N % 2 == 0 && M == (N / 2) * (N / 2)) {
			puts("YES");
			for (int i = 1; i <= N; i += 2)
				for (int j = 2; j <= N; j += 2)
					printf("%d %d\n", i, j);
		}
		else {
			puts("NO");
		}
	}
	return 0;
}
