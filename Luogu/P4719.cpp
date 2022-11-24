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
#define N 100010
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

struct Matrix{
    int n,m,a[2][2];
    inline void Clear(){
        mset(a,0);n=m=0;
    }
    inline void Print(){
        printf("%d %d\n",n,m);
        rep(i,0,n-1){
            rep(j,0,m-1) printf("%d ",a[i][j]);puts("");
        }
    }
    inline Matrix operator * (const Matrix &b)const{
        // printf("n=%d m=%d b.n=%d b.m=%d\n",n,m,b.n,b.m);
        Matrix c;c.Clear();assert(m==b.n);c.n=n;c.m=b.m;
        rep(i,0,c.n-1)rep(j,0,c.m-1){
            c.a[i][j]=-INF;
            rep(k,0,m-1){
                cmax(c.a[i][j],a[i][k]+b.a[k][j]);
            }
        }
        return c;
    }
    inline void GetI(int len){
        (*this).Clear();n=m=len;
        rep(i,0,len-1) a[i][i]=1;
    }
};
int en[N],top[N],siz[N],dep[N],id[N],rk[N],tot,fa[N],son[N],n,m,g[N][2],f[N][2],a[N];
vi e[N];
Matrix ze;
struct SegmentTree{
    #define ls(k) k<<1
    #define rs(k) k<<1|1
    Matrix a[N<<2];
    inline void PushUp(int k){
        a[k]=a[ls(k)]*a[rs(k)];
    }
    inline void Change(int k,int l,int r,int w,int i,int j,int x){
        if(l==r){
            a[k].a[i][j]=x;return;
        }int mid=(l+r)>>1;
        if(w<=mid) Change(ls(k),l,mid,w,i,j,x);
        else Change(rs(k),mid+1,r,w,i,j,x);PushUp(k);
    }
    inline Matrix Ask(int k,int l,int r,int z,int y){
        if(z<=l&&r<=y){return a[k];}int mid=(l+r)>>1;Matrix now;now.GetI(2);
        if(z<=mid) now=now*Ask(ls(k),l,mid,z,y);
        if(mid<y) now=now*Ask(rs(k),mid+1,r,z,y);
        return now;
    }
    inline void Build(int k,int l,int r){
        if(l==r){
            int i=rk[l];a[k].a[0][0]=g[i][0];a[k].a[0][1]=g[i][0];a[k].a[1][0]=g[i][1];a[k].a[1][1]=-INF;a[k].m=a[k].n=2;return;
        }int mid=(l+r)>>1;Build(ls(k),l,mid);Build(rs(k),mid+1,r);PushUp(k);
    }
}st;

inline void dfs(int k,int fat){
    fa[k]=fat;siz[k]=1;dep[k]=dep[fat]+1;for(int to:e[k])if(to!=fat){dfs(to,k);siz[k]+=siz[to];if(siz[son[k]]<siz[to]) son[k]=to;}
}
inline int Dfs(int k,int t){
    top[k]=t;id[k]=++tot;rk[tot]=k;int fia=-1;if(son[k])fia=Dfs(son[k],t);for(int to:e[k])if(to!=son[k]&&to!=fa[k]){Dfs(to,to);}if(fia==-1) fia=k;
    en[k]=fia;return en[k];
}
inline void DFs(int k){
    f[k][1]=a[k];f[k][0]=0;g[k][1]=a[k];g[k][0]=0;
    for(int to:e[k])if(to!=fa[k]) DFs(to);
    for(int to:e[k])if(to!=fa[k]){
        f[k][1]+=f[to][0];f[k][0]+=max(f[to][0],f[to][1]);
        if(to!=son[k]) g[k][1]+=f[to][0],g[k][0]+=max(f[to][0],f[to][1]);
    }
    rep(i,0,1){
        printf("f[%d][%d]=%d\n",k,i,f[k][i]);
        printf("g[%d][%d]=%d\n",k,i,g[k][i]);
    }
}
inline void Change(int u,int v){
    Matrix ch;ch.Clear();
    ch.a[1][0]+=-a[u]+v;
    while(u){
        // printf("u=%d\n",u);
        // printf("%d %d\n",id[top[u]],id[en[u]]);
        Matrix last=st.Ask(1,1,n,id[top[u]],id[en[u]])*ze;
        rep(i,0,1)rep(j,0,1)if(ch.a[i][j])st.Change(1,1,n,id[u],i,j,ch.a[i][j]);
        Matrix now=st.Ask(1,1,n,id[top[u]],id[en[u]])*ze;
        u=fa[top[u]];ch.Clear();
        ch.a[0][0]=-max(last.a[0][0],last.a[1][0])+max(now.a[0][0],now.a[1][0]);
        ch.a[0][1]=ch.a[0][0];
        ch.a[1][0]=-last.a[0][0]+now.a[0][0];
    }
}

int main(){
    freopen("my.in","r",stdin);
    freopen("my.out","w",stdout);
    read(n);read(m);rep(i,1,n) read(a[i]);
    rep(i,1,n-1){
        int u,v;read(u);read(v);e[u].pb(v);e[v].pb(u);
    }
    ze.Clear();ze.n=2;ze.m=1;
    dfs(1,0);Dfs(1,1);DFs(1);st.Build(1,1,n);
    rep(i,1,m){
        // printf("i=%d\n",i);
        int u,v;read(u);read(v);
        Change(u,v);
        Matrix now=st.Ask(1,1,n,id[1],id[en[i]])*ze;
        printf("%d\n",max(now.a[0][0],now.a[1][0]));
    }
    return 0;
}

/*
+ 忘记 Build,Build 函数写错
+ 矩阵乘法写错
*/