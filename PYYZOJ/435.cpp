#include<bits/stdc++.h>
#define mset(a,b) memset((a),(b),sizeof((a)))
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
#define dec(i,l,r) for(int i=(r);i>=(l);i--)
#define inc(a,b) (((a)+(b))>=mod?(a)+(b)-mod:(a)+(b))
#define sub(a,b) (((a)-(b))<0?(a)-(b)+mod:(a)-(b))
#define mul(a,b) 1ll*(a)*(b)%mod
#define sgn(a) (((a)&1)?(mod-1):1)
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
#define N 3010
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

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

int f[N][N<<1],a[N],g[N][N],n;

int main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);rep(i,1,n) read(a[i]);
    rep(i,3,n)dec(j,1,i-2) g[j][i]=g[j+1][i]+(j+1+a[j+1]>=i);
    // rep(i,3,n)rep(j,1,i-2) printf("g[%d][%d]=%d\n",j,i,g[j][i]);
    mset(f,INF);rep(k,1,n<<1) f[1][k]=0; 
    rep(j,1,n){
        rep(i,0,n<<1) cmin(f[j][i],f[j][i-1]);
        rep(i,j,n-1) if(j+a[j]>=i+1){
            // printf("Before f[%d][%d]=%d\n",i+1,j+a[j],f[i+1][j+a[j]]);
            cmin(f[i+1][j+a[j]],f[j][i]+g[j][i+1]);
            // printf("Update f[%d][%d]=%d\n",i+1,j+a[j],f[i+1][j+a[j]]);
        }
    }
    // rep(i,1,n)rep(j,1,(n<<1)) printf("f[%d][%d]=%d\n",i,j,f[i][j]);
    int ans=INF;
    rep(i,n,n<<1) cmin(ans,f[n][i]);
    printf("%d\n",ans);
    return 0;
}