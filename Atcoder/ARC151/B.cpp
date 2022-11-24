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
#define pb emplace_back
#define N 200010
#define M number
using namespace std;

typedef double dd;
typedef long double ld;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
#define int long long
typedef pair<int,int> P;
typedef vector<int> vi;

const int INF=0x3f3f3f3f;
const dd eps=1e-9;
const int mod=998244353;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

int n,m,p[N],pw[N],fa[N],inv2;

inline int fd(int x){return x==fa[x]?x:fa[x]=fd(fa[x]);}
inline int ksm(int a,int b,int mod){
    int res=1;while(b){if(b&1)res=1ll*res*a%mod;a=1ll*a*a%mod;b>>=1;}return res;
}
inline int inv(int x){return ksm(x,mod-2,mod);}

signed main(){
    read(n);read(m);rep(i,1,n) read(p[i]);
    pw[0]=1;
    rep(i,1,n) fa[i]=i;
    rep(i,1,n) pw[i]=pw[i-1]*m%mod;
    int siz=n;
    int ans=0;
    inv2=inv(2);
    rep(i,1,n){
        if(fd(i)==fd(p[i])) continue;
        ans=(ans+m*(m-1)%mod*inv2%mod*pw[siz-2])%mod;
        int fai=fd(i),fapi=fd(p[i]);
        fa[fai]=fapi;siz--;
    }
    printf("%lld\n",ans);
    return 0;
}