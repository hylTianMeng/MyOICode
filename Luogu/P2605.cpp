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
#define N 110
#define M 20010
using namespace std;

typedef double dd;
typedef long double ld;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
// #define int long long
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

int f[N][M],d[M],c[M],s[M],w[M],k,n;

struct Node{
    int minn,len,sum,tag;
    inline Node(){}
    inline Node(int minn,int len,int sum,int tag) : minn(minn),len(len),sum(sum),tag(tag) {}
}p[M<<2];
#define ls(k) k<<1
#define rs(k) k<<1|1
struct SegmentTree{
    inline void PushUp(int k){
        p[k].sum=p[ls(k)].sum+p[rs(k)].sum;p[k].minn=min(p[ls(k)].minn,p[rs(k)].minn);
    }
    inline void A(int k,int x){
        p[k].sum+=x*p[k].len;p[k].tag+=x;p[k].minn+=x;
    }
    inline void PushDown(int k){
        if(p[k].tag){
            A(ls(k),p[k].tag);A(rs(k),p[k].tag);p[k].tag=0;
        }
    }
    inline void Add(int k,int l,int r,int z,int y,int x){
        if(z<=l&&r<=y){A(k,x);return;}int mid=(l+r)>>1;PushDown(k);
        if(z<=mid) Add(ls(k),l,mid,z,y,x);
        if(mid<y) Add(rs(k),mid+1,r,z,y,x);PushUp(k);
    }
    inline int GetMin(int k,int l,int r,int z,int y){
        if(z<=l&&r<=y) return p[k].minn;int mid=(l+r)>>1;PushDown(k);int ans=INF;
        if(z<=mid) ans=min(ans,GetMin(ls(k),l,mid,z,y));
        if(mid<y) ans=min(ans,GetMin(rs(k),mid+1,r,z,y));return ans;
    }
    inline void Build(int k,int l,int r,int id){
        p[k].len=r-l+1;p[k].sum=p[k].tag=0;p[k].minn=INF;
        if(l==r){
            if(id>l) p[k].minn=p[k].sum=INF;
            else p[k].minn=p[k].sum=f[id][l];return;
        }int mid=(l+r)>>1;
        Build(ls(k),l,mid,id);Build(rs(k),mid+1,r,id);PushUp(k);
    }
}st;

struct sq{
    int l,r,v;
    inline bool operator < (const sq &b)const{
        return r<=b.r;
    }
}sq[M];

signed main(){
    // freopen("my.in","r",stdin);freopen("my.out","w",stdout);
    read(n);read(k);rep(i,2,n) read(d[i]);rep(i,1,n) read(c[i]);rep(i,1,n) read(s[i]);rep(i,1,n) read(w[i]);
    rep(i,1,n) sq[i].l=max(0,d[i]-s[i]),sq[i].r=d[i]+s[i],sq[i].v=w[i];sort(sq+1,sq+n+1);
    int sum=0;rep(i,1,n) sum+=w[i];
    n++;d[n]=INF;c[n]=0;s[n]=0;w[n]=INF;k++;
    rep(i,1,k){
        st.Build(1,0,n,i-1);int id=0;
        rep(j,i,n){
            while(sq[id+1].r<d[j]&&id<n){
                id++;
                int rk=lower_bound(d+1,d+n+1,sq[id].l)-d;rk--;
                if(i!=1){
                    if(rk>=0) st.Add(1,0,n,0,rk,sq[id].v);
                }
                else{
                    st.Add(1,0,n,0,n,sq[id].v);
                }
            }
            f[i][j]=st.GetMin(1,0,n,0,j-1)+c[j];
            // printf("f[%d][%d]=%d\n",i,j,f[i][j]);
        }
    }
    int ans=INF;
    rep(i,1,k) ans=min(ans,f[i][n]);
    printf("%d\n",ans);ans=min(ans,sum);
    return 0;
}