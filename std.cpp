#include<cstdio>
#include<cstring>
#include<algorithm>
#define RG 
#define file(x) freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout)

namespace IO
{
	const int BUFSIZE = 1 << 20;
	char ibuf[BUFSIZE], *is = ibuf, *it = ibuf;
	inline char getchar() { if (is == it) it = (is = ibuf) + fread(ibuf, 1, BUFSIZE, stdin); return *is++; }
}

inline int read()
{
	int data = 0, w = 1;
	char ch = IO::getchar();
	while(ch != '-' && (ch < '0' || ch > '9')) ch = IO::getchar();
	if(ch == '-') w = -1, ch = IO::getchar();
	while(ch >= '0' && ch <= '9') data = data * 10 + (ch ^ 48), ch = IO::getchar();
	return data * w;
}

const int maxn(600010);
int n, m, cur, fa[maxn], C[maxn], deg[maxn], rt[maxn];
struct node { int lson, rson, dis; long long x; } t[maxn];
long long ans;

int merge(int x, int y)
{
	if(!x || !y) return x | y;
	if(t[x].x < t[y].x) std::swap(x, y);
	t[x].rson = merge(t[x].rson, y);
	if(t[t[x].lson].dis < t[t[x].rson].dis) std::swap(t[x].lson, t[x].rson);
	if(!t[x].rson) t[x].dis = 0; else t[x].dis = t[t[x].rson].dis + 1;
	return x;
}

inline int pop(int x) { return merge(t[x].lson, t[x].rson); }
int main()
{
	freopen("my.in","r",stdin);
	freopen("std.out","w",stdout);
	n = read(), m = read();
	for(RG int i = 2; i <= n + m; i++)
		++deg[fa[i] = read()], ans += (C[i] = read());
	for(RG int i = n + m; i > 1; i--)
	{
		long long l = 0, r = 0;
		if(i <= n)
		{
			while(--deg[i]) rt[i] = pop(rt[i]);
			r = t[rt[i]].x, rt[i] = pop(rt[i]);
			l = t[rt[i]].x, rt[i] = pop(rt[i]);
		}
		t[++cur].x = l + C[i], t[++cur].x = r + C[i];
		rt[i] = merge(rt[i], merge(cur, cur - 1));
		rt[fa[i]] = merge(rt[fa[i]], rt[i]);
	}
	while(deg[1]--) rt[1] = pop(rt[1]);
	while(rt[1]) ans -= t[rt[1]].x, rt[1] = pop(rt[1]);
	printf("%lld\n", ans);
	return 0;
}
