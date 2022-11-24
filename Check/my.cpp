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

int f[N][N],n,siz[N],g[N],hei[N],jie[N],invjie[N],h[N],G[N];
vi e[N];

inline int ksm(int a,int b,int mod){
    int res=1;while(b){if(b&1)res=1ll*res*a%mod;a=1ll*a*a%mod;b>>=1;}return res;
}
inline int inv(int x){return ksm(x,mod-2,mod);}
inline int C(int n,int m){return jie[n]*invjie[m]%mod*invjie[n-m]%mod;}
inline int Cn(int n){
    return (C(2*n,n)-C(2*n,n-1)+mod)%mod;
}

inline void dfs(int k,int fa){
    hei[k]=1;siz[k]=1;int sumsiz=0;
    for(int to:e[k]) if(to!=fa){
        dfs(to,k);
        sumsiz+=siz[to];
        cmax(hei[k],hei[to]+1);
    }
    f[k][1]=1;
    for(int to:e[k]) if(to!=fa)f[k][1]=f[k][1]*f[to][0]%mod;
    for(int to:e[k])if(to!=fa){
        h[to]=1;
        for(int to2:e[k])if(to2!=fa&&to!=to2){
            h[to]=h[to]*f[to2][0]%mod;
        }
    }
    rep(i,2,hei[k]){
        for(int to:e[k]) if(to!=fa){
            f[k][i]=(f[k][i]+f[to][i-1]*h[to]%mod)%mod;
        }
    }
    // for(int to:e[k])if(to!=fa){
    //     for(int i=1;i<=siz[to];i+=2){
    //         f[k][0]=(f[k][0]+f[to][i]*h[to]%mod*Cn((i+1)/2-1)%mod)%mod;
    //     }
    // }
    rep(i,0,sumsiz) g[i]=0;
    g[1]=1;
    // printf("k=%d\n",k);
    for(int to:e[k]) if(to!=fa){
        // printf("to=%d\n",to);
        f[k][0]=f[k][0]*f[to][0]%mod;
        f[k][0]=f[to][0]*g[0]%mod;
        rep(i,1,siz[to]){
            rep(j,1,siz[k]){
                if((i+j)%2==0){
                    f[k][0]=(f[k][0]+g[j]*f[to][i]%mod*Cn((j+i)/2-1)%mod)%mod;
                    // printf("i=%d j=%d f[k][0]=%d\n",i,j,f[k][0]);
                }
            }
        }
        siz[k]+=siz[to];
        // rep(i,0,siz[to]) (g[i]+=f[to][i])%=mod;
        // g[0]=g[0]*f[to][0]%mod;
        // if(k==5) printf("f[to][0]=%d g[4]=%d g[1]=%d f[to][3]=%d\n",f[to][0],g[4],g[1],f[to][3]);
        rep(i,2,siz[k]) g[i]=(g[i]*f[to][0]%mod+g[1]*f[to][i-1]%mod)%mod;
        g[1]=g[1]*f[to][0]%mod;
        g[0]=f[k][0]%mod;
        // rep(i,0,siz[k]){
            // printf("g[%lld]=%lld\n",i,g[i]);
        // }
        
    }
    // printf("k=%lld siz[k]=%lld\n",k,siz[k]);
    // rep(i,0,siz[k]){
    //     printf("f[%lld][%lld]=%lld\n",k,i,f[k][i]);
    // }
}

signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);
    rep(i,1,n-1){
        int u,v;read(u);read(v);e[u].pb(v);e[v].pb(u);
    }
    jie[0]=1;rep(i,1,n) jie[i]=jie[i-1]*i%mod;invjie[n]=inv(jie[n]);
    dec(i,0,n-1) invjie[i]=invjie[i+1]*(i+1)%mod;
    dfs(1,0);
    printf("%lld\n",f[1][0]);
    return 0;
}