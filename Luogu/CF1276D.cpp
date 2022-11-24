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
const int mod=998244353;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

int n,f[N][4],pre[N],suf[N];
vc<P> e[N];

inline void dfs(int k,int fa){
    for(P to:e[k])if(to.se!=fa){dfs(to.se,k);}
    rep(i,0,(int)e[k].size()-1) pre[i]=suf[i]=0;
    int id=-1;rep(i,0,(int)e[k].size()-1)if(e[k][i].se==fa){id=i;break;}
    int faid=e[k][id].fi;
    e[k].erase(e[k].begin()+id);
    if(e[k].size()==0){
        f[k][0]=1;f[k][2]=1;return;
    }
    rep(i,0,(int)e[k].size()-1){
        if(i==0) pre[i]=(f[e[k][i].se][1]+f[e[k][i].se][2])%mod;
        else pre[i]=1ll*pre[i-1]*((f[e[k][i].se][1]+f[e[k][i].se][2])%mod)%mod;
    }
    suf[e[k].size()]=1;
    dec(i,0,(int)e[k].size()-1){
        suf[i]=1ll*suf[i+1]*((f[e[k][i].se][0]+f[e[k][i].se][1]+f[e[k][i].se][3])%mod)%mod;
    }
    rep(i,0,(int)e[k].size()-1){
        int nowans=1;
        if(i!=0) nowans=nowans*pre[i-1]%mod;
        if(i!=(int)e[k].size()-1) nowans=nowans*suf[i+1]%mod;
        nowans=nowans*(f[e[k][i].se][0]+f[e[k][i].se][3])%mod;
        if(e[k][i].fi<faid){
            f[k][1]=(f[k][1]+nowans)%mod;
        }
        else{
            f[k][3]=(f[k][3]+nowans)%mod;
        }
    }
    f[k][0]=pre[(int)e[k].size()-1];
    f[k][2]=1;
    rep(i,0,(int)e[k].size()-1){
        if(e[k][i].fi<faid){
            f[k][2]=f[k][2]*(f[e[k][i].se][1]+f[e[k][i].se][2])%mod;
        }
        else{
            f[k][2]=f[k][2]*(f[e[k][i].se][0]+f[e[k][i].se][1]+f[e[k][i].se][3])%mod;
        }
    }
    // rep(i,0,3) printf("f[%d][%d]=%d\n",k,i,f[k][i]);
    return;
}

signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);
    rep(i,1,n-1){
        int u,v;read(u);read(v);e[u].pb(mp(i,v));e[v].pb(mp(i,u));
    }
    e[1].pb(mp(0,0));
    rep(i,1,n) sort(e[i].begin(),e[i].end());
    dfs(1,0);
    int ans=0;
    ans=(f[1][0]+f[1][1]+f[1][3])%mod;
    printf("%lld\n",ans);
    return 0;
}