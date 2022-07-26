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
#define N 2000100
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

int n;
struct Point{
    int x,y;
}a[N];
int p[5],ma[5];
ll Ans;
vi v[5];
struct Line{
    int u,v,w;
    inline void Init(int u_,int v_,int w_){
        u=u_;v=v_;w=w_;
        // printf("u=%d v=%d w=%d\n",u,v,w);
    }
    inline bool operator < (const Line &b)const{
        return w>b.w;
    }
}li[30];
int lt,fa[5];

inline int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}

int main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);rep(i,1,n) read(a[i].x),read(a[i].y);
    mset(p,-1);ma[1]=-INF;ma[2]=INF;ma[3]=INF;ma[4]=-INF;
    rep(i,1,n){
        if(ma[1]<a[i].x+a[i].y) ma[1]=a[i].x+a[i].y,p[1]=i;
        if(ma[2]>a[i].x-a[i].y) ma[2]=a[i].x-a[i].y,p[2]=i;
        if(ma[3]>a[i].x+a[i].y) ma[3]=a[i].x+a[i].y,p[3]=i;
        if(ma[4]<a[i].x-a[i].y) ma[4]=a[i].x-a[i].y,p[4]=i;
    }
    // rep(i,1,4) printf("p[%d]=%d\n",i,p[i]);
    rep(i,1,n){
        bool op=1;rep(j,1,4) if(p[j]==i) op=0;if(!op) continue;
        int maxx=-INF,id=-1;
        rep(j,1,4) if(maxx<abs(a[i].x-a[p[j]].x)+abs(a[i].y-a[p[j]].y)){
            maxx=abs(a[i].x-a[p[j]].x)+abs(a[i].y-a[p[j]].y),id=j;
            // printf("j=%d maxx=%d\n",j,maxx);
        }
        v[id].pb(i);Ans+=maxx;
        // printf("maxx=%d\n",maxx);
    }
    rep(i,1,4) v[i].pb(p[i]);
    // printf("Ans=%d\n",Ans);
    rep(i,1,4)rep(j,i+1,4){
        int maxx=-INF;
        for(int now:v[j]) if(maxx<abs(a[now].x-a[p[i]].x)+abs(a[now].y-a[p[i]].y)) maxx=abs(a[now].x-a[p[i]].x)+abs(a[now].y-a[p[i]].y);
        for(int now:v[i]) if(maxx<abs(a[now].x-a[p[j]].x)+abs(a[now].y-a[p[j]].y)) maxx=abs(a[now].x-a[p[j]].x)+abs(a[now].y-a[p[j]].y);
        li[++lt].Init(i,j,maxx);
    }
    sort(li+1,li+lt+1);rep(i,1,4) fa[i]=i;
    rep(i,1,lt){
        int fau=Find(li[i].u),fav=Find(li[i].v);
        if(fau==fav) continue;
        Ans+=li[i].w;fa[fau]=fav;
    }
    printf("%lld\n",Ans);
    return 0;
}