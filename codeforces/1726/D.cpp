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

int n,m,t,ans[N],fa[N],fat[N],dep[N];
P ed[N];
vc<P> e[N];
bool vis[N];

inline void dfs(int k,int fath){
    vis[k]=1;fat[k]=fath;dep[k]=dep[fath]+1;
    for(P to:e[k])if(!vis[to.fi]){
        ans[to.se]=1;dfs(to.fi,k);
    }
}
inline int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}

int main(){
    // freopen("my.in","r",stdin);
    read(t);
    while(t--){
        read(n);read(m);rep(i,1,n) vis[i]=0;
        rep(i,1,m) ans[i]=-1;
        rep(i,1,n) e[i].clear();
        rep(i,1,n) vis[i]=0;
        rep(i,1,m){
            int u,v;read(u);read(v);e[u].pb(mp(v,i));e[v].pb(mp(u,i));
            ed[i].fi=u;ed[i].se=v;
        }
        dfs(1,0);
        rep(i,1,m) if(ans[i]==-1) ans[i]=0;
        rep(i,1,n) fa[i]=i;
        int id1=-1,id2=-1,id=-1;
        rep(i,1,m){
            if(ans[i]==1) continue;
            int fau=Find(ed[i].fi),fav=Find(ed[i].se);
            if(fau==fav){id1=ed[i].fi;id2=ed[i].se;id=i;break;}
            else fa[fau]=fav;
        }
        if(id1==-1){
            rep(i,1,m) printf("%d",ans[i]);
        }
        else{
            int a=id1,b=id2;
            if(dep[a]<dep[b]) swap(a,b);
            int faa=fat[a];
            int nowid=-1;
            for(P to:e[faa]){
                if(to.fi==a){
                    nowid=to.se;
                }
            }
            swap(ans[nowid],ans[id]);
            rep(i,1,m) printf("%d",ans[i]);
        }
        puts("");
    }
}