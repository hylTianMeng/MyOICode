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
#define N 10
#define M 23
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
const int mod=998244353;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

int n,m,x[N],y[N],f[31][M][M][M][M][2][2];

inline int ge(int a,int b,int c){
    if(a!=b) return (a<b)?0:1;return c;
}
inline int dfs(int p,int px,int py,int nx,int ny,int limx,int limy){
    if(p==30) return (!px&&!py&&!nx&&!ny&&!limx&&!limy);
    int &val=f[p][px][py][nx][ny][limx][limy];if(val!=-1) return val;
    val=0;int dm=(m>>p)&1;
    rep(i,0,(1<<n)-1){
        int npx=px,npy=py,nnx=nx,nny=ny;
        rep(j,0,n-1){
            if((i>>j)&1){
                (x[j]>0)?npx+=x[j]:nnx-=x[j];
                (y[j]>0)?npy+=y[j]:nny-=y[j];
            }
        }
        int dnpx=npx&1,dnpy=npy&1,dnnx=nnx&1,dnny=nny&1;
        if(dnpx==dnnx&&dnpy==dnny){
            val=(val+dfs(p+1,npx>>1,npy>>1,nnx>>1,nny>>1,ge(dnpx,dm,limx),ge(dnpy,dm,limy)))%mod;
        }
    }
    return val;
}

int main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);read(m);rep(i,0,n-1) read(x[i]),read(y[i]);
    mset(f,-1);
    int ans=dfs(0,0,0,0,0,0,0)-1;
    printf("%d\n",(ans+mod)%mod);
    return 0;
}