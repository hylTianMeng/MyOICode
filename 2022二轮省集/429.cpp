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
#define N 51
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

int dp[N][N][N][2][2][2][2],n,k,L[N][2],C[N];

inline int bit(int x,int p){return (x>>p)&1;}

inline int dfs(int p,int l,int r,int f,int x,int g,int y){
    if(p==k) return (r-l+1==2)?0:1e18;
    int &now=dp[p][l][r][f][x][g][y];
    if(now!=-1) return now;
    now=1e18;now=dfs(p+1,l,r,f,0,g,0)+(l&&r<=n&&(x^y^bit(L[l][f]^L[r][g],p))==1)*C[p];
    rep(k,l+1,r-1){
        if(!p) rep(j,0,1) cmin(now,dfs(p,l,k,f,x,j,0)+dfs(p,k,r,j,0,g,y));
        if((L[k][0]^L[k][1])>>(p+1)) rep(j,0,1) if(bit(L[k][j],p)==j) cmin(now,dfs(p,l,k,f,x,j,1)+dfs(p,k,r,j,1,g,y));
    }
    // printf("%lld %lld %lld %lld %lld %lld %lld=%lld\n",p,l,r,f,x,g,y,now);
    return now;
}

signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);read(k);
    rep(i,1,n){
        read(L[i][0]);read(L[i][1]);
    }
    mset(dp,-1);
    rep(i,0,k-1) read(C[i]);
    int Ans=dfs(0,0,n+1,0,0,0,0);
    printf("%lld\n",Ans);
    return 0;
}