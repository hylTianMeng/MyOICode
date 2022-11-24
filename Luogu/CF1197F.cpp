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
#define N 65
#define M 1010
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

struct Matrix{
    int a[N][N],n,m;
    inline void Clear(){mset(a,0);n=m=0;}
    inline Matrix operator + (const Matrix &b)const{
        Matrix c;c.Clear();c.n=n;c.m=m;
        assert(n==b.n&&m==b.m);rep(i,1,n)rep(j,1,m){
            c.a[i][j]=(a[i][j]+b.a[i][j])%mod;
        }return c;
    }
    inline Matrix operator * (const Matrix &b)const{
        // printf("n=%d m=%d b.n=%d b.m=%d\n",n,m,b.n,b.m);
        Matrix c;c.Clear();c.n=n;c.m=b.m;assert(m==b.n);
        rep(i,1,c.n)rep(j,1,c.m)rep(k,1,m){
            c.a[i][j]=(c.a[i][j]+a[i][k]*b.a[k][j]%mod)%mod;
        }return c;
    }
    inline void Print(){
        printf("n=%d m=%d\n",n,m);
        rep(i,1,n){
            rep(j,1,m) printf("%d ",a[i][j]);puts("");
        }puts("");
    }
}pw[31],col[4];

int f[4][4],n,a[M],m,ff[10],g[10],h[10];
vc<P> v[M];

inline int trans(int co,int s){
    rep(i,0,3){
        if((!f[co][3]||((s&3)^i))&&(!f[co][2]||(((s>>2)&3)^i))&&(!f[co][1]||(((s>>4)&3)^i))) return s>>2|i<<4;
    }
    assert(0);
}

signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);rep(i,1,n) read(a[i]);read(m);
    rep(i,1,m){
        int xi,yi,ci;read(xi);read(yi);read(ci);
        v[xi].pb(mp(yi,ci));
    }
    rep(i,1,n) sort(v[i].begin(),v[i].end());
    rep(i,1,3)rep(j,1,3) read(f[i][j]);
    rep(i,1,64){
        int now=i-1;
        rep(j,1,3){
            int tr=trans(j,now);tr++;
            col[j].a[i][tr]++;
            pw[0].a[i][tr]++;
        }
    }

    rep(j,1,3) col[j].n=col[j].m=64;pw[0].n=pw[0].m=64;
    // rep(j,1,3){
        // printf("col[%d]:\n",j);
    //     col[j].Print();
    // }
    // exit(0);
    rep(i,1,30){
        pw[i]=pw[i-1]*pw[i-1];
        // printf("pw[%d]:\n",i);pw[i].Print();("");
    }
    // exit(0);
    ff[0]=1;
    rep(i,1,n){
        // printf("i=%d\n",i);
        Matrix now;now.Clear();now.n=1;now.m=64;
        now.a[1][64]++;int last=0;
        // now.Print();
        for(P x:v[i]){
            int len=x.fi-last-1;
            // printf("len=%d\n",len);
            dec(j,0,30) if((len>>j)&1) now=now*pw[j];
            // now.Print();
            now=now*col[x.se];
            last=x.fi;
            // now.Print();
        }
        int len=a[i]-last;
        dec(j,0,30) if((len>>j)&1) now=now*pw[j];
        // now.Print();
        rep(j,0,3) h[j]=g[j]=0;
        rep(j,1,64) (g[(j-1)>>4]+=now.a[1][j])%=mod;
        // rep(j,0,3) printf("g[%d]=%d\n",j,g[j]);
        rep(j,0,3)rep(k,0,3) h[k^j]=(h[k^j]+ff[j]*g[k]%mod)%mod;
        rep(j,0,3) ff[j]=h[j];
    }
    printf("%lld\n",ff[0]);
    return 0;
}

