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
#define N 110
#define M 100010
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

struct edge{
    int to,next,op;
    inline void Init(int to_,int ne_,int op_){
        to=to_;next=ne_;op=op_;
    }
}li[N<<1];
int head[N],tail,n,m,b[N],d[N],id[N],tot,f[N][M],g[N][M];
vc<P> e[N];
queue<int> q;
vi v;

inline void Add(int from,int to,int op){
    // printf("from=%d to=%d op=%d\n",from,to,op);
    li[++tail].Init(to,head[from],op);head[from]=tail;
}
inline void dfs(int k,int fa){
    Next(k){
        int to=li[x].to;if(to==fa) continue;dfs(to,k);
    }
    rep(i,1,m){
        f[k][i]=1;
        Next(k){
            int to=li[x].to,op=li[x].op;if(to==fa) continue;
            if(op==0) f[k][i]=1ll*f[k][i]*g[to][i-1]%mod;
            else f[k][i]=1ll*f[k][i]*g[to][i]%mod;
        }
        g[k][i]=(g[k][i-1]+f[k][i])%mod;
        // printf("f[%d][%d]=%d\n",k,i,f[k][i]);
        // printf("g[%d][%d]=%d\n",k,i,g[k][i]);
    }
}

int main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);read(m);rep(i,1,n) read(b[i]);
    rep(i,1,n){
        if(b[i]==-1) continue;rep(j,b[i]+1,i-1) e[j].pb(mp(i,1)),d[i]++;
        if(b[i]) e[i].pb(mp(b[i],0)),d[b[i]]++;
    }
    rep(i,1,n) if(!d[i]) q.push(i);
    while(q.size()){
        int top=q.front();q.pop();id[top]=++tot;
        for(P now:e[top]){
            d[now.fi]--;if(!d[now.fi]) q.push(now.fi);
        }
    }
    assert(tot==n);id[0]=INF;
    rep(i,1,n){
        P maxx(0,0);
        for(P now:e[i]) if(id[now.fi]<id[maxx.fi]) maxx=now;
        if(maxx.fi==0) continue;Add(maxx.fi,i,maxx.se);d[i]++;
    }
    rep(i,1,n) if(!d[i]) v.pb(i);
    int Ans=1;
    for(int rt:v) dfs(rt,0);
    for(int rt:v) Ans=1ll*Ans*g[rt][m]%mod;
    printf("%d\n",Ans);
    return 0;
}