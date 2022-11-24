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
#define N 100010
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
const int mod=1e9+7;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

int n,k,a[N],jie[N],invjie[N];

inline int ksm(int a,int b,int mod){
    int res=1;while(b){if(b&1)res=1ll*res*a%mod;a=1ll*a*a%mod;b>>=1;}return res;
}
inline int inv(int a){return ksm(a,mod-2,mod);}
inline int C(int n,int m){
    if(n<m) return 0;
    return 1ll*jie[n]*invjie[m]%mod*invjie[n-m]%mod;
}

int main(){
    read(n);read(k);jie[0]=1;rep(i,1,n) jie[i]=1ll*jie[i-1]*i%mod;invjie[n]=inv(jie[n]);
    dec(i,0,n-1) invjie[i]=1ll*invjie[i+1]*(i+1)%mod;
    int ans=0;
    k=min(k,n);rep(i,0,k) ans+=C(n,i),ans%=mod;
    printf("%d\n",ans);
    return 0;
}