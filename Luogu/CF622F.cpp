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
#define N 1000100
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
const int mod=1e9+7;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

int x[N],y[N],n,k,sum;
int jie[N],invjie[N];

inline int ksm(int a,int b,int mod){
    int res=1;while(b){if(b&1)res=1ll*res*a%mod;a=1ll*a*a%mod;b>>=1;}return res;
}
inline int inv(int x){return ksm(x,mod-2,mod);}
inline int Leg(int h){
    sum=1;rep(i,1,k+2) sum=1ll*sum*(h-x[i])%mod;
    rep(i,1,k+2) x[i]=sum*inv(h-x[i])%mod;
    int ans=0;
    rep(i,1,k+2){
        ans=(ans+y[i]*x[i]%mod*invjie[i-1]%mod*invjie[k+2-i]%mod*(((k+2-i)&1)?(mod-1):1)%mod)%mod;
    }
    return ans;
}

signed main(){
    read(n);read(k);jie[0]=1;
    rep(i,1,k+2) jie[i]=jie[i-1]*i%mod;invjie[k+2]=inv(jie[k+2]);
    dec(i,0,k+1) invjie[i]=invjie[i+1]*(i+1)%mod;
    rep(i,1,k+2){
        x[i]=i;y[i]=(ksm(i,k,mod)+y[i-1])%mod;
    }
    if(n<=k+2){
        printf("%lld\n",y[n]);
    }
    else{
        int ans=Leg(n);
        printf("%lld\n",ans%mod);
    }
    return 0;
}