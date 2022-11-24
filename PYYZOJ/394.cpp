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
#define N 200010
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

int n,q,t,a[N],b[N],mod,c[N<<2];
struct Node{
    int siz,val,ls,rs;
    inline Node(){}
    inline Node(int siz,int val) : siz(siz),val(val) {}
}p[N*40];
int rt[N],fa[N<<2][21],dep[N<<2],ans;
vi e[N<<2];
#define ls(k) p[k].ls
#define rs(k) p[k].rs
struct SegmentTree{
    int tot;
    inline SegmentTree(){tot=0;}
    inline void PushUp(int k){p[k].siz=p[ls(k)].siz+p[rs(k)].siz;}
    inline void Change(int &k,int last,int l,int r,int w,int x1,int x2){
        k=++tot;p[k]=p[last];int mid=(l+r)>>1;
        if(l==r){p[k].siz=x1;p[k].val=x2;return;}
        if(w<=mid) Change(ls(k),ls(last),l,mid,w,x1,x2);
        else Change(rs(k),rs(last),mid+1,r,w,x1,x2);PushUp(k);
    }
    inline P Ask(int k,int l,int r,int siz){
        if(l==r) return mp(l,p[k].val);int mid=(l+r)>>1;
        if(siz<=p[ls(k)].siz) return Ask(ls(k),l,mid,siz);
        else return Ask(rs(k),mid+1,r,siz-p[ls(k)].siz);
    }
    inline void Build(int &k,int l,int r){
        k=++tot;int mid=(l+r)>>1;if(l==r){p[k].siz=1;p[k].val=l;return;}
        Build(ls(k),l,mid);Build(rs(k),mid+1,r);PushUp(k);
    }
}st;

inline void dfs(int k,int fat){
    fa[k][0]=fat;rep(i,1,20) fa[k][i]=fa[fa[k][i-1]][i-1];dep[k]=dep[fat]+1;
    for(int to:e[k]) if(to!=fat) dfs(to,k);
}
inline int Lca(int a,int b){
    if(dep[a]<dep[b]) swap(a,b);
    dec(i,0,20) if(dep[fa[a][i]]>=dep[b]) a=fa[a][i];if(a==b) return a;
    dec(i,0,20) if(fa[a][i]!=fa[b][i]) a=fa[a][i],b=fa[b][i];return fa[a][0];
}
inline int getid(int x){
    return lower_bound(b+1,b+n+2,x)-b;
}
inline int ID(int x){
    int id=lower_bound(b+1,b+n+2,x)-b-1;
    return x-(1+id)*id/2;
}

signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);read(q);read(t);mod=(n+1)*(n+2)/2;
    rep(i,1,n) read(a[i]);int tot=n+1;st.Build(rt[n+1],1,n+1);
    rep(i,1,n+1) b[i]=(1+i)*i/2;
    dec(i,1,n){
        // printf("ID(a[i])=%d\n",ID(a[i]));
        P now=st.Ask(rt[i+1],1,n+1,ID(a[i]));
        P now2=st.Ask(rt[i+1],1,n+1,ID(a[i])+1);
        // printf("now.fi=%d now.se=%d now2.fi=%d now2.se=%d\n",now.fi,now.se,now2.fi,now2.se);
        st.Change(rt[i],rt[i+1],1,n+1,now2.fi,0,-1);
        ++tot;st.Change(rt[i],rt[i],1,n+1,now.fi,1,tot);
        e[tot].pb(now.se);e[tot].pb(now2.se);
        // printf("Add %lld %lld\n",tot,now.se);printf("Add %lld %lld\n",tot,now2.se);
    }
    dfs(tot,0);
    rep(i,1,n) c[st.Ask(rt[getid(a[i])],1,n+1,ID(a[i])).se]=a[i];
    rep(i,1,q){
        int x,y;read(x);read(y);
        x=(x-1+t*ans)%mod+1;y=(y-1+t*ans)%mod+1;
        // printf("getid(x)=%d ID(x)=%d x=%d\n",getid(x),ID(x),x);
        P now=st.Ask(rt[getid(x)],1,n+1,ID(x));
        // printf("getid(y)=%d ID(y)=%d y=%d\n",getid(y),ID(y),y);
        P now2=st.Ask(rt[getid(y)],1,n+1,ID(y));
        // printf("now.se=%d now2.se=%d\n",now.se,now2.se);
        int l=Lca(now.se,now2.se);
        if(now.se==now2.se){
            if(x<y) swap(x,y);printf("%lld\n",(ans=y));
        }
        else if(l==now.se||l==now2.se){
            if(l==now.se) printf("%lld\n",(ans=x));
            else printf("%lld\n",(ans=y));
        }
        else{
            // puts("here");printf("l=%d\n",l);
            printf("%lld\n",(ans=c[l]));
        }
    }
    return 0;
}