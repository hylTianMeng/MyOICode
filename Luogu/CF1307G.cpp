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
#define N 54
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
    int to,next,w,f;
    inline void Init(int to_,int ne_,int w_,int f_){
        to=to_;next=ne_;w=w_;f=f_;
    }
}li[N*N*2];
int head[N],tail=1,now[N],d[N],s,t,Ans,A[N],ans,Q;
bool vis[N];
queue<int> q;

inline void Add(int from,int to,int w,int f){
    li[++tail].Init(to,head[from],w,f);head[from]=tail;swap(from,to);
    li[++tail].Init(to,head[from],-w,0);head[from]=tail;
}
inline bool spfa(int s){
    while(q.size()) q.pop();
    bool op=0;
    mset(d,INF);mset(vis,0);d[s]=0;q.push(s);vis[s]=1;now[s]=head[s];
    while(q.size()){
        int top=q.front();q.pop();vis[top]=0;
        Next(top){
            int to=li[x].to,f=li[x].f,w=li[x].w;if(!f||d[to]<=d[top]+w)continue;
            d[to]=d[top]+w;if(!vis[to]) vis[to]=1,q.push(to);now[to]=head[to];
        }
    }
    if(d[t]>=INF) return 0;else return 1;
}
inline int dinic(int k,int flow){
    if(k==t) return flow;int rest=flow,x;vis[k]=1;
    for(x=now[k];x&&rest;x=li[x].next){
        int to=li[x].to,f=li[x].f,w=li[x].w;
        if(!f||d[to]!=d[k]+w||(vis[to]&&to!=t)) continue;int val=dinic(to,min(rest,f));
        if(!val) d[to]=INF;li[x].f-=val;li[x^1].f+=val;rest-=val;Ans+=val*w;
    }
    now[k]=x;
    return flow-rest;
}

signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);read(m);
    rep(i,1,m){
        int from,to;read(from);read(to);int w;read(w);
        Add(from,to,w,1);
    }
    s=1,t=n;
    rep(i,1,n){
        if(!spfa(s)) break;
        ans+=dinic(s,1);
        A[i]=Ans;
    }
    read(Q);
    rep(i,1,Q){
        int x;read(x);
        ld nowans=INF;
        rep(i,1,n){
            if(!A[i]) break;
            cmin(nowans,(ld)(A[i]+x)/(ld)(i));
        }
        printf("%0.7Lf\n",nowans);
    }
    return 0;
}