//Tudor Cristian-Andrei 311CA
#include <stdio.h>
#include <math.h>

long long convert_octal_to_decimal(long long n)
{	int p = 0;
	long long decimal = 0;

	while (n != 0) {
		decimal += (n % 10) * pow(8, p);
		n = n / 10;
		p++;
	}

	return decimal;
}

int main(void)
{	int n, i;
	long long ai, bi;
	unsigned long long ps = 0;
	long long a_max, b_max;
	a_max = -1;
	b_max = -1;
	long long a_second_max, b_second_max;
	a_second_max = -1;
	b_second_max = -1;
	double n_a, n_b;
	n_a = 0;
	n_b = 0;

	scanf("%d", &n);
	//pentru ca elementele nu se memoreaza intr-un vector pot sa plec de la 1
	for (i = 1; i <= n; i++) {
		scanf("%lld %lld", &ai, &bi);
		ai = convert_octal_to_decimal(ai);
		bi = convert_octal_to_decimal(bi);

		if (ai > a_second_max && ai < a_max) {
			a_second_max = ai;
		} else if (ai > a_max) {
			a_second_max = a_max;
			a_max = ai;
		}

		if (bi > b_second_max && bi < b_max) {
			b_second_max = bi;
		} else if (bi > b_max) {
			b_second_max = b_max;
			b_max = bi;
		}

		ps += ai * bi;
		n_a = n_a + (unsigned long long)(ai * ai);
		n_b = n_b + (unsigned long long)(bi * bi);
	}

	printf("%llu\n", ps);
	printf("%lld %lld\n", a_second_max, b_second_max);
	printf("%.7lf %.7lf\n", sqrt(n_a), sqrt(n_b));

	return 0;
}
