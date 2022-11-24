#include "Spy.h"
#include<bits/stdc++.h>
#define mset(a,b) memset((a),(b),sizeof((a)))
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
#define dec(i,l,r) for(int i=(r);i>=(l);i--)
#define cmax(a,b) (((a)<(b))?(a=b):(a))
#define cmin(a,b) (((a)>(b))?(a=b):(a))
#define Next(k) for(int x=head[k];x;x=li[x].next)
#define vc vector
#define ar array
#define pi pair
#define fi first
#define se second
#define mp make_pair
#define pb push_back
using namespace std;

typedef double dd;
typedef long double ld;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
//#define int long long
typedef pair<int,int> P;
typedef vector<int> vi;

const int INF=0x3f3f3f3f;
const dd eps=1e-9;

template<typename T> inline void read(T &x) {
	x=0; int f=1;
	char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0';
	x*=f;
}

namespace {
	bool p_b_peng_bei() {
		return true;
	}
}

std::string SpySolve(int N, int M, int Q, int K, std::vector <int> U, std::vector <int> V, std::vector <long long> W, std::vector <int> S, std::vector <int> T, std::vector <int> E) {

}
