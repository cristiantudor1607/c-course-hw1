//Tudor Cristian-Andrei 311CA
#include <stdio.h>
#define NMAX 1000

void read_matrix(int m[][NMAX], int n)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			scanf("%d", &m[i][j]);
	}
}

int type(int i, int j)
{
	if ((i + j) % 2 == 0)
		return 1;
	else
		return -1;
	// 1 inseamna patrat alb, -1 inseamna patrat negru
}

int how_many_times(int n, int k)
{
	int nr = 0;
	while (n >= k) {
		nr++;
		n = n - k;
	}
	return nr;
}

void metoda_excel(int x)
{
	int v[26];
	int ascii = 65;
	for (int i = 0; i < 26; i++) {
		v[i] = ascii;
		ascii++;
	}

	if (x < 26)
		printf("%c\n", x + 65);

	if (26 <= x && x < 26 * 26) {
		int q = x % 26;
		int n = how_many_times(x, 26);
		printf("%c%c\n", v[n - 1], v[q]);
	}

	if (26 * 26 <= x && x < 26 * 26 * 26) {
		int q = x % 26;
		int n = how_many_times(x, 26 * 26);
		int mid = how_many_times(x, 26);
		printf("%c%c%c\n", v[n - 1], v[mid - 26], v[q]);
	}
}

int main(void)
{
	int ticket[NMAX][NMAX];
	int n, i, j;
	scanf("%d", &n);
	read_matrix(ticket, n);
	i = 0;
	j = 0;
	long long dist = 0;
	int pion = ticket[i][j];
	while (pion != 0) {
		if (type(i, j) == 1 && ticket[i][j] > 0) {
			dist = dist + ticket[i][j];
			int rest = ticket[i][j] % n;
			ticket[i][j] = 0;
			if (j + rest <= n - 1) {
				pion = ticket[i][j + rest];
				j = j + rest;
			} else if (j == n - 1) {
				pion = ticket[i][rest - 1];
				j = rest - 1;
			} else if (j + rest > n - 1) {
				int aux = n - 1 - j;
				rest = rest - aux;
				pion = ticket[i][rest - 1];
				j = rest - 1;
			}
		} else if (type(i, j) == 1 && ticket[i][j] < 0) {
			dist = dist + ticket[i][j] * (-1);
			int rest = ((-1) * ticket[i][j]) % n;
			ticket[i][j] = 0;
			if (j - rest >= 0) {
				pion = ticket[i][j - rest];
				j = j - rest;
			} else if (j == 0) {
				pion = ticket[i][n - rest];
				j = n - rest;
			} else if (j - rest < 0) {
				//int aux = j - 0;
				rest = rest - j;
				pion = ticket[i][n - rest];
				j = n - rest;
			}
		} else if (type(i, j) == -1 && ticket[i][j] > 0) {
			dist = dist + ticket[i][j];
			int rest = ticket[i][j] % n;
			ticket[i][j] = 0;
			if (i + rest <= n - 1) {
				pion = ticket[i + rest][j];
				i = i + rest;
			} else if (i == n - 1) {
				pion = ticket[rest - 1][j];
				i = rest - 1;
			} else if (i + rest > n - 1) {
				int aux = n - 1 - i;
				rest = rest - aux;
				pion = ticket[rest - 1][j];
				i = rest - 1;
			}
		} else if (type(i, j) == -1 && ticket[i][j] < 0) {
			dist = dist + ticket[i][j] * (-1);
			int rest = ((-1) * ticket[i][j]) % n;
			ticket[i][j] = 0;
			if (i - rest >= 0) {
				pion = ticket[i - rest][j];
				i = i - rest;
			} else if (i == 0) {
				pion = ticket[n - rest][j];
				i = n - rest;
			} else if (i - rest < 0) {
				//int aux = i - 0;
				rest = rest - i;
				pion = ticket[n - rest][j];
				i = n - rest;
			}
		}
	}

	printf("%llu\n", dist);
	printf("%d ", n - i);
	metoda_excel(j);
}
