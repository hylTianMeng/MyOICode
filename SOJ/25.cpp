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
#define N 1000100
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
//Change!!!
const int Len=1e6;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

int n,a[N],li[N];
ld ans[N];

struct Que{
    int q[N],l,r;
    inline void AddMax(int id){
        while(l<r&&a[q[r]]<=a[id]) r--;q[++r]=id;
    }
    inline void AddMin(int id){
        while(l<r&&a[q[r]]>=a[id]) r--;q[++r]=id;
    }
    inline void Del(int id){
        while(q[l+1]<=id&&l<r) l++;
    }
    inline int RM(){return a[q[l+1]];}
    inline void Clear(){l=r=0;mset(q,0);}
}qmx,qmn;

inline int Solve(ld x){
    // printf("x=%Lf\n",x);
    int ans=-1;
    int l=0,r=1;qmx.Clear();qmn.Clear();qmx.AddMax(r);qmn.AddMin(r);
    while(r<=n){
        while(qmx.RM()-qmn.RM()>=x){
            qmx.Del(l);qmn.Del(l);
            l++;
        }
        if(l>1) ans=max(ans,r-(l-1)+1);
        else{
            if(l==1) ans=max(ans,r-l+1)+1;
            else ans=max(ans,r-l)+1;
        }
        r++;
        qmx.AddMax(r);qmn.AddMin(r);
        // printf("l=%d r=%d\n",l,r);
        // printf("maxx=%d minn=%d\n",qmx.RM(),qmn.RM());
        // printf("maxx-minn=%d\n",qmx.RM()-qmn.RM());
    }
    // printf("ans=%d\n",ans);
    if(ans==-1) return n+1;
    return ans;
}
inline int chose(int a,int b,ld x){
    if(fabs(a-x)<=a*0.06) return a;
    if(fabs(b-x)<=b*0.06) return b;
    assert(0);
}

int main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);rep(i,1,n) read(a[i]);
    // Solve(937959.750599);
    ld now=1;
    int ir=-1;
    for(int i=0;;i++,now*=1.06){
        li[i]=Solve(now);ir=i;
        if(now>Len) break;
        // printf("i=%d li[i]=%d now=%Lf\n",i,li[i],now);
    }
    now=1;
    // printf("ir=%d\n",ir);
    // for(int j=0;j<li[0];j++) ans[j]=1;
    for(int i=0;i<=ir;i++){
        // printf("li[i]=%d li[i+1]=%d\n",li[i],li[i+1]);
        for(int j=li[i];j<li[i+1];j++){
            ans[j]=now;
        }
        now*=1.06;
    }
    // rep(i,2,n) printf("%Lf\n",ans[i]);
    rep(i,2,n) printf("%d\n",(int)ceil(ans[i]));
    // rep(i,2,n) printf("%d\n",chose((int)ans[i],(int)(ans[i]+0.5),ans[i]));
    return 0;
}
/*
+ 查询 c_k 的时候出错，应该是所有不满足的区间的长度的 max 加 1
+ 要满足输出的整数一定比原先的 ans[i] 大。
*/