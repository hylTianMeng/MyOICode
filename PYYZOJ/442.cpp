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
#define int long long
typedef pair<int,int> P;
typedef vector<int> vi;

const int INF=0x3f3f3f3f;
const int mod=998244353;
const int g=3;
const dd eps=1e-9;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

int tr[N],n,invg;
int G[N],G1[N],G2[N],jie[N],invjie[N],f[N],c[N];

inline int ksm(int a,int b,int mod){
    b%=(mod-1);int res=1;while(b){if(b&1){res=1ll*res*a%mod;}a=1ll*a*a%mod;b>>=1;}return res;
}
inline int inv(int a){return ksm(a,mod-2,mod);}
inline void Gettr(int len){for(int i=0;i<len;i++) tr[i]=(tr[i>>1]>>1)|((i&1)?(len>>1):0);}
inline void Clear(int *a,int len){for(int i=0;i<len;i++) a[i]=0;}
inline int C(int n,int m){return jie[n]*invjie[n-m]%mod*invjie[m]%mod;}
inline void NTT(int *f,int len,int flag){
    for(int i=0;i<len;i++) if(i<tr[i]) swap(f[i],f[tr[i]]);
    for(int i=2;i<=len;i<<=1){
        int tg=ksm(g,(mod-1)/i,mod),l=i>>1;
        if(flag!=1) tg=ksm(tg,mod-2,mod);
        for(int j=0;j<len;j+=i){
            int buf=1;
            for(int k=j;k<j+l;k++){
                int tt=1ll*buf*f[k+l]%mod;
                f[k+l]=((f[k]-tt)%mod+mod)%mod;
                f[k]=(f[k]+tt)%mod;buf=1ll*buf*tg%mod;
            }
        }
    }
    if(flag==1) return;
    int invn=ksm(len,mod-2,mod);for(int i=0;i<len;i++) f[i]=1ll*f[i]*invn%mod;
}
inline void GetInv(int len,const int *a,int *b){
    if(len==1){b[0]=ksm(a[0],mod-2,mod);return;}
    GetInv((len+1)>>1,a,b);int m=1;while(m<(len<<1)) m<<=1;Gettr(m);
    for(int i=0;i<len;i++) c[i]=a[i];for(int i=len;i<m;i++) c[i]=0;
    NTT(c,m,1);NTT(b,m,1);
    for(int i=0;i<m;i++) b[i]=1ll*(2-1ll*c[i]*b[i]%mod+mod)%mod*b[i]%mod;
    NTT(b,m,-1);for(int i=len;i<m;i++) b[i]=0;Clear(c,m);
}//c is not clear

signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);invg=inv(g);n++;
    jie[0]=1;rep(i,1,n) jie[i]=jie[i-1]*i%mod;invjie[n]=inv(jie[n]);
    dec(i,0,n-1) invjie[i]=invjie[i+1]*(i+1)%mod;
    rep(i,0,n-1) G[i]=ksm(2,i*(i-1)/2,mod)*invjie[i]%mod;
    rep(i,0,n-1) G1[i]=G[i];rep(i,0,n-1) G2[i]=G[i]*i%mod;
    int len=1;while(len<=(n*2)) len<<=1;
    Gettr(len);
    NTT(G,len,1);NTT(G1,len,1);NTT(G2,len,1);
    rep(i,0,len-1) G1[i]=G1[i]*G[i]%mod;rep(i,0,len-1) G2[i]=G2[i]*G[i]%mod;
    NTT(G1,len,0);NTT(G2,len,0);NTT(G,len,0);
    // printf("G: ");rep(i,0,len-1) printf("%d ",G[i]);puts("");  
    GetInv(n,G,f);
    // printf("G: ");rep(i,0,len-1) printf("%d ",G[i]);puts(""); 
    rep(i,0,len-1) f[i]=-f[i];f[0]++;
    rep(i,0,len-1) f[i]=f[i]*jie[i]%mod;
    // printf("f: ");rep(i,0,len-1) printf("%d ",(f[i]+mod)%mod);puts("");
    int Ans=0;
    // printf("G1: ");rep(i,0,len-1) printf("%d ",G1[i]);puts("");
    // printf("G2: ");rep(i,0,len-1) printf("%d ",G2[i]);puts("");
    rep(i,1,n-1) Ans=(Ans+f[i]*jie[n-2]%mod*invjie[i-1]%mod*((i*G1[n-i-1]%mod+G2[n-i-1])%mod))%mod;
    printf("%lld\n",(Ans+mod)%mod);
    return 0;
}