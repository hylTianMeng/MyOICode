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
#define N 1510
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

struct Line{
    int u,v,w;
    inline Line(){}
    inline Line(int u,int v,int w) : u(u),v(v),w(w) {}
    inline bool operator < (const Line &b)const{return w<b.w;}
}li[N*N];
int n,a[N][N],lt,fa[N<<1],siz[N<<1],en[N<<1],f[N<<1][N<<1],g[N<<1];
vi e[N<<1];
bool vis[N<<1];

inline int Find(int x){return fa[x]==x?x:fa[x]=Find(fa[x]);}
inline void Merge(int a,int b){
    if(siz[a]==1){
        rep(i,1,siz[b]) f[a][i]=f[b][i];return;
    }
    mset(g,0);
    rep(i,0,siz[a]+siz[b])rep(j,max(i-siz[b],0),siz[a]) g[i]=(g[i]+1ll*f[a][j]*f[b][i-j]%mod)%mod;
    g[0]=0;rep(i,1,siz[a]+siz[b]) f[a][i]=g[i];
}
inline void dfs(int k,int fa){
    siz[k]=1;
    for(int to:e[k]) if(to!=fa){
        dfs(to,k);Merge(k,to);siz[k]+=siz[to];
    }
    if(vis[k]) f[k][1]=1;else f[k][1]=0;
    // printf("k=%d\n",k);
    // rep(i,1,siz[k]) printf("%d ",f[k][i]);puts("");
}
inline void Add(int a,int b){
    printf("Add %d %d\n",a,b);
}

int main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);rep(i,1,n)rep(j,1,n) read(a[i][j]);
    rep(i,1,n)rep(j,i+1,n) li[++lt]=Line(i,j,a[i][j]);
    sort(li+1,li+lt+1);
    int tot=n;rep(i,1,n) vis[i]=1;rep(i,1,n<<1) en[i]=0,siz[i]=1,fa[i]=i;
    rep(i,1,lt){
        int u=li[i].u,v=li[i].v;
        int fau=Find(u),fav=Find(v);
        if(fau==fav){
            en[fau]++;if(en[fau]==siz[fau]*(siz[fau]-1)/2) vis[fau]=1;
            continue;
        }
        ++tot;fa[fau]=tot;fa[fav]=tot;e[tot].pb(fau);e[tot].pb(fav);
        // Add(tot,fau);Add(tot,fav);
        siz[tot]=siz[fau]+siz[fav];en[tot]=en[fau]+en[fav]+1;
        if(en[tot]==siz[tot]*(siz[tot]-1)/2) vis[tot]=1;
    }
    // printf("tot=%d\n",tot);
    // rep(i,1,tot) printf("vis[%d]=%d\n",i,vis[i]);
    // exit(0);
    mset(siz,0);dfs(tot,0);
    rep(i,1,n) printf("%d ",f[tot][i]);
    return 0;
}