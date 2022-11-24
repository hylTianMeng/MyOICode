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
#define N 300010
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

struct Node{
    int ls,rs,v,dist;
    inline Node(){}
    inline Node(int ls,int rs,int v,int dist) : ls(ls),rs(rs),v(v),dist(dist) {}
}p[N*20];
struct edge{
    int to,next,w;
    inline void Init(int to_,int ne_,int w_){
        to=to_;next=ne_;w=w_;
    }
}li[N<<1];
int rt[N],head[N],tail;
inline void Add(int from,int to,int w){
    li[++tail].Init(to,head[from],w);head[from]=tail;
}
int tot=0;
inline int NewNode(int val){
    ++tot;p[tot]=Node(0,0,val,1);assert(tot<=N*20);
    return tot;
}
#define ls(k) p[k].ls
#define rs(k) p[k].rs
struct LeftHeap{
    inline int Merge(int a,int b){
        if(!a||!b) return a+b;if(p[b].v>p[a].v) swap(a,b);
        rs(a)=Merge(rs(a),b);if(p[rs(a)].dist>p[ls(a)].dist) swap(rs(a),ls(a));
        p[a].dist=p[rs(a)].dist+1;return a;
    }
    inline int Pop(int k){return Merge(ls(k),rs(k));}
}st;

int n,m;
ll sum[N];

inline void dfs(int k,int l){
    // printf("k=%d\n",k);
    int cnt=0;
    Next(k){
        cnt++;
        int to=li[x].to,w=li[x].w;dfs(to,w);
        sum[k]+=sum[to]+w;
    }
    Next(k){
        int to=li[x].to;
        rt[k]=st.Merge(rt[k],rt[to]);
    }
    if(k==1) return;
    if(!cnt){
        rt[k]=NewNode(l);st.Merge(rt[k],NewNode(l));
    }
    else{
        rep(i,1,cnt-1){
            rt[k]=st.Merge(ls(rt[k]),rs(rt[k]));
        }
        int a=rt[k];rt[k]=st.Merge(ls(rt[k]),rs(rt[k]));
        int b=rt[k];rt[k]=st.Merge(ls(rt[k]),rs(rt[k]));
        a+=l;b+=l;rt[k]=st.Merge(rt[k],NewNode(a));st.Merge(rt[k],NewNode(b));
    }
}

P s[N];int top;

int main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);read(m);
    rep(i,2,n+m){
        int fat,w;read(fat);read(w);Add(fat,i,w);
    }
    dfs(1,0);
    int maxx=p[rt[1]].v;int now=0;while(p[rt[1]].v==maxx) rt[1]=st.Pop(rt[1]);
    while(rt[1]){
        int maxx=p[rt[1]].v;
        while(p[rt[1]].v==maxx) rt[1]=st.Pop(rt[1]),now--;
        s[++top]=mp(maxx,now);
    }
    rep(i,1,top) printf("%d %d\n",s[i].fi,s[i].se);
    int ans=sum[1];
    printf("ans=%d\n",ans);
    int lst=0;
    dec(i,1,top){
        int len=s[i].fi-lst;ans+=len*s[i].se;lst=s[i].fi;
    }
    printf("%d\n",ans);
    return 0;
}