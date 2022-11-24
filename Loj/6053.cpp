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
const int Len=100010;
const int mod=1e9+7;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

int pr[N],ta,h[N][2],sumh[N][2],id[N],idtot,n,g[N][2],inv6,inv2,G[N],sumf[N];
bool no[N];
unordered_map<int,int> rk;

inline int ksm(int a,int b,int mod){
    int res=1;while(b){if(b&1)res=1ll*res*a%mod;a=1ll*a*a%mod;b>>=1;}return res;
}
inline int inv(int x){return ksm(x,mod-2,mod);}
inline int f(int p,int k){return pr[p]^k;}
inline void sieve(){
    no[1]=1;
    rep(i,2,Len){
        if(!no[i]) pr[++ta]=i;
        for(int j=1;j<=ta&&1ll*pr[j]*i<=Len;j++){
            no[pr[j]*i]=1;if(i%pr[j]==0) break;
        }
    }
    rep(i,1,ta){
        h[i][0]=pr[i]%mod;sumh[i][0]=(sumh[i-1][0]+h[i][0])%mod;
        h[i][1]=1;sumh[i][1]=(sumh[i-1][1]+h[i][1])%mod;
    }
    rep(i,1,ta){
        sumf[i]=(sumf[i-1]+f(i,1))%mod;
    }
}
inline int SumH(int n,int op){
    n%=mod;
    if(op==0) return n*(n+1)%mod*inv2%mod;
    else return n;
}
inline void Init(){
    sieve();
    for(int l=1,r;l<=n;l=r+1){
        r=n/(n/l);id[++idtot]=n/l;
    }
    reverse(id+1,id+idtot+1);
    rep(i,1,idtot) rk[id[i]]=i;
    inv6=inv(6);inv2=inv(2);
}
inline void GetG(int op){
    rep(i,1,idtot) g[i][op]=SumH(id[i],op)-1;
    rep(i,1,ta){
        dec(j,1,idtot){
            if(pr[i]*pr[i]>id[j]) break;
            // if(pr[i-1]*pr[i-1]>id[j]/pr[i]) break;
            g[j][op]=((g[j][op]-g[rk[id[j]/pr[i]]][op]*h[i][op]%mod+sumh[i-1][op]*h[i][op]%mod)%mod+mod)%mod;
        }
    }
}
inline int dfs(int i,int j){
    if(i>ta) return 0;
    if(pr[i]>id[j]) return 0;
    int ans=((G[j]-sumf[i-1])%mod+mod)%mod;
    for(int k=i;k<=ta&&pr[k]*pr[k]<=id[j];k++){
        int now=pr[k];
        for(int e=1;now<=id[j]/pr[k];e++,now*=pr[k]){
            ans=((ans+f(k,e+1))%mod+dfs(k+1,rk[id[j]/(now)])*f(k,e)%mod)%mod;
        }
    }
    return ans;
}
inline int GetF(){return dfs(1,idtot);}

signed main(){
    // freopen("my.in","r",stdin);
    // freopen("std.out","w",stdout);
    read(n);Init();GetG(0);GetG(1);
    rep(i,1,idtot) G[i]=((g[i][0]-g[i][1])%mod+mod)%mod;
    rep(i,2,idtot) G[i]=(G[i]+2)%mod;
    // rep(i,1,idtot) printf("G[%d]=%d\n",i,G[i]);
    int Ans=GetF();
    printf("%lld\n",((Ans+1)%mod+mod)%mod);
    return 0;
}