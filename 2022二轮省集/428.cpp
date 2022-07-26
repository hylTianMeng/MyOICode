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

const int INF=1e18;
const dd eps=1e-9;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}
struct edge{
    int to,next,w;
    inline void Init(int to_,int ne_,int w_){
        to=to_;next=ne_;w=w_;
    }
}li[N<<1];
int head[N],tail,n,m,qu,d[N],ad[N];
queue<int> q[N];
priority_queue<P> Q;
bool vis[N];

inline void Add(int from,int to,int w){
    li[++tail].Init(to,head[from],w);head[from]=tail;
}
inline void dij(){
    Q.push(mp(0,1));fill(d+1,d+n+1,INF);mset(vis,0);d[1]=0;
    while(Q.size()){
        P top=Q.top();Q.pop();vis[top.se]=1;
        Next(top.se){
            int to=li[x].to,w=li[x].w;
            if(vis[to]||d[to]<=d[top.se]+w) continue;
            d[to]=d[top.se]+w;Q.push(mp(-d[to],to));
        }
    }
}
inline void Solve(int K){
    q[0].push(1);fill(ad+1,ad+n+1,INF);ad[1]=0;
    rep(i,0,K){
        while(q[i].size()){
            int top=q[i].front();q[i].pop();
            // printf("top=%d\n",top);
            Next(top){
                int to=li[x].to,w=li[x].w;
                if(ad[to]<=d[top]+ad[top]+w-d[to]) continue;
                if(d[top]+ad[top]+w-d[to]>K) continue;
                cmin(ad[to],d[top]+ad[top]+w-d[to]);
                q[ad[to]].push(to);
                // printf("ad[%d]=%d\n",to,ad[to]);
            }
        }
    }
    rep(i,1,n) if(d[i]<1e18){
        d[i]=d[i]+ad[i];assert(ad[i]<1e18);
    }
}

signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);read(m);read(qu);
    rep(i,1,m){
        int u,v,c;read(u);read(v);read(c);Add(u,v,c);
    }dij();
    rep(i,1,qu){
        // printf("i=%lld\n",i);
        int op;read(op);
        if(op==1){
            int x;read(x);printf("%lld\n",(d[x]<1e18)?d[x]:-1);
        }
        else{
            int k;read(k);rep(i,1,k){int x;read(x);li[x].w++;}Solve(k);
        }
    }
}