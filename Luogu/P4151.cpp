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
#define int long long
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

int n,m;

struct edge{
    int to,next,w;
    inline void Init(int to_,int ne_,int w_){
        to=to_;next=ne_;w=w_;
    }
}li[N<<1];
int head[N],tail,Ans,d[N];
bool vis[N];

struct LinearBasis{
    int p[70];
    inline bool Insert(int x){
        dec(i,0,63) if((x>>i)&1){if(!p[i]){p[i]=x;return 1;}else x^=p[i];}return 0;
    }
    inline int Ask(int x){
        int ans=x;dec(i,0,63) if((ans^p[i])>ans) ans^=p[i];return ans;
    }
}lb;

inline void Add(int from,int to,int w){
    li[++tail].Init(to,head[from],w);head[from]=tail;
}
inline void dfs(int k,int fat,int xo){
    vis[k]=1;if(k==n) Ans=xo;d[k]=xo;
    Next(k){
        int to=li[x].to;if(to==fat) continue;
        if(!vis[to]) dfs(to,k,xo^li[x].w);
        else lb.Insert(xo^li[x].w^d[to]);
    }
}

signed main(){
    // freopen("my.in","r",stdin);
    read(n);read(m);
    rep(i,1,m){
        int u,v,w;read(u);read(v);read(w);Add(u,v,w);Add(v,u,w);
    }
    dfs(1,0,0);
    Ans=lb.Ask(Ans);
    printf("%lld\n",Ans);
    return 0;
}