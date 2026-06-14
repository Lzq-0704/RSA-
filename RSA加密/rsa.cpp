#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include "rsa.h"

unsigned long long p = -1, q = -1, e = -1, d = -1, n = -1, k = 1, F_n = -1;
int textlen = 0;
int x = 0, y = 0;
char w;

int sushu(unsigned long long i)
{
	if (i <= 1)
	{
		return 0;
	}
	unsigned long long a = 0, max = 1;
	switch (i)
	{
	case 2:
	case 3:
		return 1;
	default:
		if (i % 2 == 0)
		{
			return 0;
		}
		max = (unsigned long long)sqrt(1.0 * i) + 1;
		for (a = 3; a <= max; a += 2)
		{
			if (i % a == 0)
			{
				return 0;
			}
		}
	}
	return 1;
}

int mod(unsigned long long a, unsigned long long b, unsigned long long c)
{
	unsigned long long ans = 1;
	while (b > 0)
	{
		if (b % 2 == 1)
		{
			ans *= a;
			ans %= c;
		}
		a *= a;
		a %= c;
		b /= 2;
	}
	return ans;
}

int gcd(unsigned long long a, unsigned long long b) {
	if (b == 0) {
		return a;
	}
	else {
		return gcd(b, a % b);
	}
}
