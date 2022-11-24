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
#define N 2010
#define M number
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
const int mod=998244353;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

int n,k,x[N],y[N],fenzi,fenmu;

inline int ksm(int a,int b,int mod){
    int res=1;while(b){if(b&1){res=1ll*res*a%mod;}a=1ll*a*a%mod;b>>=1;}return res;
}
inline int inv(int x){return ksm(x,mod-2,mod);}

int main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);read(k);
    rep(i,1,n) read(x[i]),read(y[i]);
    int ans=0;
    rep(i,1,n){
        int Ans=y[i];fenzi=1;fenmu=1;
        rep(j,1,n){
            if(i==j) continue;
            fenzi=1ll*fenzi*((k-x[j])%mod)%mod;
            fenmu=1ll*fenmu*((x[i]-x[j])%mod)%mod;
        }
        ans=(ans+1ll*Ans*fenzi%mod*inv(fenmu)%mod)%mod;
    }
    printf("%d\n",(ans+mod)%mod);
    return 0;
}