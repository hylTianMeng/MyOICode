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

struct Squ{
    int id;P s;
    inline Squ(){}
    inline Squ(int id,P s) : id(id),s(s) {}
    inline bool operator < (const Squ &b)const{
        if(s.fi!=b.s.fi) return s.fi<b.s.fi;return s.se<b.s.se;
    }
}sq[N];

inline void Print(const Squ b){
    printf("yuan id=%lld l=%lld r=%lld\n",b.id,b.s.fi,b.s.se);
}

struct BIT{
    int p[N];
    inline int lowbit(int x){return x&(-x);}
    inline void Add(int w,int x){
        for(int i=w;i<N;i+=lowbit(i)) p[i]+=x;
    }
    inline int Ask(int w){
        int res=0;
        for(int i=w;i;i-=lowbit(i)) res+=p[i];return res;
    }
    inline int Ask(int l,int r){
        if(r<l) return 0;return Ask(r)-Ask(l-1);
    }
}bit;

int R[N];

#define st SegmentTree
namespace SegmentTree{
    #define ls(k) k<<1
    #define rs(k) k<<1|1
    struct Node{
        P minval,minr;
        int tag;
    }p[N<<2];
    inline void A(int k,int x){
        p[k].minval.fi+=x;p[k].tag+=x;
    }
    inline void PushDown(int k){
        if(p[k].tag){A(ls(k),p[k].tag);A(rs(k),p[k].tag);p[k].tag=0;}
    }
    inline void PushUp(int k){
        p[k].minval=min(p[ls(k)].minval,p[rs(k)].minval);
        p[k].minr=min(p[ls(k)].minr,p[rs(k)].minr);
    }
    inline void Change(int k,int l,int r,int z,int y,int x,int op){
        if(z<=l&&r<=y){if(op==1) A(k,x);else p[k].minval.fi=x;return;}PushDown(k);int mid=(l+r)>>1;
        if(z<=mid) Change(ls(k),l,mid,z,y,x,op);
        if(mid<y) Change(rs(k),mid+1,r,z,y,x,op);PushUp(k);
    }
    inline void Change(int k,int l,int r,int w,int x){
        if(l==r){p[k].minr.fi=x;return;}PushDown(k);int mid=(l+r)>>1;
        if(w<=mid) Change(ls(k),l,mid,w,x);
        else Change(rs(k),mid+1,r,w,x);PushUp(k);
    }
    inline P GetMinval(){return p[1].minval;}
    inline P GetMinr(int k,int l,int r,int z,int y){
        if(z<=l&&r<=y) return p[k].minr;PushDown(k);int mid=(l+r)>>1;P ans(INF,INF);
        if(z<=mid) ans=min(ans,GetMinr(ls(k),l,mid,z,y));
        if(mid<y) ans=min(ans,GetMinr(rs(k),mid+1,r,z,y));PushUp(k);return ans;
    }
    inline void Build(int k,int l,int r){
        if(l==r){p[k].minr=mp(sq[l].s.se,sq[l].id);p[k].minval=mp(INF,sq[l].id);return;}int mid=(l+r)>>1;
        Build(ls(k),l,mid);Build(rs(k),mid+1,r);PushUp(k);
    }
}
set<P> Sw;
set<Squ> SL,SR;
map<int,int> Map;
int ID[N],n,c[N],ct;

inline vc<P> Getw(int l,int r){
    vc<P> v;v.clear();
    auto it1=Sw.lower_bound(mp(l,-INF));
    auto it2=Sw.upper_bound(mp(r,-INF));
    for(auto now=it1;now!=it2;now++) v.pb(*now);
    Sw.erase(it1,it2);return v;
}
inline P Getc(int l,int r){
    auto it1=SL.upper_bound(Squ(INF,mp(l,INF)));
    it1--;
    auto it2=SR.lower_bound(Squ(INF,mp(r,-INF)));
    return mp(ID[(*it2).id],ID[(*it1).id]);
}
inline P GetPreAnsNext(int id){
    auto it1=SL.upper_bound(sq[id]);auto it2=it1;
    it1--;
    return mp(ID[(*it1).id],ID[(*it2).id]);
}
inline void Insert(int id1,int id2){
    id1++;P now(-1,-1);
    while(id1<=n){
        P minr=st::GetMinr(1,1,n,id1,n);
        if(minr.fi==INF) break;
        if(minr.fi>=sq[id2].s.se) break;
        id1=R[ID[minr.se]]+1;
        now=sq[ID[minr.se]].s;
        int id=ID[minr.se];
        st::Change(1,1,n,id,INF);
        st::Change(1,1,n,id,id,sq[id].s.se-sq[id].s.fi+bit.Ask(Map[sq[id].s.fi],Map[sq[id].s.se]-1),0);
        SL.insert(sq[id]);
        SR.insert({sq[id].id,mp(sq[id].s.se,sq[id].s.fi)});
    }
}

inline void Init(){
    rep(i,1,n){
        c[++ct]=sq[i].s.fi;c[++ct]=sq[i].s.se;
    }
    sort(c+1,c+ct+1);int len=unique(c+1,c+ct+1)-c-1;
    rep(i,1,len) Map[c[i]]=i;
    rep(i,1,len-1){
        Sw.insert(mp(c[i],c[i+1]));
    }
    int minr=INF;
    sq[n+1].s=mp(INF,INF);
    vi v;v.clear();
    dec(i,1,n){
        if(sq[i-1].s.fi==sq[i].s.fi) continue;
        if(sq[i].s.se>=minr) continue;
        cmin(minr,sq[i].s.se);
        v.pb(i);
    }
    int l=1;
    while(l<=n){
        int r=l;while(r<=n&&sq[r+1].s.fi==sq[l].s.fi) r++;
        rep(j,l,r) R[j]=r;l=r+1;
    }
    st::Build(1,1,n);
    for(int x:v){
        st::Change(1,1,n,x,x,sq[x].s.se-sq[x].s.fi,0);
        st::Change(1,1,n,x,INF);
        SL.insert(sq[x]);
        SR.insert({sq[x].id,mp(sq[x].s.se,sq[x].s.fi)});
    }
    SL.insert({0,mp(-INF,-INF)});
    SL.insert({n+1,mp(INF,INF)});
    SR.insert({0,mp(-INF,-INF)});
    SR.insert({n+1,mp(INF,INF)});
}

signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);
    rep(i,1,n){
        int l,r;read(l);read(r);l++;r++;
        sq[i].s=mp(l,r);sq[i].id=i;
    }
    sort(sq+1,sq+n+1);rep(i,1,n) ID[sq[i].id]=i;ID[n+1]=n+1;
    Init();
    rep(i,1,n){
        P minval=st::GetMinval();
        printf("%lld ",minval.se);
        int id=ID[minval.se];vc<P> v=Getw(sq[id].s.fi,sq[id].s.se);
        for(P x:v){
            P now=Getc(x.fi,x.se);
            if(now.fi&&now.se) st::Change(1,1,n,now.fi,now.se,-x.se+x.fi,1);
            assert(!((now.fi!=0)^(now.se!=0))); 
            int Mid=Map[x.fi];bit.Add(Mid,-x.se+x.fi);
        }
        st::Change(1,1,n,id,id,INF,0);
        st::Change(1,1,n,id,INF);SL.erase(sq[id]);SR.erase(Squ(sq[id].id,mp(sq[id].s.se,sq[id].s.fi)));
        P now=GetPreAnsNext(id);
        Insert(now.fi,now.se);
    }
    puts("");
    return 0;
}
/*
+ 未处理前驱边界。
+ set 查询混乱
+ Build 忘记 PushUp
+ 线段树边界忘记 0 特判
+ inf 开小
+ Insert 中 SL,SR 未更新。
+ tag 未清零
+ lower_bound upper_bound 用错
+ se fi 写反
+ Init 去掉多余区间算法假了 N 次。
+ ID[n+1]=n+1
+ Insert 区间去重有问题导致复杂度错误
*/