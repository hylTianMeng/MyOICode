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

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

int rd[N];
int n,m,dfn[N],low[N],tot,sta[N],top,c[N],ctot;
int v[N],f[N],g[N];
bool ins[N];
vi scc[N];
struct Edge{
    vi e[N];
    inline void Init(){
        rep(i,1,n) rd[i]=0;
        rep(i,1,n){
            for(int to:e[i]){
                rd[to]++;
            }
        }
    }
}a,b,d;

inline void Tarjan(int k){
    dfn[k]=low[k]=++tot;sta[++top]=k;ins[k]=1;
    for(int to:a.e[k]){
        if(!dfn[to]){Tarjan(to);low[k]=min(low[k],low[to]);}
        else if(ins[to]) low[k]=min(dfn[to],low[k]);
    }
    if(dfn[k]==low[k]){
        int z;ctot++;do{z=sta[top--];scc[ctot].pb(z);c[z]=ctot;ins[z]=0;}while(z!=k);
    }
}
queue<int> q;
inline void DP(int *f,Edge now){
    now.Init();
    rep(i,1,n) if(!rd[i]) q.push(i);
    while(q.size()){
        int top=q.front();q.pop();
        if(top==c[1]){
            f[top]=v[c[1]];
        }
        for(int to:now.e[top]){
            if(f[top]) cmax(f[to],f[top]+v[to]);
            rd[to]--;
            if(!rd[to]) q.push(to);
        }
    }
}

int main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);read(m);
    rep(i,1,m){
        int u,v;read(u);read(v);
        a.e[u].pb(v);
    }
    rep(i,1,n) if(!dfn[i]) Tarjan(i);
    rep(i,1,n){
        for(int to:a.e[i]){
            if(c[i]==c[to]) continue;
            b.e[c[i]].pb(c[to]);
            d.e[c[to]].pb(c[i]);
        }
    }
    rep(i,1,ctot){
        v[i]=scc[i].size();
        // printf("i=%d: ",i);
        // for(int x:scc[i]){
        //     printf("%d ",x);
        // }
        // puts("");
    }
    DP(f,b);DP(g,d);
    int ans=v[c[1]];
    // printf("ans=%d\n",ans);
    // rep(i,1,ctot){
    //     printf("f[%d]=%d\n",i,f[i]);
    //     printf("g[%d]=%d\n",i,g[i]);
    // }
    rep(i,1,n){
        for(int to:b.e[i]){
            if(f[i]&&g[to]) cmax(ans,f[i]+g[to]-v[c[1]]);
            if(f[to]&&g[i]) cmax(ans,f[to]+g[i]-v[c[1]]);
        }
    }
    printf("%d\n",ans);
    return 0;
}