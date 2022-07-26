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
#define N 700010
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
    // printf("f[%lld]=%lld\n",k,f[k]);
    cmin(Ans,f[k]+G(n-siz[k]));
    for(int to:e[k]) if(to!=fa) dfs2(to,k);
}
inline bool cmp(int a,int b){return siz[a]>siz[b];}
inline int F(int x){return x*(x+1)/2-n*x;}
inline int B(int x){return f[x]+F(siz[x]);}
inline Point Po(int x){return Point(siz[x],B(x));}
int q[N],l,r;
inline void Dfs(int k,int fa){
    v.clear();
    for(int to:e[k]) if(to!=fa) v.pb(to);sort(v.begin(),v.end(),cmp);

    l=r=0;
    rep(i,0,(int)v.size()-1){
        // if(k==1) printf("l=%lld r=%lld\n",l,r);
        // if(k==1){rep(i,l+1,r) printf("%lld %lld,",Po(q[i]).x,Po(q[i]).y);puts("");}
        while(l<r-1&&((Po(q[l+2])-Po(q[l+1]))^Point(1,-siz[v[i]]))>=0){
            l++;
        }
        if(l<r){
            int a=v[i],b=q[l+1];
            // int a=7,b=4;
            // if(k==1) printf("a=%lld b=%lld B(a)=%lld B(b)=%lld\n",a,b,B(a),B(b));
            cmin(Ans,B(b)+siz[a]*siz[b]+B(a)+G(n));
        }
        while(l<r-1&&((Po(v[i])-Po(q[r]))^(Po(q[r-1])-Po(q[r])))<=0) r--;
        q[++r]=v[i];
    } 
    l=r=0;
    dec(i,0,(int)v.size()-1){
        while(l<r-1&&((Po(q[l+2])-Po(q[l+1]))^Point(1,-siz[v[i]]))<=0) l++;
        if(l<r){
            int a=v[i],b=q[l+1];
            cmin(Ans,B(b)+siz[a]*siz[b]+B(a)+G(n));
        }
        while(l<r-1&&((Po(v[i])-Po(q[r]))^(Po(q[r-1])-Po(q[r])))>=0) r--;
        q[++r]=v[i];
    }
    int Ans1=Ans;

    // bool op=1;
    // rep(i,0,(int)v.size()-1)rep(j,i+1,(int)v.size()-1){
    //     cmin(Ans,f[v[i]]+f[v[j]]+G(n-siz[v[i]]-siz[v[j]]));
    //     if(Ans==96088&&k==1&&op){
    //         op=0;
    //         printf("%lld %lld\n",v[i],v[j]);break;
    //     }
    // }
    // if(Ans1!=Ans){
    //     printf("Ans=%lld Ans1=%lld\n",Ans,Ans1);
    //     printf("k=%lld\n",k);
    //     printf("son:  ");for(int x:v) printf("%lld ",x);puts("");
    //     printf("siz:  ");for(int x:v) printf("%lld ",siz[x]);puts("");
    //     printf("f:  ");for(int x:v) printf("%lld ",f[x]);puts("");
    // }
    for(int to:e[k]) if(to!=fa) Dfs(to,k);
}

signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);rep(i,1,n-1){
        int u,v;read(u);read(v);
        e[u].pb(v);e[v].pb(u);
    }
    int rt=-1;
    rt=1;
    rep(i,1,n) if(e[i].size()>1){rt=i;break;}
    // rt=n/2;
    dfs(rt,0);dfs2(rt,0);
    // printf("Ans=%lld\n",Ans);
    Dfs(rt,0);
    // printf("Ans=%lld\n",Ans); 
    printf("%lld",n*(n-1)-Ans);
    return 0;
}