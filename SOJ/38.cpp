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
#define N 510
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

int n,K,x[N],y[N],f[N][N];

inline int Calc(int i,int j){
    return abs(x[i]-x[j])+abs(y[i]-y[j]);
}

signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);read(K);
    rep(i,1,n){
        read(x[i]);read(y[i]);
    }
    mset(f,INF);
    f[1][0]=0;
    rep(i,1,n-1)rep(j,0,K)if(f[i][j]!=INF){
        rep(k,0,K-j){
            if(i+k+1>n) break;
            int &now=f[i+k+1][j+k];
            now=cmin(now,f[i][j]+Calc(i+k+1,i));
        }
    }
    int ans=f[n][K];
    printf("%lld\n",ans);
    return 0;
}