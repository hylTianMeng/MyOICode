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

int t,n,K,s[N],c[N],sh[N],f[N],ans;
vi e[N];
bool vis[N];

inline void dfs2(int k){
    // printf("now k=%lld\n",k);
    if(e[k].size()==0) return;
    int now=c[k]/e[k].size(),yu=c[k]%e[k].size();
    vi v;v.clear();
    for(int to:e[k]){
        c[to]+=now;v.pb(to);
    }
    sh[k]=yu;
    for(int to:e[k]){
        dfs2(to);
    }
}
inline void dfs(int k){
    if(e[k].size()==0){
        f[k]=s[k];return;
    }
    for(int to:e[k]){
        dfs(to);
    }
    vi v;v.clear();
    for(int to:e[k]) v.pb(to);
    sort(v.begin(),v.end(),[&](int i,int j){return f[i]>f[j];});
    rep(i,0,sh[k]-1){
        ans+=f[v[i]];
    }
    f[k]=f[v[sh[k]]]+s[k];
}

signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(t);
    while(t--){
        read(n);read(K);
        rep(i,1,n) e[i].clear();
        rep(i,1,n) c[i]=0;
        rep(i,1,n) vis[i]=0;
        ans=0;
        rep(i,2,n){
            int x;read(x);e[x].pb(i);
        }
        rep(i,1,n) read(s[i]);
        c[1]=K;
        dfs2(1);
        dfs(1);
        // printf("ans=%d\n",ans);
        rep(i,1,n) ans+=c[i]*s[i];
        printf("%lld\n",ans);
    }
}