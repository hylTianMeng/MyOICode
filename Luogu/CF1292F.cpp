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
#define N 63
#define M 200010
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

int n,a[N],id[N],rd[N],ans,jie[N],invjie[N];
vi e[N],v,S,T;
int ts[N],cnt[M],f[M][N],sum;
bool vis[N];

inline int ksm(int a,int b,int mod){
    int res=1;while(b){if(b&1)res=1ll*res*a%mod;a=1ll*a*a%mod;b>>=1;}return res;
}
inline int inv(int a){return ksm(a,mod-2,mod);}

inline void dfs(int k){
    vis[k]=1;v.pb(k);
    for(int to:e[k])if(!vis[to]){
        // printf("k=%d to=%d\n",k,to);
        dfs(to);
    }
}
inline int DP(){
    for(int x:v){
        // printf("x=%d ",x);
        if(!id[x]) S.pb(a[x]);else T.pb(a[x]);
    }
    // puts("");
    if(T.empty()){
        S.clear();return -1;
    }
    rep(i,0,(int)T.size()-1){
        int nows=0;
        rep(j,0,(int)S.size()-1){
            // printf("T[%d]=%d S[%d]=%d\n",i,T[i],j,S[j]);
            if(T[i]%S[j]==0) nows|=(1<<j);
        }
        cnt[nows]++;ts[i]=nows;
        // printf("ts[%d]=%d\n",i,nows);
    }
    rep(i,0,(int)S.size()-1){
        rep(j,0,(1<<((int)S.size()))-1){
            if((j>>i)&1) cnt[j]+=cnt[j^(1<<i)];
        }
    }
    // printf("cnt[1]=%d\n",cnt[1]);
    rep(i,0,(int)T.size()-1){
        f[ts[i]][1]++;
    }
    rep(i,1,(int)T.size()-1)rep(j,0,(1<<((int)S.size()))-1)if(f[j][i]){
        bool op=0;
        rep(k,0,(int)T.size()-1){
            if((ts[k]&j)==0) continue;
            if((ts[k]&j)==ts[k]){
                if(op) continue;
                else{
                    // puts("");
                    f[j][i+1]=(f[j][i+1]+f[j][i]*(cnt[j]-i)%mod)%mod;op=1;
                }
            }
            else f[j|ts[k]][i+1]=(f[j|ts[k]][i+1]+f[j][i])%mod;
        }
    }
    int ans=f[(1<<((int)S.size()))-1][T.size()];
    rep(i,0,(1<<((int)S.size()))-1)rep(j,1,T.size()) f[i][j]=0,cnt[i]=0,ts[j-1]=0;
    sum+=T.size()-1;ans=ans*invjie[T.size()-1]%mod;
    S.clear();T.clear();
    return ans;
}

signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);rep(i,1,n) read(a[i]);
    jie[0]=1;rep(i,1,n) jie[i]=1ll*jie[i-1]*i%mod;
    invjie[n]=inv(jie[n]);dec(i,0,n-1) invjie[i]=invjie[i+1]*(i+1)%mod;
    rep(i,1,n)rep(j,1,n){
        if(i==j) continue;
        if(a[j]%a[i]==0){
            // printf("%d %d\n",i,j);
            e[i].pb(j);id[j]++;rd[i]++;e[j].pb(i);
        }
    }
    ans=1;sum=0;
    // printf("ans=%d\n",ans);
    rep(i,1,n)if(!vis[i]){
        v.clear();dfs(i);
        int nowans=DP();
        if(nowans==-1) continue;
        ans=ans*nowans%mod;
        // printf("nowans=%d\n",nowans);
    }
    ans=ans*jie[sum]%mod;
    printf("%d\n",ans);
    return 0;
}