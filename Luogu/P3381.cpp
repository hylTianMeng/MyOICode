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
#define N 5010
#define M 50010
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

struct edge{
    int to,next,w,f;
    inline void Init(int to_,int ne_,int w_,int f_){
        to=to_;next=ne_;w=w_;f=f_;
    }
}li[M<<1];
int head[N],now[N],tail=1,n,m,d[N],s,t,ans,Ans;
bool vis[N];
queue<int> q;

inline void Add(int from,int to,int w,int f){
    li[++tail].Init(to,head[from],w,f);head[from]=tail;swap(from,to);
    li[++tail].Init(to,head[from],-w,0);head[from]=tail;
}
inline bool spfa(){
    mset(vis,0);q.push(s);vis[s]=1;mset(d,INF);d[s]=0;
    while(q.size()){
        int top=q.front();q.pop();now[top]=head[top];vis[top]=0;
        Next(top){
            int to=li[x].to,w=li[x].w,f=li[x].f;
            if(d[to]<=d[top]+w||!f) continue;
            d[to]=d[top]+w;if(!vis[to]) q.push(to),vis[to]=1;
        }
    }
    if(d[t]==INF) return 0;return 1;
}
inline int dinic(int k,int flow){
    if(k==t) return flow;vis[k]=1;int rest=flow,x;
    for(x=now[k];x&&rest;x=li[x].next){
        int to=li[x].to,w=li[x].w,f=li[x].f;
        if((vis[to]&&to!=t)||d[to]!=d[k]+w||!f) continue;int now=dinic(to,min(rest,f));if(!now) d[to]=INF;
        rest-=now;li[x].f-=now;li[x^1].f+=now;Ans+=w*now;
    }
    now[k]=x;return flow-rest;
}

int main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);read(m);read(s);read(t);
    rep(i,1,m){
        int u,v,w,c;read(u);read(v);read(c);read(w);
        Add(u,v,w,c);
    }
    while(spfa()){
        ans+=dinic(s,INF);
    }
    printf("%d %d\n",ans,Ans);
    return 0;
}