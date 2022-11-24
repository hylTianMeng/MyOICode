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

struct Point{
    ll x,y;
    inline Point(){}
    inline Point(ll x,ll y) : x(x),y(y) {}
    inline ll operator ^ (const Point &b)const{return x*b.y-y*b.x;}
    inline Point operator - (const Point &b)const{return Point(x-b.x,y-b.y);}
    inline bool operator < (const Point &b)const{return x<b.x||(x==b.x&&y<b.y);}
}c[N];

struct Node{
    vc<Point> v,sta;
    int id,top;
    inline void GetSta(){
        top=0;
        for(Point x:v){
            while(top&&((x-sta[top])^(sta[top-1]-sta[top]))>=0) top--;
            sta[++top]=x;
        }
        id=top;
    }
    inline int Ask(int k){
        Point now(1,k);
        while(id&&((sta[id]-sta[id-1])^(now))>=0) id--;
        return sta[id].y-sta[id].x*k;
    }
}p[N<<2];

#define ls(k) k<<1
#define rs(k) k<<1|1
struct SegmentTree{
    inline void Build(int k,int l,int r){
        p[k].v.clear();
        p[k].v.resize(r-l+1);p[k].sta.resize(r-l+2);int mid=(l+r)>>1;
        if(l==r){p[k].v[0]=c[l];p[k].GetSta();return;}
        // exit(0);
        Build(ls(k),l,mid);Build(rs(k),mid+1,r);
        merge(p[ls(k)].v.begin(),p[ls(k)].v.end(),p[rs(k)].v.begin(),p[rs(k)].v.end(),p[k].v.begin());
        // exit(0);
        p[k].GetSta();
    }
    inline ll Ask(int k,int l,int r,int z,int y,int x){
        if(z<=l&&r<=y) return p[k].Ask(x);int mid=(l+r)>>1;
        ll ans=0;
        if(z<=mid) ans=max(ans,Ask(ls(k),l,mid,z,y,x));
        if(mid<y) ans=max(ans,Ask(rs(k),mid+1,r,z,y,x));return ans;
    }
}st;

int n,a[N],b[N],B[N];
ll Ans;

inline void Solve(int l,int r){
    int mid=(l+r)>>1;
    int ma=INF,mb=INF,R=mid-1;
    dec(i,l,mid){
        cmin(ma,a[i]);cmin(mb,b[i]);
        while(R+1<=r&&a[R+1]>=ma&&b[R+1]>=mb) R++;
        cmax(Ans,ma*mb*(R-i+1));
    }
    B[mid]=b[mid];rep(i,mid+1,r) B[i]=min(B[i-1],b[i]);
    rep(i,mid,r) c[i-mid+1].x=-B[i],c[i-mid+1].y=B[i]*(i-mid);
    // exit(0);
    st.Build(1,1,r-mid+1);
    // exit(0);
    R=mid-1;ma=INF;mb=INF;
    int L=mid;
    // exit(0);
    dec(i,l,mid){
        cmin(ma,a[i]);cmin(mb,b[i]);
        while(L<=r&&b[L]>mb) L++;if(L>r) break;
        while(R+1<=r&&a[R+1]>=ma) R++;
        if(L>R) continue;
        Ans=max(Ans,ma*st.Ask(1,1,r-mid+1,L-mid+1,R-mid+1,mid-i+1));
    }
}

inline void Divi(int l,int r){
    if(l>r) return;int mid=(l+r)>>1;
    Solve(l,r);reverse(a+l,a+r+1);reverse(b+l,b+r+1);
    Solve(l,r);reverse(a+l,a+r+1);reverse(b+l,b+r+1);
    Divi(l,mid-1);Divi(mid+1,r);
}

signed main(){
    // freopen("my.in","r",stdin);
    read(n);rep(i,1,n) read(a[i]),read(b[i]);
    Divi(1,n);
    printf("%lld\n",Ans);
    return 0;
}