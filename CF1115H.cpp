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
#define mr(a) ((a)=((a)+mod)%mod)
#define Next(k) for(int x=head[k];x;x=li[x].next)
#define vc vector
#define ar array
#define pi pair
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define N 400010
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

int n,k,u,v,w,a[N],b[N],c[N],xsum,inv2;
int f[N],g[N],h[N],ans[N],Ans[N];

inline int ksm(int a,int b,int mod){mr(a);int res=1;while(b){if(b&1)res=1ll*res*a%mod;a=1ll*a*a%mod;b>>=1;}return res;}
inline int inv(int a){return ksm(a,mod-2,mod);}
inline void FWT(int *f,int n,int op){
    for(int i=2;i<=n;i<<=1)
        for(int l=0;l<n;l+=i)
            for(int k=l;k<l+(i/2);k++){
                ll A=f[k],B=f[k+(i/2)];
                if(op==1) f[k]=(A+B),f[k+(i/2)]=(A-B);
                else f[k]=1ll*(A+B)*inv2%mod,f[k+(i/2)]=1ll*(A-B)*inv2%mod;
            }
}
inline void Calc(ll &a,ll &b,ll &c,ll &d,ll a1,ll a2,ll a3,ll a4){
    ll sum=(a2+a3+a4)-a1;sum%=mod;a=1ll*sum*inv2%mod;
    b=a2-a;c=a3-a;d=a4-a;mr(a);mr(b);mr(c);mr(d);
}
inline void Calc(ll &a,ll &b,ll a1,ll a2){
    ll sum=(a1+a2);sum%=mod;a=1ll*sum*inv2%mod;
    b=a1-a;mr(a);mr(b);
    // printf("a1=%lld a2=%lld a=%lld b=%lld\n",a1,a2,a,b);
}

signed main(){
    // assert(freopen("my.in","r",stdin));
    // assert(freopen("my.out","w",stdout));
    read(n);read(k);read(u);read(v);read(w);rep(i,1,n) read(a[i]),read(b[i]),read(c[i]);
    u%=mod;v%=mod;w%=mod;
    rep(i,1,n) a[i]^=c[i],b[i]^=c[i];rep(i,1,n) xsum^=c[i];
    rep(i,1,n) f[a[i]]++;rep(i,1,n) g[b[i]]++;rep(i,1,n) h[a[i]^b[i]]++;
    int ln=n;
    int nn=(1<<k)-1;n=1;while(n<=nn) n<<=1;inv2=inv(2);FWT(f,n,1);FWT(h,n,1);FWT(g,n,1);
    // printf("f: ");rep(i,0,n-1) printf("%d ",f[i]);puts("");
    // printf("g: ");rep(i,0,n-1) printf("%d ",g[i]);puts("");
    // printf("h: ");rep(i,0,n-1) printf("%d ",h[i]);puts("");
    rep(i,0,n-1){
        // printf("i=%d\n",i);
        ll A,B,C,D,a1,a2,a3,a4;a1=ln;
        ll aa,bb,aa1,aa2;
        aa1=ln;aa2=f[i];Calc(aa,bb,aa1,aa2);
        a2=aa;aa2=g[i];Calc(aa,bb,aa1,aa2);
        a3=aa;aa2=h[i];Calc(aa,bb,aa1,aa2);
        a4=aa;
        Calc(A,B,C,D,a1,a2,a3,a4);
        ans[i]=1ll*ksm(u+v+w,A,mod)*ksm(u-v+w,B,mod)%mod*ksm(-u+v+w,C,mod)%mod*ksm(-u-v+w,D,mod)%mod;
    }
    FWT(ans,n,0);
    rep(i,0,n-1) Ans[i]=ans[i^xsum];
    rep(i,0,n-1) printf("%lld ",mr(Ans[i]));
    return 0; 
}


/*


...=...
   =...
   =...

*/