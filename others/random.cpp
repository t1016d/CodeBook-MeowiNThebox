const int seed=1;

mt19937 rng(seed);
int randint(int lb,int ub) { // [lb, ub]
	return uniform_int_distribution<int>(lb,ub)(rng);
}

