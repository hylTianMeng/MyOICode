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
#define N 400010
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
const int gg=3;
const int mod=998244353;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

int n,g[N],tr[N],F[N],G[N],H[N],f[N];

inline int ksm(int a,int b,int mod){int res=1;while(b){if(b&1)res=1ll*a*res%mod;a=1ll*a*a%mod;b>>=1;}return res;}
inline int inv(int a){return ksm(a,mod-2,mod);}
inline void Gettr(int n){
    for(int i=0;i<n;i++) tr[i]=(tr[i>>1]>>1)|((i&1)?(n>>1):0);
}
inline void NTT(int *f,int n,int op){
    rep(i,0,n-1) if(i<tr[i]) swap(f[i],f[tr[i]]);
    for(int i=2;i<=n;i<<=1){
        int x=ksm(gg,(mod-1)/i,mod),l=i>>1;if(op==0) x=inv(x);
        for(int j=0;j<n;j+=i){
            int now=1;
            for(int k=j;k<j+l;k++){
                int tt=1ll*now*f[k+l]%mod;
                f[k+l]=(f[k]-tt)%mod;f[k]=(f[k]+tt)%mod;
                now=1ll*now*x%mod;
            }
        }
    }
    if(op==0){
        int invn=inv(n);rep(i,0,n-1) f[i]=1ll*f[i]*invn%mod;
    }
}
inline void Solve(int l,int r){
    if(l==r){if(l==0)f[0]=1;return;}
    int mid=(l+r)>>1,len=r-l+1;
    Solve(l,mid);rep(i,0,len-1) F[i]=G[i]=0;
    rep(i,0,mid-l) F[i]=f[i+l];
    rep(i,0,len-1) G[i]=g[i];
    // printf("l=%d r=%d\n",l,r);
    // rep(i,0,len-1) printf("F[%d]=%d\n",i,F[i]);
    // rep(i,0,len-1) printf("G[%d]=%d\n",i,G[i]);
    int nl=1;while(nl<len*2){nl<<=1;}Gettr(nl);
    rep(i,mid-l+1,nl-1) F[i]=0;rep(i,len,nl-1) G[i]=0;
    NTT(F,nl,1);NTT(G,nl,1);
    // rep(i,0,len-1) printf("F[%d]=%d\n",i,F[i]);
    // rep(i,0,len-1) printf("G[%d]=%d\n",i,G[i]);
    rep(i,0,nl-1) F[i]=1ll*F[i]*G[i]%mod;
    NTT(F,nl,0);rep(i,mid+1-l,r-l) (f[i+l]+=F[i])%=mod;
    // rep(i,mid+1,r-l) printf("F[%d]=%d\n",i,F[i]);
    Solve(mid+1,r);
}

int main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);rep(i,1,n-1) read(g[i]);
    Solve(0,n-1);
    rep(i,0,n-1) printf("%d ",(f[i]+mod)%mod);
    return 0;
}