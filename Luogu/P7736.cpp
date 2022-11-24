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
#define N 1010
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

inline int ksm(int a,int b,int mod){
    int res=1;while(b){if(b&1){res=1ll*res*a%mod;}a=1ll*a*a%mod;b>>=1;}return res;
}
inline int inv(int x){return ksm(x,mod-2,mod);}

struct Matrix{
    int n,m,a[N][N];
    inline void Clear(){mset(a,0);n=m=0;}
    inline Matrix operator * (const Matrix &b)const{
        assert(m==b.n);
        Matrix c;c.Clear();c.n=n;c.m=b.m;
        rep(i,1,c.n)rep(j,1,c.m)rep(k,1,m){
            c.a[i][j]=(c.a[i][j]+a[i][k]*b.a[k][j]%mod)%mod;
        }
        return c;
    }
    inline void Print(){
        rep(i,1,n){
            rep(j,1,m) printf("%d ",a[i][j]);
            puts("");
        }puts("");
    }
    inline int Det(){
        assert(n==m);
        int x=1;
        rep(i,1,n){
            if(!a[i][i]){
                rep(j,i+1,n) if(a[j][i]){
                    rep(k,1,n) swap(a[j][k],a[i][k]);
                    x*=-1;break;
                }
            }
            if(!a[i][i]) return 0;
            int nowinv=inv(a[i][i]);
            rep(j,i+1,n){
                int K=a[j][i]*nowinv%mod;
                rep(k,1,n) a[j][k]=((a[j][k]-K*a[i][k]%mod)%mod+mod)%mod;
            }
        }
        // (*this).Print();
        int ans=1;
        rep(i,1,n) ans=ans*a[i][i]%mod;return (ans*x%mod+mod)%mod;
    }
};

int t,n[N],m[N],K;

signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(t);
    while(t--){
        read(K);
        rep(i,1,K) read(n[i]);rep(i,1,K-1) read(m[i]);
        Matrix A;A.Clear();A.n=n[1];A.m=n[1];rep(i,1,A.n) A.a[i][i]=1;
        rep(i,1,K-1){
            Matrix B;B.Clear();
            rep(j,1,m[i]){
                int u,v;read(u);read(v);
                B.a[u][v]=1;
            }
            B.n=n[i];B.m=n[i+1];
            // B.Print();
            A=A*B;
            // A.Print();
        }
        printf("%lld\n",A.Det());
    }
    return 0;
}