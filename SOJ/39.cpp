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

int f[N],K,n,c[N],w[N],sum[N];

inline int ge(int nowid,int up){
    int l=nowid,r=n;
    while(l<r){
        int mid=(l+r+1)>>1;
        if(sum[mid]-sum[nowid]<=up) l=mid;
        else r=mid-1;
    }
    return l;
}

signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(K);read(n);
    rep(i,1,K) read(c[i]);rep(i,1,n) read(w[i]),sum[i]=sum[i-1]+w[i];
    mset(f,-1);f[0]=0;
    rep(i,0,(1<<K)-1)if(f[i]!=-1){
        rep(j,0,K-1){
            if((i>>j)&1) continue;
            int now=i|(1<<j);
            int nowid=f[i],up=c[j+1];
            int id=ge(nowid,up);
            // if(now==1){
            //     printf("nowid=%lld up=%lld id=%lld\n",nowid,up,id);
            // }
            cmax(f[now],id);
        }
    }
    int ans=-1;
    rep(i,0,(1<<K)-1){
        assert(f[i]<=n);
        if(f[i]>=n){
            // printf("i=%lld f[i]=%lld\n",i,f[i]);
            int nowans=0;
            rep(j,0,K-1){
                if((i>>j)&1) continue;
                nowans+=c[j+1];
            }
            cmax(ans,nowans);
        }
    }
    printf("%lld\n",ans);
    return 0;
}