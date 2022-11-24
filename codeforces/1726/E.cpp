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
#define N 300010
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
const int Len=300000;
const int mod=998244353;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

int t,n,jie[N],invjie[N],I[N];

inline int ksm(int a,int b,int mod){
    int res=1;while(b){if(b&1)res=1ll*a*res%mod;a=1ll*a*a%mod;b>>=1;}return res;
}
inline int inv(int a){return ksm(a,mod-2,mod);}
inline int C(int n,int m){
    if(n<m) return 0;return jie[n]*invjie[m]%mod*invjie[n-m]%mod;
}

signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(t);
    jie[0]=1;rep(i,1,Len) jie[i]=jie[i-1]*i%mod;
    invjie[Len]=inv(jie[Len]);dec(i,0,Len-1) invjie[i]=invjie[i+1]*(i+1)%mod;
    I[1]=1;I[0]=1;rep(i,2,Len) I[i]=(I[i-1]+(i-1)*I[i-2]%mod)%mod;
    while(t--){
        read(n);
        int ans=0;
        rep(i,0,n/4){
            int nowans=C(n-2*i,2*i)*jie[2*i]%mod*invjie[i]%mod;
            ans=(ans+nowans*I[n-i*4]%mod)%mod;
        }
        printf("%lld\n",ans);
    }
    return 0;
}