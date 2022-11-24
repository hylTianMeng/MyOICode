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
#define N 81
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

bool vis1[N][N],vis2[N][N],vis[N*N*2+5];
int n,m,c[N*N*2+5],mat[N*N*2+5];
char s[N];
vi e[N*N*2+5],L;

inline int ID(int x,int y,int op){
    int ans=0;ans+=(x-1)*(2*m-1);
    if(op==0) return ans+y;return ans+(m-1)+y;
}
inline void Add(int from,int to){
    e[from].pb(to);e[to].pb(from);
}
inline void dfs(int k,int co){
    c[k]=co;if(c[k]==1) L.pb(k);
    for(int to:e[k]) if(!c[to]) dfs(to,co*(-1));
    else if(c[to]){assert(c[k]!=c[to]);}
}
inline bool Dfs(int k){
    for(int to:e[k]){
        if(!vis[to]){
            vis[to]=1;if(!mat[to]||Dfs(mat[to])){mat[to]=k;return 1;}
        }
    }
    return 0;
}

int main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);read(m);
    rep(i,1,n){
        scanf("%s",s+1);
        rep(j,1,m-1) vis1[i][j]=(s[j]=='1');
    }
    rep(i,1,n-1){
        scanf("%s",s+1);
        rep(j,1,m) vis2[i][j]=(s[j]=='1');
    }
    rep(i,1,n) vis1[i][0]=vis1[i][m]=1;
    rep(i,1,m) vis2[0][i]=vis2[n][i]=1;
    rep(i,1,n)rep(j,1,m){
        if(!vis2[i-1][j]&&!vis1[i][j]) Add(ID(i-1,j,1),ID(i,j,0));
        if(!vis1[i][j]&&!vis2[i][j]) Add(ID(i,j,0),ID(i,j,1));
        if(!vis1[i][j-1]&&!vis2[i][j]) Add(ID(i,j-1,0),ID(i,j,1));
        if(!vis1[i][j-1]&&!vis2[i-1][j]) Add(ID(i,j-1,0),ID(i-1,j,1));
    }
    rep(i,1,n)rep(j,1,m){
        if(!c[ID(i,j,0)]) dfs(ID(i,j,0),1);if(!c[ID(i,j,1)]) dfs(ID(i,j,1),1);
    }
    int Ans=0;
    for(int x:L){
        memset(vis,0,sizeof(vis));
        if(Dfs(x)) Ans++;
    }
    printf("%d\n",Ans);
    return 0;
}