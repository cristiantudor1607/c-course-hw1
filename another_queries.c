//Tudor Cristian-Andrei 311CA
#include <stdio.h>
#define NMAX 20
#define line_condition (i <= x && x <= first_line + n)
#define column_condition (j <= y && y <= first_column + n)

void read_square_matrix(int m[NMAX * NMAX][NMAX * NMAX], int n)
{
	for (int i = 0; i < n * n; i++) {
		for (int j = 0; j < n * n; j++)
			scanf("%d", &m[i][j]);
	}
}

void querry_one(int line, int m[NMAX * NMAX][NMAX * NMAX], int n)
{
	int ok[n * n];
	for (int i = 0; i < n * n; i++)
		ok[i] = 1;

	for (int i = 0; i < n * n; i++) {
		for (int j = 0; j < n * n; j++) {
			if (m[line - 1][i] == j + 1)
				ok[j] = 0;
		}
	}

	for (int i = 0; i < n * n; i++)
		printf("%d ", ok[i]);
	printf("\n");
}

void querry_two(int column, int m[NMAX * NMAX][NMAX * NMAX], int n)
{
	int ok[n * n];
	for (int i = 0; i < n * n; i++)
		ok[i] = 1;
	for (int i = 0; i < n * n; i++) {
		for (int j = 0; j < n * n; j++) {
			if (m[i][column - 1] == j + 1)
				ok[j] = 0;
		}
	}

	for (int i = 0; i < n * n; i++)
		printf("%d ", ok[i]);
	printf("\n");
}

int get_column_start(int square, int n)
{
	int i = 0;
	int j = 0;
	while (i <= n * n && square != 0) {
		j = 0;
		while (j < n * n && square != 0) {
			square = square - 1;
			j = j + n;
		}
		i = i + n;
	}
	return j - n;
}

int get_line_start(int square, int n)
{
	int i = -n;
	int j = 0;
	while (i <= n * n && square != 0) {
		i = i + n;
		j = 0;
		while (j < n * n && square != 0) {
			square = square - 1;
			j = j + n;
		}
	}
	return i;
}

int get_square(int x, int y, int n)
{
	int square = 1;
	int ok = 1;
	while (ok != 0 && square <= n * n) {
		int first_line = get_line_start(square, n);
		int first_column = get_column_start(square, n);

		for (int i = first_line; i < first_line + n; i++) {
			for (int j = first_column; j < first_column + n; j++) {
				if (line_condition && column_condition) {
					return square;
					ok = 0;
				}
			}
		}
		square++;
	}
	return 0;
}

void querry_three(int square, int m[NMAX * NMAX][NMAX * NMAX], int n)
{
	int v[n * n];
	int ok[n * n];
	for (int i = 0; i < n * n; i++)
		ok[i] = 1;

	for (int i = 0; i < n * n; i++)
		v[i] = i + 1;
	int line = get_line_start(square, n);
	int column = get_column_start(square, n);

	for (int i = line; i < line + n; i++) {
		for (int j = column; j < column + n; j++) {
			for (int k = 0; k < n * n; k++)
				if (m[i][j] == v[k])
					ok[k] = 0;
		}
	}

	for (int i = 0; i < n * n; i++)
		printf("%d ", ok[i]);
	printf("\n");
}

void querry_four(int x, int y, int m[NMAX * NMAX][NMAX * NMAX], int n)
{
	int ok_line[n * n];
	int ok_column[n * n];
	int ok_square[n * n];
	int i_cell = x - 1;
	int j_cell = y - 1;
	for (int i = 0; i < n * n; i++) {
		ok_line[i] = 1;
		ok_column[i] = 1;
		ok_square[i] = 1;
	}

	for (int j = 0; j < n * n; j++) {
		for (int k = 0; k < n * n; k++) {
			if (m[i_cell][j] == k + 1)
				ok_column[k] = 0;
		}
	}

	for (int i = 0; i < n * n; i++) {
		for (int k = 0; k < n * n; k++) {
			if (m[i][j_cell] == k + 1)
				ok_line[k] = 0;
		}
	}

	int square = get_square(i_cell, j_cell, n);
	int line = get_line_start(square, n);
	int column = get_column_start(square, n);
	for (int i = line; i < line + n; i++) {
		for (int j = column; j < column + n; j++) {
			for (int k = 0; k < n * n; k++) {
				if (m[i][j] == k + 1)
					ok_square[k] = 0;
			}
		}
	}

	if (m[i_cell][j_cell] != 0) {
		for (int k = 0; k < n * n; k++)
			printf("0 ");
	} else {
		for (int k = 0; k < n * n; k++) {
			if (ok_square[k] == 1 && ok_line[k] == 1 && ok_column[k] == 1)
				printf("1 ");
			else
				printf("0 ");
		}
	}
	printf("\n");
}

int querry_six(int m[NMAX * NMAX][NMAX * NMAX], int n)
{
	int f_line[n * n][n * n];
	int f_col[n * n][n * n];
	int f_sq[n * n][n * n];
	for (int i = 0; i < n * n; i++) {
		for (int j = 0; j < n * n; j++) {
			f_line[i][j] = 0;
			f_col[i][j] = 0;
			f_sq[i][j] = 0;
		}
	}

	for (int i = 0; i < n * n; i++) {
		for (int j = 0; j < n * n; j++) {
			if (m[i][j] != 0)
				f_line[i][m[i][j] - 1]++;
		}
	}
	//pt linie salvez frecventa pe linii
	for (int j = 0; j < n * n; j++) {
		for (int i = 0; i < n * n; i++) {
			if (m[i][j] != 0)
				f_col[j][m[i][j] - 1]++;
		}
	}
	//pt coloane salvez frecventa pe linie
	for (int square = 1; square <= n * n; square++) {
		int line = get_line_start(square, n);
		int column = get_column_start(square, n);
		for (int i = line; i < line + n; i++) {
			for (int j = column; j < column + n; j++) {
				if (m[i][j] != 0)
					f_sq[square - 1][m[i][j] - 1]++;
			}
		}
	}

	for (int i = 0; i < n * n; i++) {
		for (int j = 0; j < n * n; j++) {
			if (f_sq[i][j] >= 2 || f_line[i][j] >= 2 || f_col[i][j] >= 2) {
				return 1;
				// 1 = invalid
			}
		}
	}

	for (int i = 0; i < n * n; i++) {
		for (int j = 0; j < n * n; j++) {
			if (f_sq[i][j] == 0 || f_line[i][j] == 0 || f_col[i][j] == 0) {
				return 0;
				//0 = se mai poate continua
			}
		}
	}
	return 2;
	// 2 joc castigat
}

int main(void)
{
	int sudoku[NMAX * NMAX][NMAX * NMAX];
	int n, m;
	int querr_number;
	scanf("%d%d", &n, &m);
	read_square_matrix(sudoku, n);
	for (int queries = 0; queries < m; queries++) {
		scanf("%d", &querr_number);
		if (querr_number == 1) {
			int x;
			scanf("%d", &x);
			querry_one(x, sudoku, n);
		}
		if (querr_number == 2) {
			int y;
			scanf("%d", &y);
			querry_two(y, sudoku, n);
		}
		if (querr_number == 3) {
			int z;
			scanf("%d", &z);
			querry_three(z, sudoku, n);
		}
		if (querr_number == 4) {
			int x, y;
			scanf("%d%d", &x, &y);
			querry_four(x, y, sudoku, n);
		}
		if (querr_number == 5) {
			int x, y, c;
			scanf("%d%d%d", &x, &y, &c);
			if (sudoku[x - 1][y - 1] == 0)
				sudoku[x - 1][y - 1] = c;
		}
		if (querr_number == 6) {
			int valid = querry_six(sudoku, n);
			printf("%d\n", valid);
		}
	}
}
