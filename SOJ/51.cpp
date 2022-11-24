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
#define N 200100
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

int m,n,L[N],R[N],c[N],ct,co[N],nowtail;
bool vis[N];

struct edge{
    int to,next,f,id,op;
    inline void Init(int to_,int ne_,int f_){
        to=to_;next=ne_;f=f_;
    }
}li[N<<3];
int head[N],tail=1,now[N],d[N],ans[N];
int s,t;

inline void Add(int from,int to,int f){
    li[++tail].Init(to,head[from],f);head[from]=tail;swap(from,to);
    li[++tail].Init(to,head[from],0);head[from]=tail;
}
inline int random(int n){return 1ll*rand()*rand()%n+1;}
inline void Exit(){
    puts("-1");exit(0);
}
queue<int> q;

// #define DE

namespace Dinic{
    int d[N];
    queue<int> q;
    inline bool bfs(){
        q.push(s);mset(d,0);d[s]=1;
        while(q.size()){
            int top=q.front();q.pop();now[top]=head[top];
            Next(top){
                int to=li[x].to,f=li[x].f;
                if(d[to]||!f||li[x].op) continue;
                d[to]=d[top]+1;q.push(to);
            }
        }
        if(d[t]) return 1;return 0;
    }
    inline int dinic(int k,int flow){
        if(k==t) return flow;int rest=flow,x;
        for(x=now[k];x&&rest;x=li[x].next){
            int to=li[x].to,f=li[x].f;
            if(d[to]!=d[k]+1||!f||li[x].op) continue;
            int re=dinic(to,min(rest,f));
            if(!re) d[to]=-INF;
            rest-=re;li[x].f-=re;li[x^1].f+=re;
        }
        return flow-rest;
    }
}
using Dinic::bfs;
using Dinic::dinic;

int main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(m);read(n);
    rep(i,1,m){
        read(L[i]);read(R[i]);read(co[i]);
        R[i]++;
        c[++ct]=L[i];
        c[++ct]=R[i];
    }
    sort(c+1,c+ct+1);ct=unique(c+1,c+ct+1)-c-1;
    rep(i,1,m){
        L[i]=lower_bound(c+1,c+ct+1,L[i])-c;
        R[i]=lower_bound(c+1,c+ct+1,R[i])-c;
    }
    rep(i,1,m){
        d[L[i]]++;d[R[i]]++;
        // printf("i=%d L[i]=%d R[i]=%d\n",i,L[i],R[i]);
    }
    rep(i,1,m){
        Add(L[i],R[i],1);
        li[tail].id=-i;
        li[tail-1].id=i;
        int op=co[i];
        if(co[i]==-1){
            op=random(2)-1;
        }
        else{
            li[tail].op=1;li[tail-1].op=1;
        }
        if(op==0){
            swap(li[tail].f,li[tail-1].f);
        }
        else{
            continue;
        }
    }
    s=ct+1;t=s+1;
    vi v;
    v.clear();
    // rep(i,1,ct){
    //     printf("d[%d]=%d\n",i,d[i]);
    // }
    // rep(i,1,ct)if(d[i]&1){
    //     v.pb(i);
    // }
    // if((int)v.size()&1){
    //     // puts("Here");
    //     Exit();
    // }

    rep(i,1,m){
        v.pb(L[i]);v.pb(R[i]);
    }
    sort(v.begin(),v.end());

    // for(int x:v) printf("%d ",x);puts("");

    nowtail=tail;
    for(int i=0;i<=(int)v.size()-2;i+=2){
        if(v[i]==v[i+1]) continue;
        Add(v[i],v[i+1],1);
        int op=random(2)-1;
        if(op==0){
            swap(li[tail].f,li[tail-1].f);
        }
        else{
            continue;
        }
    }
    mset(d,0);
    n=ct+2;
    rep(i,1,ct){
        Next(i){
            int to=li[x].to,f=li[x].f;
            if(!f) continue;
            d[i]++;d[to]--;
        }
    }

    #ifdef DE
    rep(i,1,n){
        Next(i){
            printf("u=%d v=%d f=%d\n",i,li[x].to,li[x].f);
        }
    }
    #endif

    rep(i,1,ct){
        if(abs(d[i])&1){
            // printf("i=%d d[i]=%d\n",i,d[i]);
            Exit();
        }
    }
    rep(i,1,ct){
        if(d[i]>0){
            Add(s,i,d[i]/2);
        }
        else Add(i,t,-d[i]/2);
    }

    #ifdef DE
    printf("tail=%d\n",tail);
    rep(i,1,n){
        Next(i){
            printf("u=%d v=%d f=%d\n",i,li[x].to,li[x].f);
        }
    }
    #endif

    while(bfs()){
        dinic(s,INF);
    }
    Next(s){
        int to=li[x].to,f=li[x].f;
        if(f){Exit();}
    }
    Next(t){
        int to=li[x].to,f=li[x^1].f;
        if(f){Exit();}
    }
    vis[s]=1;vis[t]=1;
    for(int i=2;i<=tail;i++){
        if(li[i].id==0) continue;
        if(li[i].f==0) continue;
        if(li[i].id<0){
            ans[-li[i].id]=0;
        }
        else ans[li[i].id]=1;
    }
    rep(i,1,m){
        printf("%d ",ans[i]);
    }
    return 0;
}