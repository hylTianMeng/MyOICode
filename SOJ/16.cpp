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
const int mod=1e9+7;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

int n,p[N],cnt,f[N][N],jie[N],invjie[N],PreMax[N],SufMin[N],Cnt[N][N];

inline int ksm(int a,int b,int mod){
    int res=1;while(b){if(b&1)res=1ll*res*a%mod;a=1ll*a*a%mod;b>>=1;}return res;
}
inline int inv(int x){return ksm(x,mod-2,mod);}
inline int C(int n,int m){
    return jie[n]*invjie[m]%mod*invjie[n-m]%mod;
}
inline int dfs(int l,int r){
    if(l==r) return 1;
    if(f[l][r]!=-1) return f[l][r];
    rep(i,l-1,r+1) PreMax[i]=-INF,SufMin[i]=INF;
    rep(i,l,r-1){
        PreMax[i]=max(PreMax[i-1],p[i]);
    }
    dec(i,l,r){
        SufMin[i]=min(SufMin[i+1],p[i]);
    }
    int ans=0;
    rep(k,l,r-1){
        swap(p[k],p[k+1]);
        if(max(PreMax[k-1],p[k])<min(SufMin[k+2],p[k+1])){
            int ans1=dfs(l,k);
            int ans2=dfs(k+1,r);
            int c1=Cnt[l][k];
            int c2=Cnt[k+1][r];
            ans=(ans+ans1*ans2%mod*C(r-l-1,k-l))%mod;
        }
        swap(p[k],p[k+1]);
    }
    // printf("l=%lld r=%lld ans=%lld\n",l,r,ans);
    f[l][r]=ans;
    return ans;
}

signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);rep(i,1,n) read(p[i]);
    rep(i,1,n)rep(j,i+1,n) if(p[i]>p[j]) cnt++;
    if(cnt!=n-1){puts("0");return 0;}
    jie[0]=1;rep(i,1,n) jie[i]=jie[i-1]*i%mod;
    invjie[n]=inv(jie[n]);dec(i,0,n-1) invjie[i]=invjie[i+1]*(i+1)%mod;
    rep(i,1,n)rep(j,i,n){
        rep(k,i,j)rep(k2,k+1,j){
            if(p[k]>p[k2]) Cnt[i][j]++;
        }
    }
    mset(f,-1);
    dfs(1,n);
    printf("%lld\n",f[1][n]);
    return 0;
}