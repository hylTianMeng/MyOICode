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
#define N 10010
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

int sta[N],top,dfn[N],low[N],tot,ctot,c[N],n,m,a[N],d[N],f[N],b[N];
vi vdcc[N],e[N],ee[N];
bool ins[N];
queue<int> q;

inline void Tarjan(int k){
    dfn[k]=low[k]=++tot;sta[++top]=k;ins[k]=1;
    for(int to:e[k]){
        if(!dfn[to]){Tarjan(to);low[k]=min(low[k],low[to]);}
        else if(ins[to]) low[k]=min(dfn[to],low[k]);
    }
    if(dfn[k]==low[k]){
        int z;ctot++;do{z=sta[top--];vdcc[ctot].pb(z);c[z]=ctot;ins[z]=1;}while(z!=k);
    }
}

int main(){
    // freopen("my.in","r",stdin);
    read(n);read(m);
    rep(i,1,n) read(a[i]);rep(i,1,m){int u,v;read(u);read(v);e[u].pb(v);}
    rep(i,1,n) if(!dfn[i]) Tarjan(i);
    // rep(i,1,ctot){
    //     printf("i=%d ",i);
    //     for(int x:vdcc[i]) printf("x=%d ",x);puts("");
    // }
    rep(i,1,ctot){
        for(int x:vdcc[i]) b[i]+=a[x];
    }
    rep(i,1,n) for(int to:e[i]) if(c[i]!=c[to]) ee[c[i]].pb(c[to]),d[c[to]]++;
    rep(i,1,ctot) if(!d[i]) q.push(i),f[i]=b[i];
    while(q.size()){
        int top=q.front();q.pop();
        for(int to:ee[top]){
            d[to]--;cmax(f[to],b[to]+f[top]);
            if(!d[to]) q.push(to);
        }
    }
    int ans=0;
    rep(i,1,ctot) cmax(ans,f[i]);
    printf("%d\n",ans);
    return 0;
}