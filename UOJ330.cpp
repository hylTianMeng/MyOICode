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
#define N 2000100
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

int n,a[N],b[N],inv2,c[N],inv4;

inline int ksm(int a,int b,int mod){int res=1;while(b){if(b&1)res=1ll*res*a%mod;a=1ll*a*a%mod;b>>=1;}return res;}
inline int inv(int a){return ksm(a,mod-2,mod);}
inline P Calc(int a,int b){
    int x=1ll*((a+b)%mod)*inv4%mod;
    int y=(a-x)%mod;
    // x=(x+mod)%mod;y=(y+mod)%mod;
    return mp(x,y);
}
inline void FWT(int *f,int n,int op){
    for(int i=2;i<=n;i<<=1)
        for(int l=0;l<n;l+=i)
            rep(k,l,l+i/2-1){
                // printf("k=%d\n",k);
                int a=f[k],b=f[k+i/2];
                if(op){
                    f[k]=(a+b)%mod;f[k+i/2]=(a-b)%mod;
                }
                else{
                    f[k]=1ll*((a+b)%mod)*inv2%mod;
                    f[k+i/2]=1ll*((a-b)%mod)*inv2%mod;
                }
            }
}

int main(){
    // assert(freopen("my.in","r",stdin));
    // assert(freopen("my.out","w",stdout));
    inv2=ksm(2,mod-2,mod);inv4=inv(4);
    read(n);rep(i,1,n) read(a[i]);
    int nn=n;
    rep(i,1,n) b[a[i]]+=2;b[0]+=n;
    int m=1000000;n=1;while(n<m) n<<=1;
    FWT(b,n,1);
    // rep(i,0,n-1) printf("%d ",b[i]);puts("");
    rep(i,0,n-1){
        P now=Calc(nn,b[i]);
        // printf("now.fi=%d now.se=%d\n",now.fi,now.se);
        c[i]=1ll*ksm(3,now.fi,mod)*sgn(now.se)%mod;
    }
    FWT(c,n,0);
    c[0]--;
    printf("%d\n",(c[0]+mod)%mod);
    return 0;
}
