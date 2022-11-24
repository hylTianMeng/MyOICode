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
#define pb emplace_back
#define N 70010
#define M 110
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
const int mod=1e9+7;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

int n,K,c[N],ct,b[N],g[M][N],sum[M][N];

signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);read(K);
    for(int i=1,j;i<=n;i=j+1){
        j=n/(n/i);
        c[++ct]=n/i;
        b[ct]=i;
    }
    b[ct+1]=n+1;
    rep(i,1,ct) g[0][i]=1;
    rep(i,1,ct) sum[0][i]=(sum[0][i-1]+(b[i+1]-b[i])*g[0][i]%mod)%mod;
    // rep(i,1,ct){
        // printf("g[0][%lld]=%lld\n",i,g[0][i]);
        // printf("sum[0][%lld]=%lld\n",i,sum[0][i]);
    // }
    rep(i,1,K){
        rep(j,1,ct){
            int id=upper_bound(b+1,b+ct+2,c[j])-b-1;
            g[i][j]=(sum[i-1][id]-(b[id+1]-c[j]-1)*g[i-1][id]%mod+mod)%mod;
            // printf("g[%lld][%lld]=%lld\n",i,j,g[i][j]);
            // printf("sum[%lld][%lld]=%lld\n",i,j,sum[i][j]);
        }
        rep(j,1,ct) sum[i][j]=(sum[i][j-1]+(b[j+1]-b[j])*g[i][j]%mod)%mod;
    }
    printf("%lld\n",g[K][1]);
    return 0;
}