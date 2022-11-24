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
#define N 300010
#define M 20
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
const int base=998244353;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

int G[N][M],g[M][N],n,cou[N],tmp[N],F[N],ans[N];
char s[M];
bool K[M][M];
map<ll,ll> Hash;

inline void FWTor(int *f,int op,int n){
    for(int i=2;i<=n;i<<=1)
        for(int j=0;j<n;j+=i)
            for(int k=j;k<j+(i/2);k++){
                if(op){
                    f[k+i/2]+=f[k];
                }
                else f[k+i/2]-=f[k];
            }
}
inline void FWTand(int *f,int op,int n){
    for(int i=2;i<=n;i<<=1)
        for(int j=0;j<n;j+=i)
            for(int k=j;k<j+i/2;k++){
                if(op) f[k]+=f[k+i/2];
                else f[k]-=f[k+i/2];
            }
}
vi now;
inline void dfs(int sum,int lst){
    if(!sum){
        rep(i,0,(1<<n)-1) tmp[i]=1;
        for(int x:now)rep(i,0,(1<<n)-1) tmp[i]*=g[x][i];
        int S=(1<<n)-1,ans=0;
        for(int T=S;T;T=S&(T-1)){
            if((cou[S]-cou[T])&1) ans-=tmp[T];
            else ans+=tmp[T]; 
        }
        int ha=0;
        for(int x:now) ha=(ha*base%mod+x)%mod;Hash[ha]=ans;
        // for(int x:now) printf("%lld ",x);printf("ha=%lld\n",ha);
        // printf("Hash[%lld]=%lld\n",ha,ans);
        return;
    }
    for(int i=lst;i<=sum/2;i++){
        now.pb(i);dfs(sum-i,i);now.pop_back();
    }
    now.pb(sum);dfs(0,sum);now.pop_back();
}

signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);
    rep(i,0,n-1){
        scanf("%s",s);
        rep(j,0,n-1) K[i][j]=(s[j]=='1');
    }
    rep(i,0,n-1) G[1<<i][i]=1;
    rep(i,0,(1<<n)-1)rep(j,0,n-1)if(G[i][j]){
        rep(k,0,n-1) if(K[j][k]&&!((i>>k)&1)) G[i|(1<<k)][k]+=G[i][j];
    }
    rep(i,0,(1<<n)-1) cou[i]=cou[i>>1]+(i&1);
    // rep(i,0,(1<<n)-1) rep(j,0,n-1) printf("G[%d][%d]=%d\n",i,j,G[i][j]);
    rep(i,0,(1<<n)-1) rep(j,0,n-1) g[cou[i]][i]+=G[i][j];
    // rep(i,0,(1<<n)-1) printf("g[%d][%d]=%d\n",cou[i],i,g[cou[i]][i]);
    // rep(i,0,n){printf("i=%d ",i);rep(j,0,(1<<n)-1) printf("%d ",g[i][j]);puts("");}
    rep(i,0,n){
        // printf("i=%d\n",i);
        FWTor(g[i],1,(1<<n)); 
    }
    // rep(i,0,n){printf("i=%d ",i);rep(j,0,(1<<n)-1) printf("%d ",g[i][j]);puts("");}
    dfs(n,1);
    rep(i,0,(1<<(n-1))-1){
        // printf("i=%d\n",i);
        int l=0,r=0;
        vi now;now.clear();
        while(l<=n-1){
            r=l;while(r<=(n-2)&&(i>>r)&1) r++;
            now.pb(r-l+1);l=r+1;
        }
        sort(now.begin(),now.end());
        // for(int x:now) printf("%d ",x);puts("");
        int ha=0;
        for(int x:now) ha=(ha*base%mod+x)%mod;
        F[i]=Hash[ha];
    }
    FWTand(F,0,(1<<(n-1)));
    rep(i,0,(1<<(n-1))-1) printf("%lld ",F[i]);
    return 0;
}