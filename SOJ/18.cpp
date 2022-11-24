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
#define N 10001001
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

int m,n,f[N],jie[N],invjie[N];

inline int ksm(int a,int b,int mod){
    int res=1;while(b){if(b&1){res=1ll*res*a%mod;}a=1ll*a*a%mod;b>>=1;}return res;
}
inline int inv(int x){return ksm(x,mod-2,mod);}

signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);read(m);
    f[0]=1;f[1]=n;
    jie[0]=1;rep(i,1,n) jie[i]=jie[i-1]*i%mod;
    invjie[n]=inv(jie[n]);dec(i,0,n-1) invjie[i]=invjie[i+1]*(i+1)%mod;
    rep(i,2,n) f[i]=((n-i+1)*f[i-1]%mod+(2*n-i+2)*f[i-2]%mod)%mod*invjie[i]%mod*jie[i-1]%mod;
    int la=m,lb=1;
    int ans=0;
    int suma=0,sumb=0;
    // puts("here");
    // rep(i,1,n){
    //     printf("f[n+i]=%lld f[n-i]=%lld\n",f[n+i],f[n-i]);
    //     // assert(f[n+i]==f[n-i]);
    // }
    rep(i,1,n){
        if(i&1){
            suma+=la*2;
            sumb+=lb*2;
            if(suma<=n) ans=(ans+f[n-suma])%mod;
            if(sumb<=n) ans=(ans+f[n-sumb])%mod;
        }
        else{
            suma+=lb*2;
            sumb+=la*2;
            if(suma<=n) ans=(ans-f[n-suma]+mod)%mod;
            if(sumb<=n) ans=(ans-f[n-sumb]+mod)%mod;
        }
    }
    ans=(f[n]-ans+mod)%mod;
    printf("%lld\n",ans);
    return 0;
}