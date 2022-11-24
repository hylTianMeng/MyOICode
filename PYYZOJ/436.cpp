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
#define N 210
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

int n,m,c,f;

struct edge{
    int to,next,f,v;
    inline void Init(int to_,int ne_,int f_,int v_){
        to=to_;next=ne_;f=f_;v=v_;
    }
}li[N*10];
int head[N],tail=1,va[N],ans;

inline void Add(int from,int to,int f,int v){
    // printf("from=%d to=%d w=%d c=%d\n",from,to,f,v);
    li[++tail].Init(to,head[from],f,v);head[from]=tail;swap(from,to);
    li[++tail].Init(to,head[from],0,-v);head[from]=tail;
}

queue<int> q;
int d[N],now[N],s,t,Ans;
bool vis[N];

inline bool spfa(int s){
    while(q.size()) q.pop();
    bool op=0;
    mset(d,INF);mset(vis,0);d[s]=0;q.push(s);vis[s]=1;now[s]=head[s];
    while(q.size()){
        int top=q.front();q.pop();vis[top]=0;
        Next(top){
            int to=li[x].to,f=li[x].f,v=li[x].v;if(!f||d[to]<=d[top]+v)continue;
            d[to]=d[top]+v;if(!vis[to]) vis[to]=1,q.push(to);now[to]=head[to];
        }
    }
    if(d[t]>=INF) return 0;else return 1;
}
inline int dinic(int k,int flow){
    if(k==t) return flow;int rest=flow,x;vis[k]=1;
    for(x=now[k];x&&rest;x=li[x].next){
        int to=li[x].to,f=li[x].f,v=li[x].v;
        if(!f||d[to]!=d[k]+v||(vis[to]&&to!=t)) continue;int val=dinic(to,min(rest,f));
        if(!val) d[to]=INF;li[x].f-=val;li[x^1].f+=val;rest-=val;Ans+=val*v;
    }
    now[k]=x;
    return flow-rest;
}

int main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);read(m);
    rep(i,1,m){
        int u,v,c,f;read(u);read(v);read(c);read(f);
        if(c<=f){
            Ans+=f-c;
            Add(u,v,INF,2);Add(v,u,f-c,0);Add(v,u,c,1);
        }
        else{
            Add(u,v,c-f,1);Add(v,u,f,1);Add(u,v,INF,2);
        }
        va[u]-=f;va[v]+=f;
    }
    Add(n,1,INF,0);
    Add(1,n,INF,0); 
    // puts("here");
    s=++n;t=++n;
    rep(i,1,n-2){
        // printf("i=%d\n",i);
        if(va[i]<=0) Add(i,t,-va[i],0);
        else Add(s,i,va[i],0);
    }
    // printf("Ans=%d\n",Ans);
    while(spfa(s)) ans+=dinic(s,INF);
    // printf("ans=%d\n",ans);
    printf("%d\n",Ans);
    return 0;
}