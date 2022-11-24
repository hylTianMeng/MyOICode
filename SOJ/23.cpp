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
#define N 200010
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

int n,K,m,d[N],ans[N];
P ope[N];
vc<P> e[N];
bool vis[N],v[N];
queue<int> q;

inline void Update(){
    while(q.size()){
        int top=q.front();q.pop();
        v[top]=0;
        for(P to:e[top]){
            if(d[to.fi]>d[top]+to.se){
                d[to.fi]=d[top]+to.se;
                if(!v[to.fi]){
                    q.push(to.fi);
                    v[to.fi]=1;
                }
            }
        }
    }
}

int main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);read(K);read(m);
    rep(i,1,m){
        int x,t;read(x);read(t);
        ope[i].fi=x;
        ope[i].se=t;
        vis[x]=1;
    }
    rep(i,1,n){
        if(vis[i]) continue;
        if(i!=n&&!vis[i+1]) e[i].pb({i+1,0});
        if(i+K<=n&&!vis[i+K]) e[i].pb({i+K,1});
    }
    mset(d,INF);
    d[1]=0;
    q.push(1);
    v[1]=1;
    Update();
    // printf("d[9]=%d\n",d[9]);
    dec(i,1,m){
        int x=ope[i].fi,t=ope[i].se;
        if(d[t]==INF) ans[i]=-1;
        else ans[i]=d[t];
        if(x!=1&&!vis[x-1]) e[x-1].pb({x,0}),cmin(d[x],d[x-1]);
        if(x!=n&&!vis[x+1]) e[x].pb({x+1,0});
        if(x-K>=1&&!vis[x-K]) e[x-K].pb({x,1}),cmin(d[x],d[x-K]+1);
        if(x+K<=n&&!vis[x+K]) e[x].pb({x+K,1});
        vis[x]=0;
        if(d[x]!=INF){
            q.push(x);
            v[x]=1;
            Update();
        }
    }
    rep(i,1,m){
        printf("%d\n",ans[i]);
    }
    return 0;
}