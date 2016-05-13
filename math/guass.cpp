// be care of the magic number 7 & 8
void guass() {
	for(int i = 0; i < 7; i++) {
		Frac tmp = mat[i][i]; // Frac -> the type of data
		for(int j = 0; j < 8; j++)
			mat[i][j] = mat[i][j] / tmp;
		for(int j = 0; j < 7; j++) {
			if(i == j)
				continue;
			Frac ratio = mat[j][i]; // Frac -> the type of data
			for(int k = 0; k < 8; k++)
				mat[j][k] = mat[j][k] - ratio * mat[i][k];
		}
	}
}
