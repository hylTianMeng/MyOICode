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

#define SegmentTree ST
namespace SegmentTree{
    #define ls(k) k<<1
    #define rs(k) k<<1|1
    struct Node{
        int col,val,sum,tcv,tcc,len;
    }p[N<<2];
    inline void Cc(int k,int co){
        p[k].col=co;p[k].tcc=co;
    }
    inline void Cv(int k,int va){
        p[k].val=va;p[k].tcv=va;
        p[k].sum=va*p[k].len;
    }
    inline void PushDown(int k){
        if(p[k].tcc){Cc(ls(k),p[k].tcc);Cc(rs(k),p[k].tcc);p[k].tcc=0;}
        if(p[k].tcv!=-1){Cv(ls(k),p[k].tcv);Cv(rs(k),p[k].tcv);p[k].tcv=-1;}
    }
    inline void PushUp(int k){p[k].sum=p[ls(k)].sum+p[rs(k)].sum;}
    inline void ChangeV(int k,int l,int r,int z,int y,int x){
        if(z<=l&&r<=y){Cv(k,x);return;}PushDown(k);int mid=(l+r)>>1;
        if(z<=mid) ChangeV(ls(k),l,mid,z,y,x);
        if(mid<y) ChangeV(rs(k),mid+1,r,z,y,x);PushUp(k);
    }
    inline void ChangeC(int k,int l,int r,int z,int y,int x){
        if(z<=l&&r<=y){Cc(k,x);return;}PushDown(k);int mid=(l+r)>>1;
        if(z<=mid) ChangeC(ls(k),l,mid,z,y,x);
        if(mid<y) ChangeC(rs(k),mid+1,r,z,y,x);PushUp(k);
    }
    inline void Build(int k,int l,int r){
        p[k].tcv=-1;
        int mid=(l+r)>>1;p[k].len=r-l+1;if(l==r) return;
        Build(ls(k),l,mid);Build(rs(k),mid+1,r);
    }
    inline int Ask(int k,int l,int r,int z,int y){
        if(z<=l&&r<=y) return p[k].sum;PushDown(k);int mid=(l+r)>>1,ans=0;
        if(z<=mid) ans+=Ask(ls(k),l,mid,z,y);
        if(mid<y) ans+=Ask(rs(k),mid+1,r,z,y);PushUp(k);return ans;
    }
    inline int Gc(int k,int l,int r,int w){
        if(l==r) return p[k].col;PushDown(k);int mid=(l+r)>>1;
        if(w<=mid) return Gc(ls(k),l,mid,w);else return Gc(rs(k),mid+1,r,w);PushUp(k);
    }
    inline void Clear(){mset(p,0);}
}

int t,n,m,id[N],rk[N],tot,fa[N],son[N],siz[N],dep[N],top[N];
vi e[N];

inline void dfs(int k,int fat){
    dep[k]=dep[fat]+1;fa[k]=fat;siz[k]=1;
    for(int to:e[k]) if(to!=fat){dfs(to,k);siz[k]+=siz[to];if(siz[son[k]]<siz[to]) son[k]=to;}
}
inline void Dfs(int k,int t){
    id[k]=++tot;rk[tot]=k;top[k]=t;if(son[k]) Dfs(son[k],t);
    for(int to:e[k]) if(to!=son[k]&&to!=fa[k]) Dfs(to,to);
}
inline void Clear(){
    ST::Clear();rep(i,1,n) e[i].clear(),id[i]=rk[i]=fa[i]=son[i]=siz[i]=dep[i]=top[i]=0;tot=0;
}
inline void Change(int a,int b,int v){
    int A=a,B=b,l=-1;
    while(top[a]!=top[b]){
        if(dep[top[a]]<dep[top[b]]) swap(a,b);
        ST::ChangeC(1,1,n,id[top[a]],id[a],v);
        if(top[a]!=a) ST::ChangeV(1,1,n,id[son[top[a]]],id[a],1);
        a=fa[top[a]];
        if(son[a]) ST::ChangeV(1,1,n,id[son[a]],id[son[a]],0);
    }
    if(dep[a]<dep[b]) swap(a,b);l=b;
    // if(l==A){if(son[A]) ST::ChangeV(1,1,n,id[son[A]],id[son[A]],0);}
    // else if(l==B){if(son[B]) ST::ChangeV(1,1,n,id[son[B]],id[son[B]],0);}
    // else {if(son[A]) ST::ChangeV(1,1,n,id[son[A]],id[son[A]],0);if(son[B]) ST::ChangeV(1,1,n,id[son[B]],id[son[B]],0);}
    // printf("id[%d]=%d id[%d]=%d\n",b,id[b],a,id[a]);
    ST::ChangeC(1,1,n,id[b],id[a],v);
    if(a!=b) ST::ChangeV(1,1,n,id[son[b]],id[a],1);
    ST::ChangeV(1,1,n,id[b],id[b],0);
}
inline int Ask(int a,int b){
    int Ans=0;
    while(top[a]!=top[b]){
        if(dep[top[a]]<dep[top[b]]) swap(a,b);
        if(a!=top[a]) Ans+=ST::Ask(1,1,n,id[son[top[a]]],id[a]);
        int t=top[a];a=fa[top[a]];
        int c1=ST::Gc(1,1,n,id[t]),c2=ST::Gc(1,1,n,id[a]);
        if(c1==c2&&c1!=0){
            // puts("here");
            Ans++;
        }
    }
    // printf("Ans=%d\n",Ans);
    if(dep[a]<dep[b]) swap(a,b);
    if(a!=b) Ans+=ST::Ask(1,1,n,id[son[b]],id[a]);
    return Ans;
}

int main(){
    // freopen("edge2.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(t);
    while(t--){
        // printf("t=%d\n",t);
        read(n);read(m);
        rep(i,1,n-1){
            int u,v;read(u);read(v);e[u].pb(v);e[v].pb(u);
        }
        ST::Build(1,1,n);
        dfs(1,0);Dfs(1,0);
        // rep(i,1,n) printf("son[%d]=%d\n",i,son[i]);
        rep(i,1,m){
            int op,a,b;read(op);read(a);read(b);
            if(op==1){
                Change(a,b,i);
            }
            else{
                printf("%d\n",Ask(a,b));
            }
        }
        Clear();
    }
    return 0;
}