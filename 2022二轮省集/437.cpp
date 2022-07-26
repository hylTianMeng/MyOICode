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
#define N 500010
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

struct Point{
    int x,y;
    inline Point(){}
    inline Point(int x,int y) : x(x),y(y) {}
    inline Point operator - (const Point &b)const{return Point(x-b.x,y-b.y);}
    inline int operator ^ (const Point &b)const{return x*b.y-b.x*y;}
};

int n,f[N],siz[N],Ans=INF;
vi e[N],v;

inline int G(int n){return n*(n-1)/2;}
inline void dfs(int k,int fa){
    siz[k]=1;bool op=1;
    for(int to:e[k]) if(to!=fa){
        dfs(to,k);siz[k]+=siz[to];op=0;
    }
    if(op) return;
    f[k]=G(siz[k]);
    for(int to:e[k]) if(to!=fa){
        cmin(f[k],f[to]+G(siz[k]-siz[to]));
    }
}
inline void dfs2(int k,int fa){
    // printf("f[%d]=%d\n",k,f[k]);
    cmin(Ans,f[k]+G(n-siz[k]));
    for(int to:e[k]) if(to!=fa) dfs2(to,k);
}
inline bool cmp(int a,int b){return siz[a]>siz[b];}
inline int F(int x){return x*(x+1)/2-n*x;}
inline int B(int x){return f[x]+F(siz[x]);}
inline Point Po(int x){return Point(x,B(x));}
int q[N],l,r;
inline void Dfs(int k,int fa){
    v.clear();
    for(int to:e[k]) if(to!=fa) v.pb(to);sort(v.begin(),v.end(),cmp);
    l=r=0;
    rep(i,0,(int)v.size()-1){
        while(l<r-1&&((Po(q[l+2])-Po(q[l+1]))^Point(1,-siz[v[i]]))>0) l++;
        if(l<r){
            int a=v[i],b=q[l+1];
            // printf("a=%d b=%d B(a)=%d B(b)=%d\n",a,b,B(a),B(b));
            cmin(Ans,B(b)+siz[a]*siz[b]+B(a)+G(n));
        }
        while(l<r-1&&((Po(v[i])-Po(q[r])^(Po(q[r-1])-Po(q[r]))))<0) r--;
        q[++r]=v[i];
    }
    l=r=0;
    dec(i,0,(int)v.size()-1){
        while(l<r-1&&((Po(q[l+2])-Po(q[l+1]))^Point(1,-siz[v[i]]))<0) l++;
        if(l<r){
            int a=v[i],b=q[l+1];
            cmin(Ans,B(b)+siz[a]*siz[b]+B(a)+G(n));
        }
        while(l<r-1&&((Po(v[i])-Po(q[r]))^(Po(q[r-1])-Po(q[r])))>0) r--;
        q[++r]=v[i];
    }
    for(int to:e[k]) if(to!=fa) Dfs(to,k);
}

signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);rep(i,1,n-1){
        int u,v;read(u);read(v);
        e[u].pb(v);e[v].pb(u);
    }
    dfs(1,0);dfs2(1,0);
    // printf("Ans=%lld\n",Ans);
    Dfs(1,0);
    // printf("Ans=%lld\n",Ans);
    printf("%lld\n",n*(n-1)-Ans);
    return 0;
}