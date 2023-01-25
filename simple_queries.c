//Tudor Cristian-Andrei 311CA
#include <stdio.h>
#define ALPH 26

void initialize_ascii(int v[ALPH])
{
	for (int i = 0; i < 26; i++)
		v[i] = i + 97;
}

int islwr(char c)
{
	if ('a' <= c && c <= 'z')
		return 1;
	else
		return 0;
}

int isqrry(char c)
{
	if (c == 'Q' || c == 'T' || c == 'E')
		return 1;
	else
		return 0;
}

void delete_element(char c, int ascii[ALPH], int freq[ALPH])
{
	for (int i = 0; i < 26; i++) {
		if (ascii[i] == (int)c)
			freq[i] = 0;
	}
}

int find_element(char c, int ascii[ALPH])
{
	for (int i = 0; i < 26; i++) {
		if (ascii[i] == (int)c)
			return i;
	}
	return -1;
}

void sort_frequency(int v[ALPH], int ascii[ALPH])
{
	int max, index;
	for (int i = 0; i < 25; i++) {
		max = v[i];
		index = i;
		for (int j = i + 1; j < 26; j++) {
			if (v[j] > max) {
				max = v[j];
				index = j;
			}
		}
		if (max > v[i]) {
			int aux = v[i];
			v[i] = v[index];
			v[index] = aux;

			aux = ascii[i];
			ascii[i] = ascii[index];
			ascii[index] = aux;
		}
	}
}

void sort_alpha(int freq[ALPH], int ascii[ALPH])
{
	for (int i = 0; i < 25; i++) {
		for (int j = i + 1; j < 26; j++) {
			if (freq[i] == freq[j] && ascii[i] > ascii[j]) {
				int aux = ascii[i];
				ascii[i] = ascii[j];
				ascii[j] = aux;

				aux = freq[i];
				freq[i] = freq[j];
				freq[j] = aux;
				// s - ar putea sa mearga fara
			}
		}
	}
}

int diff(int v[ALPH])
{
	int ok = 0;
	for (int i = 0; i < 26; i++) {
		if (v[i] != 0)
			ok++;
	}

	if (ok >= 2)
		return 1;
	else
		return 0;
}

int cmmdc(int a, int b)
{
	while (a != b) {
		if (a > b)
			a = a - b;
		else
			b = b - a;
	}
	return a;
}

int main(void)
{
	char ltr;
	int freq[ALPH] = {0};
	int ascii[ALPH];
	initialize_ascii(ascii);
	int n = 0;
	int ok_alert = 0;
	scanf("%c", &ltr);
	freq[ltr - 97]++;
	n++;
	ok_alert++;

	while (islwr(ltr) == 1 || isqrry(ltr) == 1) {
		if (ltr == 'E') {
			char e_input;
			getchar();
			scanf("%c", &e_input);
			int k = find_element(e_input, ascii);
			n = n - freq[k];
			delete_element(e_input, ascii, freq);
		}

		if (ltr == 'Q') {
			char q_input;
			getchar();
			scanf("%c", &q_input);
			printf("%c %d\n", q_input, freq[find_element(q_input, ascii)]);
		}

		if (ltr == 'T') {
			int k;
			getchar();
			scanf("%d", &k);
			sort_frequency(freq, ascii);
			sort_alpha(freq, ascii);
			for (int i = 0; i < k - 1; i++)
				printf("%c ", ascii[i]);
			printf("%c\n", ascii[k - 1]);
		}

		getchar();
		scanf("%c", &ltr);
		if (islwr(ltr) == 1) {
			for (int i = 0; i < 26; i++) {
				if (ascii[i] == (int)ltr)
					freq[i]++;
			}
			n++;
			ok_alert++;
			if (ok_alert >= 5 && diff(freq) == 1) {
				for (int i = 0; i < 26; i++) {
					if (freq[i] >= (float)n / 2) {
						int gcd = cmmdc(freq[i], n);
						int numerator = freq[i] / gcd;
						int denominator = n / gcd;
						printf("%c %d/%d\n", ascii[i], numerator, denominator);
						ok_alert = 0;
					}
				}
			}
		}
	}
}
