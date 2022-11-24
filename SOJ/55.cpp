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

int n,K,a[N],f[N][21],ans[N];
vi e[N];

inline void dfs(int k,int fa){
    f[k][0]+=a[k];
    for(int to:e[k]) if(to!=fa){
        dfs(to,k);
    }
    for(int to:e[k]) if(to!=fa){
        rep(i,1,20) f[k][i]+=f[to][i-1];
    }
    // rep(i,0,20){
    //     printf("f[%d][%d]=%d\n",k,i,f[k][i]);
    // }
}
inline void dp(int k,int fa){
    rep(i,0,K){
        ans[k]+=f[k][i];
        // printf("f[%d][%d]=%d\n",k,i,f[k][i]);
    }
    for(int to:e[k])if(to!=fa){
        rep(i,1,20) f[k][i]-=f[to][i-1];
        rep(i,1,20) f[to][i]+=f[k][i-1];
        dp(to,k);
        // rep(i,0,20) f[k][i]=t1[i];
        // rep(i,0,20) f[to][i]=t2[i];
        rep(i,1,20) f[to][i]-=f[k][i-1];
        rep(i,1,20) f[k][i]+=f[to][i-1];
    }
}

int main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);read(K);
    rep(i,1,n-1){
        int u,v;read(u);read(v);e[u].pb(v);e[v].pb(u);
    }
    rep(i,1,n) read(a[i]);
    dfs(1,0);
    dp(1,0);
    rep(i,1,n) printf("%d\n",ans[i]);
    return 0;
}