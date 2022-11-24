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

struct SegmentTree{
    struct Node{
        int s0,s1,tg,len;
    }p[N<<2];
    #define ls(k) k<<1
    #define rs(k) k<<1|1
    inline void PushUp(int k){p[k].s0=p[ls(k)].s0+p[rs(k)].s0;p[k].s1=p[ls(k)].s1+p[rs(k)].s1;}
    inline void C(int k){
        p[k].s1=p[k].len;p[k].s0=0;p[k].tg=1;
    }
    inline void PushDown(int k){
        if(p[k].tg) C(ls(k)),C(rs(k)),p[k].tg=0;
    }
    inline void Change(int k,int l,int r,int z,int y){
        if(z<=l&&r<=y){C(k);return;}int mid=(l+r)>>1;PushDown(k);
        if(z<=mid) Change(ls(k),l,mid,z,y);if(mid<y) Change(rs(k),mid+1,r,z,y);PushUp(k);
    }
    inline int Ask(){return p[1].s1;}
    inline void Build(int k,int l,int r){
        p[k].len=r-l+1;if(l==r) return;int mid=(l+r)>>1;Build(ls(k),l,mid);Build(rs(k),mid+1,r);
    }
}st;

int n;
vc<P> a[N],b[N];

int main(){
    read(n);
    
}