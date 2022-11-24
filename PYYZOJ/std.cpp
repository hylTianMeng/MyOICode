#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
const int Mod = 998244353;

int g[100010], a[100010];
int fac[100010], inv[100010];
int C(int n, int k)
{
	return 1ll * fac[n] * inv[k] % Mod * inv[n - k] % Mod;
}
int fpow(int a, long long b)
{
	int ans = 1;
	while (b)
	{
		if (b & 1) ans = 1ll * ans * a % Mod;
		a = 1ll * a * a % Mod;
		b >>= 1;
	}
	return ans;
}
int A(int n)
{
	return fpow(2, 1ll * n * (n - 1) / 2);
}

void init(int n)
{
	fac[0] = 1;
	for (int i = 1; i <= n; i++)
		fac[i] = 1ll * fac[i - 1] * i % Mod;
	inv[n] = fpow(fac[n], Mod - 2);
	for (int i = n; i >= 1; i--)
		inv[i - 1] = 1ll * inv[i] * i % Mod;
	
	for (int i = 0; i <= n; i++)
		a[i] = A(i);
}

//fft 
int rev[400010];
void getrev(int bit)
{
	for (int i = 1; i < (1 << bit); i++)
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
}
void ntt(long long* a, int n, int dft)
{
	for (int i = 0; i < n; i++)
		if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int step = 1; step < n; step <<= 1)
	{
		long long wn = fpow(3, (Mod - 1) / (step << 1));
		if (dft == -1) wn = fpow(wn, Mod - 2);
		for (int i = 0; i < n; i += step << 1)
		{
			long long wnk = 1;
			for (int j = i; j < i + step; j++)
			{
				long long x = a[j];
				long long y = a[j + step] * wnk % Mod;
				a[j] = (x + y) % Mod;
				a[j + step] = (x - y + Mod) % Mod;
				wnk = wnk * wn % Mod;
			}
		}
	}
	if (dft == -1)
	{
		long long invn = fpow(n, Mod - 2);
		for (int i = 0; i < n; i++)
			a[i] = a[i] * invn % Mod;
	}
	return ;
}
long long c[400010];
void getInv(long long* a, long long* b, int n)
{
	if (n == 1)
	{
		b[0] = fpow(a[0], Mod - 2);
		return ;
	}
	getInv(a, b, (n + 1) >> 1);
	int s = 1, bit = 0;
	while (s < (n << 1)) s <<= 1, bit++;
	getrev(bit);
	for (int i = 0; i < s; i++)
		if (i < n)
			c[i] = a[i];
		else c[i] = 0;
	ntt(b, s, 1);
	ntt(c, s, 1);
	for (int i = 0; i < s; i++)
		b[i] = (2 - 1ll * b[i] * c[i] % Mod + Mod) % Mod * b[i] % Mod;
	ntt(b, s, -1);
	for (int i = n; i < s; i++)
		b[i] = 0;
	return ;
}

long long x[400010], y[400010];
void solve_g(int n)
{
	for (int i = 0; i <= n; i++)
		x[i] = 1ll * a[i] * inv[i] % Mod;
	getInv(x, y, n + 1);
	for (int i = 1; i <= n; i++)
		g[i] = (Mod - y[i]) * fac[i] % Mod,printf("f[%d]=%d\n",i,g[i]);
}

long long p[400010], q[400010];
void getans(int n)
{
	for (int i = 0; i <= n; i++)
		x[i] = 1ll * a[i] * inv[i] % Mod;
	for (int i = 0; i <= n; i++)
		y[i] = 1ll * a[i] * inv[i] % Mod * i % Mod;
	int s = 1, bit = 0;
	while (s < ((n + 1) << 1)) s <<= 1, bit++;
	getrev(bit);
	ntt(x, s, 1);
	ntt(y, s, 1);
	for (int i = 0; i < s; i++)
	{
		p[i] = x[i] * x[i] % Mod;
		q[i] = x[i] * y[i] % Mod;
	}
	ntt(p, s, -1);
	ntt(q, s, -1);
	for(int i=0;i<s;i++){
		printf("G1[%d]=%d\n",i,p[i]);
		printf("G2[%d]=%d\n",i,q[i]);
	}
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		ans = (ans + 1ll * g[i] * inv[i - 1] % Mod * q[n - i] % Mod * fac[n - 1]) % Mod;
		ans = (ans + 1ll * g[i] * inv[i - 1] % Mod * p[n - i] % Mod * i % Mod * fac[n - 1]) % Mod;
	}
	printf("%d\n", ans);
}

void solve(int n)
{
	init(n);
	solve_g(n);
//	for (int i = 1; i <= n; i++)
//		printf("%d\n", g[i]);
	getans(n);
}

int main()
{
	freopen("my.in", "r", stdin);
	freopen("std.out", "w", stdout);
	int n;
	scanf("%d", &n);
	
	solve(n);
	
	fclose(stdin); fclose(stdout);
	return 0;
}
