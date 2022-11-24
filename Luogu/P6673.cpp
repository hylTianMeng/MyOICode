#include<bits/stdc++.h>
#define mset(a,b) memset((a),(b),sizeof((a)))
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
#define dec(i,l,r) for(int i=(r);i>=(l);i--)
#define mai(a) ((a)<0?((a)+mod):(((a)>mod)?(a)-mod:(a)))
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
#define N 631441
#define M 15
using namespace std;

typedef double dd;
typedef long double ld;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
// #define int long long
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
    
int mod,inv3;
inline ll exgcd(ll a,ll b,ll &x,ll &y){
    if(b==0){x=1;y=0;return a;}ll g=exgcd(b,a%b,x,y);ll tmp=x;x=y;y=tmp-a/b*y;return g;
}
inline int inv(int a){
    ll x,y;int g=exgcd(a,mod,x,y);assert(g==1);
    // printf("a=%lld mod=%lld x=%lld y=%lld\n",a,mod,x,y);
    assert(mai(1ll*x*a%mod)==1);
    return (x%mod+mod)%mod;
}
inline int ksm(int a,int b,int mod){
    int res=1;while(b){if(b&1)res=1ll*res*a%mod;a=1ll*a*a%mod;b>>=1;}return res;
}

struct cp{
    int x,y;
    inline cp() {}
    inline cp(int x,int y) : x(x),y(y) {}
    inline cp operator + (const cp &b)const{return cp((x+b.x)%mod,(y+b.y)%mod);}
    inline cp operator - (const cp &b)const{return cp(mai(x-b.x),mai(y-b.y));}
    inline cp operator * (const cp &b)const{
        return cp(mai((1ll*x*b.y%mod+1ll*b.x*y%mod)%mod-1ll*x*b.x%mod),mai(1ll*y*b.y%mod-1ll*x*b.x%mod)%mod);
    }
    inline cp operator * (const int b)const{return cp(1ll*x*b%mod,1ll*y*b%mod);}
    inline void Print(){
        printf("x=%d y=%d\n",x,y);
    }
};
inline cp ksm(cp a,int b){
    cp res;res.y=1;res.x=0;
    while(b){if(b&1)res=res*a;a=a*a;b>>=1;}return res;
}
int m,t,n,B[M][M];
cp f[N],b[N];
cp w2,w1;

inline int bit1(int x){
    int res=0;while(x){if((x%3)==1) res++;x/=3;}return res;
}
inline int bit2(int x){
    int res=0;while(x){if((x%3)==2) res++;x/=3;}return res;
}
// inline int add(int x,int y){
//     int ans=0;
//     int p=1;while(x/p!=0||y/p!=0){
//         int nowx=(x/p)%3,nowy=(y/p)%3;
//         int now=(nowx+nowy)%3;ans+=p*now;p*=3;
//     }
//     return ans;
// }
// inline int del(int x,int y){
//     int ans=0;
//     int p=1;while(x/p!=0||y/p!=0){
//         int nowx=(x/p)%3,nowy=(y/p)%3;
//         int now=(nowx-nowy+3)%3;ans+=p*now;p*=3;
//     }
//     return ans;
// }
inline void FWT(cp *f,int n){
    for(int i=1;i<n;i*=3)
        for(int j=0;j<n;j+=i*3)
            rep(k,0,i-1){
                int k1=j+k,k2=j+k+i,k3=j+k+i+i;
                cp a=f[k1],b=f[k2],c=f[k3];
                f[k1]=a+b+c;
                f[k2]=a+b*w1+c*w2;
                f[k3]=a+b*w2+c*w1;
            }
}

inline void IFWT(cp *f,int n){
    for(int i=1;i<n;i*=3)
        for(int j=0;j<n;j+=i*3)
            rep(k,0,i-1){
                int k1=j+k,k2=j+k+i,k3=j+k+i*2;
                cp a=f[k1],b=f[k2],c=f[k3];
                f[k1]=a+b+c;
                f[k2]=a+b*w2+c*w1;
                f[k3]=a+b*w1+c*w2;
                // f[k1]=f[k1]*inv3;
                // f[k2]=f[k2]*inv3;
                // f[k3]=f[k3]*inv3;
            }
    int ninv=ksm(inv3,m,mod);
    rep(i,0,n-1) f[i]=f[i]*ninv;
}

signed main(){
    // assert(freopen("my.in","r",stdin));
    // assert(freopen("my.out","w",stdout));
    // read(m);read(t);read(mod);inv3=inv(3);
    // n=1;rep(i,1,m) n=n*3;rep(i,0,n-1) read(f[i].y);
    // rep(i,1,m+1) rep(j,1,m+2-i) read(B[i-1][j-1]);
    rep(i,0,n-1) b[i].y=B[bit1(i)][bit2(i)];w1.x=1;w2=(cp){mod-1,mod-1};
    FWT(b,n);FWT(f,n);
    rep(i,0,n-1) b[i]=ksm(b[i],t);
    rep(i,0,n-1) f[i]=f[i]*b[i];
    // printf("inv3=%d\n",inv3);
    IFWT(f,n);
    rep(i,0,n-1) printf("%lld\n",f[i].y);
    return 0;
}
