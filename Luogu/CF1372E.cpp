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
#define N 110
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

int n,m,f[N][N],g[N][N][N],L[N][N],R[N][N],b[N];
vi v[N];

inline int F(int x){return x*x;}

signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);read(m);
    rep(i,1,n){
        int K;read(K);
        rep(j,1,K){
            int l,r;read(l);read(r);v[r].pb(l);
        }
    }
    rep(i,1,m){
        mset(b,0);
        rep(j,1,m){
            for(int x:v[j]) if(x>=i){
                rep(k,x,j) b[k]++;
            }
            int ans=-INF;
            rep(k,i,j) g[i][j][k]=b[k];
        }
    }
    // rep(i,1,m)rep(j,i,m)rep(k,i,j) printf("g[%lld][%lld][%lld]=%lld\n",i,j,k,g[i][j][k]);
    rep(i,1,m) f[i][i]=F(g[i][i][i]);
    rep(i,2,m){
        rep(j,1,m-i+1){
            int l=j,r=j+i-1;
            rep(k,l,r)cmax(f[l][r],f[l][k-1]+f[k+1][r]+F(g[l][r][k]));
        }
    }
    printf("%lld\n",f[1][m]);
    return 0;
}