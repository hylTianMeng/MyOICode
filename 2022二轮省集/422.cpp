#include<bits/stdc++.h>
#define mset(a,b) memset((a),(b),sizeof((a)))
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
#define dec(i,l,r) for(int i=(r);i>=(l);i--)
#define inc(a,b) (((a)+(b))>=mod?(a)+(b)-mod:(a)+(b))
#define sub(a,b) (((a)-(b))<0?(a)-(b)+mod:(a)-(b))
#define mul(a,b) 1ll*(a)*(b)%mod
#define sgn(a) (((a)&1)?(mod-1):1)
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
#define N number
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

int t;
ll p;

inline int ksm(int a,int b,int mod){
    int res=1;while(b){if(b&1) res=1ll*res*a%mod;a=1ll*a*a%mod;b>>=1;}return res;
}
inline int Calc(int p,int e){
    // printf("p=%d e=%d\n",p,e);
    return 1ll*ksm(p,2*e-1,mod)*((1ll*ksm(p,e,mod)*(p+1)%mod-1+mod)%mod)%mod;
}
inline int Solve(ll x){
    ll i=2;int ans=1;
    for(;i*i<=x;i++){
        if(x%i) continue;
        int cnt=0;while(x%i==0) cnt++,x/=i;
        ans=1ll*ans*Calc(i,cnt)%mod;
    }
    if(x!=1) ans=1ll*ans*Calc(x%mod,1)%mod;
    return ans;
}
signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(t);
    while(t--){
        read(p);p--;
        int ans=Solve(p);
        p%=mod;ans=(ans+1ll*p*p%mod)%mod;
        printf("%lld\n",ans);
    }
    return 0;
}