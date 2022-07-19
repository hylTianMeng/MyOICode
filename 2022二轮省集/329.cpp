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

const int INF=0x3f3f3f3f;
const dd eps=1e-9;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

int n,f[N][2][3];
char s[N];
vi e[N];
bool vis[N];

inline void pre(int k,int fa){
    vis[k]=s[k]-'0';
    for(int to:e[k]) if(to!=fa){
        pre(to,k);vis[k]&=vis[to];
    }
}
inline void dfs(int u,int fa){
    int tmp[2][3];mset(tmp,0);
    int op=(s[u]=='1');rep(i,0,2) f[u][op^1][i]=tmp[op^1][i]=1;
    rep(i,0,2) f[u][op][i]=tmp[op][i]=INF;
    for(int to:e[u]) if(to!=fa&&!vis[to]){
        dfs(to,u);mset(f[u],INF);
        rep(i,0,1)rep(j,0,2)rep(k,0,1)rep(o,0,j){
            cmin(f[u][i][j],f[to][k][o]+tmp[i^k^(o&1)][j-o]+2*(k^1^(o==2))+((o&1)^1));
        }
        rep(i,0,1)rep(j,0,2)tmp[i][j]=f[u][i][j];
    }
    // rep(i,0,1)rep(j,0,2)printf("f[%d][%d][%d]=%d\n",u,i,j,f[u][i][j]);
}

signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);scanf("%s",s+1);
    rep(i,1,n-1){
        int u,v;read(u);read(v);e[u].pb(v);e[v].pb(u);
    }
    int rt=-1;rep(i,1,n) if(s[i]=='0') rt=i;pre(rt,0);dfs(rt,0);
    printf("%lld\n",min(f[rt][1][2],min(f[rt][1][0],f[rt][1][1])));
    return 0;
}