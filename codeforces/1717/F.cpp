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
#define N 40010
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

struct edge{
    int from,to,next,f;
    inline void Init(int fr_,int to_,int ne_,int f_){
        from=fr_;to=to_;next=ne_;f=f_;
    }
}li[N<<1];
int head[N],now[N],tail=1;
int n,m,s,t;
P e[N];
int S[N],a[N],d[N],D[N];
bool vis[N],po[N];
vi v;
queue<int> q;

inline void Add(int from,int to,int f){
    // printf("from=%d to=%d f=%d\n",from,to,f);
    li[++tail].Init(from,to,head[from],f);head[from]=tail;swap(from,to);
    if(from<=n&&to<=n){li[++tail].Init(from,to,head[from],1);head[from]=tail;}
    else{li[++tail].Init(from,to,head[from],0);head[from]=tail;}

}
inline bool bfs(){
    mset(d,0);d[s]=1;now[s]=head[s];q.push(s);
    while(q.size()){
        int top=q.front();q.pop();
        for(int x=head[top];x;x=li[x].next){
            int to=li[x].to,f=li[x].f;
            if(!f||d[to]) continue;
            d[to]=d[top]+1;now[to]=head[to];q.push(to);
        }
    }
    if(d[t]) return 1;else return 0;
}
inline int dinic(int k,int flow){
    if(k==t) return flow;
    int rest=flow,x;
    for(x=now[k];x&&rest;x=li[x].next){
        int to=li[x].to,f=li[x].f;
        if(d[to]!=d[k]+1||!f) continue;int re=dinic(to,min(rest,f));
        if(!re) d[to]=0;li[x].f-=re;li[x^1].f+=re;rest-=re;
    }
    now[k]=x;return flow-rest;
}

int main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);read(m);
    rep(i,1,n){read(S[i]);if(S[i]) v.pb(i);}
    rep(i,1,n) read(a[i]);for(int x:v) vis[x]=1;
    rep(i,1,m){
        int u,v;read(u);read(v);D[u]++;D[v]++;
        Add(i,u+m,1);Add(i,v+m,1);e[i]=mp(u,v);
    }
    int tot=n+m;s=++tot;t=++tot;
    rep(i,1,m) Add(s,i,1);
    bool op=1;
    rep(i,1,n){
        if(abs(a[i])%2!=D[i]%2&&vis[i]) op=0;
    }
    rep(i,1,n) a[i]=(a[i]+D[i])/2;
    rep(i,1,n) if(a[i]<0) op=0;
    // printf("op=%d\n",op);
    int sum=0;
    rep(i,m+1,m+n){
        if(vis[i-m]) Add(i,t,a[i-m]),sum+=a[i-m];
        // else Add(i,t,INF);
    }
    vc<P> Ans;Ans.clear();
    int ans=0;
    while(bfs()){
        // puts("Here");
        ans+=dinic(s,INF);
    }
    if(ans!=sum) op=0;
    rep(i,1,n)if(!vis[i]) Add(i+m,t,INF);
    while(bfs()){
        ans+=dinic(s,INF);
    }
    if(ans!=m) op=0;
    if(!op){puts("No");return 0;}
    else{
        rep(i,1,m){
            Next(i){
                int to=li[x].to,f=li[x].f;
                if(to==s) continue;
                if(f) continue;
                // printf("i=%d to=%d f=%d\n",i,to,f);
                if(to-m==e[i].fi) Ans.pb(mp(e[i].se,e[i].fi));
                else Ans.pb(mp(e[i].fi,e[i].se));
            }
        }
    }
    puts("Yes");
    for(P now:Ans){
        printf("%d %d\n",now.fi,now.se);
    }
    return 0;
}